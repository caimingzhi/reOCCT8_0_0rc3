#define No_Standard_RangeError
#define No_Standard_OutOfRange
#define No_Standard_DimensionError

#include <math_Gauss.hpp>
#include <math_Jacobi.hpp>
#include <math_MultipleVarFunctionWithHessian.hpp>
#include <math_NewtonMinimum.hpp>
#include <Precision.hpp>
#include <StdFail_NotDone.hpp>

math_NewtonMinimum::math_NewtonMinimum(const math_MultipleVarFunctionWithHessian& theFunction,
                                       const double                               theTolerance,
                                       const int                                  theNbIterations,
                                       const double                               theConvexity,
                                       const bool theWithSingularity)
    : TheStatus(math_NotBracketed),
      TheLocation(1, theFunction.NbVariables()),
      TheGradient(1, theFunction.NbVariables()),
      TheStep(1, theFunction.NbVariables(), 10.0 * theTolerance),
      TheHessian(1, theFunction.NbVariables(), 1, theFunction.NbVariables()),
      PreviousMinimum(0.0),
      TheMinimum(0.0),
      MinEigenValue(0.0),
      XTol(theTolerance),
      CTol(theConvexity),
      nbiter(0),
      NoConvexTreatement(theWithSingularity),
      Convex(true),
      myIsBoundsDefined(false),
      myLeft(1, theFunction.NbVariables(), 0.0),
      myRight(1, theFunction.NbVariables(), 0.0),
      Done(false),
      Itermax(theNbIterations)
{
}

math_NewtonMinimum::~math_NewtonMinimum() = default;

void math_NewtonMinimum::SetBoundary(const math_Vector& theLeftBorder,
                                     const math_Vector& theRightBorder)
{
  myLeft            = theLeftBorder;
  myRight           = theRightBorder;
  myIsBoundsDefined = true;
}

void math_NewtonMinimum::Perform(math_MultipleVarFunctionWithHessian& F,
                                 const math_Vector&                   StartingPoint)
{
  math_Vector Point1(1, F.NbVariables());
  Point1 = StartingPoint;
  math_Vector  Point2(1, F.NbVariables());
  math_Vector* precedent = &Point1;
  math_Vector* suivant   = &Point2;

  bool   Ok     = true;
  int    NbConv = 0, ii, Nreduction;
  double VPrecedent, VItere;

  Done      = true;
  TheStatus = math_OK;
  nbiter    = 0;

  while (Ok && (NbConv < 2))
  {
    nbiter++;

    Ok = F.Values(*precedent, VPrecedent, TheGradient, TheHessian);
    if (!Ok)
    {
      Done      = false;
      TheStatus = math_FunctionError;
      return;
    }
    if (nbiter == 1)
    {
      PreviousMinimum = VPrecedent;
      TheMinimum      = VPrecedent;
    }

    math_Jacobi CalculVP(TheHessian);
    if (!CalculVP.IsDone())
    {
      Done      = false;
      TheStatus = math_FunctionError;
      return;
    }

    MinEigenValue = CalculVP.Values()(CalculVP.Values().Min());
    if (MinEigenValue < CTol)
    {
      Convex = false;
      if (NoConvexTreatement && std::abs(MinEigenValue) > CTol)
      {
        double Delta = CTol + 0.1 * std::abs(MinEigenValue) - MinEigenValue;
        for (ii = 1; ii <= TheGradient.Length(); ii++)
          TheHessian(ii, ii) += Delta;
      }
      else
      {
        Done      = false;
        TheStatus = math_FunctionError;
        return;
      }
    }

    math_Gauss LU(TheHessian, CTol / 100);
    if (!LU.IsDone())
    {
      Done      = false;
      TheStatus = math_DirectionSearchError;
      return;
    }
    LU.Solve(TheGradient, TheStep);

    if (myIsBoundsDefined)
    {

      *suivant     = *precedent - TheStep;
      double aMult = RealLast();
      for (int anIdx = 1; anIdx <= myLeft.Upper(); anIdx++)
      {
        const double anAbsStep = std::abs(TheStep(anIdx));
        if (anAbsStep < gp::Resolution())
          continue;

        if (suivant->Value(anIdx) < myLeft(anIdx))
        {
          double aValue = std::abs(precedent->Value(anIdx) - myLeft(anIdx)) / anAbsStep;
          aMult         = std::min(aValue, aMult);
        }

        if (suivant->Value(anIdx) > myRight(anIdx))
        {
          double aValue = std::abs(precedent->Value(anIdx) - myRight(anIdx)) / anAbsStep;
          aMult         = std::min(aValue, aMult);
        }
      }

      if (aMult != RealLast())
      {
        if (aMult > Precision::PConfusion())
        {

          TheStep *= aMult;
        }
        else
        {

          for (int anIdx = 1; anIdx <= myLeft.Upper(); anIdx++)
          {
            if ((std::abs(precedent->Value(anIdx) - myRight(anIdx)) < Precision::PConfusion()
                 && TheStep(anIdx) < 0.0)
                || (std::abs(precedent->Value(anIdx) - myLeft(anIdx)) < Precision::PConfusion()
                    && TheStep(anIdx) > 0.0))
            {
              TheStep(anIdx) = 0.0;
            }
          }
        }
      }
    }

    bool hasProblem = false;
    do
    {
      *suivant = *precedent - TheStep;

      hasProblem = !(F.Value(*suivant, TheMinimum));

      if (hasProblem)
      {
        TheStep /= 2.0;
      }
    } while (hasProblem);

    if (IsConverged())
    {
      NbConv++;
    }
    else
    {
      NbConv = 0;
    }

    VItere     = TheMinimum;
    TheMinimum = PreviousMinimum;
    Nreduction = 0;
    while (VItere > VPrecedent && Nreduction < 10)
    {
      TheStep *= 0.4;
      *suivant = *precedent - TheStep;
      F.Value(*suivant, VItere);
      Nreduction++;
    }

    if (VItere <= VPrecedent)
    {
      math_Vector* auxiliaire = precedent;
      precedent               = suivant;
      suivant                 = auxiliaire;
      PreviousMinimum         = VPrecedent;
      TheMinimum              = VItere;
      Ok                      = (nbiter < Itermax);
      if (!Ok && NbConv < 2)
        TheStatus = math_TooManyIterations;
    }
    else
    {
      Ok        = false;
      TheStatus = math_DirectionSearchError;
    }
  }
  TheLocation = *precedent;
}

void math_NewtonMinimum::Dump(Standard_OStream& o) const
{
  o << "math_Newton Optimisation: ";
  o << " Done   =" << Done << std::endl;
  o << " Status = " << (int)TheStatus << std::endl;
  o << " Location Vector = " << Location() << std::endl;
  o << " Minimum value = " << Minimum() << std::endl;
  o << " Previous value = " << PreviousMinimum << std::endl;
  o << " Number of iterations = " << NbIterations() << std::endl;
  o << " Convexity = " << Convex << std::endl;
  o << " Eigen Value = " << MinEigenValue << std::endl;
}

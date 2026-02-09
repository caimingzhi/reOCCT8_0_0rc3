

#include <Convert_EllipseToBSplineCurve.hpp>
#include <gp.hpp>
#include <gp_Ax2d.hpp>
#include <gp_Dir2d.hpp>
#include <gp_Elips2d.hpp>
#include <gp_Trsf2d.hpp>
#include <Precision.hpp>
#include <Standard_DomainError.hpp>
#include <gp_Pnt2d.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

Convert_EllipseToBSplineCurve::Convert_EllipseToBSplineCurve(
  const gp_Elips2d&                  E,
  const Convert_ParameterisationType Parameterisation)
    : Convert_ConicToBSplineCurve(0, 0, 0)
{

  int ii;

  double                                   R, r, value;
  occ::handle<NCollection_HArray1<double>> CosNumeratorPtr, SinNumeratorPtr;

  R = E.MajorRadius();
  r = E.MinorRadius();

  if (Parameterisation != Convert_TgtThetaOver2 && Parameterisation != Convert_RationalC1)
  {

    isperiodic = false;
    Convert_ConicToBSplineCurve::BuildCosAndSin(Parameterisation,
                                                0,
                                                2 * M_PI,
                                                CosNumeratorPtr,
                                                SinNumeratorPtr,
                                                weights,
                                                degree,
                                                knots,
                                                mults);
  }
  else
  {
    isperiodic = true;
    Convert_ConicToBSplineCurve::BuildCosAndSin(Parameterisation,
                                                CosNumeratorPtr,
                                                SinNumeratorPtr,
                                                weights,
                                                degree,
                                                knots,
                                                mults);
  }

  nbPoles = CosNumeratorPtr->Length();
  nbKnots = knots->Length();

  poles = new NCollection_HArray1<gp_Pnt2d>(1, nbPoles);

  gp_Dir2d  Ox = E.XAxis().Direction();
  gp_Dir2d  Oy = E.YAxis().Direction();
  gp_Trsf2d Trsf;
  Trsf.SetTransformation(E.XAxis(), gp::OX2d());
  if (Ox.X() * Oy.Y() - Ox.Y() * Oy.X() > 0.0e0)
  {
    value = r;
  }
  else
  {
    value = -r;
  }

  for (ii = 1; ii <= nbPoles; ii++)
  {
    poles->ChangeArray1()(ii).SetCoord(1, R * CosNumeratorPtr->Value(ii));
    poles->ChangeArray1()(ii).SetCoord(2, value * SinNumeratorPtr->Value(ii));
    poles->ChangeArray1()(ii).Transform(Trsf);
  }
}

Convert_EllipseToBSplineCurve::Convert_EllipseToBSplineCurve(
  const gp_Elips2d&                  E,
  const double                       UFirst,
  const double                       ULast,
  const Convert_ParameterisationType Parameterisation)
    : Convert_ConicToBSplineCurve(0, 0, 0)
{
#ifndef No_Exception
  double Tol   = Precision::PConfusion();
  double delta = ULast - UFirst;
#endif
  Standard_DomainError_Raise_if((delta > (2 * M_PI + Tol)) || (delta <= 0.0e0),
                                "Convert_EllipseToBSplineCurve");
  int                                      ii;
  double                                   R, r, value;
  occ::handle<NCollection_HArray1<double>> CosNumeratorPtr, SinNumeratorPtr;

  R = E.MajorRadius();
  r = E.MinorRadius();

  isperiodic = false;
  Convert_ConicToBSplineCurve::BuildCosAndSin(Parameterisation,
                                              UFirst,
                                              ULast,
                                              CosNumeratorPtr,
                                              SinNumeratorPtr,
                                              weights,
                                              degree,
                                              knots,
                                              mults);

  nbPoles = CosNumeratorPtr->Length();
  nbKnots = knots->Length();

  poles = new NCollection_HArray1<gp_Pnt2d>(1, nbPoles);

  gp_Dir2d  Ox = E.XAxis().Direction();
  gp_Dir2d  Oy = E.YAxis().Direction();
  gp_Trsf2d Trsf;
  Trsf.SetTransformation(E.XAxis(), gp::OX2d());
  if (Ox.X() * Oy.Y() - Ox.Y() * Oy.X() > 0.0e0)
  {
    value = r;
  }
  else
  {
    value = -r;
  }

  for (ii = 1; ii <= nbPoles; ii++)
  {
    poles->ChangeArray1()(ii).SetCoord(1, R * CosNumeratorPtr->Value(ii));
    poles->ChangeArray1()(ii).SetCoord(2, value * SinNumeratorPtr->Value(ii));
    poles->ChangeArray1()(ii).Transform(Trsf);
  }
}

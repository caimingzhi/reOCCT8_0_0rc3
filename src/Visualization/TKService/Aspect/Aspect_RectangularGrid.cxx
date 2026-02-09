

#include <Aspect_RectangularGrid.hpp>

#include <Standard_NegativeValue.hpp>
#include <Standard_NullValue.hpp>
#include <Standard_NumericError.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Aspect_RectangularGrid, Aspect_Grid)

Aspect_RectangularGrid::Aspect_RectangularGrid(const double aXStep,
                                               const double aYStep,
                                               const double anXOrigin,
                                               const double anYOrigin,
                                               const double aFirstAngle,
                                               const double aSecondAngle,
                                               const double aRotationAngle)
    : Aspect_Grid(anXOrigin, anYOrigin, aRotationAngle),
      myXStep(aXStep),
      myYStep(aYStep),
      myFirstAngle(aFirstAngle),
      mySecondAngle(aSecondAngle)

{
  Standard_NumericError_Raise_if(!CheckAngle(aFirstAngle, mySecondAngle), "networks are parallel");

  Standard_NegativeValue_Raise_if(aXStep < 0., "invalid x step");
  Standard_NegativeValue_Raise_if(aYStep < 0., "invalid y step");
  Standard_NullValue_Raise_if(aXStep == 0., "invalid x step");
  Standard_NullValue_Raise_if(aYStep == 0., "invalid y step");
}

void Aspect_RectangularGrid::SetXStep(const double aStep)
{
  Standard_NegativeValue_Raise_if(aStep < 0., "invalid x step");
  Standard_NullValue_Raise_if(aStep == 0., "invalid y step");
  myXStep = aStep;
  Init();
  UpdateDisplay();
}

void Aspect_RectangularGrid::SetYStep(const double aStep)
{
  Standard_NegativeValue_Raise_if(aStep < 0., "invalid x step");
  Standard_NullValue_Raise_if(aStep == 0., "invalid y step");
  myYStep = aStep;
  Init();
  UpdateDisplay();
}

void Aspect_RectangularGrid::SetAngle(const double anAngle1, const double anAngle2)
{
  Standard_NumericError_Raise_if(!CheckAngle(anAngle1, anAngle2), "axis are parallel");
  myFirstAngle  = anAngle1;
  mySecondAngle = anAngle2;
  Init();
  UpdateDisplay();
}

void Aspect_RectangularGrid::SetGridValues(const double theXOrigin,
                                           const double theYOrigin,
                                           const double theXStep,
                                           const double theYStep,
                                           const double theRotationAngle)
{

  myXOrigin = theXOrigin;
  myYOrigin = theYOrigin;
  Standard_NegativeValue_Raise_if(theXStep < 0., "invalid x step");
  Standard_NullValue_Raise_if(theXStep == 0., "invalid x step");
  myXStep = theXStep;
  Standard_NegativeValue_Raise_if(theYStep < 0., "invalid y step");
  Standard_NullValue_Raise_if(theYStep == 0., "invalid y step");
  myYStep         = theYStep;
  myRotationAngle = theRotationAngle;
  Init();
  UpdateDisplay();
}

void Aspect_RectangularGrid::Compute(const double X,
                                     const double Y,
                                     double&      gridX,
                                     double&      gridY) const
{
  double D1      = b1 * X - a1 * Y - c1;
  double D2      = b2 * X - a2 * Y - c2;
  int    n1      = int(std::abs(D1) / myXStep + 0.5);
  int    n2      = int(std::abs(D2) / myYStep + 0.5);
  double offset1 = c1 + double(n1) * std::copysign(myXStep, D1);
  double offset2 = c2 + double(n2) * std::copysign(myYStep, D2);
  double Delta   = a1 * b2 - b1 * a2;
  gridX          = (offset2 * a1 - offset1 * a2) / Delta;
  gridY          = (offset2 * b1 - offset1 * b2) / Delta;
}

double Aspect_RectangularGrid::XStep() const
{
  return myXStep;
}

double Aspect_RectangularGrid::YStep() const
{
  return myYStep;
}

double Aspect_RectangularGrid::FirstAngle() const
{
  return myFirstAngle;
}

double Aspect_RectangularGrid::SecondAngle() const
{
  return mySecondAngle;
}

void Aspect_RectangularGrid::Init()
{

  double angle1 = myFirstAngle + RotationAngle();
  double angle2 = mySecondAngle + RotationAngle();
  if (angle1 != 0.)
  {
    a1 = -std::sin(angle1);
    b1 = std::cos(angle1);
    c1 = XOrigin() * b1 - YOrigin() * a1;
  }
  else
  {
    a1 = 0.;
    b1 = 1.;
    c1 = XOrigin();
  }

  if (angle2 != 0.)
  {
    angle2 += M_PI / 2.;
    a2 = -std::sin(angle2);
    b2 = std::cos(angle2);
    c2 = XOrigin() * b2 - YOrigin() * a2;
  }
  else
  {
    a2 = -1.;
    b2 = 0.;
    c2 = YOrigin();
  }
}

bool Aspect_RectangularGrid::CheckAngle(const double alpha, const double beta) const
{
  return (std::abs(std::sin(alpha) * std::cos(beta + M_PI / 2.)
                   - std::cos(alpha) * std::sin(beta + M_PI / 2.))
          != 0);
}

void Aspect_RectangularGrid::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)

  OCCT_DUMP_BASE_CLASS(theOStream, theDepth, Aspect_Grid)

  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myXStep)
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myYStep)
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myFirstAngle)
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, mySecondAngle)
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, a1)
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, b1)
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, c1)
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, a2)
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, b2)
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, c2)
}

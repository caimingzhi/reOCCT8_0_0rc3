

#include <Standard_Type.hpp>
#include <StepGeom_CartesianPoint.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepGeom_CartesianPoint, StepGeom_Point)

StepGeom_CartesianPoint::StepGeom_CartesianPoint() = default;

void StepGeom_CartesianPoint::Init(const occ::handle<TCollection_HAsciiString>&    theName,
                                   const occ::handle<NCollection_HArray1<double>>& aCoordinates)
{
  SetCoordinates(aCoordinates);

  StepRepr_RepresentationItem::Init(theName);
}

void StepGeom_CartesianPoint::Init2D(const occ::handle<TCollection_HAsciiString>& theName,
                                     const double                                 theX,
                                     const double                                 theY)
{
  myNbCoord   = 2;
  myCoords[0] = theX;
  myCoords[1] = theY;
  myCoords[2] = 0;

  StepRepr_RepresentationItem::Init(theName);
}

void StepGeom_CartesianPoint::Init3D(const occ::handle<TCollection_HAsciiString>& theName,
                                     const double                                 theX,
                                     const double                                 theY,
                                     const double                                 theZ)
{
  myNbCoord   = 3;
  myCoords[0] = theX;
  myCoords[1] = theY;
  myCoords[2] = theZ;

  StepRepr_RepresentationItem::Init(theName);
}

void StepGeom_CartesianPoint::SetCoordinates(
  const occ::handle<NCollection_HArray1<double>>& aCoordinates)
{
  myNbCoord = aCoordinates->Length();
  if (myNbCoord > 0)
    myCoords[0] = aCoordinates->Value(1);
  if (myNbCoord > 1)
    myCoords[1] = aCoordinates->Value(2);
  if (myNbCoord > 2)
    myCoords[2] = aCoordinates->Value(3);
}

void StepGeom_CartesianPoint::SetCoordinates(const std::array<double, 3>& theCoordinates)
{
  myCoords = theCoordinates;
}

const std::array<double, 3>& StepGeom_CartesianPoint::Coordinates() const
{
  return myCoords;
}

double StepGeom_CartesianPoint::CoordinatesValue(const int num) const
{
  return myCoords[num - 1];
}

void StepGeom_CartesianPoint::SetNbCoordinates(const int num)
{
  myNbCoord = num;
}

int StepGeom_CartesianPoint::NbCoordinates() const
{
  return myNbCoord;
}

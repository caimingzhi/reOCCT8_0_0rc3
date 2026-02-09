

#include <StepGeom_Direction.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepGeom_Direction, StepGeom_GeometricRepresentationItem)

StepGeom_Direction::StepGeom_Direction() = default;

void StepGeom_Direction::Init(const occ::handle<TCollection_HAsciiString>&    theName,
                              const occ::handle<NCollection_HArray1<double>>& theDirectionRatios)
{

  SetDirectionRatios(theDirectionRatios);

  StepRepr_RepresentationItem::Init(theName);
}

void StepGeom_Direction::Init3D(const occ::handle<TCollection_HAsciiString>& theName,
                                const double                                 theDirectionRatios1,
                                const double                                 theDirectionRatios2,
                                const double                                 theDirectionRatios3)
{
  myNbCoord   = 3;
  myCoords[0] = theDirectionRatios1;
  myCoords[1] = theDirectionRatios2;
  myCoords[2] = theDirectionRatios3;

  StepRepr_RepresentationItem::Init(theName);
}

void StepGeom_Direction::Init2D(const occ::handle<TCollection_HAsciiString>& theName,
                                const double                                 theDirectionRatios1,
                                const double                                 theDirectionRatios2)
{
  myNbCoord   = 2;
  myCoords[0] = theDirectionRatios1;
  myCoords[1] = theDirectionRatios2;
  myCoords[2] = 0.0;

  StepRepr_RepresentationItem::Init(theName);
}

void StepGeom_Direction::SetDirectionRatios(
  const occ::handle<NCollection_HArray1<double>>& theDirectionRatios)
{
  myNbCoord = theDirectionRatios->Length();
  if (myNbCoord > 0)
    myCoords[0] = theDirectionRatios->Value(1);
  if (myNbCoord > 1)
    myCoords[1] = theDirectionRatios->Value(2);
  if (myNbCoord > 2)
    myCoords[2] = theDirectionRatios->Value(3);
}

void StepGeom_Direction::SetDirectionRatios(const std::array<double, 3>& theDirectionRatios)
{
  myCoords[0] = theDirectionRatios[0];
  myCoords[1] = theDirectionRatios[1];
  myCoords[2] = theDirectionRatios[2];
}

const std::array<double, 3>& StepGeom_Direction::DirectionRatios() const
{
  return myCoords;
}

double StepGeom_Direction::DirectionRatiosValue(const int theInd) const
{
  return myCoords[theInd - 1];
}

void StepGeom_Direction::SetNbDirectionRatios(const int theSize)
{
  myNbCoord = theSize;
}

int StepGeom_Direction::NbDirectionRatios() const
{
  return myNbCoord;
}

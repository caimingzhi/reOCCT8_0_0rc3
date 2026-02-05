#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <StepGeom_Point.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

#include <array>

class TCollection_HAsciiString;

class StepGeom_CartesianPoint : public StepGeom_Point
{

public:
  //! Returns a CartesianPoint
  Standard_EXPORT StepGeom_CartesianPoint();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>&    theName,
                            const occ::handle<NCollection_HArray1<double>>& theCoordinates);

  Standard_EXPORT void Init2D(const occ::handle<TCollection_HAsciiString>& theName,
                              const double                                 theX,
                              const double                                 theY);

  Standard_EXPORT void Init3D(const occ::handle<TCollection_HAsciiString>& theName,
                              const double                                 theX,
                              const double                                 theY,
                              const double                                 theZ);

  Standard_EXPORT void SetCoordinates(
    const occ::handle<NCollection_HArray1<double>>& theCoordinates);

  Standard_EXPORT void SetCoordinates(const std::array<double, 3>& theCoordinates);

  Standard_EXPORT const std::array<double, 3>& Coordinates() const;

  Standard_EXPORT double CoordinatesValue(const int theInd) const;

  Standard_EXPORT void SetNbCoordinates(const int theSize);

  Standard_EXPORT int NbCoordinates() const;

  DEFINE_STANDARD_RTTIEXT(StepGeom_CartesianPoint, StepGeom_Point)

private:
  int                   myNbCoord;
  std::array<double, 3> myCoords;
};

#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepGeom_GeometricRepresentationItem.hpp>
#include <Standard_Real.hpp>
#include <Standard_Integer.hpp>

#include <array>

class TCollection_HAsciiString;

class StepGeom_Direction : public StepGeom_GeometricRepresentationItem
{

public:
  Standard_EXPORT StepGeom_Direction();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>&    theName,
                            const occ::handle<NCollection_HArray1<double>>& theDirectionRatios);

  Standard_EXPORT void Init3D(const occ::handle<TCollection_HAsciiString>& theName,
                              const double                                 theDirectionRatios1,
                              const double                                 theDirectionRatios2,
                              const double                                 theDirectionRatios3);

  Standard_EXPORT void Init2D(const occ::handle<TCollection_HAsciiString>& theName,
                              const double                                 theDirectionRatios1,
                              const double                                 theDirectionRatios2);

  Standard_EXPORT void SetDirectionRatios(
    const occ::handle<NCollection_HArray1<double>>& theDirectionRatios);

  Standard_EXPORT void SetDirectionRatios(const std::array<double, 3>& theDirectionRatios);

  Standard_EXPORT const std::array<double, 3>& DirectionRatios() const;

  Standard_EXPORT double DirectionRatiosValue(const int theInd) const;

  Standard_EXPORT void SetNbDirectionRatios(const int theSize);

  Standard_EXPORT int NbDirectionRatios() const;

  DEFINE_STANDARD_RTTIEXT(StepGeom_Direction, StepGeom_GeometricRepresentationItem)

private:
  int                   myNbCoord;
  std::array<double, 3> myCoords;
};

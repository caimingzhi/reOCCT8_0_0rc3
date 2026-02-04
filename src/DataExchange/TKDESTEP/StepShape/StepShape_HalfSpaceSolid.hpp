#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepGeom_GeometricRepresentationItem.hpp>
class StepGeom_Surface;
class TCollection_HAsciiString;

class StepShape_HalfSpaceSolid : public StepGeom_GeometricRepresentationItem
{

public:
  //! Returns a HalfSpaceSolid
  Standard_EXPORT StepShape_HalfSpaceSolid();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aName,
                            const occ::handle<StepGeom_Surface>&         aBaseSurface,
                            const bool                                   aAgreementFlag);

  Standard_EXPORT void SetBaseSurface(const occ::handle<StepGeom_Surface>& aBaseSurface);

  Standard_EXPORT occ::handle<StepGeom_Surface> BaseSurface() const;

  Standard_EXPORT void SetAgreementFlag(const bool aAgreementFlag);

  Standard_EXPORT bool AgreementFlag() const;

  DEFINE_STANDARD_RTTIEXT(StepShape_HalfSpaceSolid, StepGeom_GeometricRepresentationItem)

private:
  occ::handle<StepGeom_Surface> baseSurface;
  bool                          agreementFlag;
};


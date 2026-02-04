#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepBasic_SiPrefix.hpp>
#include <StepBasic_SiUnitName.hpp>
#include <StepBasic_NamedUnit.hpp>
class StepBasic_DimensionalExponents;

class StepBasic_SiUnit : public StepBasic_NamedUnit
{

public:
  //! Returns a SiUnit
  Standard_EXPORT StepBasic_SiUnit();

  Standard_EXPORT void Init(const bool                 hasAprefix,
                            const StepBasic_SiPrefix   aPrefix,
                            const StepBasic_SiUnitName aName);

  Standard_EXPORT void SetPrefix(const StepBasic_SiPrefix aPrefix);

  Standard_EXPORT void UnSetPrefix();

  Standard_EXPORT StepBasic_SiPrefix Prefix() const;

  Standard_EXPORT bool HasPrefix() const;

  Standard_EXPORT void SetName(const StepBasic_SiUnitName aName);

  Standard_EXPORT StepBasic_SiUnitName Name() const;

  Standard_EXPORT void SetDimensions(
    const occ::handle<StepBasic_DimensionalExponents>& aDimensions) override;

  Standard_EXPORT occ::handle<StepBasic_DimensionalExponents> Dimensions() const override;

  DEFINE_STANDARD_RTTIEXT(StepBasic_SiUnit, StepBasic_NamedUnit)

private:
  StepBasic_SiPrefix   prefix;
  StepBasic_SiUnitName name;
  bool                 hasPrefix;
};


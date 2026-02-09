

#include <Standard_Type.hpp>
#include <StepBasic_DimensionalExponents.hpp>
#include <StepBasic_SiUnit.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_SiUnit, StepBasic_NamedUnit)

StepBasic_SiUnit::StepBasic_SiUnit() = default;

void StepBasic_SiUnit::Init(const bool                 hasAprefix,
                            const StepBasic_SiPrefix   aPrefix,
                            const StepBasic_SiUnitName aName)
{

  hasPrefix = hasAprefix;
  prefix    = aPrefix;
  name      = aName;

  occ::handle<StepBasic_DimensionalExponents> aDimensions;
  aDimensions.Nullify();
  StepBasic_NamedUnit::Init(aDimensions);
}

void StepBasic_SiUnit::SetPrefix(const StepBasic_SiPrefix aPrefix)
{
  prefix    = aPrefix;
  hasPrefix = true;
}

void StepBasic_SiUnit::UnSetPrefix()
{
  hasPrefix = false;
}

StepBasic_SiPrefix StepBasic_SiUnit::Prefix() const
{
  return prefix;
}

bool StepBasic_SiUnit::HasPrefix() const
{
  return hasPrefix;
}

void StepBasic_SiUnit::SetName(const StepBasic_SiUnitName aName)
{
  name = aName;
}

StepBasic_SiUnitName StepBasic_SiUnit::Name() const
{
  return name;
}

void StepBasic_SiUnit::SetDimensions(const occ::handle<StepBasic_DimensionalExponents>&)
{

#ifdef OCCT_DEBUG
  std::cout << "Field is redefined, SetUp Forbidden" << std::endl;
#endif
}

occ::handle<StepBasic_DimensionalExponents> StepBasic_SiUnit::Dimensions() const
{

  occ::handle<StepBasic_DimensionalExponents> aDimensions;
  aDimensions.Nullify();
  return aDimensions;
}

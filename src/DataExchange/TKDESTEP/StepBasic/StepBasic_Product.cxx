

#include <StepBasic_Product.hpp>
#include <StepBasic_ProductContext.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_Product, Standard_Transient)

StepBasic_Product::StepBasic_Product() = default;

void StepBasic_Product::Init(
  const occ::handle<TCollection_HAsciiString>&                                   aId,
  const occ::handle<TCollection_HAsciiString>&                                   aName,
  const occ::handle<TCollection_HAsciiString>&                                   aDescription,
  const occ::handle<NCollection_HArray1<occ::handle<StepBasic_ProductContext>>>& aFrameOfReference)
{

  id               = aId;
  name             = aName;
  description      = aDescription;
  frameOfReference = aFrameOfReference;
}

void StepBasic_Product::SetId(const occ::handle<TCollection_HAsciiString>& aId)
{
  id = aId;
}

occ::handle<TCollection_HAsciiString> StepBasic_Product::Id() const
{
  return id;
}

void StepBasic_Product::SetName(const occ::handle<TCollection_HAsciiString>& aName)
{
  name = aName;
}

occ::handle<TCollection_HAsciiString> StepBasic_Product::Name() const
{
  return name;
}

void StepBasic_Product::SetDescription(const occ::handle<TCollection_HAsciiString>& aDescription)
{
  description = aDescription;
}

occ::handle<TCollection_HAsciiString> StepBasic_Product::Description() const
{
  return description;
}

void StepBasic_Product::SetFrameOfReference(
  const occ::handle<NCollection_HArray1<occ::handle<StepBasic_ProductContext>>>& aFrameOfReference)
{
  frameOfReference = aFrameOfReference;
}

occ::handle<NCollection_HArray1<occ::handle<StepBasic_ProductContext>>> StepBasic_Product::
  FrameOfReference() const
{
  return frameOfReference;
}

occ::handle<StepBasic_ProductContext> StepBasic_Product::FrameOfReferenceValue(const int num) const
{
  return frameOfReference->Value(num);
}

int StepBasic_Product::NbFrameOfReference() const
{
  if (frameOfReference.IsNull())
    return 0;
  return frameOfReference->Length();
}

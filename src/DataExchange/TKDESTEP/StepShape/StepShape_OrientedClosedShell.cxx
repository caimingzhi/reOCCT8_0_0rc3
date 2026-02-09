

#include <StepShape_OrientedClosedShell.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepShape_OrientedClosedShell, StepShape_ClosedShell)

StepShape_OrientedClosedShell::StepShape_OrientedClosedShell() = default;

void StepShape_OrientedClosedShell::Init(
  const occ::handle<TCollection_HAsciiString>& aName,
  const occ::handle<StepShape_ClosedShell>&    aClosedShellElement,
  const bool                                   aOrientation)
{

  closedShellElement = aClosedShellElement;
  orientation        = aOrientation;

  occ::handle<NCollection_HArray1<occ::handle<StepShape_Face>>> aCfsFaces;
  aCfsFaces.Nullify();
  StepShape_ConnectedFaceSet::Init(aName, aCfsFaces);
}

void StepShape_OrientedClosedShell::SetClosedShellElement(
  const occ::handle<StepShape_ClosedShell>& aClosedShellElement)
{
  closedShellElement = aClosedShellElement;
}

occ::handle<StepShape_ClosedShell> StepShape_OrientedClosedShell::ClosedShellElement() const
{
  return closedShellElement;
}

void StepShape_OrientedClosedShell::SetOrientation(const bool aOrientation)
{
  orientation = aOrientation;
}

bool StepShape_OrientedClosedShell::Orientation() const
{
  return orientation;
}

void StepShape_OrientedClosedShell::SetCfsFaces(
  const occ::handle<NCollection_HArray1<occ::handle<StepShape_Face>>>&)
{

  std::cout << "Field is redefined, SetUp Forbidden" << std::endl;
}

occ::handle<NCollection_HArray1<occ::handle<StepShape_Face>>> StepShape_OrientedClosedShell::
  CfsFaces() const
{

  return closedShellElement->CfsFaces();
}

occ::handle<StepShape_Face> StepShape_OrientedClosedShell::CfsFacesValue(const int num) const
{

  return closedShellElement->CfsFacesValue(num);
}

int StepShape_OrientedClosedShell::NbCfsFaces() const
{

  return closedShellElement->NbCfsFaces();
}

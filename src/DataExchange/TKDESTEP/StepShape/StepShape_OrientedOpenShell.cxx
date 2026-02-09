

#include <StepShape_OrientedOpenShell.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepShape_OrientedOpenShell, StepShape_OpenShell)

StepShape_OrientedOpenShell::StepShape_OrientedOpenShell() = default;

void StepShape_OrientedOpenShell::Init(const occ::handle<TCollection_HAsciiString>& aName,
                                       const occ::handle<StepShape_OpenShell>& aOpenShellElement,
                                       const bool                              aOrientation)
{

  openShellElement = aOpenShellElement;
  orientation      = aOrientation;

  occ::handle<NCollection_HArray1<occ::handle<StepShape_Face>>> aCfsFaces;
  aCfsFaces.Nullify();
  StepShape_ConnectedFaceSet::Init(aName, aCfsFaces);
}

void StepShape_OrientedOpenShell::SetOpenShellElement(
  const occ::handle<StepShape_OpenShell>& aOpenShellElement)
{
  openShellElement = aOpenShellElement;
}

occ::handle<StepShape_OpenShell> StepShape_OrientedOpenShell::OpenShellElement() const
{
  return openShellElement;
}

void StepShape_OrientedOpenShell::SetOrientation(const bool aOrientation)
{
  orientation = aOrientation;
}

bool StepShape_OrientedOpenShell::Orientation() const
{
  return orientation;
}

void StepShape_OrientedOpenShell::SetCfsFaces(
  const occ::handle<NCollection_HArray1<occ::handle<StepShape_Face>>>&)
{

  std::cout << "Field is redefined, SetUp Forbidden" << std::endl;
}

occ::handle<NCollection_HArray1<occ::handle<StepShape_Face>>> StepShape_OrientedOpenShell::
  CfsFaces() const
{

  return openShellElement->CfsFaces();
}

occ::handle<StepShape_Face> StepShape_OrientedOpenShell::CfsFacesValue(const int num) const
{

  return openShellElement->CfsFacesValue(num);
}

int StepShape_OrientedOpenShell::NbCfsFaces() const
{

  return openShellElement->NbCfsFaces();
}

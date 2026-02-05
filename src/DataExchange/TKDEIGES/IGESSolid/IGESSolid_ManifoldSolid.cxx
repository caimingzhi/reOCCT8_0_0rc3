#include <IGESSolid_ManifoldSolid.hpp>
#include <IGESSolid_Shell.hpp>
#include <Standard_DimensionMismatch.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESSolid_ManifoldSolid, IGESData_IGESEntity)

IGESSolid_ManifoldSolid::IGESSolid_ManifoldSolid() = default;

void IGESSolid_ManifoldSolid::Init(
  const occ::handle<IGESSolid_Shell>&                                   aShell,
  const bool                                                            Shellflag,
  const occ::handle<NCollection_HArray1<occ::handle<IGESSolid_Shell>>>& VoidShells,
  const occ::handle<NCollection_HArray1<int>>&                          VoidShellFlags)
{
  if (!VoidShells.IsNull())
    if (VoidShells->Lower() != 1 || VoidShellFlags->Lower() != 1
        || VoidShells->Length() != VoidShellFlags->Length())
      throw Standard_DimensionError("IGESSolid_ManifoldSolid : Init");

  theShell           = aShell;
  theOrientationFlag = Shellflag;
  theVoidShells      = VoidShells;
  theOrientFlags     = VoidShellFlags;
  InitTypeAndForm(186, 0);
}

occ::handle<IGESSolid_Shell> IGESSolid_ManifoldSolid::Shell() const
{
  return theShell;
}

bool IGESSolid_ManifoldSolid::OrientationFlag() const
{
  return theOrientationFlag;
}

int IGESSolid_ManifoldSolid::NbVoidShells() const
{
  return (theVoidShells.IsNull() ? 0 : theVoidShells->Length());
}

occ::handle<IGESSolid_Shell> IGESSolid_ManifoldSolid::VoidShell(const int index) const
{
  occ::handle<IGESSolid_Shell> ashell; // par defaut sera Null
  if (!theVoidShells.IsNull())
    ashell = theVoidShells->Value(index);
  return ashell;
}

bool IGESSolid_ManifoldSolid::VoidOrientationFlag(const int index) const
{
  if (!theOrientFlags.IsNull())
    return (theOrientFlags->Value(index) != 0);
  else
    return false; // pour retourner qqchose ...
}

#pragma once

#include <Standard.hpp>

#include <IGESSolid_Shell.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Integer.hpp>
#include <IGESData_IGESEntity.hpp>
class IGESSolid_Shell;

class IGESSolid_ManifoldSolid : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESSolid_ManifoldSolid();

  Standard_EXPORT void Init(
    const occ::handle<IGESSolid_Shell>&                                   aShell,
    const bool                                                            shellflag,
    const occ::handle<NCollection_HArray1<occ::handle<IGESSolid_Shell>>>& voidShells,
    const occ::handle<NCollection_HArray1<int>>&                          voidShellFlags);

  Standard_EXPORT occ::handle<IGESSolid_Shell> Shell() const;

  Standard_EXPORT bool OrientationFlag() const;

  Standard_EXPORT int NbVoidShells() const;

  Standard_EXPORT occ::handle<IGESSolid_Shell> VoidShell(const int Index) const;

  Standard_EXPORT bool VoidOrientationFlag(const int Index) const;

  DEFINE_STANDARD_RTTIEXT(IGESSolid_ManifoldSolid, IGESData_IGESEntity)

private:
  occ::handle<IGESSolid_Shell>                                   theShell;
  bool                                                           theOrientationFlag;
  occ::handle<NCollection_HArray1<occ::handle<IGESSolid_Shell>>> theVoidShells;
  occ::handle<NCollection_HArray1<int>>                          theOrientFlags;
};

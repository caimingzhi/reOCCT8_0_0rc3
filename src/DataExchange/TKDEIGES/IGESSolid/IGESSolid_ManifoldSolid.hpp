#pragma once

#include <Standard.hpp>

#include <IGESSolid_Shell.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Integer.hpp>
#include <IGESData_IGESEntity.hpp>
class IGESSolid_Shell;

//! defines ManifoldSolid, Type <186> Form Number <0>
//! in package IGESSolid
//! A manifold solid is a bounded, closed, and finite volume
//! in three dimensional Euclidean space
class IGESSolid_ManifoldSolid : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESSolid_ManifoldSolid();

  //! This method is used to set the fields of the class
  //! ManifoldSolid
  //! - aShell         : pointer to the shell
  //! - shellflag      : orientation flag of shell
  //! - voidShells     : the void shells
  //! - voidShellFlags : orientation of the void shells
  //! raises exception if length of voidShells and voidShellFlags
  //! do not match
  Standard_EXPORT void Init(
    const occ::handle<IGESSolid_Shell>&                                   aShell,
    const bool                                                            shellflag,
    const occ::handle<NCollection_HArray1<occ::handle<IGESSolid_Shell>>>& voidShells,
    const occ::handle<NCollection_HArray1<int>>&                          voidShellFlags);

  //! returns the Shell entity which is being referred
  Standard_EXPORT occ::handle<IGESSolid_Shell> Shell() const;

  //! returns the orientation flag of the shell
  Standard_EXPORT bool OrientationFlag() const;

  //! returns the number of void shells
  Standard_EXPORT int NbVoidShells() const;

  //! returns Index'th void shell.
  //! raises exception if Index <= 0 or Index > NbVoidShells()
  Standard_EXPORT occ::handle<IGESSolid_Shell> VoidShell(const int Index) const;

  //! returns Index'th orientation flag.
  //! raises exception if Index <= 0 or Index > NbVoidShells()
  Standard_EXPORT bool VoidOrientationFlag(const int Index) const;

  DEFINE_STANDARD_RTTIEXT(IGESSolid_ManifoldSolid, IGESData_IGESEntity)

private:
  occ::handle<IGESSolid_Shell>                                   theShell;
  bool                                                           theOrientationFlag;
  occ::handle<NCollection_HArray1<occ::handle<IGESSolid_Shell>>> theVoidShells;
  occ::handle<NCollection_HArray1<int>>                          theOrientFlags;
};

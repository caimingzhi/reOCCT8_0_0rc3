#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
class TopoDS_Shell;
class TopoDS_Solid;

//! This class builds solids from a set of shells SSh and a solid F.
class TopOpeBRepBuild_ShellToSolid
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopOpeBRepBuild_ShellToSolid();

  Standard_EXPORT void Init();

  Standard_EXPORT void AddShell(const TopoDS_Shell& Sh);

  Standard_EXPORT void MakeSolids(const TopoDS_Solid& So, NCollection_List<TopoDS_Shape>& LSo);

private:
  NCollection_List<TopoDS_Shape> myLSh;
};


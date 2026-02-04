#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class TopoDS_Shell;
class TopoDS_Solid;

class BRepClass3d
{
public:
  DEFINE_STANDARD_ALLOC

  //! Returns the outer most shell of <S>. Returns a Null
  //! shell if <S> has no outer shell.
  //! If <S> has only one shell, then it will return, without checking orientation.
  Standard_EXPORT static TopoDS_Shell OuterShell(const TopoDS_Solid& S);
};


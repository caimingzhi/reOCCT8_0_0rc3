#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class TopoDS_Shape;
class TopoDS_TShape;
class TopoDS_Wire;
class TopoDS_Shell;
class TopoDS_Solid;
class TopoDS_CompSolid;
class TopoDS_Compound;

class TopoDS_Builder
{
public:
  DEFINE_STANDARD_ALLOC

  void MakeWire(TopoDS_Wire& W) const;

  void MakeShell(TopoDS_Shell& S) const;

  void MakeSolid(TopoDS_Solid& S) const;

  void MakeCompSolid(TopoDS_CompSolid& C) const;

  void MakeCompound(TopoDS_Compound& C) const;

  Standard_EXPORT void Add(TopoDS_Shape& S, const TopoDS_Shape& C) const;

  Standard_EXPORT void Remove(TopoDS_Shape& S, const TopoDS_Shape& C) const;

protected:
  Standard_EXPORT void MakeShape(TopoDS_Shape& S, const occ::handle<TopoDS_TShape>& T) const;
};

#include <TopoDS_TWire.hpp>
#include <TopoDS_TShell.hpp>
#include <TopoDS_TSolid.hpp>
#include <TopoDS_TCompSolid.hpp>
#include <TopoDS_TCompound.hpp>
#include <TopoDS_Wire.hpp>
#include <TopoDS_Shell.hpp>
#include <TopoDS_Solid.hpp>
#include <TopoDS_CompSolid.hpp>
#include <TopoDS_Compound.hpp>

inline void TopoDS_Builder::MakeWire(TopoDS_Wire& W) const
{
  occ::handle<TopoDS_TWire> TW = new TopoDS_TWire();
  MakeShape(W, TW);
}

inline void TopoDS_Builder::MakeShell(TopoDS_Shell& S) const
{
  occ::handle<TopoDS_TShell> TS = new TopoDS_TShell();
  MakeShape(S, TS);
}

inline void TopoDS_Builder::MakeSolid(TopoDS_Solid& S) const
{
  occ::handle<TopoDS_TSolid> TS = new TopoDS_TSolid();
  MakeShape(S, TS);
}

inline void TopoDS_Builder::MakeCompSolid(TopoDS_CompSolid& C) const
{
  occ::handle<TopoDS_TCompSolid> TC = new TopoDS_TCompSolid();
  MakeShape(C, TC);
}

inline void TopoDS_Builder::MakeCompound(TopoDS_Compound& C) const
{
  occ::handle<TopoDS_TCompound> TC = new TopoDS_TCompound();
  MakeShape(C, TC);
}

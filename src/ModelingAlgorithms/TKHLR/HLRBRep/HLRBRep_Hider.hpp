#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <TopoDS_Shape.hpp>
#include <BRepTopAdaptor_Tool.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
class HLRBRep_Data;

class HLRBRep_Hider
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT HLRBRep_Hider(const occ::handle<HLRBRep_Data>& DS);

  Standard_EXPORT void OwnHiding(const int FI);

  Standard_EXPORT void Hide(
    const int                                                                        FI,
    NCollection_DataMap<TopoDS_Shape, BRepTopAdaptor_Tool, TopTools_ShapeMapHasher>& MST);

private:
  occ::handle<HLRBRep_Data> myDS;
};

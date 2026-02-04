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

  //! Creates a Hider processing the set of Edges and
  //! hiding faces described by <DS>. Stores the hidden
  //! parts in <DS>.
  Standard_EXPORT HLRBRep_Hider(const occ::handle<HLRBRep_Data>& DS);

  //! own hiding the side face number <FI>.
  Standard_EXPORT void OwnHiding(const int FI);

  //! Removes from the edges, the parts hidden by the
  //! hiding face number <FI>.
  Standard_EXPORT void Hide(
    const int                                                                        FI,
    NCollection_DataMap<TopoDS_Shape, BRepTopAdaptor_Tool, TopTools_ShapeMapHasher>& MST);

private:
  occ::handle<HLRBRep_Data> myDS;
};


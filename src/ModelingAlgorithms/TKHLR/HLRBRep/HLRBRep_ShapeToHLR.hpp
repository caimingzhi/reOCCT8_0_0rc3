#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDS_Shape.hpp>
#include <BRepTopAdaptor_Tool.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_IndexedMap.hpp>
class HLRBRep_Data;
class HLRTopoBRep_OutLiner;
class HLRAlgo_Projector;
class TopoDS_Face;

//! compute the OutLinedShape of a Shape with an
//! OutLiner, a Projector and create the Data
//! Structure of a Shape.
class HLRBRep_ShapeToHLR
{
public:
  DEFINE_STANDARD_ALLOC

  //! Creates a DataStructure containing the OutLiner
  //! <S> depending on the projector <P> and nbIso.
  Standard_EXPORT static occ::handle<HLRBRep_Data> Load(
    const occ::handle<HLRTopoBRep_OutLiner>&                                         S,
    const HLRAlgo_Projector&                                                         P,
    NCollection_DataMap<TopoDS_Shape, BRepTopAdaptor_Tool, TopTools_ShapeMapHasher>& MST,
    const int                                                                        nbIso = 0);

private:
  Standard_EXPORT static void ExploreFace(
    const occ::handle<HLRTopoBRep_OutLiner>&                             S,
    const occ::handle<HLRBRep_Data>&                                     DS,
    const NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& FM,
    const NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& EM,
    int&                                                                 i,
    const TopoDS_Face&                                                   F,
    const bool                                                           closed);

  Standard_EXPORT static void ExploreShape(
    const occ::handle<HLRTopoBRep_OutLiner>&                             S,
    const occ::handle<HLRBRep_Data>&                                     DS,
    const NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& FM,
    const NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& EM);
};

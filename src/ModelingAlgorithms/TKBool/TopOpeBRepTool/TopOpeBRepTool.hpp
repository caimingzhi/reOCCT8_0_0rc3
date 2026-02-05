#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>
#include <TopoDS_Shape.hpp>
#include <Standard_Integer.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <NCollection_IndexedMap.hpp>
#include <NCollection_List.hpp>
#include <Standard_OStream.hpp>
#include <TopOpeBRepTool_OutCurveType.hpp>
class TopoDS_Face;
class TopoDS_Solid;

//! This package provides services used by the TopOpeBRep
//! package performing topological operations on the BRep
//! data structure.
class TopOpeBRepTool
{
public:
  DEFINE_STANDARD_ALLOC

  //! Fuse edges (in a wire) of a shape where we have
  //! useless vertex.
  //! In case face <FF> is built on UV-non-connexed wires
  //! (with the two closing edges FORWARD and REVERSED, in
  //! spite of one only), we find out the faulty edge, add
  //! the faulty shapes (edge,wire,face) to <MshNOK>.
  //! <FF> is a face descendant of <F>.
  //! <MWisOld>(wire) = 1 if wire is wire of <F>
  //! 0 wire results from <F>'s wire split.
  //! returns false if purge fails
  Standard_EXPORT static bool PurgeClosingEdges(
    const TopoDS_Face&                                                     F,
    const TopoDS_Face&                                                     FF,
    const NCollection_DataMap<TopoDS_Shape, int, TopTools_ShapeMapHasher>& MWisOld,
    NCollection_IndexedMap<TopoDS_Shape>&                                  MshNOK);

  Standard_EXPORT static bool PurgeClosingEdges(
    const TopoDS_Face&                                                     F,
    const NCollection_List<TopoDS_Shape>&                                  LOF,
    const NCollection_DataMap<TopoDS_Shape, int, TopTools_ShapeMapHasher>& MWisOld,
    NCollection_IndexedMap<TopoDS_Shape>&                                  MshNOK);

  Standard_EXPORT static bool CorrectONUVISO(const TopoDS_Face& F, TopoDS_Face& Fsp);

  //! Builds up the correct list of faces <LOFF> from <LOF>, using
  //! faulty shapes from map <MshNOK>.
  //! <LOF> is the list of <F>'s descendant faces.
  //! returns false if building fails
  Standard_EXPORT static bool MakeFaces(const TopoDS_Face&                          F,
                                        const NCollection_List<TopoDS_Shape>&       LOF,
                                        const NCollection_IndexedMap<TopoDS_Shape>& MshNOK,
                                        NCollection_List<TopoDS_Shape>&             LOFF);

  //! Returns <False> if the face is valid (the UV
  //! representation of the face is a set of pcurves
  //! connexed by points with connexity 2).
  //! Else, splits <aFace> in order to return a list of valid
  //! faces.
  Standard_EXPORT static bool Regularize(
    const TopoDS_Face&              aFace,
    NCollection_List<TopoDS_Shape>& aListOfFaces,
    NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>&
      ESplits);

  //! Returns <False> if the face is valid (the UV
  //! representation of the face is a set of pcurves
  //! connexed by points with connexity 2).
  //! Else, splits wires of the face, these are boundaries of the
  //! new faces to build up; <OldWiresNewWires> describes (wire,
  //! splits of wire); <ESplits> describes (edge, edge's splits)
  Standard_EXPORT static bool RegularizeWires(
    const TopoDS_Face& aFace,
    NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>&
      OldWiresNewWires,
    NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>&
      ESplits);

  //! Classify wire's splits of map <OldWiresnewWires> in order to
  //! compute <aListOfFaces>, the splits of <aFace>.
  Standard_EXPORT static bool RegularizeFace(
    const TopoDS_Face&                                  aFace,
    const NCollection_DataMap<TopoDS_Shape,
                              NCollection_List<TopoDS_Shape>,
                              TopTools_ShapeMapHasher>& OldWiresnewWires,
    NCollection_List<TopoDS_Shape>&                     aListOfFaces);

  //! Returns <False> if the shell is valid (the solid is a set
  //! of faces connexed by edges with connexity 2).
  //! Else, splits faces of the shell; <OldFacesnewFaces> describes
  //! (face, splits of face).
  Standard_EXPORT static bool RegularizeShells(
    const TopoDS_Solid& aSolid,
    NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>&
      OldSheNewShe,
    NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>&
      FSplits);

  //! Prints <OCT> as string on stream <S>; returns <S>.
  Standard_EXPORT static Standard_OStream& Print(const TopOpeBRepTool_OutCurveType OCT,
                                                 Standard_OStream&                 S);
};

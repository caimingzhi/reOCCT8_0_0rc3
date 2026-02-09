#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <MAT2d_Tool2d.hpp>
#include <Standard_Integer.hpp>
#include <MAT2d_BiInt.hpp>
#include <NCollection_DataMap.hpp>
#include <MAT_Side.hpp>
#include <GeomAbs_JoinType.hpp>
#include <MAT_BasicElt.hpp>
class MAT_Graph;
class BRepMAT2d_Explorer;
class MAT_BasicElt;
class Geom2d_Geometry;
class gp_Pnt2d;
class MAT_Node;
class Bisector_Bisec;
class MAT_Arc;

class BRepMAT2d_BisectingLocus
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepMAT2d_BisectingLocus();

  Standard_EXPORT void Compute(BRepMAT2d_Explorer&    anExplo,
                               const int              LineIndex    = 1,
                               const MAT_Side         aSide        = MAT_Left,
                               const GeomAbs_JoinType aJoinType    = GeomAbs_Arc,
                               const bool             IsOpenResult = false);

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT occ::handle<MAT_Graph> Graph() const;

  Standard_EXPORT int NumberOfContours() const;

  Standard_EXPORT int NumberOfElts(const int IndLine) const;

  Standard_EXPORT int NumberOfSections(const int IndLine, const int Index) const;

  Standard_EXPORT occ::handle<MAT_BasicElt> BasicElt(const int IndLine, const int Index) const;

  Standard_EXPORT occ::handle<Geom2d_Geometry> GeomElt(
    const occ::handle<MAT_BasicElt>& aBasicElt) const;

  Standard_EXPORT gp_Pnt2d GeomElt(const occ::handle<MAT_Node>& aNode) const;

  Standard_EXPORT Bisector_Bisec GeomBis(const occ::handle<MAT_Arc>& anArc, bool& Reverse) const;

private:
  Standard_EXPORT void Fusion();

  Standard_EXPORT void RenumerationAndFusion(
    const int                                            IndexLine,
    const int                                            LengthLine,
    int&                                                 IndexLast,
    NCollection_DataMap<int, occ::handle<MAT_BasicElt>>& NewMap);

  occ::handle<MAT_Graph>                theGraph;
  MAT2d_Tool2d                          theTool;
  bool                                  isDone;
  NCollection_DataMap<MAT2d_BiInt, int> nbSect;
  int                                   nbContours;
};

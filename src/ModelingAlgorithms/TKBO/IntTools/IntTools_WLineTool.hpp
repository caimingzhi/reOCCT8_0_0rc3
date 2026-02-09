#pragma once

#include <GeomAdaptor_Surface.hpp>
#include <IntPatch_WLine.hpp>
#include <IntPatch_Line.hpp>
#include <NCollection_Sequence.hpp>

class TopoDS_Face;
class GeomInt_LineConstructor;
class IntTools_Context;

class IntTools_WLineTool
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static bool NotUseSurfacesForApprox(const TopoDS_Face&                 aF1,
                                                      const TopoDS_Face&                 aF2,
                                                      const occ::handle<IntPatch_WLine>& WL,
                                                      const int                          ifprm,
                                                      const int                          ilprm);

  Standard_EXPORT static bool DecompositionOfWLine(
    const occ::handle<IntPatch_WLine>&                theWLine,
    const occ::handle<GeomAdaptor_Surface>&           theSurface1,
    const occ::handle<GeomAdaptor_Surface>&           theSurface2,
    const TopoDS_Face&                                theFace1,
    const TopoDS_Face&                                theFace2,
    const GeomInt_LineConstructor&                    theLConstructor,
    const bool                                        theAvoidLConstructor,
    const double                                      theTol,
    NCollection_Sequence<occ::handle<IntPatch_Line>>& theNewLines,
    const occ::handle<IntTools_Context>&);
};

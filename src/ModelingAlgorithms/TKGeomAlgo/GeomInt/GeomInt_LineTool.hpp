#pragma once


#include <GeomAdaptor_Surface.hpp>
#include <GeomInt_LineConstructor.hpp>
#include <IntPatch_Line.hpp>
#include <NCollection_Sequence.hpp>

class IntPatch_Point;
class IntPatch_WLine;

class GeomInt_LineTool
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static int NbVertex(const occ::handle<IntPatch_Line>& L);

  Standard_EXPORT static const IntPatch_Point& Vertex(const occ::handle<IntPatch_Line>& L,
                                                      const int                         I);

  Standard_EXPORT static double FirstParameter(const occ::handle<IntPatch_Line>& L);

  Standard_EXPORT static double LastParameter(const occ::handle<IntPatch_Line>& L);

  Standard_EXPORT static bool DecompositionOfWLine(
    const occ::handle<IntPatch_WLine>&                theWLine,
    const occ::handle<GeomAdaptor_Surface>&           theSurface1,
    const occ::handle<GeomAdaptor_Surface>&           theSurface2,
    const double                                      aTolSum,
    const GeomInt_LineConstructor&                    theLConstructor,
    NCollection_Sequence<occ::handle<IntPatch_Line>>& theNewLines);
};


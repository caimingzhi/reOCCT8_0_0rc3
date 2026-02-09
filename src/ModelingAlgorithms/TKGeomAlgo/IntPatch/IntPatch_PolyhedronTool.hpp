#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Bnd_Box.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Integer.hpp>
class Standard_OutOfRange;
class Bnd_Box;
class IntPatch_Polyhedron;
class gp_Pnt;

class IntPatch_PolyhedronTool
{
public:
  DEFINE_STANDARD_ALLOC

  static const Bnd_Box& Bounding(const IntPatch_Polyhedron& thePolyh);

  static const occ::handle<NCollection_HArray1<Bnd_Box>>& ComponentsBounding(
    const IntPatch_Polyhedron& thePolyh);

  static double DeflectionOverEstimation(const IntPatch_Polyhedron& thePolyh);

  static int NbTriangles(const IntPatch_Polyhedron& thePolyh);

  static void Triangle(const IntPatch_Polyhedron& thePolyh,
                       const int                  Index,
                       int&                       P1,
                       int&                       P2,
                       int&                       P3);

  static const gp_Pnt& Point(const IntPatch_Polyhedron& thePolyh, const int Index);

  static int TriConnex(const IntPatch_Polyhedron& thePolyh,
                       const int                  Triang,
                       const int                  Pivot,
                       const int                  Pedge,
                       int&                       TriCon,
                       int&                       OtherP);
};

inline const Bnd_Box& IntPatch_PolyhedronTool::Bounding(const IntPatch_Polyhedron& thePolyh)
{
  return thePolyh.Bounding();
}

inline const occ::handle<NCollection_HArray1<Bnd_Box>>& IntPatch_PolyhedronTool::ComponentsBounding(
  const IntPatch_Polyhedron& thePolyh)
{
  return thePolyh.ComponentsBounding();
}

inline double IntPatch_PolyhedronTool::DeflectionOverEstimation(const IntPatch_Polyhedron& thePolyh)
{
  return thePolyh.DeflectionOverEstimation();
}

inline int IntPatch_PolyhedronTool::NbTriangles(const IntPatch_Polyhedron& thePolyh)
{
  return thePolyh.NbTriangles();
}

inline void IntPatch_PolyhedronTool::Triangle(const IntPatch_Polyhedron& thePolyh,
                                              const int                  Index,
                                              int&                       P1,
                                              int&                       P2,
                                              int&                       P3)
{
  thePolyh.Triangle(Index, P1, P2, P3);
}

inline const gp_Pnt& IntPatch_PolyhedronTool::Point(const IntPatch_Polyhedron& thePolyh,
                                                    const int                  Index)
{
  return thePolyh.Point(Index);
}

inline int IntPatch_PolyhedronTool::TriConnex(const IntPatch_Polyhedron& thePolyh,
                                              const int                  Triang,
                                              const int                  Pivot,
                                              const int                  Pedge,
                                              int&                       TriCon,
                                              int&                       OtherP)
{
  return thePolyh.TriConnex(Triang, Pivot, Pedge, TriCon, OtherP);
}

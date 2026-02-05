#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Bnd_Box.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <gp_Pnt.hpp>
#include <HLRBRep_ThePolyhedronOfInterCSurf.hpp>

class HLRBRep_ThePolyhedronToolOfInterCSurf
{
public:
  DEFINE_STANDARD_ALLOC

  //! Give the bounding box of the PolyhedronTool.
  static const Bnd_Box& Bounding(const HLRBRep_ThePolyhedronOfInterCSurf& thePolyh)
  {
    return thePolyh.Bounding();
  }

  //! Give the array of boxes. The box <n> corresponding
  //! to the triangle <n>.
  static const occ::handle<NCollection_HArray1<Bnd_Box>>& ComponentsBounding(
    const HLRBRep_ThePolyhedronOfInterCSurf& thePolyh)
  {
    return thePolyh.ComponentsBounding();
  }

  //! Give the tolerance of the polygon.
  static double DeflectionOverEstimation(const HLRBRep_ThePolyhedronOfInterCSurf& thePolyh)
  {
    return thePolyh.DeflectionOverEstimation();
  }

  //! Give the number of triangles in this polyhedral surface.
  static int NbTriangles(const HLRBRep_ThePolyhedronOfInterCSurf& thePolyh)
  {
    return thePolyh.NbTriangles();
  }

  //! Give the indices of the 3 points of the triangle of
  //! address Index in the PolyhedronTool.
  static void Triangle(const HLRBRep_ThePolyhedronOfInterCSurf& thePolyh,
                       const int                                Index,
                       int&                                     P1,
                       int&                                     P2,
                       int&                                     P3)
  {
    thePolyh.Triangle(Index, P1, P2, P3);
  }

  //! Give the point of index i in the polyhedral surface.
  static const gp_Pnt& Point(const HLRBRep_ThePolyhedronOfInterCSurf& thePolyh, const int Index)
  {
    return thePolyh.Point(Index);
  }

  //! Give the address Tricon of the triangle connexe to
  //! the triangle of address Triang by the edge Pivot Pedge
  //! and the third point of this connexe triangle.
  //! When we are on a free edge TriCon==0 but the function return
  //! the value of the triangle in the other side of Pivot on the free edge.
  //! Used to turn around a vertex.
  static int TriConnex(const HLRBRep_ThePolyhedronOfInterCSurf& thePolyh,
                       const int                                Triang,
                       const int                                Pivot,
                       const int                                Pedge,
                       int&                                     TriCon,
                       int&                                     OtherP)
  {
    return thePolyh.TriConnex(Triang, Pivot, Pedge, TriCon, OtherP);
  }

  //! This method returns true if the edge based on points with
  //! indices Index1 and Index2 represents a boundary edge.
  //! It is necessary to take into account the boundary deflection for this edge.
  static bool IsOnBound(const HLRBRep_ThePolyhedronOfInterCSurf& thePolyh,
                        const int                                Index1,
                        const int                                Index2)
  {
    return thePolyh.IsOnBound(Index1, Index2);
  }

  //! This method returns a border deflection of the polyhedron.
  static double GetBorderDeflection(const HLRBRep_ThePolyhedronOfInterCSurf& thePolyh)
  {
    return thePolyh.GetBorderDeflection();
  }

  Standard_EXPORT static void Dump(const HLRBRep_ThePolyhedronOfInterCSurf& thePolyh);
};

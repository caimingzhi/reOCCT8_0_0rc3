#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Bnd_Box.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <gp_Pnt.hpp>
#include <IntCurveSurface_ThePolyhedronOfHInter.hpp>

class IntCurveSurface_ThePolyhedronToolOfHInter
{
public:
  DEFINE_STANDARD_ALLOC

  static const Bnd_Box& Bounding(const IntCurveSurface_ThePolyhedronOfHInter& thePolyh)
  {
    return thePolyh.Bounding();
  }

  static const occ::handle<NCollection_HArray1<Bnd_Box>>& ComponentsBounding(
    const IntCurveSurface_ThePolyhedronOfHInter& thePolyh)
  {
    return thePolyh.ComponentsBounding();
  }

  static double DeflectionOverEstimation(const IntCurveSurface_ThePolyhedronOfHInter& thePolyh)
  {
    return thePolyh.DeflectionOverEstimation();
  }

  static int NbTriangles(const IntCurveSurface_ThePolyhedronOfHInter& thePolyh)
  {
    return thePolyh.NbTriangles();
  }

  static void Triangle(const IntCurveSurface_ThePolyhedronOfHInter& thePolyh,
                       const int                                    Index,
                       int&                                         P1,
                       int&                                         P2,
                       int&                                         P3)
  {
    thePolyh.Triangle(Index, P1, P2, P3);
  }

  static const gp_Pnt& Point(const IntCurveSurface_ThePolyhedronOfHInter& thePolyh, const int Index)
  {
    return thePolyh.Point(Index);
  }

  static int TriConnex(const IntCurveSurface_ThePolyhedronOfHInter& thePolyh,
                       const int                                    Triang,
                       const int                                    Pivot,
                       const int                                    Pedge,
                       int&                                         TriCon,
                       int&                                         OtherP)
  {
    return thePolyh.TriConnex(Triang, Pivot, Pedge, TriCon, OtherP);
  }

  static bool IsOnBound(const IntCurveSurface_ThePolyhedronOfHInter& thePolyh,
                        const int                                    Index1,
                        const int                                    Index2)
  {
    return thePolyh.IsOnBound(Index1, Index2);
  }

  static double GetBorderDeflection(const IntCurveSurface_ThePolyhedronOfHInter& thePolyh)
  {
    return thePolyh.GetBorderDeflection();
  }

  Standard_EXPORT static void Dump(const IntCurveSurface_ThePolyhedronOfHInter& thePolyh);
};

#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Bnd_Box.hpp>
#include <gp_Pnt.hpp>
#include <IntCurveSurface_ThePolygonOfHInter.hpp>

class IntCurveSurface_ThePolygonToolOfHInter
{
public:
  DEFINE_STANDARD_ALLOC

  //! Give the bounding box of the polygon.
  static const Bnd_Box& Bounding(const IntCurveSurface_ThePolygonOfHInter& thePolygon)
  {
    return thePolygon.Bounding();
  }

  static double DeflectionOverEstimation(const IntCurveSurface_ThePolygonOfHInter& thePolygon)
  {
    return thePolygon.DeflectionOverEstimation();
  }

  static bool Closed(const IntCurveSurface_ThePolygonOfHInter& thePolygon)
  {
    return thePolygon.Closed();
  }

  static int NbSegments(const IntCurveSurface_ThePolygonOfHInter& thePolygon)
  {
    return thePolygon.NbSegments();
  }

  //! Give the point of range Index in the Polygon.
  static const gp_Pnt& BeginOfSeg(const IntCurveSurface_ThePolygonOfHInter& thePolygon,
                                  const int                                 Index)
  {
    return thePolygon.BeginOfSeg(Index);
  }

  //! Give the point of range Index in the Polygon.
  static const gp_Pnt& EndOfSeg(const IntCurveSurface_ThePolygonOfHInter& thePolygon,
                                const int                                 Index)
  {
    return thePolygon.EndOfSeg(Index);
  }

  Standard_EXPORT static void Dump(const IntCurveSurface_ThePolygonOfHInter& thePolygon);
};


#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Bnd_Box.hpp>
#include <gp_Pnt.hpp>
#include <HLRBRep_ThePolygonOfInterCSurf.hpp>

class HLRBRep_ThePolygonToolOfInterCSurf
{
public:
  DEFINE_STANDARD_ALLOC

  //! Give the bounding box of the polygon.
  static const Bnd_Box& Bounding(const HLRBRep_ThePolygonOfInterCSurf& thePolygon)
  {
    return thePolygon.Bounding();
  }

  static double DeflectionOverEstimation(const HLRBRep_ThePolygonOfInterCSurf& thePolygon)
  {
    return thePolygon.DeflectionOverEstimation();
  }

  static bool Closed(const HLRBRep_ThePolygonOfInterCSurf& thePolygon)
  {
    return thePolygon.Closed();
  }

  static int NbSegments(const HLRBRep_ThePolygonOfInterCSurf& thePolygon)
  {
    return thePolygon.NbSegments();
  }

  //! Give the point of range Index in the Polygon.
  static const gp_Pnt& BeginOfSeg(const HLRBRep_ThePolygonOfInterCSurf& thePolygon, const int Index)
  {
    return thePolygon.BeginOfSeg(Index);
  }

  //! Give the point of range Index in the Polygon.
  static const gp_Pnt& EndOfSeg(const HLRBRep_ThePolygonOfInterCSurf& thePolygon, const int Index)
  {
    return thePolygon.EndOfSeg(Index);
  }

  Standard_EXPORT static void Dump(const HLRBRep_ThePolygonOfInterCSurf& thePolygon);
};

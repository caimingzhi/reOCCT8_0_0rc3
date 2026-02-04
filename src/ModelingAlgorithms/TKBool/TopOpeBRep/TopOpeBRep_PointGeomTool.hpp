#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

class TopOpeBRepDS_Point;
class TopOpeBRep_VPointInter;
class TopOpeBRep_Point2d;
class TopOpeBRep_FaceEdgeIntersector;
class TopoDS_Shape;

//! Provide services needed by the Fillers
class TopOpeBRep_PointGeomTool
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static TopOpeBRepDS_Point MakePoint(const TopOpeBRep_VPointInter& IP);

  Standard_EXPORT static TopOpeBRepDS_Point MakePoint(const TopOpeBRep_Point2d& P2D);

  Standard_EXPORT static TopOpeBRepDS_Point MakePoint(const TopOpeBRep_FaceEdgeIntersector& FEI);

  Standard_EXPORT static TopOpeBRepDS_Point MakePoint(const TopoDS_Shape& S);

  Standard_EXPORT static bool IsEqual(const TopOpeBRepDS_Point& DSP1,
                                      const TopOpeBRepDS_Point& DSP2);
};


#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Standard_Integer.hpp>
#include <HLRBRep_CInter.hpp>
#include <HLRBRep_InterCSurf.hpp>

class gp_Lin;
class HLRBRep_EdgeData;
class HLRBRep_Surface;
class IntCurveSurface_IntersectionPoint;
class IntRes2d_IntersectionSegment;
class IntCurveSurface_IntersectionSegment;

class HLRBRep_Intersector
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT HLRBRep_Intersector();

  Standard_EXPORT void Perform(HLRBRep_EdgeData* theEdge1,
                               const double      theDa1,
                               const double      theDb1);

  Standard_EXPORT void Perform(const int         theNA,
                               HLRBRep_EdgeData* theEdge1,
                               const double      theDa1,
                               const double      theDb1,
                               const int         theNB,
                               HLRBRep_EdgeData* theEdge2,
                               const double      theDa2,
                               const double      theDb2,
                               const bool        theNoBound);

  Standard_EXPORT void SimulateOnePoint(HLRBRep_EdgeData* theEdge1,
                                        const double      theU,
                                        HLRBRep_EdgeData* theEdge2,
                                        const double      theV);

  Standard_EXPORT void Load(HLRBRep_Surface* theSurface);

  Standard_EXPORT void Perform(const gp_Lin& theL, const double theP);

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT int NbPoints() const;

  Standard_EXPORT const IntRes2d_IntersectionPoint& Point(const int N) const;

  Standard_EXPORT const IntCurveSurface_IntersectionPoint& CSPoint(const int N) const;

  Standard_EXPORT int NbSegments() const;

  Standard_EXPORT const IntRes2d_IntersectionSegment& Segment(const int N) const;

  Standard_EXPORT const IntCurveSurface_IntersectionSegment& CSSegment(const int N) const;

  Standard_EXPORT void Destroy();

  ~HLRBRep_Intersector() { Destroy(); }

private:
  IntRes2d_IntersectionPoint         mySinglePoint;
  int                                myTypePerform;
  HLRBRep_CInter                     myIntersector;
  HLRBRep_InterCSurf                 myCSIntersector;
  HLRBRep_Surface*                   mySurface;
  HLRBRep_ThePolyhedronOfInterCSurf* myPolyhedron;
};

#pragma once

#include <Adaptor3d_Surface.hpp>
#include <Bnd_Box.hpp>
#include <IntPolyh_ArrayOfPoints.hpp>
#include <IntPolyh_ArrayOfTriangles.hpp>
#include <IntPolyh_ArrayOfEdges.hpp>

class IntPolyh_Triangle
{
public:
  DEFINE_STANDARD_ALLOC

  IntPolyh_Triangle()
      : myHasIntersection(false),
        myIsIntersectionPossible(true),
        myIsDegenerated(false),
        myDeflection(0.0)
  {
    myPoints[0]            = -1;
    myPoints[1]            = -1;
    myPoints[2]            = -1;
    myEdges[0]             = -1;
    myEdges[1]             = -1;
    myEdges[2]             = -1;
    myEdgesOrientations[0] = 0;
    myEdgesOrientations[1] = 0;
    myEdgesOrientations[2] = 0;
  }

  IntPolyh_Triangle(const int thePoint1, const int thePoint2, const int thePoint3)
      : myHasIntersection(false),
        myIsIntersectionPossible(true),
        myIsDegenerated(false),
        myDeflection(0.0)
  {
    myPoints[0]            = thePoint1;
    myPoints[1]            = thePoint2;
    myPoints[2]            = thePoint3;
    myEdges[0]             = -1;
    myEdges[1]             = -1;
    myEdges[2]             = -1;
    myEdgesOrientations[0] = 0;
    myEdgesOrientations[1] = 0;
    myEdgesOrientations[2] = 0;
  }

  int FirstPoint() const { return myPoints[0]; }

  int SecondPoint() const { return myPoints[1]; }

  int ThirdPoint() const { return myPoints[2]; }

  int FirstEdge() const { return myEdges[0]; }

  int FirstEdgeOrientation() const { return myEdgesOrientations[0]; }

  int SecondEdge() const { return myEdges[1]; }

  int SecondEdgeOrientation() const { return myEdgesOrientations[1]; }

  int ThirdEdge() const { return myEdges[2]; }

  int ThirdEdgeOrientation() const { return myEdgesOrientations[2]; }

  double Deflection() const { return myDeflection; }

  bool IsIntersectionPossible() const { return myIsIntersectionPossible; }

  bool HasIntersection() const { return myHasIntersection; }

  bool IsDegenerated() const { return myIsDegenerated; }

  void SetFirstPoint(const int thePoint) { myPoints[0] = thePoint; }

  void SetSecondPoint(const int thePoint) { myPoints[1] = thePoint; }

  void SetThirdPoint(const int thePoint) { myPoints[2] = thePoint; }

  void SetFirstEdge(const int theEdge, const int theEdgeOrientation)
  {
    myEdges[0]             = theEdge;
    myEdgesOrientations[0] = theEdgeOrientation;
  }

  void SetSecondEdge(const int theEdge, const int theEdgeOrientation)
  {
    myEdges[1]             = theEdge;
    myEdgesOrientations[1] = theEdgeOrientation;
  }

  void SetThirdEdge(const int theEdge, const int theEdgeOrientation)
  {
    myEdges[2]             = theEdge;
    myEdgesOrientations[2] = theEdgeOrientation;
  }

  void SetDeflection(const double theDeflection) { myDeflection = theDeflection; }

  void SetIntersectionPossible(const bool theIP) { myIsIntersectionPossible = theIP; }

  void SetIntersection(const bool theInt) { myHasIntersection = theInt; }

  void SetDegenerated(const bool theDegFlag) { myIsDegenerated = theDegFlag; }

  int GetEdgeNumber(const int theEdgeIndex) const
  {
    return ((theEdgeIndex >= 1 && theEdgeIndex <= 3) ? myEdges[theEdgeIndex - 1] : 0);
  }

  void SetEdge(const int theEdgeIndex, const int theEdgeNumber)
  {
    if (theEdgeIndex >= 1 && theEdgeIndex <= 3)
    {
      myEdges[theEdgeIndex - 1] = theEdgeNumber;
    }
  }

  int GetEdgeOrientation(const int theEdgeIndex) const
  {
    return ((theEdgeIndex >= 1 && theEdgeIndex <= 3) ? myEdgesOrientations[theEdgeIndex - 1] : 0);
  }

  void SetEdgeOrientation(const int theEdgeIndex, const int theEdgeOrientation)
  {
    if (theEdgeIndex >= 1 && theEdgeIndex <= 3)
    {
      myEdgesOrientations[theEdgeIndex - 1] = theEdgeOrientation;
    }
  }

  Standard_EXPORT double ComputeDeflection(const occ::handle<Adaptor3d_Surface>& theSurface,
                                           const IntPolyh_ArrayOfPoints&         thePoints);

  Standard_EXPORT int GetNextTriangle(const int                    theTriangle,
                                      const int                    theEdgeNum,
                                      const IntPolyh_ArrayOfEdges& TEdges) const;

  Standard_EXPORT void MiddleRefinement(const int                             theTriangleNumber,
                                        const occ::handle<Adaptor3d_Surface>& theSurface,
                                        IntPolyh_ArrayOfPoints&               TPoints,
                                        IntPolyh_ArrayOfTriangles&            TTriangles,
                                        IntPolyh_ArrayOfEdges&                TEdges);

  Standard_EXPORT void MultipleMiddleRefinement(const double   theRefineCriterion,
                                                const Bnd_Box& theBox,
                                                const int      theTriangleNumber,
                                                const occ::handle<Adaptor3d_Surface>& theSurface,
                                                IntPolyh_ArrayOfPoints&               TPoints,
                                                IntPolyh_ArrayOfTriangles&            TTriangles,
                                                IntPolyh_ArrayOfEdges&                TEdges);

  Standard_EXPORT void LinkEdges2Triangle(const IntPolyh_ArrayOfEdges& TEdges,
                                          const int                    theEdge1,
                                          const int                    theEdge2,
                                          const int                    theEdge3);

  Standard_EXPORT void SetEdgeAndOrientation(const IntPolyh_Edge& theEdge, const int theEdgeIndex);

  Standard_EXPORT const Bnd_Box& BoundingBox(const IntPolyh_ArrayOfPoints& thePoints);

  Standard_EXPORT void Dump(const int v) const;

private:
  int     myPoints[3];
  int     myEdges[3];
  int     myEdgesOrientations[3];
  bool    myHasIntersection : 1;
  bool    myIsIntersectionPossible : 1;
  bool    myIsDegenerated : 1;
  double  myDeflection;
  Bnd_Box myBox;
};

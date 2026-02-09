#pragma once

#include <gp_Pnt.hpp>
#include <BRepExtrema_SupportType.hpp>
#include <TopoDS_Vertex.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>

class BRepExtrema_SolutionElem
{
public:
  DEFINE_STANDARD_ALLOC

  BRepExtrema_SolutionElem()
      : myDist(0.0),
        myPoint(0.0, 0.0, 0.0),
        mySupType(BRepExtrema_IsVertex),
        myPar1(0.0),
        myPar2(0.0)
  {
  }

  BRepExtrema_SolutionElem(const double                  theDist,
                           const gp_Pnt&                 thePoint,
                           const BRepExtrema_SupportType theSolType,
                           const TopoDS_Vertex&          theVertex)
      : myDist(theDist),
        myPoint(thePoint),
        mySupType(theSolType),
        myVertex(theVertex),
        myPar1(0.0),
        myPar2(0.0)
  {
  }

  BRepExtrema_SolutionElem(const double                  theDist,
                           const gp_Pnt&                 thePoint,
                           const BRepExtrema_SupportType theSolType,
                           const TopoDS_Edge&            theEdge,
                           const double                  theParam)
      : myDist(theDist),
        myPoint(thePoint),
        mySupType(theSolType),
        myEdge(theEdge),
        myPar1(theParam),
        myPar2(0.0)
  {
  }

  BRepExtrema_SolutionElem(const double                  theDist,
                           const gp_Pnt&                 thePoint,
                           const BRepExtrema_SupportType theSolType,
                           const TopoDS_Face&            theFace,
                           const double                  theU,
                           const double                  theV)
      : myDist(theDist),
        myPoint(thePoint),
        mySupType(theSolType),
        myFace(theFace),
        myPar1(theU),
        myPar2(theV)
  {
  }

  double Dist() const { return myDist; }

  const gp_Pnt& Point() const { return myPoint; }

  BRepExtrema_SupportType SupportKind() const { return mySupType; }

  const TopoDS_Vertex& Vertex() const { return myVertex; }

  const TopoDS_Edge& Edge() const { return myEdge; }

  const TopoDS_Face& Face() const { return myFace; }

  void EdgeParameter(double& theParam) const { theParam = myPar1; }

  void FaceParameter(double& theU, double& theV) const
  {
    theU = myPar1;
    theV = myPar2;
  }

private:
  double                  myDist;
  gp_Pnt                  myPoint;
  BRepExtrema_SupportType mySupType;
  TopoDS_Vertex           myVertex;
  TopoDS_Edge             myEdge;
  TopoDS_Face             myFace;
  double                  myPar1;
  double                  myPar2;
};

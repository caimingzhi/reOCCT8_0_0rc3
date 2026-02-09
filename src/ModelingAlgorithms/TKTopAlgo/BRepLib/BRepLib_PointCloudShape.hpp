#pragma once

#include <TopoDS_Shape.hpp>
#include <Standard_Integer.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <Quantity_Color.hpp>
#include <Precision.hpp>

class BRepLib_PointCloudShape
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepLib_PointCloudShape(const TopoDS_Shape& theShape = TopoDS_Shape(),
                                          const double        theTol   = Precision::Confusion());

  Standard_EXPORT virtual ~BRepLib_PointCloudShape();

  const TopoDS_Shape& Shape() const { return myShape; }

  void SetShape(const TopoDS_Shape& theShape) { myShape = theShape; }

  double Tolerance() const { return myTol; }

  void SetTolerance(double theTol) { myTol = theTol; }

  double GetDistance() const { return myDist; }

  void SetDistance(const double theDist) { myDist = theDist; }

  Standard_EXPORT int NbPointsByDensity(const double theDensity = 0.0);

  Standard_EXPORT int NbPointsByTriangulation() const;

  Standard_EXPORT bool GeneratePointsByDensity(const double theDensity = 0.0);

  Standard_EXPORT bool GeneratePointsByTriangulation();

protected:
  Standard_EXPORT double faceArea(const TopoDS_Shape& theShape);

  Standard_EXPORT double computeDensity();

  Standard_EXPORT bool addDensityPoints(const TopoDS_Shape& theFace);

  Standard_EXPORT bool addTriangulationPoints(const TopoDS_Shape& theFace);

protected:
  Standard_EXPORT virtual void clear();

  Standard_EXPORT virtual void addPoint(const gp_Pnt&       thePoint,
                                        const gp_Vec&       theNorm,
                                        const gp_Pnt2d&     theUV,
                                        const TopoDS_Shape& theFace) = 0;

protected:
  TopoDS_Shape                                                       myShape;
  double                                                             myDist;
  double                                                             myTol;
  NCollection_DataMap<TopoDS_Shape, double, TopTools_ShapeMapHasher> myFaceArea;
  NCollection_DataMap<TopoDS_Shape, int, TopTools_ShapeMapHasher>    myFacePoints;
  int                                                                myNbPoints;
};

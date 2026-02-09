#pragma once

#include <IMeshTools_CurveTessellator.hpp>
#include <GCPnts_TangentialDeflection.hpp>
#include <TopoDS_Vertex.hpp>
#include <BRepAdaptor_Curve.hpp>
#include <IMeshData_Types.hpp>

class Geom_Surface;
class Geom2d_Curve;
struct IMeshTools_Parameters;

class BRepMesh_CurveTessellator : public IMeshTools_CurveTessellator
{
public:
  Standard_EXPORT BRepMesh_CurveTessellator(const IMeshData::IEdgeHandle& theEdge,
                                            const IMeshTools_Parameters&  theParameters,
                                            const int                     theMinPointsNb = 2);

  Standard_EXPORT BRepMesh_CurveTessellator(const IMeshData::IEdgeHandle& theEdge,
                                            const TopAbs_Orientation      theOrientation,
                                            const IMeshData::IFaceHandle& theFace,
                                            const IMeshTools_Parameters&  theParameters,
                                            const int                     theMinPointsNb = 2);

  Standard_EXPORT ~BRepMesh_CurveTessellator() override;

  Standard_EXPORT int PointsNb() const override;

  Standard_EXPORT bool Value(const int theIndex,
                             gp_Pnt&   thePoint,
                             double&   theParameter) const override;

  DEFINE_STANDARD_RTTIEXT(BRepMesh_CurveTessellator, IMeshTools_CurveTessellator)

private:
  void init();

  void addInternalVertices();

  void splitByDeflection2d();

  void splitSegment(const occ::handle<Geom_Surface>& theSurf,
                    const occ::handle<Geom2d_Curve>& theCurve2d,
                    const double                     theFirst,
                    const double                     theLast,
                    const int                        theNbIter);

  bool isInToleranceOfVertex(const gp_Pnt& thePoint, const TopoDS_Vertex& theVertex) const;

private:
  BRepMesh_CurveTessellator(const BRepMesh_CurveTessellator& theOther) = delete;

  void operator=(const BRepMesh_CurveTessellator& theOther) = delete;

private:
  const IMeshData::IEdgeHandle& myDEdge;
  const IMeshTools_Parameters&  myParameters;
  TopoDS_Edge                   myEdge;
  BRepAdaptor_Curve             myCurve;
  int                           myMinPointsNb;
  GCPnts_TangentialDeflection   myDiscretTool;
  TopoDS_Vertex                 myFirstVertex;
  TopoDS_Vertex                 myLastVertex;
  double                        mySquareEdgeDef;
  double                        mySquareMinSize;
  double                        myEdgeSqTol;
  double                        myFaceRangeU[2];
  double                        myFaceRangeV[2];
};

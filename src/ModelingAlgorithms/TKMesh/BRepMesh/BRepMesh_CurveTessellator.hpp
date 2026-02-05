#pragma once

#include <IMeshTools_CurveTessellator.hpp>
#include <GCPnts_TangentialDeflection.hpp>
#include <TopoDS_Vertex.hpp>
#include <BRepAdaptor_Curve.hpp>
#include <IMeshData_Types.hpp>

class Geom_Surface;
class Geom2d_Curve;
struct IMeshTools_Parameters;

//! Auxiliary class performing tessellation of passed edge according to specified parameters.
class BRepMesh_CurveTessellator : public IMeshTools_CurveTessellator
{
public:
  //! Constructor.
  Standard_EXPORT BRepMesh_CurveTessellator(const IMeshData::IEdgeHandle& theEdge,
                                            const IMeshTools_Parameters&  theParameters,
                                            const int                     theMinPointsNb = 2);

  //! Constructor.
  Standard_EXPORT BRepMesh_CurveTessellator(const IMeshData::IEdgeHandle& theEdge,
                                            const TopAbs_Orientation      theOrientation,
                                            const IMeshData::IFaceHandle& theFace,
                                            const IMeshTools_Parameters&  theParameters,
                                            const int                     theMinPointsNb = 2);

  //! Destructor.
  Standard_EXPORT ~BRepMesh_CurveTessellator() override;

  //! Returns number of tessellation points.
  Standard_EXPORT int PointsNb() const override;

  //! Returns parameters of solution with the given index.
  //! @param theIndex index of tessellation point.
  //! @param theParameter parameters on PCurve corresponded to the solution.
  //! @param thePoint tessellation point.
  //! @return True in case of valid result, false elewhere.
  Standard_EXPORT bool Value(const int theIndex,
                             gp_Pnt&   thePoint,
                             double&   theParameter) const override;

  DEFINE_STANDARD_RTTIEXT(BRepMesh_CurveTessellator, IMeshTools_CurveTessellator)

private:
  //! Performs initialization of this tool.
  void init();

  //! Adds internal vertices to discrete polygon.
  void addInternalVertices();

  // Check deflection in 2d space for improvement of edge tessellation.
  void splitByDeflection2d();

  void splitSegment(const occ::handle<Geom_Surface>& theSurf,
                    const occ::handle<Geom2d_Curve>& theCurve2d,
                    const double                     theFirst,
                    const double                     theLast,
                    const int                        theNbIter);

  //! Checks whether the given point lies within tolerance of the vertex.
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

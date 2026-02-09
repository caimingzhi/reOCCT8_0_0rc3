#include <BRepMesh_MeshAlgoFactory.hpp>
#include <BRepMesh_SphereRangeSplitter.hpp>
#include <BRepMesh_CylinderRangeSplitter.hpp>
#include <BRepMesh_ConeRangeSplitter.hpp>
#include <BRepMesh_TorusRangeSplitter.hpp>
#include <BRepMesh_DelaunayBaseMeshAlgo.hpp>
#include <BRepMesh_DelaunayDeflectionControlMeshAlgo.hpp>
#include <BRepMesh_BoundaryParamsRangeSplitter.hpp>
#include <BRepMesh_ExtrusionRangeSplitter.hpp>
#include <BRepMesh_UndefinedRangeSplitter.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BRepMesh_MeshAlgoFactory, IMeshTools_MeshAlgoFactory)

namespace
{
  struct BaseMeshAlgo
  {
    typedef BRepMesh_DelaunayBaseMeshAlgo Type;
  };

  template <class RangeSplitter>
  struct NodeInsertionMeshAlgo
  {
    typedef BRepMesh_DelaunayNodeInsertionMeshAlgo<RangeSplitter, BRepMesh_DelaunayBaseMeshAlgo>
      Type;
  };

  template <class RangeSplitter>
  struct DeflectionControlMeshAlgo
  {
    typedef BRepMesh_DelaunayDeflectionControlMeshAlgo<RangeSplitter, BRepMesh_DelaunayBaseMeshAlgo>
      Type;
  };
} // namespace

BRepMesh_MeshAlgoFactory::BRepMesh_MeshAlgoFactory() = default;

BRepMesh_MeshAlgoFactory::~BRepMesh_MeshAlgoFactory() = default;

occ::handle<IMeshTools_MeshAlgo> BRepMesh_MeshAlgoFactory::GetAlgo(
  const GeomAbs_SurfaceType    theSurfaceType,
  const IMeshTools_Parameters& theParameters) const
{
  switch (theSurfaceType)
  {
    case GeomAbs_Plane:
      return theParameters.EnableControlSurfaceDeflectionAllSurfaces
               ? new DeflectionControlMeshAlgo<BRepMesh_DefaultRangeSplitter>::Type
               : (theParameters.InternalVerticesMode
                    ? new NodeInsertionMeshAlgo<BRepMesh_DefaultRangeSplitter>::Type
                    : new BaseMeshAlgo::Type);
      break;

    case GeomAbs_Sphere:
      return theParameters.EnableControlSurfaceDeflectionAllSurfaces
               ? new DeflectionControlMeshAlgo<BRepMesh_SphereRangeSplitter>::Type
               : new NodeInsertionMeshAlgo<BRepMesh_SphereRangeSplitter>::Type;
      break;

    case GeomAbs_Cylinder:
      return theParameters.EnableControlSurfaceDeflectionAllSurfaces
               ? new DeflectionControlMeshAlgo<BRepMesh_CylinderRangeSplitter>::Type
               : (theParameters.InternalVerticesMode
                    ? new NodeInsertionMeshAlgo<BRepMesh_CylinderRangeSplitter>::Type
                    : new BaseMeshAlgo::Type);
      break;

    case GeomAbs_Cone:
      return theParameters.EnableControlSurfaceDeflectionAllSurfaces
               ? new DeflectionControlMeshAlgo<BRepMesh_ConeRangeSplitter>::Type
               : new NodeInsertionMeshAlgo<BRepMesh_ConeRangeSplitter>::Type;
      break;

    case GeomAbs_Torus:
      return theParameters.EnableControlSurfaceDeflectionAllSurfaces
               ? new DeflectionControlMeshAlgo<BRepMesh_TorusRangeSplitter>::Type
               : new NodeInsertionMeshAlgo<BRepMesh_TorusRangeSplitter>::Type;
      break;

    case GeomAbs_SurfaceOfRevolution:
      return new DeflectionControlMeshAlgo<BRepMesh_BoundaryParamsRangeSplitter>::Type;
      break;

    case GeomAbs_SurfaceOfExtrusion:
      return new DeflectionControlMeshAlgo<BRepMesh_ExtrusionRangeSplitter>::Type;
      break;

    case GeomAbs_BezierSurface:
    case GeomAbs_BSplineSurface:
      return new DeflectionControlMeshAlgo<BRepMesh_NURBSRangeSplitter>::Type;
      break;

    case GeomAbs_OffsetSurface:
    case GeomAbs_OtherSurface:
    default:
      return new DeflectionControlMeshAlgo<BRepMesh_UndefinedRangeSplitter>::Type;
  }
}

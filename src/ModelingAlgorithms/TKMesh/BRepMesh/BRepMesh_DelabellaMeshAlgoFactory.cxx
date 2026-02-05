#include <BRepMesh_DelabellaMeshAlgoFactory.hpp>
#include <BRepMesh_SphereRangeSplitter.hpp>
#include <BRepMesh_CylinderRangeSplitter.hpp>
#include <BRepMesh_ConeRangeSplitter.hpp>
#include <BRepMesh_TorusRangeSplitter.hpp>
#include <BRepMesh_DelaunayBaseMeshAlgo.hpp>
#include <BRepMesh_DelabellaBaseMeshAlgo.hpp>
#include <BRepMesh_CustomDelaunayBaseMeshAlgo.hpp>
#include <BRepMesh_DelaunayDeflectionControlMeshAlgo.hpp>
#include <BRepMesh_BoundaryParamsRangeSplitter.hpp>

namespace
{
  struct DefaultBaseMeshAlgo
  {
    typedef BRepMesh_DelaunayBaseMeshAlgo Type;
  };

  template <class RangeSplitter>
  struct DefaultNodeInsertionMeshAlgo
  {
    typedef BRepMesh_DelaunayNodeInsertionMeshAlgo<RangeSplitter, BRepMesh_DelaunayBaseMeshAlgo>
      Type;
  };

  struct BaseMeshAlgo
  {
    typedef BRepMesh_DelabellaBaseMeshAlgo Type;
  };

  template <class RangeSplitter>
  struct NodeInsertionMeshAlgo
  {
    typedef BRepMesh_DelaunayNodeInsertionMeshAlgo<
      RangeSplitter,
      BRepMesh_CustomDelaunayBaseMeshAlgo<BRepMesh_DelabellaBaseMeshAlgo>>
      Type;
  };

  template <class RangeSplitter>
  struct DeflectionControlMeshAlgo
  {
    typedef BRepMesh_DelaunayDeflectionControlMeshAlgo<
      RangeSplitter,
      BRepMesh_CustomDelaunayBaseMeshAlgo<BRepMesh_DelabellaBaseMeshAlgo>>
      Type;
  };
} // namespace

IMPLEMENT_STANDARD_RTTIEXT(BRepMesh_DelabellaMeshAlgoFactory, IMeshTools_MeshAlgoFactory)

//=================================================================================================

BRepMesh_DelabellaMeshAlgoFactory::BRepMesh_DelabellaMeshAlgoFactory() = default;

//=================================================================================================

BRepMesh_DelabellaMeshAlgoFactory::~BRepMesh_DelabellaMeshAlgoFactory() = default;

//=================================================================================================

occ::handle<IMeshTools_MeshAlgo> BRepMesh_DelabellaMeshAlgoFactory::GetAlgo(
  const GeomAbs_SurfaceType    theSurfaceType,
  const IMeshTools_Parameters& theParameters) const
{
  switch (theSurfaceType)
  {
    case GeomAbs_Plane:
      return theParameters.InternalVerticesMode
               ? new NodeInsertionMeshAlgo<BRepMesh_DefaultRangeSplitter>::Type
               : new BaseMeshAlgo::Type;
      break;

    case GeomAbs_Sphere:
    {
      NodeInsertionMeshAlgo<BRepMesh_SphereRangeSplitter>::Type* aMeshAlgo =
        new NodeInsertionMeshAlgo<BRepMesh_SphereRangeSplitter>::Type;
      aMeshAlgo->SetPreProcessSurfaceNodes(true);
      return aMeshAlgo;
    }
    break;

    case GeomAbs_Cylinder:
      return theParameters.InternalVerticesMode
               ? new DefaultNodeInsertionMeshAlgo<BRepMesh_CylinderRangeSplitter>::Type
               : new DefaultBaseMeshAlgo::Type;
      break;

    case GeomAbs_Cone:
    {
      NodeInsertionMeshAlgo<BRepMesh_ConeRangeSplitter>::Type* aMeshAlgo =
        new NodeInsertionMeshAlgo<BRepMesh_ConeRangeSplitter>::Type;
      aMeshAlgo->SetPreProcessSurfaceNodes(true);
      return aMeshAlgo;
    }
    break;

    case GeomAbs_Torus:
    {
      NodeInsertionMeshAlgo<BRepMesh_TorusRangeSplitter>::Type* aMeshAlgo =
        new NodeInsertionMeshAlgo<BRepMesh_TorusRangeSplitter>::Type;
      aMeshAlgo->SetPreProcessSurfaceNodes(true);
      return aMeshAlgo;
    }
    break;

    case GeomAbs_SurfaceOfRevolution:
    {
      DeflectionControlMeshAlgo<BRepMesh_BoundaryParamsRangeSplitter>::Type* aMeshAlgo =
        new DeflectionControlMeshAlgo<BRepMesh_BoundaryParamsRangeSplitter>::Type;
      aMeshAlgo->SetPreProcessSurfaceNodes(true);
      return aMeshAlgo;
    }
    break;

    default:
    {
      DeflectionControlMeshAlgo<BRepMesh_NURBSRangeSplitter>::Type* aMeshAlgo =
        new DeflectionControlMeshAlgo<BRepMesh_NURBSRangeSplitter>::Type;
      aMeshAlgo->SetPreProcessSurfaceNodes(true);
      return aMeshAlgo;
    }
  }
}

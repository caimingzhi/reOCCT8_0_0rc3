

#include <RWMesh_FaceIterator.hpp>

#include <BRepAdaptor_Surface.hpp>
#include <BRep_Tool.hpp>
#include <TopExp.hpp>
#include <TopoDS.hpp>
#include <XCAFDoc_ShapeTool.hpp>
#include <XCAFPrs.hpp>

RWMesh_FaceIterator::RWMesh_FaceIterator(const TDF_Label&       theLabel,
                                         const TopLoc_Location& theLocation,
                                         const bool             theToMapColors,
                                         const XCAFPrs_Style&   theStyle)
    : RWMesh_ShapeIterator(theLabel,
                           theLocation,
                           TopAbs_FACE,
                           TopAbs_SHAPE,
                           theToMapColors,
                           theStyle),
      mySLTool(1, 1e-12),
      myHasNormals(false),
      myIsMirrored(false)
{
  Next();
}

RWMesh_FaceIterator::RWMesh_FaceIterator(const TopoDS_Shape&  theShape,
                                         const XCAFPrs_Style& theStyle)
    : RWMesh_ShapeIterator(theShape, TopAbs_FACE, TopAbs_SHAPE, theStyle),
      mySLTool(1, 1e-12),
      myHasNormals(false),
      myIsMirrored(false)
{
  Next();
}

gp_Dir RWMesh_FaceIterator::normal(int theNode) const
{
  gp_Dir aNormal(gp::DZ());
  if (myPolyTriang->HasNormals())
  {
    NCollection_Vec3<float> aNormVec3;
    myPolyTriang->Normal(theNode, aNormVec3);
    if (aNormVec3.Modulus() != 0.0f)
    {
      aNormal.SetCoord(aNormVec3.x(), aNormVec3.y(), aNormVec3.z());
    }
  }
  else if (myHasNormals && myPolyTriang->HasUVNodes())
  {
    const gp_XY anUV = myPolyTriang->UVNode(theNode).XY();
    mySLTool.SetParameters(anUV.X(), anUV.Y());
    if (mySLTool.IsNormalDefined())
    {
      aNormal = mySLTool.Normal();
    }
  }
  return aNormal;
}

void RWMesh_FaceIterator::Next()
{
  for (; myIter.More(); myIter.Next())
  {
    myFace       = TopoDS::Face(myIter.Current());
    myPolyTriang = BRep_Tool::Triangulation(myFace, myLocation);
    myTrsf       = myLocation.Transformation();
    if (myPolyTriang.IsNull() || myPolyTriang->NbTriangles() == 0)
    {
      resetFace();
      continue;
    }

    initFace();
    myIter.Next();
    return;
  }

  resetFace();
}

void RWMesh_FaceIterator::initFace()
{
  myHasNormals = false;
  myIsMirrored = myTrsf.VectorialPart().Determinant() < 0.0;
  if (myPolyTriang->HasNormals())
  {
    myHasNormals = true;
  }
  if (myPolyTriang->HasUVNodes() && !myHasNormals)
  {
    TopoDS_Face aFaceFwd = TopoDS::Face(myFace.Oriented(TopAbs_FORWARD));
    aFaceFwd.Location(TopLoc_Location());
    TopLoc_Location aLoc;
    if (!BRep_Tool::Surface(aFaceFwd, aLoc).IsNull())
    {
      myFaceAdaptor.Initialize(aFaceFwd, false);
      mySLTool.SetSurface(myFaceAdaptor);
      myHasNormals = true;
    }
  }

  initShape();
}

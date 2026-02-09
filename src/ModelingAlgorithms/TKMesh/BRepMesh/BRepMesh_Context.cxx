#include <BRepMesh_Context.hpp>
#include <BRepMesh_ModelBuilder.hpp>
#include <BRepMesh_EdgeDiscret.hpp>
#include <BRepMesh_ModelHealer.hpp>
#include <BRepMesh_FaceDiscret.hpp>
#include <BRepMesh_ModelPreProcessor.hpp>
#include <BRepMesh_ModelPostProcessor.hpp>

#include <BRepMesh_MeshAlgoFactory.hpp>
#include <BRepMesh_DelabellaMeshAlgoFactory.hpp>
#include <Message.hpp>
#include <OSD_Environment.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BRepMesh_Context, IMeshTools_Context)

BRepMesh_Context::BRepMesh_Context(IMeshTools_MeshAlgoType theMeshType)
{
  if (theMeshType == IMeshTools_MeshAlgoType_DEFAULT)
  {
    TCollection_AsciiString aValue = OSD_Environment("CSF_MeshAlgo").Value();
    aValue.LowerCase();
    if (aValue == "watson" || aValue == "0")
    {
      theMeshType = IMeshTools_MeshAlgoType_Watson;
    }
    else if (aValue == "delabella" || aValue == "1")
    {
      theMeshType = IMeshTools_MeshAlgoType_Delabella;
    }
    else
    {
      if (!aValue.IsEmpty())
      {
        Message::SendWarning(TCollection_AsciiString("BRepMesh_Context, ignore unknown algorithm '")
                             + aValue + "' specified in CSF_MeshAlgo variable");
      }
      theMeshType = IMeshTools_MeshAlgoType_Watson;
    }
  }

  occ::handle<IMeshTools_MeshAlgoFactory> aAlgoFactory;
  switch (theMeshType)
  {
    case IMeshTools_MeshAlgoType_DEFAULT:
    case IMeshTools_MeshAlgoType_Watson:
      aAlgoFactory = new BRepMesh_MeshAlgoFactory();
      break;
    case IMeshTools_MeshAlgoType_Delabella:
      aAlgoFactory = new BRepMesh_DelabellaMeshAlgoFactory();
      break;
  }

  SetModelBuilder(new BRepMesh_ModelBuilder);
  SetEdgeDiscret(new BRepMesh_EdgeDiscret);
  SetModelHealer(new BRepMesh_ModelHealer);
  SetPreProcessor(new BRepMesh_ModelPreProcessor);
  SetFaceDiscret(new BRepMesh_FaceDiscret(aAlgoFactory));
  SetPostProcessor(new BRepMesh_ModelPostProcessor);
}

BRepMesh_Context::~BRepMesh_Context() = default;

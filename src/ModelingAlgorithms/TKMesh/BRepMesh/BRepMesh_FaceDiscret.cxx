#include <BRepMesh_FaceDiscret.hpp>
#include <IMeshData_Model.hpp>
#include <IMeshData_Wire.hpp>
#include <IMeshData_Edge.hpp>
#include <IMeshTools_MeshAlgo.hpp>
#include <OSD_Parallel.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BRepMesh_FaceDiscret, IMeshTools_ModelAlgo)

BRepMesh_FaceDiscret::BRepMesh_FaceDiscret(
  const occ::handle<IMeshTools_MeshAlgoFactory>& theAlgoFactory)
    : myAlgoFactory(theAlgoFactory)
{
}

BRepMesh_FaceDiscret::~BRepMesh_FaceDiscret() = default;

class BRepMesh_FaceDiscret::FaceListFunctor
{
public:
  FaceListFunctor(BRepMesh_FaceDiscret* theAlgo, const Message_ProgressRange& theRange)
      : myAlgo(theAlgo),
        myScope(theRange, "Face Discret", theAlgo->myModel->FacesNb())
  {
    myRanges.reserve(theAlgo->myModel->FacesNb());
    for (int aFaceIter = 0; aFaceIter < theAlgo->myModel->FacesNb(); ++aFaceIter)
    {
      myRanges.push_back(myScope.Next());
    }
  }

  void operator()(const int theFaceIndex) const
  {
    if (!myScope.More())
    {
      return;
    }
    Message_ProgressScope aFaceScope(myRanges[theFaceIndex], nullptr, 1);
    myAlgo->process(theFaceIndex, aFaceScope.Next());
  }

private:
  mutable BRepMesh_FaceDiscret*      myAlgo;
  Message_ProgressScope              myScope;
  std::vector<Message_ProgressRange> myRanges;
};

bool BRepMesh_FaceDiscret::performInternal(const occ::handle<IMeshData_Model>& theModel,
                                           const IMeshTools_Parameters&        theParameters,
                                           const Message_ProgressRange&        theRange)
{
  myModel      = theModel;
  myParameters = theParameters;
  if (myModel.IsNull())
  {
    return false;
  }

  FaceListFunctor aFunctor(this, theRange);
  OSD_Parallel::For(0,
                    myModel->FacesNb(),
                    aFunctor,
                    !myParameters.InParallel || myModel->FacesNb() <= 1);
  if (!theRange.More())
  {
    return false;
  }

  myModel.Nullify();
  return true;
}

void BRepMesh_FaceDiscret::process(const int                    theFaceIndex,
                                   const Message_ProgressRange& theRange) const
{
  const IMeshData::IFaceHandle& aDFace = myModel->GetFace(theFaceIndex);
  if (aDFace->IsSet(IMeshData_Failure) || aDFace->IsSet(IMeshData_Reused))
  {
    return;
  }

  try
  {
    OCC_CATCH_SIGNALS

    occ::handle<IMeshTools_MeshAlgo> aMeshingAlgo =
      myAlgoFactory->GetAlgo(aDFace->GetSurface()->GetType(), myParameters);

    if (aMeshingAlgo.IsNull())
    {
      aDFace->SetStatus(IMeshData_Failure);
      return;
    }

    if (!theRange.More())
    {
      aDFace->SetStatus(IMeshData_UserBreak);
      return;
    }
    aMeshingAlgo->Perform(aDFace, myParameters, theRange);
  }
  catch (Standard_Failure const&)
  {
    aDFace->SetStatus(IMeshData_Failure);
  }
}

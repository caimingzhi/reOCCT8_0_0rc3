

#include <StepTidy_DuplicateCleaner.hpp>

#include <Interface_EntityIterator.hpp>
#include <Interface_Graph.hpp>
#include <StepTidy_Axis2Placement3dReducer.hpp>
#include <StepTidy_CartesianPointReducer.hpp>
#include <StepTidy_DirectionReducer.hpp>
#include <StepTidy_LineReducer.hpp>
#include <StepTidy_VectorReducer.hpp>
#include <StepTidy_PlaneReducer.hpp>
#include <StepTidy_CircleReducer.hpp>
#include <StepData_StepModel.hpp>
#include <utility>

StepTidy_DuplicateCleaner::StepTidy_DuplicateCleaner(occ::handle<XSControl_WorkSession> theWS)
    : myWS(std::move(theWS))
{
}

void StepTidy_DuplicateCleaner::Perform()
{
  occ::handle<StepData_StepModel> aModel = occ::down_cast<StepData_StepModel>(myWS->Model());
  if (aModel.IsNull())
  {
    return;
  }

  StepTidy_CartesianPointReducer   aCartesianPointReducer(myWS);
  StepTidy_DirectionReducer        aDirectionReducer(myWS);
  StepTidy_Axis2Placement3dReducer aAxis2Placement3dReducer(myWS);
  StepTidy_VectorReducer           aVectorReducer(myWS);
  StepTidy_LineReducer             aLineReducer(myWS);
  StepTidy_PlaneReducer            aPlaneReducer(myWS);
  StepTidy_CircleReducer           aCircleReducer(myWS);

  for (int anIndex = 1; anIndex <= aModel->NbEntities(); ++anIndex)
  {
    const occ::handle<Standard_Transient> anEntity = aModel->Value(anIndex);
    aCartesianPointReducer.ProcessEntity(anEntity);
    aDirectionReducer.ProcessEntity(anEntity);
    aAxis2Placement3dReducer.ProcessEntity(anEntity);
    aVectorReducer.ProcessEntity(anEntity);
    aLineReducer.ProcessEntity(anEntity);
    aPlaneReducer.ProcessEntity(anEntity);
    aCircleReducer.ProcessEntity(anEntity);
  }

  NCollection_Map<occ::handle<Standard_Transient>> aReplacedEntities;
  aCartesianPointReducer.Perform(aReplacedEntities);
  aDirectionReducer.Perform(aReplacedEntities);
  aAxis2Placement3dReducer.Perform(aReplacedEntities);
  aVectorReducer.Perform(aReplacedEntities);
  aLineReducer.Perform(aReplacedEntities);
  aPlaneReducer.Perform(aReplacedEntities);
  aCircleReducer.Perform(aReplacedEntities);

  removeEntities(aReplacedEntities);
}

void StepTidy_DuplicateCleaner::removeEntities(
  const NCollection_Map<occ::handle<Standard_Transient>>& theToRemove)
{
  if (theToRemove.IsEmpty())
  {
    return;
  }

  occ::handle<StepData_StepModel> anIntermediateModel = new StepData_StepModel();
  occ::handle<StepData_StepModel> aReadModel = occ::down_cast<StepData_StepModel>(myWS->Model());
  anIntermediateModel->SetProtocol(aReadModel->Protocol());
  anIntermediateModel->SetGTool(aReadModel->GTool());

  for (int i = 1; i <= aReadModel->NbEntities(); i++)
  {
    const occ::handle<Standard_Transient>& anEnt = aReadModel->Value(i);
    if (!theToRemove.Contains(anEnt))
    {
      anIntermediateModel->AddWithRefs(anEnt);
    }
  }

  myWS->SetModel(anIntermediateModel);
  myWS->ComputeGraph();

  occ::handle<StepData_StepModel> aNewModel = new StepData_StepModel();
  aNewModel->SetProtocol(anIntermediateModel->Protocol());
  aNewModel->SetGTool(anIntermediateModel->GTool());
  const auto& aGraph = myWS->Graph();

  for (int i = 1; i <= anIntermediateModel->NbEntities(); i++)
  {
    const occ::handle<Standard_Transient>& anEnt = anIntermediateModel->Value(i);
    if (aGraph.Shareds(anEnt).NbEntities() > 0 || aGraph.Sharings(anEnt).NbEntities() > 0)
    {
      aNewModel->AddWithRefs(anEnt);
    }
  }

  myWS->SetModel(aNewModel);
  myWS->ComputeGraph();
}

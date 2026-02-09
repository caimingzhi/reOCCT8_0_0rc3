#pragma once

#include <Standard_Type.hpp>
#include <IMeshTools_ModelBuilder.hpp>
#include <IMeshData_Model.hpp>
#include <IMeshTools_Parameters.hpp>
#include <IMeshTools_ModelAlgo.hpp>
#include <Message_ProgressRange.hpp>

class IMeshTools_Context : public IMeshData_Shape
{
public:
  IMeshTools_Context() = default;

  ~IMeshTools_Context() override = default;

  virtual bool BuildModel()
  {
    if (myModelBuilder.IsNull())
    {
      return false;
    }

    myModel = myModelBuilder->Perform(GetShape(), myParameters);

    return !myModel.IsNull();
  }

  virtual bool DiscretizeEdges()
  {
    if (myModel.IsNull() || myEdgeDiscret.IsNull())
    {
      return false;
    }

    return myEdgeDiscret->Perform(myModel, myParameters, Message_ProgressRange());
  }

  virtual bool HealModel()
  {
    if (myModel.IsNull())
    {
      return false;
    }

    return myModelHealer.IsNull()
             ? true
             : myModelHealer->Perform(myModel, myParameters, Message_ProgressRange());
  }

  virtual bool PreProcessModel()
  {
    if (myModel.IsNull())
    {
      return false;
    }

    return myPreProcessor.IsNull()
             ? true
             : myPreProcessor->Perform(myModel, myParameters, Message_ProgressRange());
  }

  virtual bool DiscretizeFaces(const Message_ProgressRange& theRange)
  {
    if (myModel.IsNull() || myFaceDiscret.IsNull())
    {
      return false;
    }

    return myFaceDiscret->Perform(myModel, myParameters, theRange);
  }

  virtual bool PostProcessModel()
  {
    if (myModel.IsNull())
    {
      return false;
    }

    return myPostProcessor.IsNull()
             ? true
             : myPostProcessor->Perform(myModel, myParameters, Message_ProgressRange());
  }

  virtual void Clean()
  {
    if (myParameters.CleanModel)
    {
      myModel.Nullify();
    }
  }

  const occ::handle<IMeshTools_ModelBuilder>& GetModelBuilder() const { return myModelBuilder; }

  void SetModelBuilder(const occ::handle<IMeshTools_ModelBuilder>& theBuilder)
  {
    myModelBuilder = theBuilder;
  }

  const occ::handle<IMeshTools_ModelAlgo>& GetEdgeDiscret() const { return myEdgeDiscret; }

  void SetEdgeDiscret(const occ::handle<IMeshTools_ModelAlgo>& theEdgeDiscret)
  {
    myEdgeDiscret = theEdgeDiscret;
  }

  const occ::handle<IMeshTools_ModelAlgo>& GetModelHealer() const { return myModelHealer; }

  void SetModelHealer(const occ::handle<IMeshTools_ModelAlgo>& theModelHealer)
  {
    myModelHealer = theModelHealer;
  }

  const occ::handle<IMeshTools_ModelAlgo>& GetPreProcessor() const { return myPreProcessor; }

  void SetPreProcessor(const occ::handle<IMeshTools_ModelAlgo>& thePreProcessor)
  {
    myPreProcessor = thePreProcessor;
  }

  const occ::handle<IMeshTools_ModelAlgo>& GetFaceDiscret() const { return myFaceDiscret; }

  void SetFaceDiscret(const occ::handle<IMeshTools_ModelAlgo>& theFaceDiscret)
  {
    myFaceDiscret = theFaceDiscret;
  }

  const occ::handle<IMeshTools_ModelAlgo>& GetPostProcessor() const { return myPostProcessor; }

  void SetPostProcessor(const occ::handle<IMeshTools_ModelAlgo>& thePostProcessor)
  {
    myPostProcessor = thePostProcessor;
  }

  const IMeshTools_Parameters& GetParameters() const { return myParameters; }

  IMeshTools_Parameters& ChangeParameters() { return myParameters; }

  const occ::handle<IMeshData_Model>& GetModel() const { return myModel; }

  DEFINE_STANDARD_RTTIEXT(IMeshTools_Context, IMeshData_Shape)

private:
  occ::handle<IMeshTools_ModelBuilder> myModelBuilder;
  occ::handle<IMeshData_Model>         myModel;
  occ::handle<IMeshTools_ModelAlgo>    myEdgeDiscret;
  occ::handle<IMeshTools_ModelAlgo>    myModelHealer;
  occ::handle<IMeshTools_ModelAlgo>    myPreProcessor;
  occ::handle<IMeshTools_ModelAlgo>    myFaceDiscret;
  occ::handle<IMeshTools_ModelAlgo>    myPostProcessor;
  IMeshTools_Parameters                myParameters;
};

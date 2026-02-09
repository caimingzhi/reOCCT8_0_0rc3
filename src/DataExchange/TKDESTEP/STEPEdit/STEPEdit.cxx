

#include <STEPEdit.hpp>

#include <IFSelect_SelectModelEntities.hpp>
#include <IFSelect_SelectModelRoots.hpp>
#include <IFSelect_SelectSignature.hpp>
#include <StepAP214.hpp>
#include <StepAP214_Protocol.hpp>
#include <StepData_StepModel.hpp>
#include <StepSelect_StepType.hpp>

#include <mutex>

occ::handle<Interface_Protocol> STEPEdit::Protocol()
{

  return StepAP214::Protocol();
}

occ::handle<StepData_StepModel> STEPEdit::NewModel()
{
  occ::handle<StepData_StepModel> stepmodel = new StepData_StepModel;
  stepmodel->SetProtocol(STEPEdit::Protocol());
  return stepmodel;
}

occ::handle<IFSelect_Signature> STEPEdit::SignType()
{
  static std::mutex                       aMutex;
  std::lock_guard<std::mutex>             aLock(aMutex);
  static occ::handle<StepSelect_StepType> sty;
  if (!sty.IsNull())
    return sty;
  sty = new StepSelect_StepType;
  sty->SetProtocol(STEPEdit::Protocol());
  return sty;
}

occ::handle<IFSelect_SelectSignature> STEPEdit::NewSelectSDR()
{
  occ::handle<IFSelect_SelectSignature> sel =
    new IFSelect_SelectSignature(STEPEdit::SignType(), "SHAPE_DEFINITION_REPRESENTATION");
  sel->SetInput(new IFSelect_SelectModelRoots);
  return sel;
}

occ::handle<IFSelect_SelectSignature> STEPEdit::NewSelectPlacedItem()
{
  occ::handle<IFSelect_SelectSignature> sel =
    new IFSelect_SelectSignature(STEPEdit::SignType(),
                                 "MAPPED_ITEM|CONTEXT_DEPENDENT_SHAPE_REPRESENTATION",
                                 false);
  sel->SetInput(new IFSelect_SelectModelEntities);
  return sel;
}

occ::handle<IFSelect_SelectSignature> STEPEdit::NewSelectShapeRepr()
{
  occ::handle<IFSelect_SelectSignature> sel =
    new IFSelect_SelectSignature(STEPEdit::SignType(), "SHAPE_REPRESENTATION", false);

  sel->SetInput(new IFSelect_SelectModelEntities);
  return sel;
}

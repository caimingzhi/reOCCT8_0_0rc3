#include <Message_Messenger.hpp>
#include <Message_Msg.hpp>
#include <Resource_Manager.hpp>
#include <ShapeProcess.hpp>
#include <ShapeProcess_OperLibrary.hpp>
#include <ShapeProcess_ShapeContext.hpp>
#include <ShapeProcessAPI_ApplySequence.hpp>
#include <TCollection_AsciiString.hpp>
#include <TopoDS_Shape.hpp>

ShapeProcessAPI_ApplySequence::ShapeProcessAPI_ApplySequence(const char* rscName,
                                                             const char* seqName)
{

  myContext = new ShapeProcess_ShapeContext(rscName);
  myContext->SetDetalisation(TopAbs_FACE);
  TCollection_AsciiString str(seqName);

  ShapeProcess_OperLibrary::Init();

  mySeq = str;
}

occ::handle<ShapeProcess_ShapeContext>& ShapeProcessAPI_ApplySequence::Context()
{
  return myContext;
}

TopoDS_Shape ShapeProcessAPI_ApplySequence::PrepareShape(const TopoDS_Shape& shape,
                                                         const bool,
                                                         const TopAbs_ShapeEnum,
                                                         const Message_ProgressRange& theProgress)
{
  if (shape.IsNull())
    return shape;
  occ::handle<Resource_Manager> rsc = myContext->ResourceManager();
  myContext->Init(shape);

  TCollection_AsciiString str(mySeq);
  str += ".exec.op";
  if (rsc->Find(str.ToCString()))
  {
    ShapeProcess::Perform(myContext, mySeq.ToCString(), theProgress);
  }

  return myContext->Result();
}

void ShapeProcessAPI_ApplySequence::ClearMap() {}

const NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>&
  ShapeProcessAPI_ApplySequence::Map() const
{
  return myContext->Map();
}

void ShapeProcessAPI_ApplySequence::PrintPreparationResult() const
{
  int SS = 0, SN = 0, FF = 0, FS = 0, FN = 0;
  for (NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>::Iterator It(
         myContext->Map());
       It.More();
       It.Next())
  {
    TopoDS_Shape keyshape = It.Key(), valueshape = It.Value();
    if (keyshape.ShapeType() == TopAbs_SHELL)
    {
      if (valueshape.IsNull())
        SN++;
      else
        SS++;
    }
    else if (keyshape.ShapeType() == TopAbs_FACE)
    {
      if (valueshape.IsNull())
        FN++;
      else if (valueshape.ShapeType() == TopAbs_SHELL)
        FS++;
      else
        FF++;
    }
  }

  occ::handle<Message_Messenger> aMessenger = myContext->Messenger();

  Message_Msg EPMSG100("PrResult.Print.MSG100");
  aMessenger->Send(EPMSG100, Message_Info);
  Message_Msg TPMSG50("PrResult.Print.MSG50");
  aMessenger->Send(TPMSG50, Message_Info);
  Message_Msg EPMSG110("PrResult.Print.MSG110");
  EPMSG110.Arg(SS);
  aMessenger->Send(EPMSG110, Message_Info);
  Message_Msg EPMSG150("PrResult.Print.MSG150");
  EPMSG150.Arg(SN);
  aMessenger->Send(EPMSG150, Message_Info);

  TCollection_AsciiString tmp110(EPMSG110.Original()), tmp150(EPMSG150.Original());
  EPMSG110.Set(tmp110.ToCString());
  EPMSG150.Set(tmp150.ToCString());

  Message_Msg TPMSG55("PrResult.Print.MSG55");
  aMessenger->Send(TPMSG55, Message_Info);
  Message_Msg EPMSG115("PrResult.Print.MSG115");
  EPMSG115.Arg(FF);
  aMessenger->Send(EPMSG115, Message_Info);
  EPMSG110.Arg(FS);
  aMessenger->Send(EPMSG110, Message_Info);
  EPMSG150.Arg(FN);
  aMessenger->Send(EPMSG150, Message_Info);

  double SPR = 1, FPR = 1;
  int    STotalR = SS, FTotalR = FF + FS;
  int    NbS = STotalR + SN, NbF = FTotalR + FN;
  if (NbS > 0)
    SPR = 1. * (NbS - SN) / NbS;
  if (NbF > 0)
    FPR = 1. * (NbF - FN) / NbF;
  Message_Msg PMSG200("PrResult.Print.MSG200");
  aMessenger->Send(PMSG200, Message_Info);
  Message_Msg PMSG205("PrResult.Print.MSG205");
  PMSG205.Arg((int)(100 * SPR));
  aMessenger->Send(PMSG205, Message_Info);
  Message_Msg PMSG210("PrResult.Print.MSG210");
  PMSG210.Arg((int)(100 * FPR));
  aMessenger->Send(PMSG210, Message_Info);
}

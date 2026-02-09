

#include <TransferBRep.hpp>

#include <BRep_Builder.hpp>
#include <BRepLib.hpp>
#include <Interface_CheckIterator.hpp>
#include <MoniTool_Macros.hpp>
#include <Message_Msg.hpp>
#include <Message_Printer.hpp>
#include <Standard_Transient.hpp>
#include <TopoDS_HShape.hpp>
#include <TopoDS_Shape.hpp>
#include <Transfer_FinderProcess.hpp>
#include <Transfer_IteratorOfProcessForTransient.hpp>
#include <Transfer_SimpleBinderOfTransient.hpp>
#include <Transfer_TransientProcess.hpp>
#include <TransferBRep_ShapeBinder.hpp>
#include <TransferBRep_ShapeListBinder.hpp>
#include <TransferBRep_ShapeMapper.hpp>
#include <TransferBRep_TransferResultInfo.hpp>

#include <cstdio>

static void ShapeAppend(const occ::handle<Transfer_Binder>&                     binder,
                        const occ::handle<NCollection_HSequence<TopoDS_Shape>>& shapes)
{
  if (binder.IsNull())
    return;
  if (binder->IsKind(STANDARD_TYPE(TransferBRep_BinderOfShape)))
  {
    DeclareAndCast(TransferBRep_BinderOfShape, shbind, binder);
    if (shbind->HasResult())
      shapes->Append(shbind->Result());
  }
  else if (binder->IsKind(STANDARD_TYPE(TransferBRep_ShapeListBinder)))
  {
    DeclareAndCast(TransferBRep_ShapeListBinder, slbind, binder);
    int i, nb = slbind->NbShapes();
    for (i = 1; i <= nb; i++)
      shapes->Append(slbind->Shape(i));
  }
  else if (binder->IsKind(STANDARD_TYPE(Transfer_SimpleBinderOfTransient)))
  {
    DeclareAndCast(Transfer_SimpleBinderOfTransient, trbind, binder);
    DeclareAndCast(TopoDS_HShape, hs, trbind->Result());
    if (!hs.IsNull())
      shapes->Append(hs->Shape());
  }
  occ::handle<Transfer_Binder> nextr = binder->NextResult();
  if (!nextr.IsNull())
    ShapeAppend(nextr, shapes);
}

TopoDS_Shape TransferBRep::ShapeResult(const occ::handle<Transfer_Binder>& binder)
{
  TopoDS_Shape                 shape;
  occ::handle<Transfer_Binder> bnd = binder;
  while (!bnd.IsNull())
  {
    DeclareAndCast(TransferBRep_BinderOfShape, shb, bnd);
    if (!shb.IsNull())
      return shb->Result();
    DeclareAndCast(Transfer_SimpleBinderOfTransient, hsb, bnd);
    if (!hsb.IsNull())
    {
      occ::handle<TopoDS_HShape> hsp = GetCasted(TopoDS_HShape, hsb->Result());
      if (!hsp.IsNull())
        return hsp->Shape();
    }
    bnd = bnd->NextResult();
  }
  return shape;
}

TopoDS_Shape TransferBRep::ShapeResult(const occ::handle<Transfer_TransientProcess>& TP,
                                       const occ::handle<Standard_Transient>&        ent)
{
  TopoDS_Shape                 shape;
  occ::handle<Transfer_Binder> binder = TP->Find(ent);
  if (binder.IsNull())
    binder = GetCasted(Transfer_Binder, ent);
  if (!binder.IsNull())
    return TransferBRep::ShapeResult(binder);
  DeclareAndCast(TopoDS_HShape, hsp, ent);
  if (!hsp.IsNull())
    return hsp->Shape();
  return shape;
}

void TransferBRep::SetShapeResult(const occ::handle<Transfer_TransientProcess>& TP,
                                  const occ::handle<Standard_Transient>&        ent,
                                  const TopoDS_Shape&                           result)
{
  if (result.IsNull() || ent.IsNull() || TP.IsNull())
    return;
  TP->Bind(ent, new TransferBRep_ShapeBinder(result));
}

occ::handle<NCollection_HSequence<TopoDS_Shape>> TransferBRep::Shapes(
  const occ::handle<Transfer_TransientProcess>& TP,
  const bool                                    roots)
{
  occ::handle<NCollection_HSequence<TopoDS_Shape>> shapes;
  if (TP.IsNull())
    return shapes;
  shapes = new NCollection_HSequence<TopoDS_Shape>();

  Transfer_IteratorOfProcessForTransient list = (roots ? TP->RootResult() : TP->CompleteResult());

  for (list.Start(); list.More(); list.Next())
  {
    const occ::handle<Transfer_Binder>& binder = list.Value();
    ShapeAppend(binder, shapes);
  }
  return shapes;
}

occ::handle<NCollection_HSequence<TopoDS_Shape>> TransferBRep::Shapes(
  const occ::handle<Transfer_TransientProcess>&                              TP,
  const occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>>& list)
{
  occ::handle<NCollection_HSequence<TopoDS_Shape>> shapes;
  if (TP.IsNull() && list.IsNull())
    return shapes;
  shapes = new NCollection_HSequence<TopoDS_Shape>();

  int ie, ne = list->Length();
  for (ie = 1; ie <= ne; ie++)
  {
    occ::handle<Transfer_Binder> binder = TP->Find(list->Value(ie));
    ShapeAppend(binder, shapes);
  }

  return shapes;
}

TopAbs_Orientation TransferBRep::ShapeState(const occ::handle<Transfer_FinderProcess>& FP,
                                            const TopoDS_Shape&                        shape)
{
  if (FP.IsNull() || shape.IsNull())
    return TopAbs_EXTERNAL;
  occ::handle<TransferBRep_ShapeMapper> sm    = new TransferBRep_ShapeMapper(shape);
  int                                   index = FP->MapIndex(sm);
  if (index == 0)
    return TopAbs_EXTERNAL;
  sm = occ::down_cast<TransferBRep_ShapeMapper>(FP->Mapped(index));
  if (sm.IsNull())
    return TopAbs_EXTERNAL;
  const TopoDS_Shape& mapped = sm->Value();

  if (mapped.Orientation() != shape.Orientation())
    return TopAbs_REVERSED;
  return TopAbs_FORWARD;
}

occ::handle<Transfer_Binder> TransferBRep::ResultFromShape(
  const occ::handle<Transfer_FinderProcess>& FP,
  const TopoDS_Shape&                        shape)
{
  occ::handle<Transfer_Binder> res;
  if (FP.IsNull() || shape.IsNull())
    return res;
  occ::handle<TransferBRep_ShapeMapper> sm = new TransferBRep_ShapeMapper(shape);
  return FP->Find(sm);
}

occ::handle<Standard_Transient> TransferBRep::TransientFromShape(
  const occ::handle<Transfer_FinderProcess>& FP,
  const TopoDS_Shape&                        shape)
{
  occ::handle<Standard_Transient> res;
  if (FP.IsNull() || shape.IsNull())
    return res;
  occ::handle<TransferBRep_ShapeMapper> sm = new TransferBRep_ShapeMapper(shape);
  return FP->FindTransient(sm);
}

void TransferBRep::SetTransientFromShape(const occ::handle<Transfer_FinderProcess>& FP,
                                         const TopoDS_Shape&                        shape,
                                         const occ::handle<Standard_Transient>&     result)
{
  if (FP.IsNull() || shape.IsNull())
    return;
  occ::handle<TransferBRep_ShapeMapper> sm = new TransferBRep_ShapeMapper(shape);
  FP->BindTransient(sm, result);
}

occ::handle<TransferBRep_ShapeMapper> TransferBRep::ShapeMapper(
  const occ::handle<Transfer_FinderProcess>& FP,
  const TopoDS_Shape&                        shape)
{
  occ::handle<TransferBRep_ShapeMapper> mapper = new TransferBRep_ShapeMapper(shape);
  int                                   index  = FP->MapIndex(mapper);
  if (index == 0)
    return mapper;
  return occ::down_cast<TransferBRep_ShapeMapper>(FP->Mapped(index));
}

static void FillInfo(const occ::handle<Transfer_Binder>&                 Binder,
                     const occ::handle<Interface_Check>&                 Check,
                     const occ::handle<TransferBRep_TransferResultInfo>& Info)
{
  int R = 0, RW = 0, RF = 0, RWF = 0, NR = 0, NRW = 0, NRF = 0, NRWF = 0;
  if (Binder->HasResult())
    if (Check->HasWarnings() && Check->HasFailed())
      RWF++;
    else if (Check->HasWarnings())
      RW++;
    else if (Check->HasFailed())
      RF++;
    else
      R++;
  else if (Check->HasWarnings() && Check->HasFailed())
    NRWF++;
  else if (Check->HasWarnings())
    NRW++;
  else if (Check->HasFailed())
    NRF++;
  else
    NR++;
  Info->Result() += R;
  Info->ResultWarning() += RW;
  Info->ResultFail() += RF;
  Info->ResultWarningFail() += RWF;
  Info->NoResult() += NR;
  Info->NoResultWarning() += NRW;
  Info->NoResultFail() += NRF;
  Info->NoResultWarningFail() += NRWF;
}

void TransferBRep::TransferResultInfo(
  const occ::handle<Transfer_TransientProcess>&                                     TP,
  const occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>>&        EntityTypes,
  occ::handle<NCollection_HSequence<occ::handle<TransferBRep_TransferResultInfo>>>& InfoSeq)
{

  InfoSeq = new NCollection_HSequence<occ::handle<TransferBRep_TransferResultInfo>>;
  if (TP.IsNull() || EntityTypes.IsNull())
    return;
  int SeqLen = EntityTypes->Length();
  int i;
  for (i = 1; i <= SeqLen; i++)
  {
    InfoSeq->Append(new TransferBRep_TransferResultInfo);
  }

  int NbMapped = TP->NbMapped();
  for (i = 1; i <= NbMapped; i++)
  {
    occ::handle<Standard_Transient> Entity = TP->Mapped(i);

    occ::handle<Transfer_Binder> Binder = TP->Find(Entity);
    if (Binder.IsNull())
      continue;
    const occ::handle<Interface_Check> Check = Binder->Check();

    for (int index = 1; index <= SeqLen; index++)
    {
      if (Entity->IsKind(EntityTypes->Value(index)->DynamicType()))
      {
        occ::handle<TransferBRep_TransferResultInfo> Info = InfoSeq->Value(index);

        FillInfo(Binder, Check, Info);
      }
    }
  }
}

void TransferBRep::TransferResultInfo(
  const occ::handle<Transfer_FinderProcess>&                                        FP,
  const occ::handle<NCollection_HSequence<int>>&                                    ShapeTypes,
  occ::handle<NCollection_HSequence<occ::handle<TransferBRep_TransferResultInfo>>>& InfoSeq)
{

  InfoSeq = new NCollection_HSequence<occ::handle<TransferBRep_TransferResultInfo>>;
  if (FP.IsNull() || ShapeTypes.IsNull())
    return;
  int SeqLen = ShapeTypes->Length();
  int i;
  for (i = 1; i <= SeqLen; i++)
  {
    InfoSeq->Append(new TransferBRep_TransferResultInfo);
  }

  int NbMapped = FP->NbMapped();
  for (i = 1; i <= NbMapped; i++)
  {
    occ::handle<TransferBRep_ShapeMapper> Mapper =
      occ::down_cast<TransferBRep_ShapeMapper>(FP->Mapped(i));
    occ::handle<Transfer_Binder> Binder = FP->Find(Mapper);
    if (Binder.IsNull())
      continue;
    const occ::handle<Interface_Check> Check = Binder->Check();

    TopoDS_Shape     S         = Mapper->Value();
    TopAbs_ShapeEnum ShapeType = S.ShapeType();

    for (int index = 1; index <= SeqLen; index++)
    {

      TopAbs_ShapeEnum CurrentType = (TopAbs_ShapeEnum)ShapeTypes->Value(index);

      if (CurrentType == ShapeType || CurrentType == TopAbs_SHAPE)
      {
        occ::handle<TransferBRep_TransferResultInfo> Info = InfoSeq->Value(index);

        FillInfo(Binder, Check, Info);
      }
    }
  }
}

Interface_CheckIterator TransferBRep::ResultCheckList(
  const Interface_CheckIterator&               chl,
  const occ::handle<Transfer_FinderProcess>&   FP,
  const occ::handle<Interface_InterfaceModel>& model)
{
  Interface_CheckIterator nchl;
  if (FP.IsNull() || model.IsNull())
    return nchl;
  nchl.SetModel(model);
  for (chl.Start(); chl.More(); chl.Next())
  {
    int                                 num = 0;
    const occ::handle<Interface_Check>& ach = chl.Value();
    if (ach->NbFails() + ach->NbWarnings() == 0)
      continue;
    DeclareAndCast(Transfer_Finder, starting, ach->Entity());
    occ::handle<Standard_Transient> ent;
    if (!starting.IsNull())
      ent = FP->FindTransient(starting);
    if (!ent.IsNull())
    {
      ach->SetEntity(ent);
      num = model->Number(ent);
    }
    nchl.Add(ach, num);
  }
  return nchl;
}

occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>> TransferBRep::Checked(
  const Interface_CheckIterator& chl,
  const bool                     alsoshapes)
{
  occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>> ls =
    new NCollection_HSequence<occ::handle<Standard_Transient>>();
  for (chl.Start(); chl.More(); chl.Next())
  {
    const occ::handle<Interface_Check>& ach = chl.Value();
    if (ach->NbFails() + ach->NbWarnings() == 0)
      continue;
    occ::handle<Standard_Transient> ent = ach->Entity();
    if (ent.IsNull())
      continue;
    if (!alsoshapes)
    {
      if (ent->IsKind(STANDARD_TYPE(TransferBRep_BinderOfShape))
          || ent->IsKind(STANDARD_TYPE(TopoDS_HShape))
          || ent->IsKind(STANDARD_TYPE(TransferBRep_ShapeMapper)))
        continue;
    }
    ls->Append(ent);
  }
  return ls;
}

occ::handle<NCollection_HSequence<TopoDS_Shape>> TransferBRep::CheckedShapes(
  const Interface_CheckIterator& chl)
{
  occ::handle<NCollection_HSequence<TopoDS_Shape>> ls = new NCollection_HSequence<TopoDS_Shape>();
  for (chl.Start(); chl.More(); chl.Next())
  {
    const occ::handle<Interface_Check>& ach = chl.Value();
    if (ach->NbFails() + ach->NbWarnings() == 0)
      continue;
    occ::handle<Standard_Transient> ent = ach->Entity();
    if (ent.IsNull())
      continue;
    DeclareAndCast(TopoDS_HShape, hs, ent);
    DeclareAndCast(TransferBRep_BinderOfShape, sb, ent);
    DeclareAndCast(TransferBRep_ShapeMapper, sm, ent);
    if (!hs.IsNull())
      ls->Append(hs->Shape());
    if (!sb.IsNull())
      ls->Append(sb->Result());
    if (!sm.IsNull())
      ls->Append(sm->Value());
  }
  return ls;
}

Interface_CheckIterator TransferBRep::CheckObject(const Interface_CheckIterator&         chl,
                                                  const occ::handle<Standard_Transient>& obj)
{
  TopoDS_Shape S;
  DeclareAndCast(TopoDS_HShape, hs, obj);
  DeclareAndCast(TransferBRep_BinderOfShape, sb, obj);
  DeclareAndCast(TransferBRep_ShapeMapper, sm, obj);
  if (!hs.IsNull())
    S = hs->Shape();
  if (!sb.IsNull())
    S = sb->Result();
  if (!sm.IsNull())
    S = sm->Value();
  Interface_CheckIterator nchl;

  for (chl.Start(); chl.More(); chl.Next())
  {
    const occ::handle<Interface_Check>& ach = chl.Value();
    if (ach->NbFails() + ach->NbWarnings() == 0)
      continue;
    occ::handle<Standard_Transient> ent = ach->Entity();
    if (ent.IsNull())
      continue;
    if (S.IsNull())
    {
      if (ent == obj)
      {
        const occ::handle<Interface_Check>& bch(ach);
        bch->SetEntity(ent);
        nchl.Add(bch, 0);
      }
    }
    else
    {
      TopoDS_Shape sh;
      DeclareAndCast(TopoDS_HShape, hsh, ent);
      DeclareAndCast(TransferBRep_BinderOfShape, sbs, ent);
      DeclareAndCast(TransferBRep_ShapeMapper, smp, ent);
      if (!hsh.IsNull())
        sh = hsh->Shape();
      if (!sbs.IsNull())
        sh = sbs->Result();
      if (!smp.IsNull())
        sh = smp->Value();
      if (sh == S)
      {
        const occ::handle<Interface_Check>& bch(ach);
        bch->SetEntity(ent);
        nchl.Add(bch, 0);
      }
    }
  }
  return nchl;
}

void TransferBRep::PrintResultInfo(const occ::handle<Message_Printer>&                 Printer,
                                   const Message_Msg&                                  Header,
                                   const occ::handle<TransferBRep_TransferResultInfo>& ResultInfo,
                                   const bool                                          printEmpty)
{
  int R, RW, RF, RWF, NR, NRW, NRF, NRWF;
  R    = ResultInfo->Result();
  RW   = ResultInfo->ResultWarning();
  RF   = ResultInfo->ResultFail();
  RWF  = ResultInfo->ResultWarningFail();
  NR   = ResultInfo->NoResult();
  NRW  = ResultInfo->NoResultWarning();
  NRF  = ResultInfo->NoResultFail();
  NRWF = ResultInfo->NoResultWarningFail();

  Message_Msg aLocalHeader = Header;
  Printer->Send(aLocalHeader, Message_Info);

  Message_Msg EPMSG30("Result.Print.MSG30");
  EPMSG30.Arg(R);
  Printer->Send(EPMSG30, Message_Info);
  if (printEmpty || (RW > 0))
  {
    Message_Msg EPMSG32("Result.Print.MSG32");
    EPMSG32.Arg(RW);
    Printer->Send(EPMSG32, Message_Info);
  }
  if (printEmpty || (RF > 0))
  {
    Message_Msg EPMSG34("Result.Print.MSG34");
    EPMSG34.Arg(RF);
    Printer->Send(EPMSG34, Message_Info);
  }
  if (printEmpty || (RWF > 0))
  {
    Message_Msg EPMSG36("Result.Print.MSG36");
    EPMSG36.Arg(RWF);
    Printer->Send(EPMSG36, Message_Info);
  }
  Message_Msg EPMSG38("Result.Print.MSG38");
  EPMSG38.Arg(R + RW + RF + RWF);
  Printer->Send(EPMSG38, Message_Info);
  if (printEmpty || (NR > 0))
  {
    Message_Msg EPMSG40("Result.Print.MSG40");
    EPMSG40.Arg(NR);
    Printer->Send(EPMSG40, Message_Info);
  }
  if (printEmpty || (NRW > 0))
  {
    Message_Msg EPMSG42("Result.Print.MSG42");
    EPMSG42.Arg(NRW);
    Printer->Send(EPMSG42, Message_Info);
  }
  if (printEmpty || (NRF > 0))
  {
    Message_Msg EPMSG44("Result.Print.MSG44");
    EPMSG44.Arg(NRF);
    Printer->Send(EPMSG44, Message_Info);
  }
  if (printEmpty || (NRWF > 0))
  {
    Message_Msg EPMSG46("Result.Print.MSG46");
    EPMSG46.Arg(NRWF);
    Printer->Send(EPMSG46, Message_Info);
  }

  Message_Msg EPMSG48("Result.Print.MSG48");
  EPMSG48.Arg(NR + NRW + NRF + NRWF);
  Printer->Send(EPMSG48, Message_Info);
}

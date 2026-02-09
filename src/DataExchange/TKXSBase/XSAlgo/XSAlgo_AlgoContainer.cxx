#include <BRepTools_ReShape.hpp>
#include <Interface_Static.hpp>
#include <Resource_Manager.hpp>
#include <ShapeAlgo.hpp>
#include <ShapeAlgo_AlgoContainer.hpp>
#include <ShapeAlgo_ToolContainer.hpp>
#include <ShapeExtend_MsgRegistrator.hpp>
#include <ShapeFix_Shape.hpp>
#include <ShapeProcess_ShapeContext.hpp>
#include <Standard_ErrorHandler.hpp>
#include <TopExp_Explorer.hpp>
#include <Transfer_FinderProcess.hpp>
#include <Transfer_TransientListBinder.hpp>
#include <Transfer_TransientProcess.hpp>
#include <TransferBRep.hpp>
#include <TransferBRep_ShapeBinder.hpp>
#include <TransferBRep_ShapeMapper.hpp>
#include <XSAlgo_AlgoContainer.hpp>
#include <XSAlgo_ShapeProcessor.hpp>

IMPLEMENT_STANDARD_RTTIEXT(XSAlgo_AlgoContainer, Standard_Transient)

void XSAlgo_AlgoContainer::PrepareForTransfer() const
{
  XSAlgo_ShapeProcessor::PrepareForTransfer();
}

TopoDS_Shape XSAlgo_AlgoContainer::ProcessShape(const TopoDS_Shape&              theShape,
                                                const double                     thePrec,
                                                const double                     theMaxTol,
                                                const char*                      thePrscfile,
                                                const char*                      thePseq,
                                                occ::handle<Standard_Transient>& theInfo,
                                                const Message_ProgressRange&     theProgress,
                                                const bool                       theNonManifold,
                                                const TopAbs_ShapeEnum theDetailingLevel) const
{
  if (theShape.IsNull())
  {
    return theShape;
  }

  occ::handle<ShapeProcess_ShapeContext> aContext =
    occ::down_cast<ShapeProcess_ShapeContext>(theInfo);
  if (aContext.IsNull())
  {
    const char* aRscfile = Interface_Static::CVal(thePrscfile);
    aContext             = new ShapeProcess_ShapeContext(theShape, aRscfile);
    if (!aContext->ResourceManager()->IsInitialized())
    {

      Interface_Static::FillMap(aContext->ResourceManager()->GetMap());
    }
    aContext->SetDetalisation(theDetailingLevel);
  }
  aContext->SetNonManifold(theNonManifold);
  theInfo = aContext;

  const char* aSeq = Interface_Static::CVal(thePseq);
  if (!aSeq)
    aSeq = thePseq;

  occ::handle<Resource_Manager> aRsc = aContext->ResourceManager();
  TCollection_AsciiString       aStr(aSeq);
  aStr += ".exec.op";
  if (!aRsc->Find(aStr.ToCString()))
  {

    if (!strncmp(thePseq, "read.", 5))
    {
      try
      {
        OCC_CATCH_SIGNALS
        occ::handle<ShapeExtend_MsgRegistrator> aMsg = new ShapeExtend_MsgRegistrator;
        occ::handle<ShapeFix_Shape> aSfs = ShapeAlgo::AlgoContainer()->ToolContainer()->FixShape();
        aSfs->Init(theShape);
        aSfs->SetMsgRegistrator(aMsg);
        aSfs->SetPrecision(thePrec);
        aSfs->SetMaxTolerance(theMaxTol);
        aSfs->FixFaceTool()->FixWireTool()->FixSameParameterMode() = false;
        aSfs->FixSolidTool()->CreateOpenSolidMode()                = false;
        aSfs->Perform(theProgress);

        TopoDS_Shape aShape = aSfs->Shape();
        if (!aShape.IsNull() && aShape != theShape)
        {
          aContext->RecordModification(aSfs->Context(), aMsg);
          aContext->SetResult(aShape);
        }
      }
      catch (Standard_Failure const& anException)
      {
        (void)anException;
      }
      return aContext->Result();
    }

    else if (!strncmp(thePseq, "write.", 6))
    {
      aRsc->SetResource(aStr.ToCString(), "DirectFaces");
    }
  }

  aRsc->SetResource("Runtime.Tolerance", thePrec);
  aRsc->SetResource("Runtime.MaxTolerance", theMaxTol);

  if (!ShapeProcess::Perform(aContext, aSeq, theProgress))
    return theShape;

  return aContext->Result();
}

bool XSAlgo_AlgoContainer::CheckPCurve(const TopoDS_Edge& theEdge,
                                       const TopoDS_Face& theFace,
                                       const double       thePrecision,
                                       const bool         theIsSeam) const
{
  return XSAlgo_ShapeProcessor::CheckPCurve(theEdge, theFace, thePrecision, theIsSeam);
}

void XSAlgo_AlgoContainer::MergeTransferInfo(const occ::handle<Transfer_TransientProcess>& TP,
                                             const occ::handle<Standard_Transient>&        info,
                                             const int startTPitem) const
{
  occ::handle<ShapeProcess_ShapeContext> context = occ::down_cast<ShapeProcess_ShapeContext>(info);
  if (context.IsNull())
    return;

  const NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>& map =
    context->Map();
  occ::handle<ShapeExtend_MsgRegistrator> msg = context->Messages();
  if (map.Extent() <= 0 && (msg.IsNull() || msg->MapShape().Extent() <= 0))
    return;

  int i = (startTPitem > 0 ? startTPitem : 1);
  for (; i <= TP->NbMapped(); i++)
  {
    occ::handle<Transfer_Binder>          bnd = TP->MapItem(i);
    occ::handle<TransferBRep_ShapeBinder> sb  = occ::down_cast<TransferBRep_ShapeBinder>(bnd);
    if (sb.IsNull() || sb->Result().IsNull())
      continue;

    TopoDS_Shape orig = sb->Result();

    if (map.IsBound(orig))
    {
      sb->SetResult(map.Find(orig));
    }
    else if (!orig.Location().IsIdentity())
    {
      TopLoc_Location aNullLoc;
      TopoDS_Shape    atmpSh = orig.Located(aNullLoc);
      if (map.IsBound(atmpSh))
        sb->SetResult(map.Find(atmpSh));
    }
    else
    {

      BRepTools_ReShape aReShape;
      bool              hasModifiedEdges = false;
      TopExp_Explorer   anExpSE(orig, TopAbs_EDGE);

      for (; anExpSE.More(); anExpSE.Next())
      {
        if (map.IsBound(anExpSE.Current()))
        {
          hasModifiedEdges            = true;
          TopoDS_Shape aModifiedShape = map.Find(anExpSE.Current());
          aReShape.Replace(anExpSE.Current(), aModifiedShape);
        }
      }

      if (hasModifiedEdges)
      {
        TopoDS_Shape aRes = aReShape.Apply(orig);
        sb->SetResult(aRes);
      }
    }

    if (!msg.IsNull())
    {
      const NCollection_DataMap<TopoDS_Shape,
                                NCollection_List<Message_Msg>,
                                TopTools_ShapeMapHasher>& msgmap = msg->MapShape();
      if (msgmap.IsBound(orig))
      {
        const NCollection_List<Message_Msg>& msglist = msgmap.Find(orig);
        for (NCollection_List<Message_Msg>::Iterator iter(msglist); iter.More(); iter.Next())
        {
          const Message_Msg& mess = iter.Value();
          sb->AddWarning(TCollection_AsciiString(mess.Value()).ToCString(),
                         TCollection_AsciiString(mess.Original()).ToCString());
        }
      }
    }
  }
}

void XSAlgo_AlgoContainer::MergeTransferInfo(const occ::handle<Transfer_FinderProcess>& FP,
                                             const occ::handle<Standard_Transient>&     info) const
{
  occ::handle<ShapeProcess_ShapeContext> context = occ::down_cast<ShapeProcess_ShapeContext>(info);
  if (context.IsNull())
    return;

  const NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>& map =
    context->Map();
  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>::Iterator
                                          ShapeShapeIterator(map);
  occ::handle<ShapeExtend_MsgRegistrator> msg = context->Messages();

  for (; ShapeShapeIterator.More(); ShapeShapeIterator.Next())
  {

    TopoDS_Shape orig = ShapeShapeIterator.Key(), res = ShapeShapeIterator.Value();
    occ::handle<TransferBRep_ShapeMapper> resMapper = TransferBRep::ShapeMapper(FP, res);
    occ::handle<Transfer_Binder>          resBinder = FP->Find(resMapper);

    if (resBinder.IsNull())
    {
      resBinder = new TransferBRep_ShapeBinder(res);

      if (orig.ShapeType() > res.ShapeType())
      {
        TopoDS_Shape                              sub;
        occ::handle<Transfer_TransientListBinder> TransientListBinder =
          new Transfer_TransientListBinder;
        for (TopoDS_Iterator it(res); it.More(); it.Next())
        {
          occ::handle<Transfer_Finder> subMapper = TransferBRep::ShapeMapper(FP, it.Value());
          if (subMapper.IsNull())
            continue;

          occ::handle<Standard_Transient> tr = FP->FindTransient(subMapper);
          if (tr.IsNull())
            continue;
          TransientListBinder->AddResult(tr);
          sub = it.Value();
        }
        if (TransientListBinder->NbTransients() == 1)
          resBinder = new TransferBRep_ShapeBinder(sub);
        else if (TransientListBinder->NbTransients() > 1)
        {
          resBinder->AddResult(TransientListBinder);
        }
      }
    }

    occ::handle<TransferBRep_ShapeMapper> origMapper = TransferBRep::ShapeMapper(FP, orig);
    occ::handle<Transfer_Binder>          origBinder = FP->Find(origMapper);
    if (origBinder.IsNull())
    {
      FP->Bind(origMapper, resBinder);
    }
    else
    {
      origBinder->AddResult(resBinder);
    }

    if (!msg.IsNull())
    {
      const NCollection_DataMap<TopoDS_Shape,
                                NCollection_List<Message_Msg>,
                                TopTools_ShapeMapHasher>& msgmap = msg->MapShape();
      if (msgmap.IsBound(orig))
      {
        const NCollection_List<Message_Msg>& msglist = msgmap.Find(orig);
        for (NCollection_List<Message_Msg>::Iterator iter(msglist); iter.More(); iter.Next())
        {
          const Message_Msg& mess = iter.Value();
          resBinder->AddWarning(TCollection_AsciiString(mess.Value()).ToCString(),
                                TCollection_AsciiString(mess.Original()).ToCString());
        }
      }
    }
  }
}

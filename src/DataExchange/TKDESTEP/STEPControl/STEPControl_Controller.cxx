

#include <APIHeaderSection_EditHeader.hpp>
#include <IFSelect_EditForm.hpp>
#include <IFSelect_SelectModelRoots.hpp>
#include <IFSelect_SelectSignature.hpp>
#include <IFSelect_SignAncestor.hpp>
#include <IFSelect_SignCounter.hpp>
#include <MoniTool_Macros.hpp>
#include <Interface_Static.hpp>
#include <RWHeaderSection.hpp>
#include "../RWStepAP214/RWStepAP214.hpp"
#include <Standard_Type.hpp>
#include <Standard_Version.hxx>
#include <STEPControl_ActorRead.hpp>
#include <STEPControl_ActorWrite.hpp>
#include <STEPControl_Controller.hpp>
#include <StepData_FileProtocol.hpp>
#include <StepData_StepModel.hpp>
#include <STEPEdit.hpp>
#include <STEPEdit_EditContext.hpp>
#include <STEPEdit_EditSDR.hpp>
#include <StepSelect_WorkLibrary.hpp>
#include <STEPSelections_SelectAssembly.hpp>
#include <STEPSelections_SelectDerived.hpp>
#include <STEPSelections_SelectFaces.hpp>
#include <STEPSelections_SelectForTransfer.hpp>
#include <STEPSelections_SelectGSCurves.hpp>
#include <STEPSelections_SelectInstances.hpp>
#include <ShapeUpgrade_RemoveLocations.hpp>
#include <TopoDS_Shape.hpp>
#include <Transfer_ActorOfTransientProcess.hpp>
#include <XSAlgo.hpp>
#include <XSAlgo_ShapeProcessor.hpp>
#include <XSControl_WorkSession.hpp>

#include <mutex>

IMPLEMENT_STANDARD_RTTIEXT(STEPControl_Controller, XSControl_Controller)

STEPControl_Controller::STEPControl_Controller()
    : XSControl_Controller("STEP", "step")
{
  static bool                 init = false;
  static std::mutex           aMutex;
  std::lock_guard<std::mutex> aLock(aMutex);
  if (!init)
  {
    RWHeaderSection::Init();
    RWStepAP214::Init();

    Interface_Static::Init("step",
                           "write.step.product.name",
                           't',
                           "Open CASCADE STEP translator " OCC_VERSION_STRING);
    Interface_Static::Init("step", "write.step.assembly", 'e', "");
    Interface_Static::Init("step", "write.step.assembly", '&', "enum 0");
    Interface_Static::Init("step", "write.step.assembly", '&', "eval Off");
    Interface_Static::Init("step", "write.step.assembly", '&', "eval On");
    Interface_Static::Init("step", "write.step.assembly", '&', "eval Auto");
    Interface_Static::SetCVal("write.step.assembly", "Auto");

    Interface_Static::Init("step", "step.angleunit.mode", 'e', "");
    Interface_Static::Init("step", "step.angleunit.mode", '&', "enum 0");
    Interface_Static::Init("step", "step.angleunit.mode", '&', "eval File");
    Interface_Static::Init("step", "step.angleunit.mode", '&', "eval Rad");
    Interface_Static::Init("step", "step.angleunit.mode", '&', "eval Deg");
    Interface_Static::SetCVal("step.angleunit.mode", "File");

    Interface_Static::Init("step", "write.step.schema", 'e', "");
    Interface_Static::Init("step", "write.step.schema", '&', "enum 1");
    Interface_Static::Init("step", "write.step.schema", '&', "eval AP214CD");
    Interface_Static::Init("step", "write.step.schema", '&', "eval AP214DIS");
    Interface_Static::Init("step", "write.step.schema", '&', "eval AP203");
    Interface_Static::Init("step", "write.step.schema", '&', "eval AP214IS");
    Interface_Static::Init("step", "write.step.schema", '&', "eval AP242DIS");
    Interface_Static::SetCVal("write.step.schema", "AP214IS");

    Interface_Static::Init("step", "read.step.shape.repr", 'e', "");
    Interface_Static::Init("step", "read.step.shape.repr", '&', "enum 1");
    Interface_Static::Init("step", "read.step.shape.repr", '&', "eval All");
    Interface_Static::Init("step", "read.step.shape.repr", '&', "eval ABSR");
    Interface_Static::Init("step", "read.step.shape.repr", '&', "eval MSSR");
    Interface_Static::Init("step", "read.step.shape.repr", '&', "eval GBSSR");
    Interface_Static::Init("step", "read.step.shape.repr", '&', "eval FBSR");
    Interface_Static::Init("step", "read.step.shape.repr", '&', "eval EBWSR");
    Interface_Static::Init("step", "read.step.shape.repr", '&', "eval GBWSR");
    Interface_Static::SetCVal("read.step.shape.repr", "All");

    Interface_Static::Init("step", "read.step.shape.relationship", 'e', "");
    Interface_Static::Init("step", "read.step.shape.relationship", '&', "enum 0");
    Interface_Static::Init("step", "read.step.shape.relationship", '&', "eval OFF");
    Interface_Static::Init("step", "read.step.shape.relationship", '&', "eval ON");
    Interface_Static::SetCVal("read.step.shape.relationship", "ON");

    Interface_Static::Init("step", "read.step.shape.aspect", 'e', "");
    Interface_Static::Init("step", "read.step.shape.aspect", '&', "enum 0");
    Interface_Static::Init("step", "read.step.shape.aspect", '&', "eval OFF");
    Interface_Static::Init("step", "read.step.shape.aspect", '&', "eval ON");
    Interface_Static::SetCVal("read.step.shape.aspect", "ON");

    Interface_Static::Init("step", "read.step.product.mode", 'e', "");
    Interface_Static::Init("step", "read.step.product.mode", '&', "enum 0");
    Interface_Static::Init("step", "read.step.product.mode", '&', "eval OFF");
    Interface_Static::Init("step", "read.step.product.mode", '&', "eval ON");
    Interface_Static::SetCVal("read.step.product.mode", "ON");

    Interface_Static::Init("step", "read.step.product.context", 'e', "");
    Interface_Static::Init("step", "read.step.product.context", '&', "enum 1");
    Interface_Static::Init("step", "read.step.product.context", '&', "eval all");
    Interface_Static::Init("step", "read.step.product.context", '&', "eval design");
    Interface_Static::Init("step", "read.step.product.context", '&', "eval analysis");
    Interface_Static::SetCVal("read.step.product.context", "all");

    Interface_Static::Init("step", "read.step.assembly.level", 'e', "");
    Interface_Static::Init("step", "read.step.assembly.level", '&', "enum 1");
    Interface_Static::Init("step", "read.step.assembly.level", '&', "eval all");
    Interface_Static::Init("step", "read.step.assembly.level", '&', "eval assembly");
    Interface_Static::Init("step", "read.step.assembly.level", '&', "eval structure");
    Interface_Static::Init("step", "read.step.assembly.level", '&', "eval shape");
    Interface_Static::SetCVal("read.step.assembly.level", "all");

    Interface_Static::Init("step", "write.step.unit", 'e', "");
    Interface_Static::Init("step", "write.step.unit", '&', "enum 1");
    Interface_Static::Init("step", "write.step.unit", '&', "eval INCH");
    Interface_Static::Init("step", "write.step.unit", '&', "eval MM");
    Interface_Static::Init("step", "write.step.unit", '&', "eval ??");
    Interface_Static::Init("step", "write.step.unit", '&', "eval FT");
    Interface_Static::Init("step", "write.step.unit", '&', "eval MI");
    Interface_Static::Init("step", "write.step.unit", '&', "eval M");
    Interface_Static::Init("step", "write.step.unit", '&', "eval KM");
    Interface_Static::Init("step", "write.step.unit", '&', "eval MIL");
    Interface_Static::Init("step", "write.step.unit", '&', "eval UM");
    Interface_Static::Init("step", "write.step.unit", '&', "eval CM");
    Interface_Static::Init("step", "write.step.unit", '&', "eval UIN");
    Interface_Static::SetCVal("write.step.unit", "MM");

    Interface_Static::Init("step", "read.step.nonmanifold", 'e', "");
    Interface_Static::Init("step", "read.step.nonmanifold", '&', "enum 0");
    Interface_Static::Init("step", "read.step.nonmanifold", '&', "eval Off");
    Interface_Static::Init("step", "read.step.nonmanifold", '&', "eval On");
    Interface_Static::SetIVal("read.step.nonmanifold", 0);

    Interface_Static::Init("step", "write.step.nonmanifold", 'e', "");
    Interface_Static::Init("step", "write.step.nonmanifold", '&', "enum 0");
    Interface_Static::Init("step", "write.step.nonmanifold", '&', "eval Off");
    Interface_Static::Init("step", "write.step.nonmanifold", '&', "eval On");
    Interface_Static::SetIVal("write.step.nonmanifold", 0);

    Interface_Static::Init("step", "read.step.ideas", 'e', "");
    Interface_Static::Init("step", "read.step.ideas", '&', "enum 0");
    Interface_Static::Init("step", "read.step.ideas", '&', "eval Off");
    Interface_Static::Init("step", "read.step.ideas", '&', "eval On");
    Interface_Static::SetIVal("read.step.ideas", 0);

    Interface_Static::Init("step", "write.step.vertex.mode", 'e', "");
    Interface_Static::Init("step", "write.step.vertex.mode", '&', "enum 0");
    Interface_Static::Init("step", "write.step.vertex.mode", '&', "eval One Compound");
    Interface_Static::Init("step", "write.step.vertex.mode", '&', "eval Single Vertex");
    Interface_Static::SetIVal("write.step.vertex.mode", 0);

    Interface_Static::Init("XSTEP", "write.step.resource.name", 't', "STEP");
    Interface_Static::Init("XSTEP", "read.step.resource.name", 't', "STEP");
    Interface_Static::Init("XSTEP", "write.step.sequence", 't', "ToSTEP");
    Interface_Static::Init("XSTEP", "read.step.sequence", 't', "FromSTEP");
    Interface_Static::Init("XSTEP", "ToSTEP.exec.op", 't', "SplitCommonVertex,DirectFaces");
    Interface_Static::Init("XSTEP", "FromSTEP.exec.op", 't', "FixShape");
    Interface_Static::Init("XSTEP", "FromSTEP.FixShape.Tolerance3d", 't', "&Runtime.Tolerance");
    Interface_Static::Init("XSTEP",
                           "FromSTEP.FixShape.MaxTolerance3d",
                           't',
                           "&Runtime.MaxTolerance");
    Interface_Static::Init("XSTEP", "FromSTEP.FixShape.MinTolerance3d", 't', "1.e-7");
    Interface_Static::Init("XSTEP", "FromSTEP.FixShape.FixFreeShellMode", 't', "-1");
    Interface_Static::Init("XSTEP", "FromSTEP.FixShape.FixFreeFaceMode", 't', "-1");
    Interface_Static::Init("XSTEP", "FromSTEP.FixShape.FixFreeWireMode", 't', "-1");
    Interface_Static::Init("XSTEP", "FromSTEP.FixShape.FixSameParameterMode", 't', "-1");
    Interface_Static::Init("XSTEP", "FromSTEP.FixShape.FixSolidMode", 't', "-1");
    Interface_Static::Init("XSTEP", "FromSTEP.FixShape.FixShellOrientationMode", 't', "-1");
    Interface_Static::Init("XSTEP", "FromSTEP.FixShape.CreateOpenSolidMode", 't', "0");
    Interface_Static::Init("XSTEP", "FromSTEP.FixShape.FixShellMode", 't', "-1");
    Interface_Static::Init("XSTEP", "FromSTEP.FixShape.FixFaceOrientationMode", 't', "-1");
    Interface_Static::Init("XSTEP", "FromSTEP.FixShape.FixFaceMode", 't', "-1");
    Interface_Static::Init("XSTEP", "FromSTEP.FixShape.FixWireMode", 't', "-1");
    Interface_Static::Init("XSTEP", "FromSTEP.FixShape.FixOrientationMode", 't', "-1");
    Interface_Static::Init("XSTEP", "FromSTEP.FixShape.FixAddNaturalBoundMode", 't', "-1");
    Interface_Static::Init("XSTEP", "FromSTEP.FixShape.FixMissingSeamMode", 't', "-1");
    Interface_Static::Init("XSTEP", "FromSTEP.FixShape.FixSmallAreaWireMode", 't', "-1");
    Interface_Static::Init("XSTEP", "FromSTEP.FixShape.RemoveSmallAreaFaceMode", 't', "-1");
    Interface_Static::Init("XSTEP", "FromSTEP.FixShape.FixIntersectingWiresMode", 't', "-1");
    Interface_Static::Init("XSTEP", "FromSTEP.FixShape.FixLoopWiresMode", 't', "-1");
    Interface_Static::Init("XSTEP", "FromSTEP.FixShape.FixSplitFaceMode", 't', "-1");
    Interface_Static::Init("XSTEP", "FromSTEP.FixShape.AutoCorrectPrecisionMode", 't', "1");
    Interface_Static::Init("XSTEP", "FromSTEP.FixShape.ModifyTopologyMode", 't', "0");
    Interface_Static::Init("XSTEP", "FromSTEP.FixShape.ModifyGeometryMode", 't', "1");
    Interface_Static::Init("XSTEP", "FromSTEP.FixShape.ClosedWireMode", 't', "1");
    Interface_Static::Init("XSTEP", "FromSTEP.FixShape.PreferencePCurveMode", 't', "1");
    Interface_Static::Init("XSTEP", "FromSTEP.FixShape.FixReorderMode", 't', "-1");
    Interface_Static::Init("XSTEP", "FromSTEP.FixShape.FixSmallMode", 't', "-1");
    Interface_Static::Init("XSTEP", "FromSTEP.FixShape.FixConnectedMode", 't', "-1");
    Interface_Static::Init("XSTEP", "FromSTEP.FixShape.FixEdgeCurvesMode", 't', "-1");
    Interface_Static::Init("XSTEP", "FromSTEP.FixShape.FixDegeneratedMode", 't', "-1");
    Interface_Static::Init("XSTEP", "FromSTEP.FixShape.FixLackingMode", 't', "-1");
    Interface_Static::Init("XSTEP", "FromSTEP.FixShape.FixSelfIntersectionMode", 't', "-1");
    Interface_Static::Init("XSTEP", "FromSTEP.FixShape.RemoveLoopMode", 't', "-1");
    Interface_Static::Init("XSTEP", "FromSTEP.FixShape.FixReversed2dMode", 't', "-1");
    Interface_Static::Init("XSTEP", "FromSTEP.FixShape.FixRemovePCurveMode", 't', "-1");
    Interface_Static::Init("XSTEP", "FromSTEP.FixShape.FixRemoveCurve3dMode", 't', "-1");
    Interface_Static::Init("XSTEP", "FromSTEP.FixShape.FixAddPCurveMode", 't', "-1");
    Interface_Static::Init("XSTEP", "FromSTEP.FixShape.FixAddCurve3dMode", 't', "-1");
    Interface_Static::Init("XSTEP", "FromSTEP.FixShape.FixSeamMode", 't', "-1");
    Interface_Static::Init("XSTEP", "FromSTEP.FixShape.FixShiftedMode", 't', "-1");
    Interface_Static::Init("XSTEP", "FromSTEP.FixShape.FixEdgeSameParameterMode", 't', "0");
    Interface_Static::Init("XSTEP", "FromSTEP.FixShape.FixNotchedEdgesMode", 't', "-1");
    Interface_Static::Init("XSTEP", "FromSTEP.FixShape.FixTailMode", 't', "0");
    Interface_Static::Init("XSTEP", "FromSTEP.FixShape.MaxTailAngle", 't', "0.0");
    Interface_Static::Init("XSTEP", "FromSTEP.FixShape.MaxTailWidth", 't', "-1.0");
    Interface_Static::Init("XSTEP", "FromSTEP.FixShape.FixSelfIntersectingEdgeMode", 't', "-1");
    Interface_Static::Init("XSTEP", "FromSTEP.FixShape.FixIntersectingEdgesMode", 't', "-1");
    Interface_Static::Init("XSTEP",
                           "FromSTEP.FixShape.FixNonAdjacentIntersectingEdgesMode",
                           't',
                           "-1");
    Interface_Static::Init("XSTEP", "FromSTEP.FixShape.FixVertexPositionMode", 't', "0");
    Interface_Static::Init("XSTEP", "FromSTEP.FixShape.FixVertexToleranceMode", 't', "-1");
    Interface_Static::Init("XSTEP", "FromSTEP.FixFaceSize.Tolerance", 't', "1.e-7");

    Interface_Static::Init("step", "read.step.all.shapes", 'e', "");
    Interface_Static::Init("step", "read.step.all.shapes", '&', "enum 0");
    Interface_Static::Init("step", "read.step.all.shapes", '&', "eval Off");
    Interface_Static::Init("step", "read.step.all.shapes", '&', "eval On");
    Interface_Static::SetIVal("read.step.all.shapes", 0);

    Interface_Static::Init("step", "read.step.constructivegeom.relationship", 'e', "");
    Interface_Static::Init("step", "read.step.constructivegeom.relationship", '&', "enum 0");
    Interface_Static::Init("step", "read.step.constructivegeom.relationship", '&', "eval OFF");
    Interface_Static::Init("step", "read.step.constructivegeom.relationship", '&', "eval ON");
    Interface_Static::SetCVal("read.step.constructivegeom.relationship", "OFF");

    Interface_Static::Init("step", "read.step.root.transformation", 'e', "");
    Interface_Static::Init("step", "read.step.root.transformation", '&', "enum 0");
    Interface_Static::Init("step", "read.step.root.transformation", '&', "eval OFF");
    Interface_Static::Init("step", "read.step.root.transformation", '&', "eval ON");
    Interface_Static::SetCVal("read.step.root.transformation", "ON");

    Interface_Static::Init("step", "read.step.codepage", 'e', "");
    Interface_Static::Init("step", "read.step.codepage", '&', "enum 0");

    Interface_Static::Init("step", "read.step.codepage", '&', "eval SJIS");
    Interface_Static::Init("step", "read.step.codepage", '&', "eval EUC");
    Interface_Static::Init("step", "read.step.codepage", '&', "eval NoConversion");
    Interface_Static::Init("step", "read.step.codepage", '&', "eval GB");
    Interface_Static::Init("step", "read.step.codepage", '&', "eval UTF8");
    Interface_Static::Init("step", "read.step.codepage", '&', "eval SystemLocale");
    Interface_Static::Init("step", "read.step.codepage", '&', "eval CP1250");
    Interface_Static::Init("step", "read.step.codepage", '&', "eval CP1251");
    Interface_Static::Init("step", "read.step.codepage", '&', "eval CP1252");
    Interface_Static::Init("step", "read.step.codepage", '&', "eval CP1253");
    Interface_Static::Init("step", "read.step.codepage", '&', "eval CP1254");
    Interface_Static::Init("step", "read.step.codepage", '&', "eval CP1255");
    Interface_Static::Init("step", "read.step.codepage", '&', "eval CP1256");
    Interface_Static::Init("step", "read.step.codepage", '&', "eval CP1257");
    Interface_Static::Init("step", "read.step.codepage", '&', "eval CP1258");
    Interface_Static::Init("step", "read.step.codepage", '&', "eval iso8859-1");
    Interface_Static::Init("step", "read.step.codepage", '&', "eval iso8859-2");
    Interface_Static::Init("step", "read.step.codepage", '&', "eval iso8859-3");
    Interface_Static::Init("step", "read.step.codepage", '&', "eval iso8859-4");
    Interface_Static::Init("step", "read.step.codepage", '&', "eval iso8859-5");
    Interface_Static::Init("step", "read.step.codepage", '&', "eval iso8859-6");
    Interface_Static::Init("step", "read.step.codepage", '&', "eval iso8859-7");
    Interface_Static::Init("step", "read.step.codepage", '&', "eval iso8859-8");
    Interface_Static::Init("step", "read.step.codepage", '&', "eval iso8859-9");
    Interface_Static::Init("step", "read.step.codepage", '&', "eval CP850");

    Interface_Static::SetCVal("read.step.codepage", "UTF8");

    Interface_Static::Init("step", "read.step.tessellated", 'e', "");
    Interface_Static::Init("step", "read.step.tessellated", '&', "enum 0");
    Interface_Static::Init("step", "read.step.tessellated", '&', "eval Off");
    Interface_Static::Init("step", "read.step.tessellated", '&', "eval On");
    Interface_Static::Init("step", "read.step.tessellated", '&', "eval OnNoBRep");
    Interface_Static::SetCVal("read.step.tessellated", "On");

    Interface_Static::Init("step", "write.step.tessellated", 'e', "");
    Interface_Static::Init("step", "write.step.tessellated", '&', "enum 0");
    Interface_Static::Init("step", "write.step.tessellated", '&', "eval Off");
    Interface_Static::Init("step", "write.step.tessellated", '&', "eval On");
    Interface_Static::Init("step", "write.step.tessellated", '&', "eval OnNoBRep");
    Interface_Static::SetCVal("write.step.tessellated", "OnNoBRep");

    Standard_STATIC_ASSERT((int)Resource_FormatType_CP850 - (int)Resource_FormatType_CP1250 == 18);

    init = true;
  }

  occ::handle<STEPControl_ActorWrite> ActWrite = new STEPControl_ActorWrite;
  myAdaptorWrite                               = ActWrite;

  occ::handle<StepSelect_WorkLibrary> swl = new StepSelect_WorkLibrary;
  swl->SetDumpLabel(1);
  myAdaptorLibrary  = swl;
  myAdaptorProtocol = STEPEdit::Protocol();

  SetModeWrite(0, 4);
  SetModeWriteHelp(0, "As Is");
  SetModeWriteHelp(1, "Faceted Brep");
  SetModeWriteHelp(2, "Shell Based");
  SetModeWriteHelp(3, "Manifold Solid");
  SetModeWriteHelp(4, "Wireframe");
  TraceStatic("read.surfacecurve.mode", 5);

  DeclareAndCast(IFSelect_Selection, xmr, SessionItem("xst-model-roots"));
  if (!xmr.IsNull())
  {
    occ::handle<IFSelect_Signature> sty = STEPEdit::SignType();
    AddSessionItem(sty, "step-type");
    occ::handle<IFSelect_SignCounter> tys = new IFSelect_SignCounter(sty, false, true);
    AddSessionItem(tys, "step-types");

    AddSessionItem(new IFSelect_SignAncestor(), "xst-derived");

    occ::handle<STEPSelections_SelectDerived> stdvar = new STEPSelections_SelectDerived();
    stdvar->SetProtocol(STEPEdit::Protocol());
    AddSessionItem(stdvar, "step-derived");

    occ::handle<IFSelect_SelectSignature> selsdr = STEPEdit::NewSelectSDR();
    selsdr->SetInput(xmr);
    AddSessionItem(selsdr, "step-shape-def-repr");

    AddSessionItem(STEPEdit::NewSelectPlacedItem(), "step-placed-items");

    AddSessionItem(STEPEdit::NewSelectShapeRepr(), "step-shape-repr");
  }

  occ::handle<STEPSelections_SelectFaces> stfaces = new STEPSelections_SelectFaces;
  stfaces->SetInput(xmr);
  AddSessionItem(stfaces, "step-faces");

  occ::handle<STEPSelections_SelectInstances> stinst = new STEPSelections_SelectInstances;
  AddSessionItem(stinst, "step-instances");

  occ::handle<STEPSelections_SelectGSCurves> stcurves = new STEPSelections_SelectGSCurves;
  stcurves->SetInput(xmr);
  AddSessionItem(stcurves, "step-GS-curves");

  occ::handle<STEPSelections_SelectAssembly> assembly = new STEPSelections_SelectAssembly;
  assembly->SetInput(xmr);
  AddSessionItem(assembly, "step-assembly");

  occ::handle<APIHeaderSection_EditHeader> edhead = new APIHeaderSection_EditHeader;
  occ::handle<IFSelect_EditForm>           edheadf =
    new IFSelect_EditForm(edhead, false, true, "Step Header");
  AddSessionItem(edhead, "step-header-edit");
  AddSessionItem(edheadf, "step-header");

  occ::handle<STEPEdit_EditContext> edctx = new STEPEdit_EditContext;
  occ::handle<IFSelect_EditForm>    edctxf =
    new IFSelect_EditForm(edctx, false, true, "STEP Product Definition Context");
  AddSessionItem(edctx, "step-context-edit");
  AddSessionItem(edctxf, "step-context");

  occ::handle<STEPEdit_EditSDR>  edsdr = new STEPEdit_EditSDR;
  occ::handle<IFSelect_EditForm> edsdrf =
    new IFSelect_EditForm(edsdr, false, true, "STEP Product Data (SDR)");
  AddSessionItem(edsdr, "step-SDR-edit");
  AddSessionItem(edsdrf, "step-SDR-data");
}

occ::handle<Interface_InterfaceModel> STEPControl_Controller::NewModel() const
{
  return STEPEdit::NewModel();
}

occ::handle<Transfer_ActorOfTransientProcess> STEPControl_Controller::ActorRead(
  const occ::handle<Interface_InterfaceModel>& theModel) const
{
  DeclareAndCast(STEPControl_ActorRead, anAdap, myAdaptorRead);
  if (anAdap.IsNull())
  {
    anAdap = new STEPControl_ActorRead(theModel);
    anAdap->SetModel(theModel);
  }
  return anAdap;
}

IFSelect_ReturnStatus STEPControl_Controller::TransferWriteShape(
  const TopoDS_Shape&                          shape,
  const occ::handle<Transfer_FinderProcess>&   FP,
  const occ::handle<Interface_InterfaceModel>& model,
  const int                                    modeshape,
  const Message_ProgressRange&                 theProgress) const
{
  if (modeshape < 0 || modeshape > 4)
    return IFSelect_RetError;
  occ::handle<STEPControl_ActorWrite> ActWrite =
    occ::down_cast<STEPControl_ActorWrite>(myAdaptorWrite);

  occ::handle<StepData_StepModel> aModel = occ::down_cast<StepData_StepModel>(model);
  if (!ActWrite.IsNull())
    ActWrite->SetGroupMode(aModel->InternalParameters.WriteAssembly);
  TopoDS_Shape                                                             aShape = shape;
  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher> aModifedMap;
  if (aModel->InternalParameters.WriteNonmanifold)
  {
    ShapeUpgrade_RemoveLocations aRemLoc;
    aRemLoc.SetRemoveLevel(TopAbs_COMPOUND);
    aRemLoc.Remove(aShape);
    aShape      = aRemLoc.GetResult();
    aModifedMap = aRemLoc.GetModifiedShapesMap();
  }
  const IFSelect_ReturnStatus aStatus =
    XSControl_Controller::TransferWriteShape(aShape, FP, model, modeshape, theProgress);
  XSAlgo_ShapeProcessor::MergeShapeTransferInfo(FP,
                                                aModifedMap,
                                                occ::handle<ShapeExtend_MsgRegistrator>());
  return aStatus;
}

bool STEPControl_Controller::Init()
{
  static bool inic = false;
  if (!inic)
  {
    occ::handle<STEPControl_Controller> STEPCTL = new STEPControl_Controller;
    STEPCTL->AutoRecord();
    XSAlgo::Init();
    inic = true;
  }
  return true;
}

void STEPControl_Controller::Customise(occ::handle<XSControl_WorkSession>& WS)
{
  XSControl_Controller::Customise(WS);

  occ::handle<IFSelect_SelectModelRoots> slr;
  occ::handle<Standard_Transient>        slr1 = WS->NamedItem("xst-model-roots");
  if (!slr1.IsNull())
    slr = occ::down_cast<IFSelect_SelectModelRoots>(slr1);
  else
  {
    slr = new IFSelect_SelectModelRoots;
    WS->AddNamedItem("xst-model-roots", slr);
  }

  occ::handle<STEPSelections_SelectForTransfer> st1 = new STEPSelections_SelectForTransfer;
  st1->SetReader(WS->TransferReader());
  WS->AddNamedItem("xst-transferrable-roots", st1);

  if (!slr.IsNull())
  {
    occ::handle<IFSelect_Signature> sty = STEPEdit::SignType();
    WS->AddNamedItem("step-type", sty);

    occ::handle<IFSelect_SignCounter> tys = new IFSelect_SignCounter(sty, false, true);
    WS->AddNamedItem("step-types", tys);

    WS->SetSignType(sty);

    WS->AddNamedItem("xst-derived", new IFSelect_SignAncestor());
    occ::handle<STEPSelections_SelectDerived> stdvar = new STEPSelections_SelectDerived();
    stdvar->SetProtocol(STEPEdit::Protocol());
    WS->AddNamedItem("step-derived", stdvar);

    occ::handle<IFSelect_SelectSignature> selsdr = STEPEdit::NewSelectSDR();
    selsdr->SetInput(slr);
    WS->AddNamedItem("step-shape-def-repr", selsdr);
    occ::handle<IFSelect_SelectSignature> selrrs = STEPEdit::NewSelectPlacedItem();
    WS->AddNamedItem("step-placed-items", selrrs);
    occ::handle<IFSelect_SelectSignature> selsr = STEPEdit::NewSelectShapeRepr();

    WS->AddNamedItem("step-shape-repr", selsr);
  }

  occ::handle<STEPSelections_SelectFaces> stfaces = new STEPSelections_SelectFaces;
  stfaces->SetInput(slr);
  WS->AddNamedItem("step-faces", stfaces);

  occ::handle<STEPSelections_SelectInstances> stinst = new STEPSelections_SelectInstances;
  WS->AddNamedItem("step-instances", stinst);

  occ::handle<STEPSelections_SelectGSCurves> stcurves = new STEPSelections_SelectGSCurves;
  stcurves->SetInput(slr);
  WS->AddNamedItem("step-GS-curves", stcurves);

  occ::handle<STEPSelections_SelectAssembly> assembly = new STEPSelections_SelectAssembly;
  assembly->SetInput(slr);
  WS->AddNamedItem("step-assembly", assembly);

  occ::handle<APIHeaderSection_EditHeader> edhead = new APIHeaderSection_EditHeader;
  occ::handle<IFSelect_EditForm>           edheadf =
    new IFSelect_EditForm(edhead, false, true, "Step Header");
  WS->AddNamedItem("step-header-edit", edhead);
  WS->AddNamedItem("step-header", edheadf);

  occ::handle<STEPEdit_EditContext> edctx = new STEPEdit_EditContext;
  occ::handle<IFSelect_EditForm>    edctxf =
    new IFSelect_EditForm(edctx, false, true, "STEP Product Definition Context");
  WS->AddNamedItem("step-context-edit", edctx);
  WS->AddNamedItem("step-context", edctxf);

  occ::handle<STEPEdit_EditSDR>  edsdr = new STEPEdit_EditSDR;
  occ::handle<IFSelect_EditForm> edsdrf =
    new IFSelect_EditForm(edsdr, false, true, "STEP Product Data (SDR)");
  WS->AddNamedItem("step-SDR-edit", edsdr);
  WS->AddNamedItem("step-SDR-data", edsdrf);
}

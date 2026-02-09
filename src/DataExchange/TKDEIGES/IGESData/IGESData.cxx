

#include <IGESData.hpp>
#include <IGESData_DefaultGeneral.hpp>
#include <IGESData_DefaultSpecific.hpp>
#include <IGESData_IGESModel.hpp>
#include <IGESData_Protocol.hpp>
#include <Interface_InterfaceModel.hpp>
#include <Interface_Static.hpp>
#include <Interface_Version.hpp>
#include <OSD_Process.hpp>
#include <Quantity_Date.hpp>
#include <Standard_Integer.hpp>
#include <Standard_Real.hpp>
#include <TCollection_HAsciiString.hpp>

#include <cstdio>
static occ::handle<IGESData_Protocol> proto;

static occ::handle<IGESData_DefaultGeneral>  stmod;
static occ::handle<IGESData_DefaultSpecific> speci;

void IGESData::Init()
{
  if (proto.IsNull())
    proto = new IGESData_Protocol;
  if (stmod.IsNull())
    stmod = new IGESData_DefaultGeneral;
  if (speci.IsNull())
    speci = new IGESData_DefaultSpecific;

  if (Interface_InterfaceModel::HasTemplate("iges"))
    return;

  OSD_Process process;

  Interface_Static::Standards();

  Interface_Static::Init("XSTEP", "read.iges.bspline.approxd1.mode", 'e', "");
  Interface_Static::Init("XSTEP", "read.iges.bspline.approxd1.mode", '&', "ematch 0");
  Interface_Static::Init("XSTEP", "read.iges.bspline.approxd1.mode", '&', "eval Off");
  Interface_Static::Init("XSTEP", "read.iges.bspline.approxd1.mode", '&', "eval On");
  Interface_Static::SetIVal("read.iges.bspline.approxd1.mode", 0);

  Interface_Static::Init("XSTEP", "read.iges.bspline.continuity", 'i', "1");
  Interface_Static::Init("XSTEP", "read.iges.bspline.continuity", '&', "imin 0");
  Interface_Static::Init("XSTEP", "read.iges.bspline.continuity", '&', "imax 2");

  Interface_Static::Init("XSTEP", "write.iges.header.receiver", 't', "");
  Interface_Static::Init("XSTEP", "write.iges.header.author", 't', process.UserName().ToCString());
  Interface_Static::Init("XSTEP", "write.iges.header.company", 't', "");

  Interface_Static::Init("XSTEP", "write.iges.unit", 'e', "");
  Interface_Static::Init("XSTEP", "write.iges.unit", '&', "enum 1");
  Interface_Static::Init("XSTEP", "write.iges.unit", '&', "eval INCH");
  Interface_Static::Init("XSTEP", "write.iges.unit", '&', "eval MM");
  Interface_Static::Init("XSTEP", "write.iges.unit", '&', "eval ??");
  Interface_Static::Init("XSTEP", "write.iges.unit", '&', "eval FT");
  Interface_Static::Init("XSTEP", "write.iges.unit", '&', "eval MI");
  Interface_Static::Init("XSTEP", "write.iges.unit", '&', "eval M");
  Interface_Static::Init("XSTEP", "write.iges.unit", '&', "eval KM");
  Interface_Static::Init("XSTEP", "write.iges.unit", '&', "eval MIL");
  Interface_Static::Init("XSTEP", "write.iges.unit", '&', "eval UM");
  Interface_Static::Init("XSTEP", "write.iges.unit", '&', "eval CM");
  Interface_Static::Init("XSTEP", "write.iges.unit", '&', "eval UIN");
  Interface_Static::SetCVal("write.iges.unit", "MM");

  Interface_Static::Init("XSTEP", "write.iges.brep.mode", 'e', "");
  Interface_Static::Init("XSTEP", "write.iges.brep.mode", '&', "ematch 0");
  Interface_Static::Init("XSTEP", "write.iges.brep.mode", '&', "eval Faces");
  Interface_Static::Init("XSTEP", "write.iges.brep.mode", '&', "eval BRep");
  Interface_Static::SetIVal("write.iges.brep.mode", 0);

  Interface_Static::Init("XSTEP", "write.convertsurface.mode", 'e', "");
  Interface_Static::Init("XSTEP", "write.convertsurface.mode", '&', "ematch 0");
  Interface_Static::Init("XSTEP", "write.convertsurface.mode", '&', "eval Off");
  Interface_Static::Init("XSTEP", "write.convertsurface.mode", '&', "eval On");
  Interface_Static::SetIVal("write.convertsurface.mode", 0);

  Interface_Static::Init("XSTEP", "write.iges.resource.name", 't', "IGES");
  Interface_Static::Init("XSTEP", "read.iges.resource.name", 't', "IGES");
  Interface_Static::Init("XSTEP", "write.iges.sequence", 't', "ToIGES");
  Interface_Static::Init("XSTEP", "read.iges.sequence", 't', "FromIGES");
  Interface_Static::Init("XSTEP", "ToIGES.exec.op", 't', "DirectFaces");
  Interface_Static::Init("XSTEP", "FromIGES.exec.op", 't', "FixShape");
  Interface_Static::Init("XSTEP", "FromIGES.FixShape.Tolerance3d", 't', "&Runtime.Tolerance");
  Interface_Static::Init("XSTEP", "FromIGES.FixShape.MaxTolerance3d", 't', "&Runtime.MaxTolerance");
  Interface_Static::Init("XSTEP", "FromIGES.FixShape.MinTolerance3d", 't', "1.e-7");
  Interface_Static::Init("XSTEP", "FromIGES.FixShape.FixFreeShellMode", 't', "-1");
  Interface_Static::Init("XSTEP", "FromIGES.FixShape.FixFreeFaceMode", 't', "-1");
  Interface_Static::Init("XSTEP", "FromIGES.FixShape.FixFreeWireMode", 't', "-1");
  Interface_Static::Init("XSTEP", "FromIGES.FixShape.FixSameParameterMode", 't', "-1");
  Interface_Static::Init("XSTEP", "FromIGES.FixShape.FixSolidMode", 't', "-1");
  Interface_Static::Init("XSTEP", "FromIGES.FixShape.FixShellOrientationMode", 't', "-1");
  Interface_Static::Init("XSTEP", "FromIGES.FixShape.CreateOpenSolidMode", 't', "1");
  Interface_Static::Init("XSTEP", "FromIGES.FixShape.FixShellMode", 't', "-1");
  Interface_Static::Init("XSTEP", "FromIGES.FixShape.FixFaceOrientationMode", 't', "-1");
  Interface_Static::Init("XSTEP", "FromIGES.FixShape.FixFaceMode", 't', "-1");
  Interface_Static::Init("XSTEP", "FromIGES.FixShape.FixWireMode", 't', "-1");
  Interface_Static::Init("XSTEP", "FromIGES.FixShape.FixOrientationMode", 't', "-1");
  Interface_Static::Init("XSTEP", "FromIGES.FixShape.FixAddNaturalBoundMode", 't', "-1");
  Interface_Static::Init("XSTEP", "FromIGES.FixShape.FixMissingSeamMode", 't', "-1");
  Interface_Static::Init("XSTEP", "FromIGES.FixShape.FixSmallAreaWireMode", 't', "-1");
  Interface_Static::Init("XSTEP", "FromIGES.FixShape.RemoveSmallAreaFaceMode", 't', "-1");
  Interface_Static::Init("XSTEP", "FromIGES.FixShape.FixIntersectingWiresMode", 't', "-1");
  Interface_Static::Init("XSTEP", "FromIGES.FixShape.FixLoopWiresMode", 't', "-1");
  Interface_Static::Init("XSTEP", "FromIGES.FixShape.FixSplitFaceMode", 't', "-1");
  Interface_Static::Init("XSTEP", "FromIGES.FixShape.AutoCorrectPrecisionMode", 't', "1");
  Interface_Static::Init("XSTEP", "FromIGES.FixShape.ModifyTopologyMode", 't', "0");
  Interface_Static::Init("XSTEP", "FromIGES.FixShape.ModifyGeometryMode", 't', "1");
  Interface_Static::Init("XSTEP", "FromIGES.FixShape.ClosedWireMode", 't', "1");
  Interface_Static::Init("XSTEP", "FromIGES.FixShape.PreferencePCurveMode", 't', "1");
  Interface_Static::Init("XSTEP", "FromIGES.FixShape.FixReorderMode", 't', "-1");
  Interface_Static::Init("XSTEP", "FromIGES.FixShape.FixSmallMode", 't', "-1");
  Interface_Static::Init("XSTEP", "FromIGES.FixShape.FixConnectedMode", 't', "-1");
  Interface_Static::Init("XSTEP", "FromIGES.FixShape.FixEdgeCurvesMode", 't', "-1");
  Interface_Static::Init("XSTEP", "FromIGES.FixShape.FixDegeneratedMode", 't', "-1");
  Interface_Static::Init("XSTEP", "FromIGES.FixShape.FixLackingMode", 't', "-1");
  Interface_Static::Init("XSTEP", "FromIGES.FixShape.FixSelfIntersectionMode", 't', "-1");
  Interface_Static::Init("XSTEP", "FromIGES.FixShape.RemoveLoopMode", 't', "-1");
  Interface_Static::Init("XSTEP", "FromIGES.FixShape.FixReversed2dMode", 't', "-1");
  Interface_Static::Init("XSTEP", "FromIGES.FixShape.FixRemovePCurveMode", 't', "-1");
  Interface_Static::Init("XSTEP", "FromIGES.FixShape.FixRemoveCurve3dMode", 't', "-1");
  Interface_Static::Init("XSTEP", "FromIGES.FixShape.FixAddPCurveMode", 't', "-1");
  Interface_Static::Init("XSTEP", "FromIGES.FixShape.FixAddCurve3dMode", 't', "-1");
  Interface_Static::Init("XSTEP", "FromIGES.FixShape.FixSeamMode", 't', "-1");
  Interface_Static::Init("XSTEP", "FromIGES.FixShape.FixShiftedMode", 't', "-1");
  Interface_Static::Init("XSTEP", "FromIGES.FixShape.FixEdgeSameParameterMode", 't', "0");
  Interface_Static::Init("XSTEP", "FromIGES.FixShape.FixNotchedEdgesMode", 't', "-1");
  Interface_Static::Init("XSTEP", "FromIGES.FixShape.FixTailMode", 't', "0");
  Interface_Static::Init("XSTEP", "FromIGES.FixShape.MaxTailAngle", 't', "0.0");
  Interface_Static::Init("XSTEP", "FromIGES.FixShape.MaxTailWidth", 't', "-1.0");
  Interface_Static::Init("XSTEP", "FromIGES.FixShape.FixSelfIntersectingEdgeMode", 't', "-1");
  Interface_Static::Init("XSTEP", "FromIGES.FixShape.FixIntersectingEdgesMode", 't', "-1");
  Interface_Static::Init("XSTEP",
                         "FromIGES.FixShape.FixNonAdjacentIntersectingEdgesMode",
                         't',
                         "-1");
  Interface_Static::Init("XSTEP", "FromIGES.FixShape.FixVertexPositionMode", 't', "0");
  Interface_Static::Init("XSTEP", "FromIGES.FixShape.FixVertexToleranceMode", 't', "-1");

  Interface_Static::Init("XSTEP", "read.iges.onlyvisible", 'e', "");
  Interface_Static::Init("XSTEP", "read.iges.onlyvisible", '&', "ematch 0");
  Interface_Static::Init("XSTEP", "read.iges.onlyvisible", '&', "eval Off");
  Interface_Static::Init("XSTEP", "read.iges.onlyvisible", '&', "eval On");
  Interface_Static::SetIVal("read.iges.onlyvisible", 0);

  Interface_Static::Init("XSTEP", "read.iges.faulty.entities", 'e', "");
  Interface_Static::Init("XSTEP", "read.iges.faulty.entities", '&', "ematch 0");
  Interface_Static::Init("XSTEP", "read.iges.faulty.entities", '&', "eval Off");
  Interface_Static::Init("XSTEP", "read.iges.faulty.entities", '&', "eval On");
  Interface_Static::SetIVal("read.iges.faulty.entities", 0);

  Interface_Static::Init("XSTEP", "write.iges.plane.mode", 'e', "");
  Interface_Static::Init("XSTEP", "write.iges.plane.mode", '&', "ematch 0");
  Interface_Static::Init("XSTEP", "write.iges.plane.mode", '&', "eval Plane");
  Interface_Static::Init("XSTEP", "write.iges.plane.mode", '&', "eval BSpline");
  Interface_Static::SetIVal("write.iges.plane.mode", 0);

  Interface_Static::Init("XSTEP", "write.iges.offset.mode", 'e', "");
  Interface_Static::Init("XSTEP", "write.iges.offset.mode", '&', "ematch 0");
  Interface_Static::Init("XSTEP", "write.iges.offset.mode", '&', "eval On");
  Interface_Static::Init("XSTEP", "write.iges.offset.mode", '&', "eval Off");
  Interface_Static::SetIVal("write.iges.offset.mode", 0);

  IGESData_GlobalSection GS;

  char procver[80];
  Sprintf(procver, XSTEP_PROCESSOR_VERSION, "IGES");
  occ::handle<TCollection_HAsciiString> gsys = new TCollection_HAsciiString(procver);
  Interface_Static::Init("XSTEP", "write.iges.header.product", 't', procver);

  int           year;
  OSD_Process   system;
  Quantity_Date ladate = system.SystemDate();
  year                 = ladate.Year();
  occ::handle<TCollection_HAsciiString> datestr;
  if (year < 2000)

    datestr = IGESData_GlobalSection::NewDateString(0, 0, 0, 0, 0, 0, 0);
  else

    datestr = IGESData_GlobalSection::NewDateString(0, 0, 0, 0, 0, 0, -1);
  GS.SetSeparator(',');
  GS.SetEndMark(';');
  GS.SetSendName(new TCollection_HAsciiString(Interface_Static::CVal("write.iges.header.product")));
  GS.SetFileName(new TCollection_HAsciiString("Filename.iges"));

  GS.SetSystemId(new TCollection_HAsciiString(XSTEP_SYSTEM_VERSION));

  GS.SetInterfaceVersion(gsys);
  GS.SetIntegerBits(IntegerSize());
  GS.SetMaxPower10Single(RealLast10Exp());
  GS.SetMaxDigitsSingle(RealDigits());
  GS.SetMaxPower10Double(RealLast10Exp());
  GS.SetMaxDigitsDouble(RealDigits());
  GS.SetReceiveName(Interface_Static::Static("write.iges.header.receiver")->HStringValue());

  GS.SetScale(1.0);
  GS.SetUnitFlag(Interface_Static::IVal("write.iges.unit"));
  GS.SetUnitName(new TCollection_HAsciiString(Interface_Static::CVal("write.iges.unit")));
  GS.SetLineWeightGrad(1);
  GS.SetMaxLineWeight(0.01);
  GS.SetDate(datestr);
  GS.SetResolution(0.0001);
  GS.SetMaxCoord(0.0);
  GS.SetAuthorName(Interface_Static::Static("write.iges.header.author")->HStringValue());

  GS.SetCompanyName(Interface_Static::Static("write.iges.header.company")->HStringValue());

  GS.SetIGESVersion(11);
  GS.SetDraftingStandard(0);
  GS.SetLastChangeDate(datestr);
  GS.SetApplicationProtocol(new TCollection_HAsciiString(""));

  occ::handle<IGESData_IGESModel> model = new IGESData_IGESModel;
  model->SetGlobalSection(GS);
  Interface_InterfaceModel::SetTemplate("iges", model);
}

occ::handle<IGESData_Protocol> IGESData::Protocol()
{
  return proto;
}

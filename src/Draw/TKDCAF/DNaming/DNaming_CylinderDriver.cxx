#include <BRepAdaptor_Curve.hpp>
#include <BRepCheck_Analyzer.hpp>
#include <BRepPrimAPI_MakeCylinder.hpp>
#include <DNaming.hpp>
#include <DNaming_CylinderDriver.hpp>
#include <gp_Lin.hpp>
#include <ModelDefinitions.hpp>
#include <Standard_Real.hpp>
#include <Standard_Type.hpp>
#include <TDataStd_Integer.hpp>
#include <TDataStd_Real.hpp>
#include <TDF_Label.hpp>
#include <TFunction_Function.hpp>
#include <TFunction_Logbook.hpp>
#include <TNaming.hpp>
#include <TNaming_Builder.hpp>
#include <TNaming_NamedShape.hpp>
#include <TopExp.hpp>
#include <TopExp_Explorer.hpp>
#include <TopLoc_Location.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Solid.hpp>

IMPLEMENT_STANDARD_RTTIEXT(DNaming_CylinderDriver, TFunction_Driver)

DNaming_CylinderDriver::DNaming_CylinderDriver() = default;

void DNaming_CylinderDriver::Validate(occ::handle<TFunction_Logbook>&) const {}

bool DNaming_CylinderDriver::MustExecute(const occ::handle<TFunction_Logbook>&) const
{
  return true;
}

int DNaming_CylinderDriver::Execute(occ::handle<TFunction_Logbook>& theLog) const
{
  occ::handle<TFunction_Function> aFunction;
  Label().FindAttribute(TFunction_Function::GetID(), aFunction);
  if (aFunction.IsNull())
    return -1;

  double                           aRadius  = DNaming::GetReal(aFunction, CYL_RADIUS)->Get();
  double                           aHeight  = DNaming::GetReal(aFunction, CYL_HEIGHT)->Get();
  occ::handle<TDataStd_UAttribute> anObject = DNaming::GetObjectArg(aFunction, CYL_AXIS);
  occ::handle<TNaming_NamedShape>  aNSAxis  = DNaming::GetObjectValue(anObject);
  if (aNSAxis->IsEmpty())
  {
#ifdef OCCT_DEBUG
    std::cout << "CylinderDriver:: Axis is empty" << std::endl;
#endif
    aFunction->SetFailure(WRONG_AXIS);
    return -1;
  }
  TopoDS_Shape aTopoDSAxis = aNSAxis->Get();
  if (aTopoDSAxis.IsNull())
  {
#ifdef OCCT_DEBUG
    std::cout << "CylinderDriver:: Axis is null" << std::endl;
#endif
    aFunction->SetFailure(WRONG_AXIS);
    return -1;
  }

  if (aTopoDSAxis.ShapeType() != TopAbs_EDGE && aTopoDSAxis.ShapeType() != TopAbs_WIRE)
  {
#ifdef OCCT_DEBUG
    std::cout << "CylinderDriver:: Wrong axis, ShapeType = " << aTopoDSAxis.ShapeType()
              << std::endl;
#endif
    aFunction->SetFailure(WRONG_AXIS);
    return -1;
  }

  gp_Ax2 anAxis;
  if (aTopoDSAxis.ShapeType() == TopAbs_WIRE)
  {
    TopExp_Explorer anExplorer(aTopoDSAxis, TopAbs_EDGE);
    aTopoDSAxis = anExplorer.Current();
  }

  BRepAdaptor_Curve aCurveAda(TopoDS::Edge(aTopoDSAxis));
  if (aCurveAda.GetType() == GeomAbs_Line)
  {
    gp_Lin aLin = aCurveAda.Line();
    anAxis      = gp_Ax2(aLin.Location(), aLin.Direction());
    if (!aTopoDSAxis.Infinite())
    {
      TopoDS_Vertex V1, V2;
      TopExp::Vertices(TopoDS::Edge(aTopoDSAxis), V1, V2);
      gp_Pnt aP1 = BRep_Tool::Pnt(V1);
      anAxis.SetLocation(aP1);
    }
  }
  else
  {
#ifdef OCCT_DEBUG
    std::cout << "CylinderDriver:: I don't support wires for a while" << std::endl;
#endif
    aFunction->SetFailure(WRONG_AXIS);
    return -1;
  }

  occ::handle<TNaming_NamedShape> aPrevCyl = DNaming::GetFunctionResult(aFunction);

  TopLoc_Location aLocation;
  if (!aPrevCyl.IsNull() && !aPrevCyl->IsEmpty())
  {
    aLocation = aPrevCyl->Get().Location();
  }

  BRepPrimAPI_MakeCylinder aMakeCylinder(anAxis, aRadius, aHeight);
  aMakeCylinder.Build();
  if (!aMakeCylinder.IsDone())
  {
    aFunction->SetFailure(ALGO_FAILED);
    return -1;
  }

  TopoDS_Shape       aResult = aMakeCylinder.Solid();
  BRepCheck_Analyzer aCheck(aResult);
  if (!aCheck.IsValid(aResult))
  {
    aFunction->SetFailure(RESULT_NOT_VALID);
    return -1;
  }

  LoadNamingDS(RESPOSITION(aFunction), aMakeCylinder);

  if (!aLocation.IsIdentity())
    TNaming::Displace(RESPOSITION(aFunction), aLocation, true);

  theLog->SetValid(RESPOSITION(aFunction), true);
  aFunction->SetFailure(DONE);
  return 0;
}

void DNaming_CylinderDriver::LoadNamingDS(const TDF_Label&          theResultLabel,
                                          BRepPrimAPI_MakeCylinder& MS) const
{
  TNaming_Builder Builder(theResultLabel);
  Builder.Generated(MS.Solid());

  BRepPrim_Cylinder& S = MS.Cylinder();

  if (S.HasBottom())
  {
    TopoDS_Face     BottomFace = S.BottomFace();
    TNaming_Builder BOF(theResultLabel.FindChild(1, true));
    BOF.Generated(BottomFace);
  }

  if (S.HasTop())
  {
    TopoDS_Face     TopFace = S.TopFace();
    TNaming_Builder TOF(theResultLabel.FindChild(2, true));
    TOF.Generated(TopFace);
  }

  TopoDS_Face     LateralFace = S.LateralFace();
  TNaming_Builder LOF(theResultLabel.FindChild(3, true));
  LOF.Generated(LateralFace);

  if (S.HasSides())
  {
    TopoDS_Face     StartFace = S.StartFace();
    TNaming_Builder SF(theResultLabel.FindChild(4, true));
    SF.Generated(StartFace);
    TopoDS_Face     EndFace = S.EndFace();
    TNaming_Builder EF(theResultLabel.FindChild(5, true));
    EF.Generated(EndFace);
  }
}

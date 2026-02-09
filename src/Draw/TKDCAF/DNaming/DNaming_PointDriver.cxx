#include <BRep_Tool.hpp>
#include <BRepBuilderAPI_MakeVertex.hpp>
#include <DNaming.hpp>
#include <DNaming_PointDriver.hpp>
#include <gp_Pnt.hpp>
#include <ModelDefinitions.hpp>
#include <Standard_Type.hpp>
#include <TDataStd_Real.hpp>
#include <TDF_Label.hpp>
#include <TFunction_Function.hpp>
#include <TFunction_Logbook.hpp>
#include <TNaming.hpp>
#include <TNaming_Builder.hpp>
#include <TNaming_NamedShape.hpp>
#include <TopLoc_Location.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDS_Vertex.hpp>

IMPLEMENT_STANDARD_RTTIEXT(DNaming_PointDriver, TFunction_Driver)

DNaming_PointDriver::DNaming_PointDriver() = default;

void DNaming_PointDriver::Validate(occ::handle<TFunction_Logbook>&) const {}

bool DNaming_PointDriver::MustExecute(const occ::handle<TFunction_Logbook>&) const
{
  return true;
}

int DNaming_PointDriver::Execute(occ::handle<TFunction_Logbook>& theLog) const
{
  occ::handle<TFunction_Function> aFunction;
  Label().FindAttribute(TFunction_Function::GetID(), aFunction);
  if (aFunction.IsNull())
    return -1;

  double aDX = DNaming::GetReal(aFunction, PNT_DX)->Get();
  double aDY = DNaming::GetReal(aFunction, PNT_DY)->Get();
  double aDZ = DNaming::GetReal(aFunction, PNT_DZ)->Get();

  occ::handle<TNaming_NamedShape> aPrevPnt = DNaming::GetFunctionResult(aFunction);

  TopLoc_Location aLocation;
  if (!aPrevPnt.IsNull() && !aPrevPnt->IsEmpty())
  {
    aLocation = aPrevPnt->Get().Location();
  }
  gp_Pnt aPoint;
  if (aFunction->GetDriverGUID() == PNTRLT_GUID)
  {
    occ::handle<TDataStd_UAttribute> aRefPnt   = DNaming::GetObjectArg(aFunction, PNTRLT_REF);
    occ::handle<TNaming_NamedShape>  aRefPntNS = DNaming::GetObjectValue(aRefPnt);
    if (aRefPntNS.IsNull() || aRefPntNS->IsEmpty())
    {
#ifdef OCCT_DEBUG
      std::cout << "PointDriver:: Ref Point is empty" << std::endl;
#endif
      aFunction->SetFailure(WRONG_ARGUMENT);
      return -1;
    }
    TopoDS_Shape  aRefPntShape = aRefPntNS->Get();
    TopoDS_Vertex aVertex      = TopoDS::Vertex(aRefPntShape);
    aPoint                     = BRep_Tool::Pnt(aVertex);
    aPoint.SetX(aPoint.X() + aDX);
    aPoint.SetY(aPoint.Y() + aDY);
    aPoint.SetZ(aPoint.Z() + aDZ);
  }
  else
    aPoint = gp_Pnt(aDX, aDY, aDZ);

  BRepBuilderAPI_MakeVertex aMakeVertex(aPoint);

  if (!aMakeVertex.IsDone())
  {
    aFunction->SetFailure(ALGO_FAILED);
    return -1;
  }

  const TDF_Label& aResultLabel = RESPOSITION(aFunction);
  TNaming_Builder  aBuilder(aResultLabel);
  aBuilder.Generated(aMakeVertex.Shape());

  if (!aLocation.IsIdentity())
    TNaming::Displace(aResultLabel, aLocation, true);

  theLog->SetValid(aResultLabel, true);

  aFunction->SetFailure(DONE);
  return 0;
}

#include <BRepCheck_Analyzer.hpp>
#include <BRepPrimAPI_MakeBox.hpp>
#include <DNaming.hpp>
#include <DNaming_BoxDriver.hpp>
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
#include <TopLoc_Location.hpp>
#include <TopoDS_Solid.hpp>

IMPLEMENT_STANDARD_RTTIEXT(DNaming_BoxDriver, TFunction_Driver)

//=================================================================================================

DNaming_BoxDriver::DNaming_BoxDriver() = default;

//=======================================================================
// function : Validate
// purpose  : Validates labels of a function in <log>.
//=======================================================================
void DNaming_BoxDriver::Validate(occ::handle<TFunction_Logbook>&) const {}

//=======================================================================
// function : MustExecute
// purpose  : Analyse in <log> if the loaded function must be executed
//=======================================================================
bool DNaming_BoxDriver::MustExecute(const occ::handle<TFunction_Logbook>&) const
{
  return true;
}

//=======================================================================
// function : Execute
// purpose  : Execute the function and push in <log> the impacted labels
//=======================================================================
int DNaming_BoxDriver::Execute(occ::handle<TFunction_Logbook>& theLog) const
{
  occ::handle<TFunction_Function> aFunction;
  Label().FindAttribute(TFunction_Function::GetID(), aFunction);
  if (aFunction.IsNull())
    return -1;

  // perform calculations

  double aDX = DNaming::GetReal(aFunction, BOX_DX)->Get();
  double aDY = DNaming::GetReal(aFunction, BOX_DY)->Get();
  double aDZ = DNaming::GetReal(aFunction, BOX_DZ)->Get();

  occ::handle<TNaming_NamedShape> aPrevBox = DNaming::GetFunctionResult(aFunction);
  // Save location
  TopLoc_Location aLocation;
  if (!aPrevBox.IsNull() && !aPrevBox->IsEmpty())
  {
    aLocation = aPrevBox->Get().Location();
  }
  BRepPrimAPI_MakeBox aMakeBox(aDX, aDY, aDZ);
  aMakeBox.Build();
  if (!aMakeBox.IsDone())
  {
    aFunction->SetFailure(ALGO_FAILED);
    return -1;
  }

  TopoDS_Shape       aResult = aMakeBox.Solid();
  BRepCheck_Analyzer aCheck(aResult);
  if (!aCheck.IsValid(aResult))
  {
    aFunction->SetFailure(RESULT_NOT_VALID);
    return -1;
  }

  // Naming
  LoadNamingDS(RESPOSITION(aFunction), aMakeBox);

  // restore location
  if (!aLocation.IsIdentity())
    TNaming::Displace(RESPOSITION(aFunction), aLocation, true);

  theLog->SetValid(RESPOSITION(aFunction), true);

  aFunction->SetFailure(DONE);
  return 0;
}

//=================================================================================================

void DNaming_BoxDriver::LoadNamingDS(const TDF_Label& theResultLabel, BRepPrimAPI_MakeBox& MS) const
{
  TNaming_Builder Builder(theResultLabel);
  Builder.Generated(MS.Solid());

  // Load the faces of the box :
  TopoDS_Face     BottomFace = MS.BottomFace();
  TNaming_Builder BOF(theResultLabel.FindChild(1, true));
  BOF.Generated(BottomFace);

  TopoDS_Face     TopFace = MS.TopFace();
  TNaming_Builder TF(theResultLabel.FindChild(2, true));
  TF.Generated(TopFace);

  TopoDS_Face     FrontFace = MS.FrontFace();
  TNaming_Builder FF(theResultLabel.FindChild(3, true));
  FF.Generated(FrontFace);

  TopoDS_Face     RightFace = MS.RightFace();
  TNaming_Builder RF(theResultLabel.FindChild(4, true));
  RF.Generated(RightFace);

  TopoDS_Face     BackFace = MS.BackFace();
  TNaming_Builder BF(theResultLabel.FindChild(5, true));
  BF.Generated(BackFace);

  TopoDS_Face     LeftFace = MS.LeftFace();
  TNaming_Builder LF(theResultLabel.FindChild(6, true));
  LF.Generated(LeftFace);
}

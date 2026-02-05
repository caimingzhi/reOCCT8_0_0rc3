#include <BRepAlgo.hpp>
#include <BRepFilletAPI_MakeFillet.hpp>
#include <DNaming.hpp>
#include <DNaming_FilletDriver.hpp>
#include <ModelDefinitions.hpp>
#include <Precision.hpp>
#include <Standard_Real.hpp>
#include <Standard_Type.hpp>
#include <TDataStd_Integer.hpp>
#include <TDataStd_Real.hpp>
#include <TDF_Label.hpp>
#include <TFunction_Function.hpp>
#include <TFunction_Logbook.hpp>
#include <TNaming_Builder.hpp>
#include <TNaming_NamedShape.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Shape.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <NCollection_List.hpp>
#include <NCollection_Map.hpp>

IMPLEMENT_STANDARD_RTTIEXT(DNaming_FilletDriver, TFunction_Driver)

//=================================================================================================

DNaming_FilletDriver::DNaming_FilletDriver() = default;

//=======================================================================
// function : Validate
// purpose  : Validates labels of a function in <log>.
//=======================================================================
void DNaming_FilletDriver::Validate(occ::handle<TFunction_Logbook>&) const {}

//=======================================================================
// function : MustExecute
// purpose  : Analyse in <log> if the loaded function must be executed
//=======================================================================
bool DNaming_FilletDriver::MustExecute(const occ::handle<TFunction_Logbook>&) const
{
  return true;
}

//=======================================================================
// function : Execute
// purpose  : Execute the function and push in <log> the impacted labels
//=======================================================================
int DNaming_FilletDriver::Execute(occ::handle<TFunction_Logbook>& theLog) const
{
  occ::handle<TFunction_Function> aFunction;
  Label().FindAttribute(TFunction_Function::GetID(), aFunction);
  if (aFunction.IsNull())
    return -1;

  occ::handle<TFunction_Function> aPrevFun = DNaming::GetPrevFunction(aFunction);
  if (aPrevFun.IsNull())
    return -1;
  const TDF_Label&                aLab = RESPOSITION(aPrevFun);
  occ::handle<TNaming_NamedShape> aContextNS;
  aLab.FindAttribute(TNaming_NamedShape::GetID(), aContextNS);
  if (aContextNS.IsNull() || aContextNS->IsEmpty())
  {
#ifdef OCCT_DEBUG
    std::cout << "FilletDriver:: Context is empty" << std::endl;
#endif
    aFunction->SetFailure(WRONG_ARGUMENT);
    return -1;
  }

  const double             aRadius = DNaming::GetReal(aFunction, FILLET_RADIUS)->Get();
  const ChFi3d_FilletShape aSurfaceType =
    (ChFi3d_FilletShape)DNaming::GetInteger(aFunction, FILLET_SURFTYPE)->Get();

  if (aRadius < Precision::Confusion())
  {
    aFunction->SetFailure(WRONG_ARGUMENT);
#ifdef OCCT_DEBUG
    std::cout << "FilletDriver:: Radius < Precision::Confusion" << std::endl;
#endif
    return -1;
  }

  occ::handle<TDataStd_UAttribute> aPathObj = DNaming::GetObjectArg(aFunction, FILLET_PATH);
  occ::handle<TNaming_NamedShape>  aPathNS  = DNaming::GetObjectValue(aPathObj);
  if (aPathNS.IsNull() || aPathNS->IsEmpty())
  {
#ifdef OCCT_DEBUG
    std::cout << "FilletDriver:: Path is empty" << std::endl;
#endif
    aFunction->SetFailure(WRONG_ARGUMENT);
    return -1;
  }

  TopoDS_Shape aPATH    = aPathNS->Get();
  TopoDS_Shape aCONTEXT = aContextNS->Get();
  if (aPATH.IsNull() || aCONTEXT.IsNull())
  {
#ifdef OCCT_DEBUG
    std::cout << "FilletDriver:: Path or Context is null" << std::endl;
#endif
    aFunction->SetFailure(WRONG_ARGUMENT);
    return -1;
  }

  TopExp_Explorer                                        expl;
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> View;

  BRepFilletAPI_MakeFillet aMkFillet(aCONTEXT, aSurfaceType);

  if (aPATH.ShapeType() != TopAbs_EDGE && aPATH.ShapeType() != TopAbs_FACE)
  {
    aFunction->SetFailure(WRONG_ARGUMENT);
    return -1;
  }

  if (aPATH.ShapeType() == TopAbs_FACE)
  {
    for (expl.Init(aPATH, TopAbs_EDGE); expl.More(); expl.Next())
    {
      const TopoDS_Edge& anEdge = TopoDS::Edge(expl.Current());
      if (!View.Add(anEdge))
        continue;
      else
        aMkFillet.Add(aRadius, anEdge); // Edge
    }
  }
  else
  {
    const TopoDS_Edge& anEdge = TopoDS::Edge(aPATH);
    aMkFillet.Add(aRadius, anEdge); // Edge
  }

  aMkFillet.Build();

  if (!aMkFillet.IsDone())
  {
    aFunction->SetFailure(ALGO_FAILED);
    return -1;
  }
  NCollection_List<TopoDS_Shape> aLarg;
  aLarg.Append(aCONTEXT);
  if (!BRepAlgo::IsValid(aLarg, aMkFillet.Shape(), false, false))
  {
    aFunction->SetFailure(RESULT_NOT_VALID);
    return -1;
  }

  // Naming
  LoadNamingDS(RESPOSITION(aFunction), aMkFillet, aCONTEXT);

  theLog->SetValid(RESPOSITION(aFunction), true);
  aFunction->SetFailure(DONE);
  return 0;
}

//=================================================================================================

void DNaming_FilletDriver::LoadNamingDS(const TDF_Label&          theResultLabel,
                                        BRepFilletAPI_MakeFillet& theMkFillet,
                                        const TopoDS_Shape&       theContext) const
{
  TNaming_Builder aBuilder(theResultLabel);
  TopoDS_Shape    aResult = theMkFillet.Shape();

  if (aResult.ShapeType() == TopAbs_COMPOUND)
  {
    if (aResult.NbChildren() == 1)
    {
      TopoDS_Iterator itr(aResult);
      if (itr.More())
        aResult = itr.Value();
    }
  }
  if (aResult.IsNull())
    aBuilder.Generated(aResult);
  else
    aBuilder.Modify(theContext, aResult);

  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher> SubShapes;
  for (TopExp_Explorer Exp(aResult, TopAbs_FACE); Exp.More(); Exp.Next())
  {
    SubShapes.Bind(Exp.Current(), Exp.Current());
  }

  // New faces generated from edges
  TNaming_Builder anEdgeBuilder(theResultLabel.FindChild(1, true));
  DNaming::LoadAndOrientGeneratedShapes(theMkFillet,
                                        theContext,
                                        TopAbs_EDGE,
                                        anEdgeBuilder,
                                        SubShapes);

  // Faces of the initial shape modified by theMkFillet
  TNaming_Builder aFacesBuilder(theResultLabel.FindChild(2, true));
  DNaming::LoadAndOrientModifiedShapes(theMkFillet,
                                       theContext,
                                       TopAbs_FACE,
                                       aFacesBuilder,
                                       SubShapes);

  // New faces generated from vertices (if exist)
  TNaming_Builder aVFacesBuilder(theResultLabel.FindChild(3, true));
  DNaming::LoadAndOrientGeneratedShapes(theMkFillet,
                                        theContext,
                                        TopAbs_VERTEX,
                                        aVFacesBuilder,
                                        SubShapes);

  // Deleted faces of the initial shape
  TNaming_Builder aDelBuilder(theResultLabel.FindChild(4, true));
  DNaming::LoadDeletedShapes(theMkFillet, theContext, TopAbs_FACE, aDelBuilder);
}

#include <BRep_Builder.hpp>
#include <BRep_Tool.hpp>
#include <BRepAlgo.hpp>
#include <BRepBuilderAPI_MakeEdge.hpp>
#include <BRepBuilderAPI_MakeWire.hpp>
#include <DNaming.hpp>
#include <DNaming_Line3DDriver.hpp>
#include <gp_Pnt.hpp>
#include <ModelDefinitions.hpp>
#include <Precision.hpp>
#include <Standard_Type.hpp>
#include <TDataStd_Integer.hpp>
#include <TDataStd_Name.hpp>
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
#include <TopoDS_Shape.hpp>
#include <TopoDS_Vertex.hpp>
#include <TopoDS_Wire.hpp>
#include <NCollection_Array1.hpp>

IMPLEMENT_STANDARD_RTTIEXT(DNaming_Line3DDriver, TFunction_Driver)

DNaming_Line3DDriver::DNaming_Line3DDriver() = default;

void DNaming_Line3DDriver::Validate(occ::handle<TFunction_Logbook>&) const {}

bool DNaming_Line3DDriver::MustExecute(const occ::handle<TFunction_Logbook>&) const
{
  return true;
}

int DNaming_Line3DDriver::Execute(occ::handle<TFunction_Logbook>& theLog) const
{
  occ::handle<TFunction_Function> aFunction;
  Label().FindAttribute(TFunction_Function::GetID(), aFunction);
  if (aFunction.IsNull())
    return -1;

  aFunction->SetFailure(NOTDONE);
  occ::handle<TNaming_NamedShape> aPrevILine3D = DNaming::GetFunctionResult(aFunction);

  TopLoc_Location aLocation;
  if (!aPrevILine3D.IsNull() && !aPrevILine3D->IsEmpty())
  {
    aLocation = aPrevILine3D->Get().Location();
  }

  const int aType    = DNaming::GetInteger(aFunction, LINE3D_TYPE)->Get();
  bool      isClosed = (aType != 0);
  int       aCounter(0), aLength = DNaming::GetInteger(aFunction, LINE3D_PNTNB)->Get();
  if (aLength < 2)
  {
    aFunction->SetFailure(WRONG_ARGUMENT);
    return -1;
  }

  occ::handle<TNaming_NamedShape> aNS1, aNS2;
  BRepBuilderAPI_MakeWire         aMakeWire;
  TopoDS_Wire                     aWire;
  TopoDS_Shape                    aShape1, aShape2;

  NCollection_Array1<TopoDS_Shape> anArV(1, aLength);
  for (aCounter = 1; aCounter <= aLength - 1; aCounter++)
  {
    occ::handle<TDataStd_UAttribute> aRefP1 =
      DNaming::GetObjectArg(aFunction, (LINE3D_TYPE + aCounter));
    aNS1 = DNaming::GetObjectValue(aRefP1);
    occ::handle<TDataStd_UAttribute> aRefP2 =
      DNaming::GetObjectArg(aFunction, (LINE3D_TYPE + aCounter + 1));
    aNS2 = DNaming::GetObjectValue(aRefP2);
#ifdef OCCT_DEBUG
    if (!aNS1->IsEmpty())
    {
      aShape1                = aNS1->Get();
      const gp_Pnt aDebPoint = BRep_Tool::Pnt(TopoDS::Vertex(aShape1));
      (void)aDebPoint;
    }
    else
      std::cout << " Line3DDriver:: NS1 is empty" << std::endl;
    if (!aNS2->IsEmpty())
    {
      aShape2                = aNS2->Get();
      const gp_Pnt aDebPoint = BRep_Tool::Pnt(TopoDS::Vertex(aShape2));
      (void)aDebPoint;
    }
    else
      std::cout << " Line3DDriver:: NS2 is empty" << std::endl;
#endif
    if (aNS1->IsEmpty() || aNS2->IsEmpty() || aNS1->Get().IsNull() || aNS2->Get().IsNull())
    {
      aFunction->SetFailure(WRONG_ARGUMENT);
      return -1;
    }
    aShape1 = aNS1->Get();
    aShape2 = aNS2->Get();
#ifdef OCCT_DEBUG
    const gp_Pnt aDebPoint1 = BRep_Tool::Pnt(TopoDS::Vertex(aShape1));
    const gp_Pnt aDebPoint2 = BRep_Tool::Pnt(TopoDS::Vertex(aShape2));

    (void)aDebPoint1;
    (void)aDebPoint2;
#endif
    if (aShape1.ShapeType() != TopAbs_VERTEX || aShape2.ShapeType() != TopAbs_VERTEX)
    {
      aFunction->SetFailure(WRONG_ARGUMENT);
      return -1;
    }
    BRepBuilderAPI_MakeEdge aMakeEdge(TopoDS::Vertex(aShape1), TopoDS::Vertex(aShape2));
    if (aMakeEdge.IsDone())
    {
      anArV.SetValue(aCounter, aShape1);
      anArV.SetValue(aCounter + 1, aShape2);
      aMakeWire.Add(aMakeEdge.Edge());
    }
  }

  if (isClosed)
  {
    occ::handle<TDataStd_UAttribute> aRefP1 = DNaming::GetObjectArg(aFunction, (LINE3D_TYPE + 1));
    aNS1                                    = DNaming::GetObjectValue(aRefP1);
    aShape1                                 = aNS1->Get();
    BRepBuilderAPI_MakeEdge aMakeEdge(TopoDS::Vertex(aShape2), TopoDS::Vertex(aShape1));
    if (aMakeEdge.IsDone())
      aMakeWire.Add(aMakeEdge.Edge());
  }
  if (aMakeWire.IsDone())
    aWire = aMakeWire.Wire();

  if (aWire.IsNull())
  {
    aFunction->SetFailure(ALGO_FAILED);
    return -1;
  }

  if (!BRepAlgo::IsValid(aWire))
  {
    aFunction->SetFailure(RESULT_NOT_VALID);
    return -1;
  }

  TDF_Label aResultLabel = RESPOSITION(aFunction);
  try
  {
    LoadNamingDS(aResultLabel, aWire, anArV, isClosed);
  }
  catch (Standard_Failure const&)
  {
    aFunction->SetFailure(NAMING_FAILED);
    return -1;
  }

  if (!aLocation.IsIdentity())
    TNaming::Displace(aResultLabel, aLocation, true);

  theLog->SetValid(aResultLabel, true);

  aFunction->SetFailure(DONE);
  return 0;
}

void DNaming_Line3DDriver::LoadNamingDS(const TDF_Label&                        theResultLabel,
                                        const TopoDS_Wire&                      theWire,
                                        const NCollection_Array1<TopoDS_Shape>& theArV,
                                        const bool                              isClosed) const
{
  if (theWire.IsNull())
    return;

  TNaming_Builder aWBuilder(theResultLabel);
  aWBuilder.Generated(theWire);
#ifdef OCCT_DEBUG
  TDataStd_Name::Set(theResultLabel, "Line3DCurve");
#endif
  int aLength = theArV.Length();
  if (aLength < 2)
    return;
  TopoDS_Shape                     aShape;
  NCollection_Array1<TopoDS_Shape> anArE(1, aLength);
  TopoDS_Vertex                    aFirst, aLast;
  for (int i = 1; i < aLength; i++)
  {
    gp_Pnt          aP1    = BRep_Tool::Pnt(TopoDS::Vertex(theArV.Value(i)));
    gp_Pnt          aP2    = BRep_Tool::Pnt(TopoDS::Vertex(theArV.Value(i + 1)));
    bool            aFound = false;
    TopExp_Explorer anExp(theWire, TopAbs_EDGE);
    for (; anExp.More(); anExp.Next())
    {
      const TopoDS_Edge& anE = TopoDS::Edge(anExp.Current());
      TopoDS_Vertex      aV, aV1, aV2;
      TopExp::Vertices(anE, aV1, aV2);
      gp_Pnt aPE1 = BRep_Tool::Pnt(aV1);
      gp_Pnt aPE2 = BRep_Tool::Pnt(aV2);
      if (aP1.IsEqual(aPE1, Precision::Confusion()) && aP2.IsEqual(aPE2, Precision::Confusion()))
      {
        anArE.SetValue(i, anE);
        aFound = true;
        break;
      }
    }
    if (!aFound)
      anArE.SetValue(i, aShape);
    else
      aFound = false;
  }
  if (isClosed)
  {
    bool            aFound = false;
    gp_Pnt          aP1    = BRep_Tool::Pnt(TopoDS::Vertex(theArV.Value(aLength)));
    gp_Pnt          aP2    = BRep_Tool::Pnt(TopoDS::Vertex(theArV.Value(1)));
    TopExp_Explorer anExp(theWire, TopAbs_EDGE);
    for (; anExp.More(); anExp.Next())
    {
      const TopoDS_Edge& anE = TopoDS::Edge(anExp.Current());
      TopoDS_Vertex      aV, aV1, aV2;
      TopExp::Vertices(anE, aV1, aV2);
      gp_Pnt aPE1 = BRep_Tool::Pnt(aV1);
      gp_Pnt aPE2 = BRep_Tool::Pnt(aV2);
      if (aP1.IsEqual(aPE1, Precision::Confusion()) && aP2.IsEqual(aPE2, Precision::Confusion()))
      {
        anArE.SetValue(aLength, anE);
        aFound = true;

        aFirst = aV2;
        aLast  = aV1;
        break;
      }
    }
    if (!aFound)
      anArE.SetValue(aLength, aShape);
  }
  else
  {

    anArE.SetValue(aLength, aShape);
    TopExp::Vertices(theWire, aFirst, aLast);
  }

  for (int i1 = 1; i1 <= aLength; i1++)
  {
    TDF_Label aLab = theResultLabel.FindChild(i1);
    if (!anArE.Value(i1).IsNull())
    {
      TNaming_Builder aBuilder(aLab);
      aBuilder.Generated(anArE.Value(i1));
    }
    else
    {
      occ::handle<TNaming_NamedShape> aNS;
      if (aLab.FindAttribute(TNaming_NamedShape::GetID(), aNS))
        TNaming_Builder aB(aLab);
    }
  }

  TDF_Label aLab1 = theResultLabel.FindChild(aLength + 1);
  TDF_Label aLab2 = theResultLabel.FindChild(aLength + 2);
  if (!aFirst.IsNull())
  {
    TNaming_Builder aBuilder(aLab1);
    aBuilder.Generated(aFirst);
  }
  else
  {
    occ::handle<TNaming_NamedShape> aNS;
    if (aLab1.FindAttribute(TNaming_NamedShape::GetID(), aNS))
      TNaming_Builder aB(aLab1);
  }
  if (!aLast.IsNull())
  {
    TNaming_Builder aBuilder(aLab2);
    aBuilder.Generated(aLast);
  }
  else
  {
    occ::handle<TNaming_NamedShape> aNS;
    if (aLab2.FindAttribute(TNaming_NamedShape::GetID(), aNS))
      TNaming_Builder aB(aLab2);
  }
}

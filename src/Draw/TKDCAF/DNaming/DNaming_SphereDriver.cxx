#include <BRepAlgo.hpp>
#include <BRepPrimAPI_MakeSphere.hpp>
#include <DNaming.hpp>
#include <DNaming_SphereDriver.hpp>
#include <gp_Ax2.hpp>
#include <gp_Dir.hpp>
#include <gp_Pnt.hpp>
#include <ModelDefinitions.hpp>
#include <Standard_Type.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_List.hpp>
#include <TDataStd_Integer.hpp>
#include <TDataStd_Real.hpp>
#include <TDataStd_UAttribute.hpp>
#include <TDF_Label.hpp>
#include <TFunction_Function.hpp>
#include <TFunction_Logbook.hpp>
#include <TNaming.hpp>
#include <TNaming_Builder.hpp>
#include <TNaming_NamedShape.hpp>
#include <TopExp.hpp>
#include <TopLoc_Location.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Iterator.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDS_Solid.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedMap.hpp>

IMPLEMENT_STANDARD_RTTIEXT(DNaming_SphereDriver, TFunction_Driver)

//=================================================================================================

DNaming_SphereDriver::DNaming_SphereDriver() = default;

//=======================================================================
// function : Validate
// purpose  : Validates labels of a function in <theLog>
//=======================================================================
void DNaming_SphereDriver::Validate(occ::handle<TFunction_Logbook>&) const {}

//=======================================================================
// function : MustExecute
// purpose  : Analyses in <theLog> if the loaded function must be executed
//=======================================================================
bool DNaming_SphereDriver::MustExecute(const occ::handle<TFunction_Logbook>&) const
{
  return true;
}

//=================================================================================================

int DNaming_SphereDriver::Execute(occ::handle<TFunction_Logbook>& theLog) const
{
  occ::handle<TFunction_Function> aFunction;
  Label().FindAttribute(TFunction_Function::GetID(), aFunction);
  if (aFunction.IsNull())
    return -1;

  double                           aRadius  = DNaming::GetReal(aFunction, SPHERE_RADIUS)->Get();
  occ::handle<TDataStd_UAttribute> anObject = DNaming::GetObjectArg(aFunction, SPHERE_CENTER);
  occ::handle<TNaming_NamedShape>  aNSCnt   = DNaming::GetObjectValue(anObject);
  if (aNSCnt.IsNull() || aNSCnt->IsEmpty())
  {
#ifdef OCCT_DEBUG
    std::cout << "SphereDriver:: Center point is null or empty" << std::endl;
#endif
    aFunction->SetFailure(WRONG_ARGUMENT);
    return -1;
  }

  occ::handle<TNaming_NamedShape> aPrevSphere = DNaming::GetFunctionResult(aFunction);

  // Save location
  TopLoc_Location aLocation;
  if (!aPrevSphere.IsNull() && !aPrevSphere->IsEmpty())
  {
    aLocation = aPrevSphere->Get().Location();
  }

  TopoDS_Shape aCntShape = aNSCnt->Get();
  if (aCntShape.IsNull())
  {
#ifdef OCCT_DEBUG
    std::cout << "SphereDriver:: Center point is null" << std::endl;
#endif
    aFunction->SetFailure(WRONG_ARGUMENT);
    return -1;
  }
  gp_Pnt aCenter = gp_Pnt(0., 0., 0.);
  if (aCntShape.ShapeType() == TopAbs_VERTEX)
  {
    aCenter = BRep_Tool::Pnt(TopoDS::Vertex(aCntShape));
  }
  gp_Ax2                 anAxis = gp_Ax2(aCenter, gp_Dir(gp_Dir::D::Z), gp_Dir(gp_Dir::D::X));
  BRepPrimAPI_MakeSphere aMakeSphere(anAxis, aRadius);

  aMakeSphere.Build();
  if (!aMakeSphere.IsDone())
  {
    aFunction->SetFailure(ALGO_FAILED);
    return -1;
  }

  TopoDS_Shape aResult = aMakeSphere.Solid();
  if (!BRepAlgo::IsValid(aResult))
  {
    aFunction->SetFailure(RESULT_NOT_VALID);
    return -1;
  }

  // Naming
  LoadNamingDS(RESPOSITION(aFunction), aMakeSphere);
  // restore location
  if (!aLocation.IsIdentity())
    TNaming::Displace(RESPOSITION(aFunction), aLocation, true);

  theLog->SetValid(RESPOSITION(aFunction), true);
  aFunction->SetFailure(DONE);
  return 0;
}

//=================================================================================================

void DNaming_SphereDriver::LoadNamingDS(const TDF_Label&        theResultLabel,
                                        BRepPrimAPI_MakeSphere& MS) const
{

  occ::handle<TDF_TagSource> Tagger = TDF_TagSource::Set(theResultLabel);
  if (Tagger.IsNull())
    return;
  Tagger->Set(0);

  TNaming_Builder Builder(theResultLabel);
  Builder.Generated(MS.Solid());

  BRepPrim_Sphere& S = MS.Sphere();

  // Load faces of the Sph :
  if (S.HasBottom())
  {
    TopoDS_Face     BottomFace = S.BottomFace();
    TNaming_Builder BOF(theResultLabel.NewChild());
    BOF.Generated(BottomFace);
  }

  if (S.HasTop())
  {
    TopoDS_Face     TopFace = S.TopFace();
    TNaming_Builder TOF(theResultLabel.NewChild());
    TOF.Generated(TopFace);
  }

  TopoDS_Face     LateralFace = S.LateralFace();
  TNaming_Builder LOF(theResultLabel.NewChild());
  LOF.Generated(LateralFace);

  if (S.HasSides())
  {
    TopoDS_Face     StartFace = S.StartFace();
    TNaming_Builder SF(theResultLabel.NewChild());
    SF.Generated(StartFace);
    TopoDS_Face     EndFace = S.EndFace();
    TNaming_Builder EF(theResultLabel.NewChild());
    EF.Generated(EndFace);
  }
  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> LateralEdges;
  TopExp::MapShapes(LateralFace, TopAbs_EDGE, LateralEdges);
  int                   i = 1;
  NCollection_List<int> goodEdges;
  for (; i <= LateralEdges.Extent(); i++)
    if (!BRep_Tool::Degenerated(TopoDS::Edge(LateralEdges.FindKey(i))))
      goodEdges.Append(i);

  if (goodEdges.Extent() == 1)
  {
    const TopoDS_Edge& aLateralEdge = TopoDS::Edge(LateralEdges.FindKey(goodEdges.First()));
    TNaming_Builder    MeridianBuilder(theResultLabel.NewChild());
    MeridianBuilder.Generated(aLateralEdge);
    TopoDS_Iterator it(aLateralEdge);
    for (; it.More(); it.Next())
    {
      // const TopoDS_Shape& aV = it.Value();
      TNaming_Builder aVBuilder(theResultLabel.NewChild());
      aVBuilder.Generated(it.Value());
    }
  }
}

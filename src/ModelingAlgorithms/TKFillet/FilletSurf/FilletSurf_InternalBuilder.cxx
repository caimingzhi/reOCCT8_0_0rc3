

#include <FilletSurf_InternalBuilder.hpp>

#include <Adaptor3d_TopolTool.hpp>
#include <BRep_Tool.hpp>
#include <BRepAdaptor_Curve2d.hpp>
#include <BRepAdaptor_Surface.hpp>
#include <BRepBlend_ConstRad.hpp>
#include <BRepBlend_ConstRadInv.hpp>
#include <BRepBlend_Line.hpp>
#include <BRepExtrema_DistShapeShape.hpp>
#include <ChFi3d_Builder_0.hpp>
#include <ChFi3d_FilBuilder.hpp>
#include <ChFiDS_CircSection.hpp>
#include <ChFiDS_CommonPoint.hpp>
#include <ChFiDS_FaceInterference.hpp>
#include <ChFiDS_FilSpine.hpp>
#include <ChFiDS_SurfData.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <ChFiDS_ElSpine.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <ChFiDS_Spine.hpp>
#include <ChFiDS_Stripe.hpp>
#include <ElSLib.hpp>
#include <FilletSurf_StatusType.hpp>
#include <Geom2d_Curve.hpp>
#include <Geom_Circle.hpp>
#include <Geom_Curve.hpp>
#include <Geom_Plane.hpp>
#include <Geom_Surface.hpp>
#include <Geom_TrimmedCurve.hpp>
#include <GeomAbs_Shape.hpp>
#include <GeomAdaptor_Surface.hpp>
#include <gp_Circ.hpp>
#include <gp_Pln.hpp>
#include <IntCurveSurface_HInter.hpp>
#include <IntCurveSurface_IntersectionPoint.hpp>
#include <Standard_ConstructionError.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Shape.hpp>
#include <TopOpeBRepDS_HDataStructure.hpp>

static bool isinlist(const TopoDS_Shape& E, const NCollection_List<TopoDS_Shape>& L)
{
  NCollection_List<TopoDS_Shape>::Iterator It;
  for (It.Initialize(L); It.More(); It.Next())
  {
    if (E.IsSame(It.Value()))
      return true;
  }
  return false;
}

static bool IntPlanEdge(occ::handle<BRepAdaptor_Curve>& Ed,
                        const gp_Pln&                   P,
                        double&                         w,
                        const double                    tol3d)
{
  bool                             done = false;
  double                           f    = Ed->FirstParameter();
  double                           l    = Ed->LastParameter();
  gp_Pnt                           Or   = P.Location();
  occ::handle<Geom_Plane>          Pln  = new Geom_Plane(P);
  occ::handle<GeomAdaptor_Surface> Plan = new GeomAdaptor_Surface(GeomAdaptor_Surface(Pln));

  IntCurveSurface_HInter            Intersection;
  int                               nbp, iip;
  IntCurveSurface_IntersectionPoint IP;
  double                            dist = RealLast();

  Intersection.Perform(Ed, Plan);

  if (Intersection.IsDone())
  {
    nbp = Intersection.NbPoints();
    for (iip = 1; iip <= nbp; iip++)
    {
      IP          = Intersection.Point(iip);
      gp_Pnt pint = IP.Pnt();
      double d    = pint.Distance(Or);
      if (d < dist)
      {
        done = true;
        w    = IP.W();
        dist = d;
      }
    }
  }
  gp_Pnt pdeb = Ed->Value(f);
  gp_Pnt pfin = Ed->Value(l);
  double u, v;

  ElSLib::Parameters(P, pdeb, u, v);
  gp_Pnt projdeb  = ElSLib::Value(u, v, P);
  double dprojdeb = pdeb.Distance(projdeb);
  if (dprojdeb < tol3d)
  {
    double d = pdeb.Distance(Or);
    if (d < dist)
    {
      done = true;
      w    = f;
      dist = d;
    }
  }
  ElSLib::Parameters(P, pfin, u, v);
  gp_Pnt projfin  = ElSLib::Value(u, v, P);
  double dprojfin = pfin.Distance(projfin);
  if (dprojfin < tol3d)
  {
    double d = pfin.Distance(Or);
    if (d < dist)
    {
      done = true;
      w    = l;
      dist = d;
    }
  }
  return done;
}

static bool ComputeEdgeParameter(const occ::handle<ChFiDS_Spine>& Spine,
                                 const int                        ind,
                                 const double                     pelsp,
                                 double&                          ped,
                                 const double                     tol3d)
{
  occ::handle<ChFiDS_ElSpine> Guide = Spine->ElSpine(ind);
  gp_Pnt                      P;
  gp_Vec                      V;
  Guide->D1(pelsp, P, V);
  gp_Pln                         pln(P, V);
  occ::handle<BRepAdaptor_Curve> ed = new BRepAdaptor_Curve(Spine->CurrentElementarySpine(ind));
  return IntPlanEdge(ed, pln, ped, tol3d);
}

FilletSurf_InternalBuilder::FilletSurf_InternalBuilder(const TopoDS_Shape&      S,
                                                       const ChFi3d_FilletShape FShape,
                                                       const double             Ta,
                                                       const double             Tapp3d,
                                                       const double             Tapp2d)
    : ChFi3d_FilBuilder(S, FShape, Ta)
{
  SetParams(Ta, Tapp3d, Tapp2d, Tapp3d, Tapp2d, 1.e-3);
  SetContinuity(GeomAbs_C2, Ta);
}

int FilletSurf_InternalBuilder::Add(const NCollection_List<TopoDS_Shape>& E, const double R)
{
  if (E.IsEmpty())
    return 1;
  NCollection_List<TopoDS_Shape>::Iterator It;
  for (It.Initialize(E); It.More(); It.Next())
  {
    TopoDS_Edge cured = TopoDS::Edge(It.Value());
    if (cured.IsNull())
      return 4;
    if (!myEFMap.Contains(cured))
      return 4;

    TopoDS_Face ff1, ff2;
    for (It.Initialize(myEFMap(cured)); It.More(); It.Next())
    {
      if (ff1.IsNull())
      {
        ff1 = TopoDS::Face(It.Value());
      }
      else
      {
        ff2 = TopoDS::Face(It.Value());
        if (!ff2.IsSame(ff1))
        {
          break;
        }
      }
    }
    if (ff1.IsNull() || ff2.IsNull())
      return 5;
    if (ff1.IsSame(ff2))
      return 5;
    if (BRep_Tool::Continuity(cured, ff1, ff2) != GeomAbs_C0)
      return 5;
  }
  TopoDS_Edge ed = TopoDS::Edge(E.First());
  ed.Orientation(TopAbs_FORWARD);
  ChFi3d_FilBuilder::Add(R, ed);
  occ::handle<ChFiDS_Stripe> st       = myListStripe.First();
  occ::handle<ChFiDS_Spine>& sp       = st->ChangeSpine();
  bool                       periodic = sp->IsPeriodic();

  for (It.Initialize(E); It.More(); It.Next())
  {
    TopoDS_Edge cured = TopoDS::Edge(It.Value());
    if (!Contains(cured))
      return 2;
  }

  occ::handle<ChFiDS_FilSpine> newsp              = new ChFiDS_FilSpine();
  bool                         debut              = false;
  int                          premierquinyestpas = 0;
  int                          yatrou             = 0;
  for (int i = 1; i <= sp->NbEdges(); i++)
  {
    TopoDS_Edge cured = sp->Edges(i);
    if (isinlist(cured, E))
    {
      debut = true;
      if (premierquinyestpas)
      {
        yatrou = 1;
        break;
      }
      newsp->SetEdges(cured);
    }
    else if (debut && !premierquinyestpas)
      premierquinyestpas = i;
  }
  if (!periodic && yatrou)
    return 2;
  if (periodic && yatrou)
  {
    bool vraitrou = false, aLocalDebut = false;
    for (int i = sp->NbEdges(); i > yatrou; i--)
    {
      TopoDS_Edge cured = sp->Edges(i);
      if (isinlist(cured, E))
      {
        if (vraitrou)
          return 2;
        newsp->PutInFirst(cured);
      }
      else if (aLocalDebut)
        vraitrou = true;
      aLocalDebut = true;
    }
  }

  if (newsp->NbEdges() != sp->NbEdges())
  {
    newsp->Load();
    newsp->SetRadius(R);
    sp = newsp;
  }

  occ::handle<ChFiDS_ElSpine> hels = new ChFiDS_ElSpine();
  gp_Vec                      TFirst, TLast;
  gp_Pnt                      PFirst, PLast;
  sp->D1(sp->FirstParameter(), PFirst, TFirst);
  sp->D1(sp->LastParameter(), PLast, TLast);
  hels->FirstParameter(sp->FirstParameter());
  hels->SetFirstPointAndTgt(PFirst, TFirst);
  hels->LastParameter(sp->LastParameter());
  hels->SetLastPointAndTgt(PLast, TLast);
  ChFi3d_PerformElSpine(hels, sp, myConti, tolesp);
  sp->AppendElSpine(hels);
  sp->SplitDone(true);
  return 0;
}

void FilletSurf_InternalBuilder::Perform()
{

  occ::handle<ChFiDS_Stripe>                                        Stripe = myListStripe.First();
  occ::handle<NCollection_HSequence<occ::handle<ChFiDS_SurfData>>>& HData =
    Stripe->ChangeSetOfSurfData();
  HData                            = new NCollection_HSequence<occ::handle<ChFiDS_SurfData>>();
  occ::handle<ChFiDS_Spine>& Spine = Stripe->ChangeSpine();
  TopAbs_Orientation         RefOr1, RefOr2;
  int                        RefChoix;
  StripeOrientations(Spine, RefOr1, RefOr2, RefChoix);
  Stripe->OrientationOnFace1(RefOr1);
  Stripe->OrientationOnFace2(RefOr2);
  Stripe->Choix(RefChoix);
  PerformSetOfKGen(Stripe, false);
}

bool FilletSurf_InternalBuilder::PerformSurf(
  NCollection_Sequence<occ::handle<ChFiDS_SurfData>>& SeqData,
  const occ::handle<ChFiDS_ElSpine>&                  Guide,
  const occ::handle<ChFiDS_Spine>&                    Spine,
  const int                                           Choix,
  const occ::handle<BRepAdaptor_Surface>&             S1,
  const occ::handle<Adaptor3d_TopolTool>&             I1,
  const occ::handle<BRepAdaptor_Surface>&             S2,
  const occ::handle<Adaptor3d_TopolTool>&             I2,
  const double                                        MaxStep,
  const double                                        Fleche,
  const double                                        TolGuide,
  double&                                             First,
  double&                                             Last,
  const bool                                          Inside,
  const bool                                          Appro,
  const bool                                          Forward,
  const bool                                          RecOnS1,
  const bool                                          RecOnS2,
  const math_Vector&                                  Soldep,
  int&                                                Intf,
  int&                                                Intl)
{
  occ::handle<ChFiDS_SurfData> Data = SeqData(1);
  occ::handle<ChFiDS_FilSpine> fsp  = occ::down_cast<ChFiDS_FilSpine>(Spine);
  if (fsp.IsNull())
    throw Standard_ConstructionError("PerformSurf : this is not the spine of a fillet");
  occ::handle<BRepBlend_Line> lin;
  TopAbs_Orientation          Or = S1->Face().Orientation();
  if (!fsp->IsConstant())
    throw Standard_ConstructionError("PerformSurf : no variable radiuses");

  occ::handle<ChFiDS_ElSpine> EmptyGuide;

  BRepBlend_ConstRad    Func(S1, S2, Guide);
  BRepBlend_ConstRadInv FInv(S1, S2, Guide);
  Func.Set(fsp->Radius(), Choix);
  FInv.Set(fsp->Radius(), Choix);
  switch (GetFilletShape())
  {
    case ChFi3d_Rational:
      Func.Set(BlendFunc_Rational);
      break;
    case ChFi3d_QuasiAngular:
      Func.Set(BlendFunc_QuasiAngular);
      break;
    case ChFi3d_Polynomial:
      Func.Set(BlendFunc_Polynomial);
  }
  double PFirst = First;
  done          = SimulData(Data,
                   Guide,
                   EmptyGuide,
                   lin,
                   S1,
                   I1,
                   S2,
                   I2,
                   Func,
                   FInv,
                   PFirst,
                   MaxStep,
                   Fleche,
                   TolGuide,
                   First,
                   Last,
                   Inside,
                   Appro,
                   Forward,
                   Soldep,
                   20,
                   RecOnS1,
                   RecOnS2);
  if (!done)
    return false;
  if (lin->StartPointOnFirst().NbPointOnRst() != 0)
  {
    ChFi3d_FilCommonPoint(lin->StartPointOnFirst(),
                          lin->TransitionOnS1(),
                          true,
                          Data->ChangeVertexFirstOnS1(),
                          tolapp3d);
  }
  if (lin->EndPointOnFirst().NbPointOnRst() != 0)
  {
    ChFi3d_FilCommonPoint(lin->EndPointOnFirst(),
                          lin->TransitionOnS1(),
                          false,
                          Data->ChangeVertexLastOnS1(),
                          tolapp3d);
  }
  if (lin->StartPointOnSecond().NbPointOnRst() != 0)
  {
    ChFi3d_FilCommonPoint(lin->StartPointOnSecond(),
                          lin->TransitionOnS2(),
                          true,
                          Data->ChangeVertexFirstOnS2(),
                          tolapp3d);
  }
  if (lin->EndPointOnSecond().NbPointOnRst() != 0)
  {
    ChFi3d_FilCommonPoint(lin->EndPointOnSecond(),
                          lin->TransitionOnS2(),
                          false,
                          Data->ChangeVertexLastOnS2(),
                          tolapp3d);
  }
  done = CompleteData(Data, Func, lin, S1, S2, Or, false, false, false, false);
  if (!done)
    throw Standard_Failure("PerformSurf : Failed approximation!");

  bool ok = false;
  if (!Forward)
  {
    Intf                           = 0;
    const ChFiDS_CommonPoint& cpf1 = Data->VertexFirstOnS1();
    if (cpf1.IsOnArc())
    {
      TopoDS_Face F1 = S1->Face();
      TopoDS_Face bid;
      Intf = !SearchFace(Spine, cpf1, F1, bid);
      ok   = Intf != 0;
    }
    const ChFiDS_CommonPoint& cpf2 = Data->VertexFirstOnS2();
    if (cpf2.IsOnArc() && !ok)
    {
      TopoDS_Face F2 = S2->Face();
      TopoDS_Face bid;
      Intf = !SearchFace(Spine, cpf2, F2, bid);
    }
  }
  Intl                           = 0;
  ok                             = false;
  const ChFiDS_CommonPoint& cpl1 = Data->VertexLastOnS1();
  if (cpl1.IsOnArc())
  {
    TopoDS_Face F1 = S1->Face();
    TopoDS_Face bid;
    Intl = !SearchFace(Spine, cpl1, F1, bid);
    ok   = Intl != 0;
  }
  const ChFiDS_CommonPoint& cpl2 = Data->VertexLastOnS2();
  if (cpl2.IsOnArc() && !ok)
  {
    TopoDS_Face F2 = S2->Face();
    TopoDS_Face bid;
    Intl = !SearchFace(Spine, cpl2, F2, bid);
  }
  Data->FirstSpineParam(First);
  Data->LastSpineParam(Last);

  return true;
}

void FilletSurf_InternalBuilder::PerformSurf(NCollection_Sequence<occ::handle<ChFiDS_SurfData>>&,
                                             const occ::handle<ChFiDS_ElSpine>&,
                                             const occ::handle<ChFiDS_Spine>&,
                                             const int,
                                             const occ::handle<BRepAdaptor_Surface>&,
                                             const occ::handle<Adaptor3d_TopolTool>&,
                                             const occ::handle<BRepAdaptor_Curve2d>&,
                                             const occ::handle<BRepAdaptor_Surface>&,
                                             const occ::handle<BRepAdaptor_Curve2d>&,
                                             bool&,
                                             const occ::handle<BRepAdaptor_Surface>&,
                                             const occ::handle<Adaptor3d_TopolTool>&,
                                             const TopAbs_Orientation,
                                             const double,
                                             const double,
                                             const double,
                                             double&,
                                             double&,
                                             const bool,
                                             const bool,
                                             const bool,
                                             const bool,
                                             const bool,
                                             const bool,
                                             const math_Vector&)
{
  throw Standard_DomainError("BlendFunc_CSConstRad::Section : Not implemented");
}

void FilletSurf_InternalBuilder::PerformSurf(NCollection_Sequence<occ::handle<ChFiDS_SurfData>>&,
                                             const occ::handle<ChFiDS_ElSpine>&,
                                             const occ::handle<ChFiDS_Spine>&,
                                             const int,
                                             const occ::handle<BRepAdaptor_Surface>&,
                                             const occ::handle<Adaptor3d_TopolTool>&,
                                             const TopAbs_Orientation,
                                             const occ::handle<BRepAdaptor_Surface>&,
                                             const occ::handle<Adaptor3d_TopolTool>&,
                                             const occ::handle<BRepAdaptor_Curve2d>&,
                                             const occ::handle<BRepAdaptor_Surface>&,
                                             const occ::handle<BRepAdaptor_Curve2d>&,
                                             bool&,
                                             const double,
                                             const double,
                                             const double,
                                             double&,
                                             double&,
                                             const bool,
                                             const bool,
                                             const bool,
                                             const bool,
                                             const bool,
                                             const bool,
                                             const math_Vector&)
{
  throw Standard_DomainError("BlendFunc_CSConstRad::Section : Not implemented");
}

void FilletSurf_InternalBuilder::PerformSurf(NCollection_Sequence<occ::handle<ChFiDS_SurfData>>&,
                                             const occ::handle<ChFiDS_ElSpine>&,
                                             const occ::handle<ChFiDS_Spine>&,
                                             const int,
                                             const occ::handle<BRepAdaptor_Surface>&,
                                             const occ::handle<Adaptor3d_TopolTool>&,
                                             const occ::handle<BRepAdaptor_Curve2d>&,
                                             const occ::handle<BRepAdaptor_Surface>&,
                                             const occ::handle<BRepAdaptor_Curve2d>&,
                                             bool&,
                                             const TopAbs_Orientation,
                                             const occ::handle<BRepAdaptor_Surface>&,
                                             const occ::handle<Adaptor3d_TopolTool>&,
                                             const occ::handle<BRepAdaptor_Curve2d>&,
                                             const occ::handle<BRepAdaptor_Surface>&,
                                             const occ::handle<BRepAdaptor_Curve2d>&,
                                             bool&,
                                             const TopAbs_Orientation,
                                             const double,
                                             const double,
                                             const double,
                                             double&,
                                             double&,
                                             const bool,
                                             const bool,
                                             const bool,
                                             const bool,
                                             const bool,
                                             const bool,
                                             const bool,
                                             const math_Vector&)
{
  throw Standard_DomainError("BlendFunc_CSConstRad::Section : Not implemented");
}

bool FilletSurf_InternalBuilder::Done() const
{
  return done;
}

int FilletSurf_InternalBuilder::NbSurface() const
{
  return myListStripe.First()->SetOfSurfData()->Length();
}

const occ::handle<Geom_Surface>& FilletSurf_InternalBuilder::SurfaceFillet(const int Index) const
{
  int isurf = myListStripe.First()->SetOfSurfData()->Value(Index)->Surf();

  return myDS->Surface(isurf).Surface();
}

double FilletSurf_InternalBuilder::TolApp3d(const int Index) const
{
  int isurf = myListStripe.First()->SetOfSurfData()->Value(Index)->Surf();

  return myDS->Surface(isurf).Tolerance();
}

const TopoDS_Face& FilletSurf_InternalBuilder::SupportFace1(const int Index) const
{
  int isurf = myListStripe.First()->SetOfSurfData()->Value(Index)->IndexOfS1();

  return TopoDS::Face(myDS->Shape(isurf));
}

const TopoDS_Face& FilletSurf_InternalBuilder::SupportFace2(const int Index) const
{
  int isurf = myListStripe.First()->SetOfSurfData()->Value(Index)->IndexOfS2();

  return TopoDS::Face(myDS->Shape(isurf));
}

const occ::handle<Geom_Curve>& FilletSurf_InternalBuilder::CurveOnFace1(const int Index) const
{
  int icurv = myListStripe.First()->SetOfSurfData()->Value(Index)->InterferenceOnS1().LineIndex();
  return myDS->Curve(icurv).Curve();
}

const occ::handle<Geom_Curve>& FilletSurf_InternalBuilder::CurveOnFace2(const int Index) const
{
  int icurv = myListStripe.First()->SetOfSurfData()->Value(Index)->InterferenceOnS2().LineIndex();
  return myDS->Curve(icurv).Curve();
}

const occ::handle<Geom2d_Curve>& FilletSurf_InternalBuilder::PCurveOnFace1(const int Index) const
{
  return myListStripe.First()->SetOfSurfData()->Value(Index)->InterferenceOnS1().PCurveOnFace();
}

const occ::handle<Geom2d_Curve>& FilletSurf_InternalBuilder::PCurve1OnFillet(const int Index) const
{
  return myListStripe.First()->SetOfSurfData()->Value(Index)->InterferenceOnS1().PCurveOnSurf();
}

const occ::handle<Geom2d_Curve>& FilletSurf_InternalBuilder::PCurveOnFace2(const int Index) const
{
  return myListStripe.First()->SetOfSurfData()->Value(Index)->InterferenceOnS2().PCurveOnFace();
}

const occ::handle<Geom2d_Curve>& FilletSurf_InternalBuilder::PCurve2OnFillet(const int Index) const
{
  return myListStripe.First()->SetOfSurfData()->Value(Index)->InterferenceOnS2().PCurveOnSurf();
}

double FilletSurf_InternalBuilder::FirstParameter() const
{
  const occ::handle<ChFiDS_Stripe>&   st  = myListStripe.First();
  const occ::handle<ChFiDS_Spine>&    sp  = st->Spine();
  const occ::handle<ChFiDS_SurfData>& sd  = st->SetOfSurfData()->Value(1);
  double                              p   = sd->FirstSpineParam();
  int                                 ind = 1;
  if (sp->IsPeriodic())
    ind = sp->Index(p);
  double ep;
  if (ComputeEdgeParameter(sp, ind, p, ep, tolapp3d))
    return ep;
  return 0.0;
}

double FilletSurf_InternalBuilder::LastParameter() const
{
  const occ::handle<ChFiDS_Stripe>&   st  = myListStripe.First();
  const occ::handle<ChFiDS_Spine>&    sp  = st->Spine();
  const occ::handle<ChFiDS_SurfData>& sd  = st->SetOfSurfData()->Value(NbSurface());
  double                              p   = sd->LastSpineParam();
  int                                 ind = sp->NbEdges();
  if (sp->IsPeriodic())
    ind = sp->Index(p);
  double ep;
  if (ComputeEdgeParameter(sp, ind, p, ep, tolapp3d))
    return ep;
  return 0.0;
}

FilletSurf_StatusType FilletSurf_InternalBuilder::StartSectionStatus() const
{

  bool isonedge1 = myListStripe.First()->SetOfSurfData()->Value(1)->VertexFirstOnS1().IsOnArc();
  bool isonedge2 = myListStripe.First()->SetOfSurfData()->Value(1)->VertexFirstOnS2().IsOnArc();

  if (isonedge1 && isonedge2)
  {
    return FilletSurf_TwoExtremityOnEdge;
  }
  else if ((!isonedge1) && (!isonedge2))
  {
    return FilletSurf_NoExtremityOnEdge;
  }
  else
  {
    return FilletSurf_OneExtremityOnEdge;
  }
}

FilletSurf_StatusType FilletSurf_InternalBuilder::EndSectionStatus() const
{
  bool isonedge1 =
    myListStripe.First()->SetOfSurfData()->Value(NbSurface())->VertexLastOnS1().IsOnArc();
  bool isonedge2 =
    myListStripe.First()->SetOfSurfData()->Value(NbSurface())->VertexLastOnS2().IsOnArc();

  if (isonedge1 && isonedge2)
  {
    return FilletSurf_TwoExtremityOnEdge;
  }
  else if ((!isonedge1) && (!isonedge2))
  {
    return FilletSurf_NoExtremityOnEdge;
  }
  else
  {
    return FilletSurf_OneExtremityOnEdge;
  }
}

void FilletSurf_InternalBuilder::Simulate()
{

  occ::handle<ChFiDS_Stripe>                                        Stripe = myListStripe.First();
  occ::handle<NCollection_HSequence<occ::handle<ChFiDS_SurfData>>>& HData =
    Stripe->ChangeSetOfSurfData();
  HData                            = new NCollection_HSequence<occ::handle<ChFiDS_SurfData>>();
  occ::handle<ChFiDS_Spine>& Spine = Stripe->ChangeSpine();
  TopAbs_Orientation         RefOr1, RefOr2;
  int                        RefChoix;
  StripeOrientations(Spine, RefOr1, RefOr2, RefChoix);
  Stripe->OrientationOnFace1(RefOr1);
  Stripe->OrientationOnFace2(RefOr2);
  Stripe->Choix(RefChoix);
  PerformSetOfKGen(Stripe, true);
}

int FilletSurf_InternalBuilder::NbSection(const int IndexSurf) const
{
  return Sect(1, IndexSurf)->Length();
}

void FilletSurf_InternalBuilder::Section(const int                       IndexSurf,
                                         const int                       IndexSec,
                                         occ::handle<Geom_TrimmedCurve>& Circ) const
{
  gp_Circ c;
  double  deb, fin;
  Sect(1, IndexSurf)->Value(IndexSec).Get(c, deb, fin);
  occ::handle<Geom_Circle> Gc = new Geom_Circle(c);
  Circ                        = new Geom_TrimmedCurve(Gc, deb, fin);
}

#include <Adaptor3d_Curve.hpp>
#include <BRep_Builder.hpp>
#include <BRep_Tool.hpp>
#include <BRepAdaptor_Curve.hpp>
#include <BRepBuilderAPI_Transform.hpp>
#include <BRepFill_LocationLaw.hpp>
#include <BRepTools_WireExplorer.hpp>
#include <GCPnts_AbscissaPoint.hpp>
#include <GeomFill_LocationLaw.hpp>
#include <gp_Mat.hpp>
#include <gp_Trsf.hpp>
#include <gp_Vec.hpp>
#include <gp_XYZ.hpp>
#include <Standard_Type.hpp>
#include <gp_Pnt2d.hpp>
#include <NCollection_Array1.hpp>
#include <gp_Vec2d.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Sequence.hpp>
#include <TopExp.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDS_Vertex.hpp>
#include <TopoDS_Wire.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BRepFill_LocationLaw, Standard_Transient)

static double Norm(const gp_Mat& M)
{
  double R, Norme;
  gp_XYZ Coord;
  Coord = M.Row(1);
  Norme = std::abs(Coord.X()) + std::abs(Coord.Y()) + std::abs(Coord.Z());
  Coord = M.Row(2);
  R     = std::abs(Coord.X()) + std::abs(Coord.Y()) + std::abs(Coord.Z());
  if (R > Norme)
    Norme = R;
  Coord = M.Row(3);
  R     = std::abs(Coord.X()) + std::abs(Coord.Y()) + std::abs(Coord.Z());
  if (R > Norme)
    Norme = R;

  return Norme;
}

static void ToG0(const gp_Mat& M1, const gp_Mat& M2, gp_Mat& T)
{
  T = M2.Inverted();
  T *= M1;
}

void BRepFill_LocationLaw::Init(const TopoDS_Wire& Path)

{
  int                    NbEdge;
  BRepTools_WireExplorer wexp;

  TopoDS_Edge E;

  myPath = Path;
  myTol  = 1.e-4;

  for (NbEdge = 0, wexp.Init(myPath); wexp.More(); wexp.Next())

    if (!BRep_Tool::Degenerated(wexp.Current()))
      NbEdge++;

  myLaws   = new (NCollection_HArray1<occ::handle<GeomFill_LocationLaw>>)(1, NbEdge);
  myLength = new (NCollection_HArray1<double>)(1, NbEdge + 1);
  myLength->Init(-1.);
  myLength->SetValue(1, 0.);
  myEdges = new (NCollection_HArray1<TopoDS_Shape>)(1, NbEdge);
  myDisc.Nullify();
  TangentIsMain();
}

GeomFill_PipeError BRepFill_LocationLaw::GetStatus() const
{
  int                ii, N = myLaws->Length();
  GeomFill_PipeError Status = GeomFill_PipeOk;
  for (ii = 1; ii <= N && (Status == GeomFill_PipeOk); ii++)
  {
    Status = myLaws->Value(ii)->ErrorStatus();
  }
  return Status;
}

void BRepFill_LocationLaw::TangentIsMain()
{
  myType = 1;
}

void BRepFill_LocationLaw::NormalIsMain()
{
  myType = 2;
}

void BRepFill_LocationLaw::BiNormalIsMain()
{
  myType = 3;
}

void BRepFill_LocationLaw::TransformInCompatibleLaw(const double TolAngular)
{

  double First, Last, Angle;
  int    ipath;
  gp_Mat Trsf, M1, M2;
  gp_Vec V, T1, T2, N1, N2;
  gp_XYZ OZ(0, 0, 1);

  myLaws->Value(1)->GetDomain(First, Last);

  for (ipath = 2; ipath <= myLaws->Length(); ipath++)
  {
    myLaws->Value(ipath - 1)->D0(Last, M1, V);
    myLaws->Value(ipath)->GetDomain(First, Last);
    myLaws->Value(ipath)->D0(First, M2, V);
    T1.SetXYZ(M1.Column(3));
    T2.SetXYZ(M2.Column(3));
    N1.SetXYZ(M1.Column(1));
    N2.SetXYZ(M2.Column(1));
    if (T1.IsParallel(T2, TolAngular) && !T1.IsOpposite(T2, TolAngular))
    {
      ToG0(M1, M2, Trsf);
    }
    else
    {
      double alpha;
      gp_Vec cross(T1);
      cross.Cross(T2);
      alpha = T2.AngleWithRef(T1, cross);
      gp_Ax1 axe(gp::Origin(), cross.XYZ());
      N2.Rotate(axe, alpha);

#ifdef OCCT_DEBUG
      if (N2.Dot(T1) > 1.e-9)
      {
        std::cout << "Inprecision in TransformInCompatibleLaw" << std::endl;
        std::cout << "--- T1.R(N2) = " << N2.Dot(T1) << std::endl;
        gp_Vec tt;
        tt = T1;
        tt.Rotate(axe, alpha);
        std::cout << "--- T1.R(T2) = " << tt.Dot(T1) << std::endl;
        std::cout << "--- R(N2).R(T2) = " << N2.Dot(tt) << std::endl;
      }
#endif
      Angle = N2.AngleWithRef(N1, T1);
      Trsf.SetRotation(OZ, Angle);
    }
    myLaws->Value(ipath)->SetTrsf(Trsf);
  }
}

void BRepFill_LocationLaw::TransformInG0Law()
{

  double First, Last;
  int    ipath;
  gp_Mat M1, M2, aux;
  gp_Vec V;
  myLaws->Value(1)->GetDomain(First, Last);
  for (ipath = 2; ipath <= myLaws->Length(); ipath++)
  {
    myLaws->Value(ipath - 1)->D0(Last, M1, V);
    myLaws->Value(ipath)->GetDomain(First, Last);
    myLaws->Value(ipath)->D0(First, M2, V);
    ToG0(M1, M2, aux);
    myLaws->Value(ipath)->SetTrsf(aux);
  }

  if (myPath.Closed())
  {
    myLaws->Value(myLaws->Length())->D0(Last, M1, V);
    myLaws->Value(1)->GetDomain(First, Last);
    myLaws->Value(1)->D0(First, M2, V);
  }
}

void BRepFill_LocationLaw::DeleteTransform()
{
  gp_Mat Id;
  Id.SetIdentity();
  for (int ii = 1; ii <= myEdges->Length(); ii++)
  {
    myLaws->ChangeValue(ii)->SetTrsf(Id);
  }
  myDisc.Nullify();
}

int BRepFill_LocationLaw::NbHoles(const double Tol)
{
  if (myDisc.IsNull())
  {
    NCollection_Sequence<int> Seq;
    int                       ii, NbDisc;
    for (ii = 2, NbDisc = -1; ii <= myLaws->Length() + 1; ii++)
    {
      if (IsG1(ii - 1, Tol, 1.e-12) == -1)
      {
        Seq.Append(ii);
      }
    }
    NbDisc = Seq.Length();
    if (NbDisc > 0)
    {
      myDisc = new (NCollection_HArray1<int>)(1, NbDisc);
      for (ii = 1; ii <= NbDisc; ii++)
        myDisc->SetValue(ii, Seq(ii));
    }
  }
  if (myDisc.IsNull())
    return 0;
  return myDisc->Length();
}

void BRepFill_LocationLaw::Holes(NCollection_Array1<int>& Disc) const
{
  if (!myDisc.IsNull())
  {
    for (int ii = 1; ii <= myDisc->Length(); ii++)
      Disc(ii) = myDisc->Value(ii);
  }
}

int BRepFill_LocationLaw::NbLaw() const
{
  return myLaws->Length();
}

const occ::handle<GeomFill_LocationLaw>& BRepFill_LocationLaw::Law(const int Index) const
{
  return myLaws->Value(Index);
}

const TopoDS_Wire& BRepFill_LocationLaw::Wire() const
{
  return myPath;
}

const TopoDS_Edge& BRepFill_LocationLaw::Edge(const int Index) const
{
  return TopoDS::Edge(myEdges->Value(Index));
}

TopoDS_Vertex BRepFill_LocationLaw::Vertex(const int Index) const
{
  TopoDS_Edge   E;
  TopoDS_Vertex V;
  if (Index <= myEdges->Length())
  {
    E = TopoDS::Edge(myEdges->Value(Index));
    if (E.Orientation() == TopAbs_REVERSED)
      V = TopExp::LastVertex(E);
    else
      V = TopExp::FirstVertex(E);
  }
  else if (Index == myEdges->Length() + 1)
  {
    E = TopoDS::Edge(myEdges->Value(Index - 1));
    if (E.Orientation() == TopAbs_REVERSED)
      V = TopExp::FirstVertex(E);
    else
      V = TopExp::LastVertex(E);
  }
  return V;
}

void BRepFill_LocationLaw::PerformVertex(const int            Index,
                                         const TopoDS_Vertex& Input,
                                         const double         TolMin,
                                         TopoDS_Vertex&       Output,
                                         const int            ILoc) const
{
  BRep_Builder B;
  bool         IsBary = (ILoc == 0);
  double       First, Last;
  gp_Pnt       P;
  gp_Vec       V1, V2;
  gp_Mat       M1, M2;

  if (Index > 0 && Index < myLaws->Length())
  {
    if (ILoc <= 0)
    {
      myLaws->Value(Index)->GetDomain(First, Last);
      myLaws->Value(Index)->D0(Last, M1, V1);
    }

    if (ILoc >= 0)
    {
      myLaws->Value(Index + 1)->GetDomain(First, Last);
      if (ILoc == 0)
        myLaws->Value(Index + 1)->D0(First, M2, V2);
      else
        myLaws->Value(Index + 1)->D0(First, M1, V1);
    }
  }

  if (Index == 0 || Index == myLaws->Length())
  {
    if (!myPath.Closed() || (IsG1(Index, TolMin) != 1))
    {
      IsBary = false;
      if (Index == 0)
      {
        myLaws->Value(1)->GetDomain(First, Last);
        myLaws->Value(1)->D0(First, M1, V1);
      }
      else
      {
        myLaws->Value(myLaws->Length())->GetDomain(First, Last);
        myLaws->Value(myLaws->Length())->D0(Last, M1, V1);
      }
    }
    else
    {
      if (ILoc <= 0)
      {
        myLaws->Value(myLaws->Length())->GetDomain(First, Last);
        myLaws->Value(myLaws->Length())->D0(Last, M1, V1);
      }

      if (ILoc >= 0)
      {
        myLaws->Value(1)->GetDomain(First, Last);
        if (ILoc == 0)
          myLaws->Value(1)->D0(First, M2, V2);
        else
          myLaws->Value(1)->D0(First, M1, V1);
      }
    }
  }

  P = BRep_Tool::Pnt(Input);

  if (IsBary)
  {
    gp_XYZ P1(P.XYZ()), P2(P.XYZ());
    P1 *= M1;
    P1 += V1.XYZ();
    P2 *= M2;
    P2 += V2.XYZ();

    P.ChangeCoord().SetLinearForm(0.5, P1, 0.5, P2);
    P1 -= P2;
    double Tol = P1.Modulus() / 2;
    Tol += TolMin;
    B.MakeVertex(Output, P, Tol);
  }
  else
  {
    P.ChangeCoord() *= M1;
    P.ChangeCoord() += V1.XYZ();
    B.MakeVertex(Output, P, TolMin);
  }
}

void BRepFill_LocationLaw::CurvilinearBounds(const int Index, double& First, double& Last) const
{
  First = myLength->Value(Index);
  Last  = myLength->Value(Index + 1);
  if (Last < 0)
  {
    int                  ii, NbE = myEdges->Length();
    double               Length, f, l;
    GCPnts_AbscissaPoint AbsC;

    for (ii = 1, Length = 0.; ii <= NbE; ii++)
    {
      myLaws->Value(ii)->GetDomain(f, l);
      Length += GCPnts_AbscissaPoint::Length(*myLaws->Value(ii)->GetCurve(), myTol);
      myLength->SetValue(ii + 1, Length);
    }

    First = myLength->Value(Index);
    Last  = myLength->Value(Index + 1);
  }
}

bool BRepFill_LocationLaw::IsClosed() const
{
  if (myPath.Closed())
    return true;

  TopoDS_Vertex V1, V2;
  TopExp::Vertices(myPath, V1, V2);
  return (V1.IsSame(V2));
}

int BRepFill_LocationLaw::IsG1(const int    Index,
                               const double SpatialTolerance,
                               const double AngularTolerance) const
{
  gp_Vec                       V1, DV1, V2, DV2;
  gp_Mat                       M1, M2, DM1, DM2;
  double                       First, Last, EpsNul = 1.e-12;
  double                       TolEps = SpatialTolerance;
  bool                         Ok_D1  = false;
  TopoDS_Vertex                V;
  TopoDS_Edge                  E;
  NCollection_Array1<gp_Pnt2d> Bid1(1, 1);
  NCollection_Array1<gp_Vec2d> Bid2(1, 1);

  if (Index > 0 && Index < myLaws->Length())
  {
    myLaws->Value(Index)->GetDomain(First, Last);
    Ok_D1 = myLaws->Value(Index)->D1(Last, M1, V1, DM1, DV1, Bid1, Bid2);
    if (!Ok_D1)
      myLaws->Value(Index)->D0(Last, M1, V1);

    myLaws->Value(Index + 1)->GetDomain(First, Last);
    if (Ok_D1)
      Ok_D1 = myLaws->Value(Index + 1)->D1(First, M2, V2, DM2, DV2, Bid1, Bid2);
    if (!Ok_D1)
      myLaws->Value(Index + 1)->D0(First, M2, V2);

    E = TopoDS::Edge(myEdges->Value(Index + 1));
  }
  if (Index == 0 || Index == myLaws->Length())
  {
    if (!myPath.Closed())
      return -1;
    myLaws->Value(myLaws->Length())->GetDomain(First, Last);
    Ok_D1 = myLaws->Value(myLaws->Length())->D1(Last, M1, V1, DM1, DV1, Bid1, Bid2);
    if (!Ok_D1)
      myLaws->Value(myLaws->Length())->D0(Last, M1, V1);

    myLaws->Value(1)->GetDomain(First, Last);
    if (Ok_D1)
      myLaws->Value(1)->D1(First, M2, V2, DM2, DV2, Bid1, Bid2);
    if (!Ok_D1)
      myLaws->Value(1)->D0(First, M2, V2);

    E = TopoDS::Edge(myEdges->Value(1));
  }

  if (E.Orientation() == TopAbs_REVERSED)
    V = TopExp::LastVertex(E);
  else
    V = TopExp::FirstVertex(E);

  TolEps += 2 * BRep_Tool::Tolerance(V);

  bool isG0 = true;
  bool isG1 = true;

  if ((V1 - V2).Magnitude() > TolEps)
    isG0 = false;
  if (Norm(M1 - M2) > SpatialTolerance)
    isG0 = false;

  if (!isG0)
    return -1;
  if (!Ok_D1)
    return 0;

  if ((DV1.Magnitude() > EpsNul) && (DV2.Magnitude() > EpsNul)
      && (DV1.Angle(DV2) > AngularTolerance))
    isG1 = false;

  double Norm1 = Norm(DM1);
  double Norm2 = Norm(DM2);

  if ((Norm1 > EpsNul) || (Norm2 > EpsNul))
  {

    if ((Norm1 > EpsNul) && (Norm2 > EpsNul))
    {
      DM1 /= Norm1;
      DM2 /= Norm2;
      if (Norm(DM1 - DM2) > AngularTolerance)
        isG1 = false;
    }
    else
      isG1 = false;
  }

  if (isG1)
    return 1;
  else
    return 0;
}

void BRepFill_LocationLaw::Parameter(const double Abcissa, int& Index, double& U)
{
  int  iedge, NbE = myEdges->Length();
  bool Trouve = false;

  if (myLength->Value(NbE + 1) < 0)
  {
    double f, l;
    CurvilinearBounds(NbE, f, l);
  }

  for (iedge = 1; iedge <= NbE && !Trouve;)
  {
    if (myLength->Value(iedge + 1) >= Abcissa)
    {
      Trouve = true;
    }
    else
      iedge++;
  }

  if (Trouve)
  {
    double                                   f, l;
    const occ::handle<GeomFill_LocationLaw>& Law = myLaws->Value(iedge);
    Law->GetDomain(f, l);

    if (Abcissa == myLength->Value(iedge + 1))
    {
      U = l;
    }
    else if (Abcissa == myLength->Value(iedge))
    {
      U = f;
    }
    else
    {
      GCPnts_AbscissaPoint AbsC(myTol,
                                *myLaws->Value(iedge)->GetCurve(),
                                Abcissa - myLength->Value(iedge),
                                f);
      U = AbsC.Parameter();
    }
    Index = iedge;
  }
  else
  {
    Index = 0;
  }
}

void BRepFill_LocationLaw::D0(const double Abcissa, TopoDS_Shape& W)
{
  double u;
  int    ind;
  gp_Mat M;
  gp_Vec V;

  Parameter(Abcissa, ind, u);
  if (ind != 0)
  {

    myLaws->Value(ind)->D0(u, M, V);
    gp_Trsf fila;
    fila.SetValues(M(1, 1),
                   M(1, 2),
                   M(1, 3),
                   V.X(),
                   M(2, 1),
                   M(2, 2),
                   M(2, 3),
                   V.Y(),
                   M(3, 1),
                   M(3, 2),
                   M(3, 3),
                   V.Z());

    W = BRepBuilderAPI_Transform(W, fila, true);
  }
  else
  {
    W.Nullify();
#ifdef OCCT_DEBUG
    std::cout << "BRepFill_LocationLaw::D0 : Attention position out of limits" << std::endl;
#endif
  }
}

double BRepFill_LocationLaw::Abscissa(const int Index, const double Param)
{
  GCPnts_AbscissaPoint AbsC;
  double               Length = myLength->Value(Index);
  if (Length < 0)
  {
    double bid;
    CurvilinearBounds(Index, bid, Length);
  }

  Length += GCPnts_AbscissaPoint::Length(*myLaws->Value(Index)->GetCurve(),
                                         myLaws->Value(Index)->GetCurve()->FirstParameter(),
                                         Param,
                                         myTol);
  return Length;
}

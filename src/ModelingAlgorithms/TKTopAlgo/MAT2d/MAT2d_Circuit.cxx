#include <Adaptor2d_OffsetCurve.hpp>
#include <Geom2d_CartesianPoint.hpp>
#include <Geom2d_Geometry.hpp>
#include <Geom2d_TrimmedCurve.hpp>
#include <Geom2dAdaptor_Curve.hpp>
#include <Geom2dInt_GInter.hpp>
#include <MAT2d_Circuit.hpp>
#include <MAT2d_Connexion.hpp>
#include <MAT2d_BiInt.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_DataMap.hpp>
#include <MAT2d_MiniPath.hpp>
#include <Precision.hpp>
#include <Standard_Type.hpp>
#include <NCollection_Array1.hpp>

IMPLEMENT_STANDARD_RTTIEXT(MAT2d_Circuit, Standard_Transient)

#ifdef OCCT_DEBUG
  #include <GCE2d_MakeSegment.hpp>
  #include <Geom2d_Curve.hpp>
  #include <Geom2d_Parabola.hpp>
  #include <Geom2d_Hyperbola.hpp>
  #include <Geom2d_Line.hpp>
  #include <Geom2d_Circle.hpp>
#endif

#ifdef OCCT_DEBUG
static void MAT2d_DrawCurve(const occ::handle<Geom2d_Curve>& aCurve, const int Indice);
static bool AffichCircuit = 0;
#endif

static double CrossProd(const occ::handle<Geom2d_Geometry>& Geom1,
                        const occ::handle<Geom2d_Geometry>& Geom2,
                        double&                             DotProd);

MAT2d_Circuit::MAT2d_Circuit(const GeomAbs_JoinType aJoinType, const bool IsOpenResult)
    : direction(0.0)
{
  myJoinType     = aJoinType;
  myIsOpenResult = IsOpenResult;
}

void MAT2d_Circuit::Perform(
  NCollection_Sequence<NCollection_Sequence<occ::handle<Geom2d_Geometry>>>& FigItem,
  const NCollection_Sequence<bool>&                                         IsClosed,
  const int                                                                 IndRefLine,
  const bool                                                                Trigo)
{
  int                                                NbLines = FigItem.Length();
  int                                                i;
  NCollection_Array1<bool>                           Open(1, NbLines);
  NCollection_Sequence<occ::handle<MAT2d_Connexion>> SVide;
  occ::handle<MAT2d_Connexion>                       ConnexionNul;

  if (Trigo)
    direction = 1.;
  else
    direction = -1.;

  geomElements.Clear();
  connexionMap.Clear();
  linkRefEqui.Clear();
  linesLength.Clear();

  for (i = 1; i <= NbLines; i++)
  {
    occ::handle<Geom2d_TrimmedCurve> Curve;
    Curve       = occ::down_cast<Geom2d_TrimmedCurve>(FigItem.Value(i).First());
    gp_Pnt2d P1 = Curve->StartPoint();
    Curve       = occ::down_cast<Geom2d_TrimmedCurve>(FigItem.Value(i).Last());
    gp_Pnt2d P2 = Curve->EndPoint();

    if (IsClosed(i))
      Open(i) = false;
    else if (P1.IsEqual(P2, Precision::Confusion()))
      Open(i) = false;
    else
      Open(i) = true;
  }

  for (i = 1; i <= NbLines; i++)
  {
    if (Open(i))
    {
      InitOpen(FigItem.ChangeValue(i));
      linesLength.Append(FigItem.Value(i).Length());
    }
    else
    {
      InsertCorner(FigItem.ChangeValue(i));
      linesLength.Append(FigItem.Value(i).Length());
    }
  }

  if (NbLines == 1)
  {
    if (Open(1))
    {
      DoubleLine(FigItem.ChangeValue(1), SVide, ConnexionNul, direction);
      linesLength.SetValue(1, FigItem.Value(1).Length());
    }
    geomElements = FigItem.Value(1);
    UpDateLink(1, 1, 1, geomElements.Length());
    linesLength.Append(FigItem.Value(1).Length());
    return;
  }

  MAT2d_MiniPath Road;
  Road.Perform(FigItem, IndRefLine, Trigo);

  for (i = 1; i <= NbLines; i++)
  {
    if (Open(i))
    {
      occ::handle<MAT2d_Connexion> CF;
      if (Road.IsRoot(i))
        CF = ConnexionNul;
      else
        CF = Road.Father(i);
      if (Road.IsConnexionsFrom(i))
      {
        DoubleLine(FigItem.ChangeValue(i), Road.ConnexionsFrom(i), CF, direction);
      }
      else
      {
        DoubleLine(FigItem.ChangeValue(i), SVide, CF, direction);
      }
      linesLength.SetValue(i, FigItem.Value(i).Length());
    }
  }

  Road.RunOnConnexions();

#ifdef OCCT_DEBUG
  if (AffichCircuit)
  {
    int NbConnexions = Road.Path().Length();
    for (i = 1; i <= NbConnexions; i++)
    {
      occ::handle<Geom2d_TrimmedCurve> edge;
      edge = GCE2d_MakeSegment(Road.Path().Value(i)->PointOnFirst(),
                               Road.Path().Value(i)->PointOnSecond());
      MAT2d_DrawCurve(edge, 2);
    }
  }
#endif

  ConstructCircuit(FigItem, IndRefLine, Road);
}

bool MAT2d_Circuit::IsSharpCorner(const occ::handle<Geom2d_Geometry>& Geom1,
                                  const occ::handle<Geom2d_Geometry>& Geom2,
                                  const double                        Direction) const
{
  double                           DotProd;
  double                           ProVec = CrossProd(Geom1, Geom2, DotProd);
  int                              NbTest = 1;
  constexpr double                 DU     = Precision::Confusion();
  occ::handle<Geom2d_TrimmedCurve> C1, C2;

  C1 = occ::down_cast<Geom2d_TrimmedCurve>(Geom1);
  C2 = occ::down_cast<Geom2d_TrimmedCurve>(Geom2);

  double TolAng = 1.E-8;

  if (myJoinType == GeomAbs_Arc)
  {
    while (NbTest <= 10)
    {
      if ((ProVec)*Direction < -TolAng)
        return true;
      if ((ProVec)*Direction > TolAng)
        return false;
      else
      {
        if (DotProd > 0)
        {
          return false;
        }
        TolAng      = 1.E-8;
        double   U1 = C1->LastParameter() - NbTest * DU;
        double   U2 = C2->FirstParameter() + NbTest * DU;
        gp_Dir2d Dir1(C1->DN(U1, 1));
        gp_Dir2d Dir2(C2->DN(U2, 1));
        DotProd = Dir1.Dot(Dir2);
        ProVec  = Dir1 ^ Dir2;
        NbTest++;
      }
    }

    double           D;
    constexpr double Tol   = Precision::Confusion();
    double           MilC1 = (C1->LastParameter() + C1->FirstParameter()) * 0.5;
    double           MilC2 = (C2->LastParameter() + C2->FirstParameter()) * 0.5;
    gp_Pnt2d         P     = C1->Value(C1->LastParameter());
    gp_Pnt2d         P1    = C1->Value(MilC1);
    gp_Pnt2d         P2    = C2->Value(MilC2);

    D = std::min(P1.Distance(P), P2.Distance(P));
    D /= 10;

    if (Direction < 0.)
      D = -D;

    occ::handle<Geom2dAdaptor_Curve> HC1 = new Geom2dAdaptor_Curve(C1);
    occ::handle<Geom2dAdaptor_Curve> HC2 = new Geom2dAdaptor_Curve(C2);
    Adaptor2d_OffsetCurve            OC1(HC1, D, MilC1, C1->LastParameter());
    Adaptor2d_OffsetCurve            OC2(HC2, D, C2->FirstParameter(), MilC2);
    Geom2dInt_GInter                 Intersect;
    Intersect.Perform(OC1, OC2, Tol, Tol);

#ifdef OCCT_DEBUG
    static bool Affich = 0;
    if (Affich)
    {
    }
#endif

    return !Intersect.IsDone() || Intersect.IsEmpty();
  }
  else if (myJoinType == GeomAbs_Intersection)
  {
    if (std::abs(ProVec) <= TolAng && DotProd < 0)
    {
      while (NbTest <= 10)
      {
        double   U1 = C1->LastParameter() - NbTest * DU;
        double   U2 = C2->FirstParameter() + NbTest * DU;
        gp_Dir2d Dir1(C1->DN(U1, 1));
        gp_Dir2d Dir2(C2->DN(U2, 1));
        DotProd = Dir1.Dot(Dir2);
        ProVec  = Dir1 ^ Dir2;
        if ((ProVec)*Direction < -TolAng)
          return true;
        if ((ProVec)*Direction > TolAng)
          return false;

        NbTest++;
      }
      return false;
    }
    else
      return false;
  }
  return false;
}

static void SubSequence(const NCollection_Sequence<occ::handle<Geom2d_Geometry>>& S1,
                        int                                                       IF,
                        int                                                       IL,
                        NCollection_Sequence<occ::handle<Geom2d_Geometry>>&       S2)
{
  S2.Clear();
  for (int i = IF; i <= IL; i++)
  {
    S2.Append(S1.Value(i));
  }
}

void MAT2d_Circuit::ConstructCircuit(
  const NCollection_Sequence<NCollection_Sequence<occ::handle<Geom2d_Geometry>>>& FigItem,
  const int                                                                       IndRefLine,
  const MAT2d_MiniPath&                                                           Road)
{
  occ::handle<MAT2d_Connexion>                       PrevC, CurC;
  NCollection_Sequence<occ::handle<Geom2d_Geometry>> SetOfItem;
  int                                                NbConnexions;
  int                                                ILastItem;
  int                                                IndLast;
  int                                                i;

  NbConnexions = Road.Path().Length();

  PrevC = Road.Path().Value(1);
  SubSequence(FigItem.Value(IndRefLine), 1, PrevC->IndexItemOnFirst(), geomElements);
  UpDateLink(1, IndRefLine, 1, PrevC->IndexItemOnFirst());
  connexionMap.Bind(geomElements.Length() + 1, PrevC);
  ILastItem = geomElements.Length();

  for (i = 2; i <= NbConnexions; i++)
  {
    CurC = Road.Path().Value(i);
    if (PassByLast(PrevC, CurC))
    {

      IndLast = FigItem.Value(CurC->IndexFirstLine()).Length();
      SubSequence(FigItem.Value(CurC->IndexFirstLine()),
                  PrevC->IndexItemOnSecond(),
                  IndLast,
                  SetOfItem);
      UpDateLink(ILastItem + 1, CurC->IndexFirstLine(), PrevC->IndexItemOnSecond(), IndLast);
      geomElements.Append(SetOfItem);
      ILastItem = geomElements.Length();

      if (FigItem.Value(CurC->IndexFirstLine()).Length() > 1)
      {
        SubSequence(FigItem.Value(CurC->IndexFirstLine()), 1, CurC->IndexItemOnFirst(), SetOfItem);
        UpDateLink(ILastItem + 1, CurC->IndexFirstLine(), 1, CurC->IndexItemOnFirst());
        geomElements.Append(SetOfItem);
        ILastItem = geomElements.Length();
      }
      connexionMap.Bind(ILastItem + 1, CurC);
    }
    else
    {

      SubSequence(FigItem.Value(CurC->IndexFirstLine()),
                  PrevC->IndexItemOnSecond(),
                  CurC->IndexItemOnFirst(),
                  SetOfItem);
      UpDateLink(ILastItem + 1,
                 CurC->IndexFirstLine(),
                 PrevC->IndexItemOnSecond(),
                 CurC->IndexItemOnFirst());
      geomElements.Append(SetOfItem);
      ILastItem = geomElements.Length();
      connexionMap.Bind(ILastItem + 1, CurC);
    }
    PrevC = CurC;
  }

  IndLast = FigItem.Value(IndRefLine).Length();
  if (IndLast == 1)
  {
    connexionMap.Bind(1, CurC);
    connexionMap.UnBind(ILastItem + 1);
  }
  else
  {
    SubSequence(FigItem.Value(IndRefLine), PrevC->IndexItemOnSecond(), IndLast, SetOfItem);
    UpDateLink(ILastItem + 1, IndRefLine, PrevC->IndexItemOnSecond(), IndLast);
    geomElements.Append(SetOfItem);
    ILastItem = geomElements.Length();
  }

  NCollection_DataMap<MAT2d_BiInt, NCollection_Sequence<int>>::Iterator Ite;

  for (Ite.Initialize(linkRefEqui); Ite.More(); Ite.Next())
  {
    if (Ite.Value().Length() > 1)
    {
      SortRefToEqui(Ite.Key());
    }
  }

#ifdef OCCT_DEBUG
  if (AffichCircuit)
  {
    ILastItem = geomElements.Length();
    for (i = 1; i <= ILastItem; i++)
    {
      if (geomElements.Value(i)->DynamicType() != STANDARD_TYPE(Geom2d_CartesianPoint))
      {
        MAT2d_DrawCurve(occ::down_cast<Geom2d_Curve>(geomElements.Value(i)), 2);
      }
    }
  }
#endif
}

void MAT2d_Circuit::InitOpen(NCollection_Sequence<occ::handle<Geom2d_Geometry>>& Line) const
{
  occ::handle<Geom2d_TrimmedCurve> Curve;
  double                           DotProd;

  Curve = occ::down_cast<Geom2d_TrimmedCurve>(Line.First());
  Line.InsertBefore(1, new Geom2d_CartesianPoint(Curve->StartPoint()));
  Curve = occ::down_cast<Geom2d_TrimmedCurve>(Line.Last());
  Line.Append(new Geom2d_CartesianPoint(Curve->EndPoint()));

  for (int i = 2; i <= Line.Length() - 2; i++)
  {
    if (std::abs(CrossProd(Line.Value(i), Line.Value(i + 1), DotProd)) > 1.E-8 || DotProd < 0.)
    {
      Curve = occ::down_cast<Geom2d_TrimmedCurve>(Line.Value(i));
      Line.InsertAfter(i, new Geom2d_CartesianPoint(Curve->EndPoint()));
      i++;
    }
  }
}

void MAT2d_Circuit::DoubleLine(NCollection_Sequence<occ::handle<Geom2d_Geometry>>& Line,
                               NCollection_Sequence<occ::handle<MAT2d_Connexion>>& ConnexionFrom,
                               const occ::handle<MAT2d_Connexion>&                 ConnexionFather,
                               const double                                        SideRef) const
{
  occ::handle<Standard_Type>       Type;
  occ::handle<Geom2d_TrimmedCurve> Curve;
  int                              NbItems = Line.Length();
  int                              i;
  double                           ProVec, DotProd;
  occ::handle<MAT2d_Connexion>     CC;

  if (!myIsOpenResult)
  {
    for (i = NbItems - 1; i > 1; i--)
    {
      Type = Line.Value(i)->DynamicType();
      if (Type == STANDARD_TYPE(Geom2d_CartesianPoint))
      {
        Line.Append(Line.Value(i));
      }
      else
      {
        Curve = occ::down_cast<Geom2d_TrimmedCurve>(Line.Value(i)->Copy());
        Curve->Reverse();
        Line.Append(Curve);
      }
    }
  }

  int IAfter       = ConnexionFrom.Length();
  int NbConnexions = IAfter;
  int IndCOF;

  for (i = 1; i <= IAfter; i++)
  {
    CC     = ConnexionFrom.Value(i);
    IndCOF = CC->IndexItemOnFirst();
    Type   = Line.Value(IndCOF)->DynamicType();

    if (Type == STANDARD_TYPE(Geom2d_CartesianPoint))
    {
      if (IndCOF != NbItems && IndCOF != 1)
      {
        ProVec = CrossProd(Line.Value(IndCOF - 1), Line.Value(IndCOF + 1), DotProd);
        if ((ProVec)*SideRef > 0)
        {
          CC->IndexItemOnFirst(2 * NbItems - IndCOF);
          ConnexionFrom.InsertAfter(IAfter, CC);
          ConnexionFrom.Remove(i);
          IAfter--;
          i--;
        }
      }
    }
    else if (Side(CC, Line) != SideRef)
    {
      Curve = occ::down_cast<Geom2d_TrimmedCurve>(Line.Value(IndCOF));
      CC->IndexItemOnFirst(2 * NbItems - IndCOF);
      CC->ParameterOnFirst(Curve->ReversedParameter(CC->ParameterOnFirst()));
      ConnexionFrom.InsertAfter(IAfter, CC);
      ConnexionFrom.Remove(i);
      IAfter--;
      i--;
    }
  }

  if (!ConnexionFather.IsNull())
  {
    CC     = ConnexionFather->Reverse();
    IndCOF = CC->IndexItemOnFirst();
    Type   = Line.Value(IndCOF)->DynamicType();

    if (Type == STANDARD_TYPE(Geom2d_CartesianPoint))
    {
      if (IndCOF != NbItems && IndCOF != 1)
      {
        ProVec = CrossProd(Line.Value(IndCOF - 1), Line.Value(IndCOF + 1), DotProd);
        if ((ProVec)*SideRef > 0)
        {
          ConnexionFather->IndexItemOnSecond(2 * NbItems - IndCOF);
        }
      }
    }
    else if (Side(CC, Line) != SideRef)
    {
      Curve = occ::down_cast<Geom2d_TrimmedCurve>(Line.Value(IndCOF));
      ConnexionFather->IndexItemOnSecond(2 * NbItems - IndCOF);
      ConnexionFather->ParameterOnSecond(
        Curve->ReversedParameter(ConnexionFather->ParameterOnSecond()));
    }
  }

  int                     IndLine = 1;
  int                     ICorres = 1;
  NCollection_Array1<int> Corres(1, Line.Length());

  while (Line.Value(IndLine) != Line.Last())
  {
    Corres(ICorres) = IndLine;
    Type            = Line.Value(IndLine)->DynamicType();

    if (Type == STANDARD_TYPE(Geom2d_CartesianPoint) && ICorres != 1 && ICorres != NbItems)
    {

      if (!IsSharpCorner(Line.Value(IndLine - 1), Line.Value(IndLine + 1), SideRef))
      {
        Line.Remove(IndLine);
        IndLine--;
        Corres(ICorres) = 0;
      }
    }
    IndLine++;
    ICorres++;
  }
  Corres(ICorres) = IndLine;

  if (!myIsOpenResult)
  {
    for (i = 1; i < 2 * NbItems - 2; i++)
    {
      if (Corres(i) == 0)
        Corres(i) = Corres(2 * NbItems - i);
    }

#ifdef OCCT_DEBUG
    if (AffichCircuit)
    {
      for (i = 1; i <= 2 * NbItems - 2; i++)
      {
        std::cout << "Correspondance " << i << " -> " << Corres(i) << std::endl;
      }
    }
#endif

    for (i = 1; i <= NbConnexions; i++)
    {
      CC = ConnexionFrom.ChangeValue(i);
      CC->IndexItemOnFirst(Corres(CC->IndexItemOnFirst()));
    }

    if (!ConnexionFather.IsNull())
    {
      ConnexionFather->IndexItemOnSecond(Corres(ConnexionFather->IndexItemOnSecond()));
    }
  }
}

void MAT2d_Circuit::InsertCorner(NCollection_Sequence<occ::handle<Geom2d_Geometry>>& Line) const
{
  int                              i, isuiv;
  occ::handle<Geom2d_TrimmedCurve> Curve;
  bool                             Insert;

  for (i = 1; i <= Line.Length(); i++)
  {
    isuiv  = (i == Line.Length()) ? 1 : i + 1;
    Insert = IsSharpCorner(Line.Value(i), Line.Value(isuiv), direction);

#ifdef OCCT_DEBUG
    if (AffichCircuit)
    {
      if (Insert)
      {
        Curve = occ::down_cast<Geom2d_TrimmedCurve>(Line.Value(isuiv));
      }
    }
#endif

    if (Insert)
    {
      Curve = occ::down_cast<Geom2d_TrimmedCurve>(Line.Value(isuiv));
      Line.InsertAfter(i, new Geom2d_CartesianPoint(Curve->StartPoint()));
      i++;
    }
  }
}

int MAT2d_Circuit::NumberOfItems() const
{
  return geomElements.Length();
}

int MAT2d_Circuit::LineLength(const int I) const
{
  return linesLength(I);
}

occ::handle<Geom2d_Geometry> MAT2d_Circuit::Value(const int Index) const
{
  return geomElements.Value(Index);
}

const NCollection_Sequence<int>& MAT2d_Circuit::RefToEqui(const int IndLine,
                                                          const int IndCurve) const
{
  MAT2d_BiInt Key(IndLine, IndCurve);
  return linkRefEqui(Key);
}

void MAT2d_Circuit::SortRefToEqui(const MAT2d_BiInt& BiRef)
{
  int                        i;
  NCollection_Sequence<int>& S = linkRefEqui.ChangeFind(BiRef);
  NCollection_Sequence<int>  SFin;

  for (i = 1; i <= S.Length(); i++)
  {
    if (!ConnexionOn(S.Value(i)))
      break;
  }
  if (i > 1 && i <= S.Length())
  {
    SFin = S;
    SFin.Split(i, S);
    S.Append(SFin);
  }
}

occ::handle<MAT2d_Connexion> MAT2d_Circuit::Connexion(const int I) const
{
  return connexionMap(I);
}

bool MAT2d_Circuit::ConnexionOn(const int I) const
{
  return connexionMap.IsBound(I);
}

double MAT2d_Circuit::Side(const occ::handle<MAT2d_Connexion>&                       C1,
                           const NCollection_Sequence<occ::handle<Geom2d_Geometry>>& Line) const
{
  occ::handle<Geom2d_TrimmedCurve> Curve;

  gp_Vec2d Vect1(C1->PointOnSecond().X() - C1->PointOnFirst().X(),
                 C1->PointOnSecond().Y() - C1->PointOnFirst().Y());
  Curve          = occ::down_cast<Geom2d_TrimmedCurve>(Line.Value(C1->IndexItemOnFirst()));
  gp_Vec2d Vect2 = Curve->DN(C1->ParameterOnFirst(), 1);
  if ((Vect1 ^ Vect2) > 0.)
    return -1.;
  else
    return 1.;
}

bool MAT2d_Circuit::PassByLast(const occ::handle<MAT2d_Connexion>& C1,
                               const occ::handle<MAT2d_Connexion>& C2) const
{
  if (C2->IndexFirstLine() == C1->IndexSecondLine())
  {
    if (C2->IndexItemOnFirst() < C1->IndexItemOnSecond())
    {
      return true;
    }
    else if (C2->IndexItemOnFirst() == C1->IndexItemOnSecond())
    {
      if (C1->IndexFirstLine() == C2->IndexSecondLine())
      {
        return true;
      }
      if (C2->ParameterOnFirst() == C1->ParameterOnSecond())
      {
        gp_Vec2d Vect1(C1->PointOnSecond(), C1->PointOnFirst());
        gp_Vec2d Vect2(C2->PointOnFirst(), C2->PointOnSecond());
        if ((Vect1 ^ Vect2) * direction > 0)
        {
          return true;
        }
      }
      else if (C2->ParameterOnFirst() < C1->ParameterOnSecond())
      {
        return true;
      }
    }
  }
  return false;
}

void MAT2d_Circuit::UpDateLink(const int IFirst,
                               const int ILine,
                               const int ICurveFirst,
                               const int ICurveLast)
{
  int IEqui = IFirst;
  int i;

  for (i = ICurveFirst; i <= ICurveLast; i++)
  {
    MAT2d_BiInt Key(ILine, i);
    if (linkRefEqui.IsBound(Key))
    {
      linkRefEqui(Key).Append(IEqui);
    }
    else
    {
      NCollection_Sequence<int> L;
      linkRefEqui.Bind(Key, L);
      linkRefEqui(Key).Append(IEqui);
    }
    IEqui++;
  }
}

static double CrossProd(const occ::handle<Geom2d_Geometry>& Geom1,
                        const occ::handle<Geom2d_Geometry>& Geom2,
                        double&                             DotProd)
{
  occ::handle<Geom2d_TrimmedCurve> Curve;

  Curve = occ::down_cast<Geom2d_TrimmedCurve>(Geom1);
  gp_Dir2d Dir1(Curve->DN(Curve->LastParameter(), 1));
  Curve = occ::down_cast<Geom2d_TrimmedCurve>(Geom2);
  gp_Dir2d Dir2(Curve->DN(Curve->FirstParameter(), 1));
  DotProd = Dir1.Dot(Dir2);
  return Dir1 ^ Dir2;
}

#ifdef OCCT_DEBUG

void MAT2d_DrawCurve(const occ::handle<Geom2d_Curve>& aCurve, const int)
{
  occ::handle<Standard_Type> type = aCurve->DynamicType();
  occ::handle<Geom2d_Curve>  curve, CurveDraw;

  if (type == STANDARD_TYPE(Geom2d_TrimmedCurve))
  {
    curve = occ::down_cast<Geom2d_TrimmedCurve>(aCurve)->BasisCurve();
    type  = curve->DynamicType();

    gp_Parab2d gpParabola;
    gp_Hypr2d  gpHyperbola;
    double     Focus;
    double     Limit = 50000.;
    double     delta = 400;

    if (aCurve->LastParameter() == Precision::Infinite())
    {

      if (type == STANDARD_TYPE(Geom2d_Parabola))
      {
        gpParabola  = occ::down_cast<Geom2d_Parabola>(curve)->Parab2d();
        Focus       = gpParabola.Focal();
        double Val1 = std::sqrt(Limit * Focus);
        double Val2 = std::sqrt(Limit * Limit);
        delta       = (Val1 <= Val2 ? Val1 : Val2);
      }
      else if (type == STANDARD_TYPE(Geom2d_Hyperbola))
      {
        gpHyperbola  = occ::down_cast<Geom2d_Hyperbola>(curve)->Hypr2d();
        double Majr  = gpHyperbola.MajorRadius();
        double Minr  = gpHyperbola.MinorRadius();
        double Valu1 = Limit / Majr;
        double Valu2 = Limit / Minr;
        double Val1  = Log(Valu1 + std::sqrt(Valu1 * Valu1 - 1));
        double Val2  = Log(Valu2 + std::sqrt(Valu2 * Valu2 + 1));
        delta        = (Val1 <= Val2 ? Val1 : Val2);
      }
      CurveDraw =
        new Geom2d_TrimmedCurve(aCurve, aCurve->FirstParameter(), aCurve->FirstParameter() + delta);
    }
    else
    {
      CurveDraw = aCurve;
    }
  }
  else
  {
    CurveDraw = aCurve;
  }
}

#endif

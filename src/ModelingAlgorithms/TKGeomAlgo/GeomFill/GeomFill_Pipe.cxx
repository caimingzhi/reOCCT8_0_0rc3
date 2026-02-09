#include <GeomFill_Pipe.hpp>

#include <Adaptor3d_CurveOnSurface.hpp>
#include <Adaptor3d_Curve.hpp>
#include <Approx_SweepApproximation.hpp>
#include <ElCLib.hpp>
#include <Geom2dAdaptor_Curve.hpp>
#include <Geom_BSplineCurve.hpp>
#include <Geom_BSplineSurface.hpp>
#include <Geom_Circle.hpp>
#include <Geom_Curve.hpp>
#include <Geom_CylindricalSurface.hpp>
#include <Geom_Line.hpp>
#include <Geom_RectangularTrimmedSurface.hpp>
#include <Geom_Surface.hpp>
#include <Geom_ToroidalSurface.hpp>
#include <GeomAdaptor_Surface.hpp>
#include <GeomFill_AppSweep.hpp>
#include <GeomFill_CircularBlendFunc.hpp>
#include <GeomFill_ConstantBiNormal.hpp>
#include <GeomFill_CorrectedFrenet.hpp>
#include <GeomFill_CurveAndTrihedron.hpp>
#include <GeomFill_Darboux.hpp>
#include <GeomFill_Fixed.hpp>
#include <GeomFill_Frenet.hpp>
#include <GeomFill_GuideTrihedronAC.hpp>
#include <GeomFill_GuideTrihedronPlan.hpp>
#include <GeomFill_Line.hpp>
#include <GeomFill_LocationGuide.hpp>
#include <GeomFill_LocationLaw.hpp>
#include <GeomFill_NSections.hpp>
#include <GeomFill_SectionLaw.hpp>
#include <GeomFill_SectionPlacement.hpp>
#include <GeomFill_Sweep.hpp>
#include <GeomFill_SweepSectionGenerator.hpp>
#include <GeomFill_UniformSection.hpp>
#include <GeomLib.hpp>
#include <GeomLProp_CLProps.hpp>
#include <gp_Ax2.hpp>
#include <gp_Ax3.hpp>
#include <gp_Dir.hpp>
#include <gp_Torus.hpp>
#include <Precision.hpp>
#include <Standard_ConstructionError.hpp>
#include <NCollection_Sequence.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array1.hpp>

#include <cstdio>
#ifdef OCCT_DEBUG
static bool Affich     = false;
static int  NbSections = 0;
#endif

static bool CheckSense(const NCollection_Sequence<occ::handle<Geom_Curve>>& Seq1,
                       NCollection_Sequence<occ::handle<Geom_Curve>>&       Seq2)
{

  bool no_sing = true;
  Seq2.Clear();

  const occ::handle<Geom_Curve>& C1 = Seq1.Value(1);
  double                         f = C1->FirstParameter(), l = C1->LastParameter();
  int                            iP, NP                      = 21;
  NCollection_Array1<gp_Pnt>     Tab(1, NP);
  double                         u = f, h = std::abs(f - l) / 20.;
  for (iP = 1; iP <= NP; iP++)
  {
    C1->D0(u, Tab(iP));
    u += h;
    if ((u - f) * (u - l) > 0.0)
      u = l;
  }
  gp_Ax2 AxeRef, Axe;
  gp_Pnt Pos;
  bool   sing;
  GeomLib::AxeOfInertia(Tab, AxeRef, sing);

  if (sing)
    no_sing = false;

  Pos = AxeRef.Location();
  double alpha1, alpha2, alpha3;
  gp_Pnt P1, P2;
  u = (f + l - h) / 2 - h;
  C1->D0(u, P1);
  u += h;
  C1->D0(u, P2);
  alpha1 = gp_Vec(Pos, P1).AngleWithRef(gp_Vec(Pos, P2), AxeRef.Direction());
  P1     = P2;
  u += h;
  C1->D0(u, P2);
  alpha2 = gp_Vec(Pos, P1).AngleWithRef(gp_Vec(Pos, P2), AxeRef.Direction());
  P1     = P2;
  u += h;
  C1->D0(u, P2);
  alpha3 = gp_Vec(Pos, P1).AngleWithRef(gp_Vec(Pos, P2), AxeRef.Direction());
  Seq2.Append(C1);

  for (int iseq = 2; iseq <= Seq1.Length(); iseq++)
  {

    const occ::handle<Geom_Curve>& C2 = Seq1.Value(iseq);
    f                                 = C2->FirstParameter();
    l                                 = C2->LastParameter();
    u                                 = f;
    for (iP = 1; iP <= NP; iP++)
    {
      C2->D0(u, Tab(iP));
      u += h;
      if ((u - f) * (u - l) > 0.0)
        u = l;
    }
    GeomLib::AxeOfInertia(Tab, Axe, sing);

    if (sing)
      no_sing = false;

    Pos = Axe.Location();
    double beta1, beta2, beta3;
    u = (f + l - h) / 2 - h;
    C2->D0(u, P1);
    u += h;
    C2->D0(u, P2);
    beta1 = gp_Vec(Pos, P1).AngleWithRef(gp_Vec(Pos, P2), AxeRef.Direction());
    P1    = P2;
    u += h;
    C2->D0(u, P2);
    beta2 = gp_Vec(Pos, P1).AngleWithRef(gp_Vec(Pos, P2), AxeRef.Direction());
    P1    = P2;
    u += h;
    C2->D0(u, P2);
    beta3 = gp_Vec(Pos, P1).AngleWithRef(gp_Vec(Pos, P2), AxeRef.Direction());

    bool ok      = true,
         pasnul1 = (std::abs(alpha1) > Precision::Confusion())
                   && (std::abs(beta1) > Precision::Confusion()),
         pasnul2 = (std::abs(alpha2) > Precision::Confusion())
                   && (std::abs(beta2) > Precision::Confusion()),
         pasnul3 = (std::abs(alpha3) > Precision::Confusion())
                   && (std::abs(beta3) > Precision::Confusion());
    if (pasnul1 && pasnul2 && pasnul3)
    {
      if (alpha1 * beta1 > 0.0)
        ok = (alpha2 * beta2 > 0.0) || (alpha3 * beta3 > 0.0);
      else
        ok = (alpha2 * beta2 > 0.0) && (alpha3 * beta3 > 0.0);
    }
    else if (pasnul1 && pasnul2 && !pasnul3)
      ok = (alpha1 * beta1 > 0.0) || (alpha2 * beta2 > 0.0);
    else if (pasnul1 && !pasnul2 && pasnul3)
      ok = (alpha1 * beta1 > 0.0) || (alpha3 * beta3 > 0.0);
    else if (!pasnul1 && pasnul2 && pasnul3)
      ok = (alpha2 * beta2 > 0.0) || (alpha3 * beta3 > 0.0);
    else if (pasnul1)
      ok = (alpha1 * beta1 > 0.0);
    else if (pasnul2)
      ok = (alpha2 * beta2 > 0.0);
    else if (pasnul3)
      ok = (alpha3 * beta3 > 0.0);

    if (no_sing && !ok)
    {
      C2->Reverse();
    }
    Seq2.Append(C2);
  }

  return no_sing;
}

GeomFill_Pipe::GeomFill_Pipe()
    : myStatus(GeomFill_PipeNotOk),
      myExchUV(false),
      myKPart(false)
{
  Init();
}

GeomFill_Pipe::GeomFill_Pipe(const occ::handle<Geom_Curve>& Path, const double Radius)
    : myStatus(GeomFill_PipeNotOk),
      myExchUV(false),
      myKPart(false)
{
  Init();
  Init(Path, Radius);
}

GeomFill_Pipe::GeomFill_Pipe(const occ::handle<Geom_Curve>& Path,
                             const occ::handle<Geom_Curve>& FirstSect,
                             const GeomFill_Trihedron       Option)
    : myStatus(GeomFill_PipeNotOk),
      myExchUV(false),
      myKPart(false)
{
  Init();
  Init(Path, FirstSect, Option);
}

GeomFill_Pipe::GeomFill_Pipe(const occ::handle<Geom2d_Curve>& Path,
                             const occ::handle<Geom_Surface>& Support,
                             const occ::handle<Geom_Curve>&   FirstSect)
    : myStatus(GeomFill_PipeNotOk),
      myExchUV(false),
      myKPart(false)
{
  Init();
  Init(Path, Support, FirstSect);
}

GeomFill_Pipe::GeomFill_Pipe(const occ::handle<Geom_Curve>& Path,
                             const occ::handle<Geom_Curve>& FirstSect,
                             const occ::handle<Geom_Curve>& LastSect)
    : myStatus(GeomFill_PipeNotOk),
      myExchUV(false),
      myKPart(false)
{
  Init();
  Init(Path, FirstSect, LastSect);
}

GeomFill_Pipe::GeomFill_Pipe(const occ::handle<Geom_Curve>&                       Path,
                             const NCollection_Sequence<occ::handle<Geom_Curve>>& NSections)
    : myStatus(GeomFill_PipeNotOk),
      myExchUV(false),
      myKPart(false)
{
  Init();
  Init(Path, NSections);
}

GeomFill_Pipe::GeomFill_Pipe(const occ::handle<Geom_Curve>& Path,
                             const occ::handle<Geom_Curve>& Curve1,
                             const gp_Dir&                  Direction)
    : myStatus(GeomFill_PipeNotOk),
      myExchUV(false),
      myKPart(false)
{
  Init(Path, Curve1, Direction);
}

GeomFill_Pipe::GeomFill_Pipe(const occ::handle<Geom_Curve>& Path,
                             const occ::handle<Geom_Curve>& Curve1,
                             const occ::handle<Geom_Curve>& Curve2,
                             const double                   Radius)
    : myStatus(GeomFill_PipeNotOk),
      myExchUV(false),
      myKPart(false)
{
  Init();
  occ::handle<GeomAdaptor_Curve> AdpPath   = new GeomAdaptor_Curve(Path);
  occ::handle<GeomAdaptor_Curve> AdpCurve1 = new GeomAdaptor_Curve(Curve1);
  occ::handle<GeomAdaptor_Curve> AdpCurve2 = new GeomAdaptor_Curve(Curve2);

  Init(AdpPath, AdpCurve1, AdpCurve2, Radius);
}

GeomFill_Pipe::GeomFill_Pipe(const occ::handle<Adaptor3d_Curve>& Path,
                             const occ::handle<Adaptor3d_Curve>& Curve1,
                             const occ::handle<Adaptor3d_Curve>& Curve2,
                             const double                        Radius)
    : myStatus(GeomFill_PipeNotOk),
      myExchUV(false),
      myKPart(false)
{
  Init();
  Init(Path, Curve1, Curve2, Radius);
}

GeomFill_Pipe::GeomFill_Pipe(const occ::handle<Geom_Curve>&      Path,
                             const occ::handle<Adaptor3d_Curve>& Guide,
                             const occ::handle<Geom_Curve>&      FirstSect,
                             const bool                          byACR,
                             const bool                          rotat)
    : myStatus(GeomFill_PipeNotOk),
      myExchUV(false),
      myKPart(false)

{
  Init();
  Init(Path, Guide, FirstSect, byACR, rotat);
}

void GeomFill_Pipe::Init(const occ::handle<Geom_Curve>&      Path,
                         const occ::handle<Adaptor3d_Curve>& Guide,
                         const occ::handle<Geom_Curve>&      FirstSect,
                         const bool                          byACR,
                         const bool                          rotat)

{
  double angle;
  myAdpPath = new (GeomAdaptor_Curve)(occ::down_cast<Geom_Curve>(Path->Copy()));

  occ::handle<GeomFill_TrihedronWithGuide> TLaw;

  if (byACR)
  {
    TLaw = new (GeomFill_GuideTrihedronAC)(Guide);
    TLaw->SetCurve(myAdpPath);
  }
  else
  {
    TLaw = new (GeomFill_GuideTrihedronPlan)(Guide);
    TLaw->SetCurve(myAdpPath);
  }

  occ::handle<GeomFill_LocationGuide> TheLoc = new (GeomFill_LocationGuide)(TLaw);
  TheLoc->SetCurve(myAdpPath);

  GeomFill_SectionPlacement Place(TheLoc, FirstSect);
  Place.Perform(Precision::Confusion());

  mySec = new (GeomFill_UniformSection)(Place.Section(false),
                                        myAdpPath->FirstParameter(),
                                        myAdpPath->LastParameter());

  if (rotat)
    TheLoc->Set(mySec, rotat, myAdpPath->FirstParameter(), myAdpPath->LastParameter(), 0., angle);
  myLoc = TheLoc;
}

void GeomFill_Pipe::Init()
{
  myType       = 0;
  myError      = 0;
  myRadius     = 0.;
  myKPart      = true;
  myPolynomial = false;
  myAdpPath.Nullify();
  myAdpFirstSect.Nullify();
  myAdpLastSect.Nullify();
  myLoc.Nullify();
  mySec.Nullify();
}

void GeomFill_Pipe::Init(const occ::handle<Geom_Curve>& Path, const double Radius)
{

  myType   = 1;
  myError  = 0;
  myRadius = Radius;

  myAdpPath                  = new (GeomAdaptor_Curve)(Path);
  occ::handle<Geom_Circle> C = new (Geom_Circle)(gp::XOY(), Radius);
  C->Rotate(gp::OZ(), M_PI / 2.);

  mySec = new (GeomFill_UniformSection)(C, Path->FirstParameter(), Path->LastParameter());
  occ::handle<GeomFill_CorrectedFrenet> TLaw = new (GeomFill_CorrectedFrenet)();
  myLoc                                      = new (GeomFill_CurveAndTrihedron)(TLaw);
  myLoc->SetCurve(myAdpPath);
}

void GeomFill_Pipe::Init(const occ::handle<Geom_Curve>& Path,
                         const occ::handle<Geom_Curve>& FirstSect,
                         const GeomFill_Trihedron       Option)
{
  occ::handle<Geom_Curve>            Sect;
  occ::handle<GeomFill_TrihedronLaw> TLaw;
  myAdpPath    = new (GeomAdaptor_Curve)(occ::down_cast<Geom_Curve>(Path->Copy()));
  double param = Path->FirstParameter();

  switch (Option)
  {
    case GeomFill_IsCorrectedFrenet:
    {
      TLaw = new (GeomFill_CorrectedFrenet)();
      break;
    }

    case GeomFill_IsDarboux:
#ifdef OCCT_DEBUG
    {
      std::cout << "Option Darboux: non realisable" << std::endl;
    }
#endif
    case GeomFill_IsFrenet:
    {
      TLaw = new (GeomFill_Frenet)();
      break;
    }

    case GeomFill_IsFixed:
    {
      double            Eps = 1.e-9;
      gp_Vec            V1(0, 0, 1), V2(0, 1, 0);
      gp_Dir            D;
      GeomLProp_CLProps CP(Path, param, 2, Eps);
      if (CP.IsTangentDefined())
      {
        CP.Tangent(D);
        V1.SetXYZ(D.XYZ());
        V1.Normalize();
        if (CP.Curvature() > Eps)
        {
          CP.Normal(D);
          V2.SetXYZ(D.XYZ());
          V2.Normalize();
        }
        else
        {
          gp_Pnt P0(0., 0., 0.);
          gp_Ax2 Axe(P0, D);
          D = Axe.XDirection();
          V2.SetXYZ(D.XYZ());
          V2.Normalize();
        }
      }
      TLaw = new (GeomFill_Fixed)(V1, V2);
      break;
    }

    case GeomFill_IsConstantNormal:
    {
      TLaw  = new (GeomFill_Frenet)();
      myLoc = new (GeomFill_CurveAndTrihedron)(TLaw);
      myLoc->SetCurve(myAdpPath);
      GeomFill_SectionPlacement Place(myLoc, FirstSect);
      Place.Perform(Precision::Confusion());
      double ponsec = Place.ParameterOnSection();

      double            Eps = 1.e-9;
      gp_Vec            V(0, 1, 0);
      gp_Dir            D;
      GeomLProp_CLProps CP(FirstSect, ponsec, 2, Eps);
      if (CP.IsTangentDefined())
      {
        CP.Tangent(D);
        if (CP.Curvature() > Eps)
        {
          CP.Normal(D);
          V.SetXYZ(D.XYZ());
          V.Normalize();
        }
        else
        {
          gp_Pnt P0(0., 0., 0.);
          gp_Ax2 Axe(P0, D);
          D = Axe.XDirection();
          V.SetXYZ(D.XYZ());
          V.Normalize();
        }
      }
      TLaw = new (GeomFill_ConstantBiNormal)(V);
      break;
    }

    default:
    {
      throw Standard_ConstructionError("GeomFill::Init : Unknown Option");
    }
  }

  if (!TLaw.IsNull())
  {
    myLoc = new (GeomFill_CurveAndTrihedron)(TLaw);
    myLoc->SetCurve(myAdpPath);
    GeomFill_SectionPlacement Place(myLoc, FirstSect);
    Place.Perform(Precision::Confusion());
    param = Place.ParameterOnPath();
    Sect  = Place.Section(false);

    mySec = new (GeomFill_UniformSection)(Sect, Path->FirstParameter(), Path->LastParameter());
  }
}

void GeomFill_Pipe::Init(const occ::handle<Geom2d_Curve>& Path,
                         const occ::handle<Geom_Surface>& Support,
                         const occ::handle<Geom_Curve>&   FirstSect)
{
  occ::handle<Geom_Curve>            Sect;
  occ::handle<GeomFill_TrihedronLaw> TLaw = new (GeomFill_Darboux)();
  myAdpPath                               = new Adaptor3d_CurveOnSurface(
    Adaptor3d_CurveOnSurface(new Geom2dAdaptor_Curve(Path), new GeomAdaptor_Surface(Support)));

  myLoc = new (GeomFill_CurveAndTrihedron)(TLaw);
  myLoc->SetCurve(myAdpPath);
  GeomFill_SectionPlacement Place(myLoc, FirstSect);
  Place.Perform(myAdpPath, Precision::Confusion());
  Sect = Place.Section(false);

  mySec =
    new (GeomFill_UniformSection)(Sect, myAdpPath->FirstParameter(), myAdpPath->LastParameter());
}

void GeomFill_Pipe::Init(const occ::handle<Geom_Curve>& Path,
                         const occ::handle<Geom_Curve>& FirstSect,
                         const gp_Dir&                  Direction)
{
  Init();

  occ::handle<Geom_Curve> Sect;
  myAdpPath = new (GeomAdaptor_Curve)(occ::down_cast<Geom_Curve>(Path->Copy()));
  gp_Vec V;
  V.SetXYZ(Direction.XYZ());
  occ::handle<GeomFill_ConstantBiNormal> TLaw = new (GeomFill_ConstantBiNormal)(V);

  myLoc = new (GeomFill_CurveAndTrihedron)(TLaw);
  myLoc->SetCurve(myAdpPath);
  GeomFill_SectionPlacement Place(myLoc, FirstSect);
  Place.Perform(Precision::Confusion());
  Sect = Place.Section(false);

  mySec = new (GeomFill_UniformSection)(Sect, Path->FirstParameter(), Path->LastParameter());
}

void GeomFill_Pipe::Init(const occ::handle<Geom_Curve>&                       Path,
                         const NCollection_Sequence<occ::handle<Geom_Curve>>& NSections)
{
  myType   = 3;
  myError  = 0;
  myRadius = 0;

  occ::handle<GeomFill_TrihedronLaw> TLaw;
  TLaw      = new (GeomFill_CorrectedFrenet)();
  myAdpPath = new (GeomAdaptor_Curve)(occ::down_cast<Geom_Curve>(Path->Copy()));
  if (!TLaw.IsNull())
  {
    myLoc = new (GeomFill_CurveAndTrihedron)(TLaw);
    myLoc->SetCurve(myAdpPath);
    NCollection_Sequence<occ::handle<Geom_Curve>> SeqC;
    NCollection_Sequence<double>                  SeqP;
    SeqC.Clear();
    SeqP.Clear();
    int i;
    for (i = 1; i <= NSections.Length(); i++)
    {
      GeomFill_SectionPlacement Place(myLoc, NSections(i));
      Place.Perform(Precision::Confusion());
      SeqP.Append(Place.ParameterOnPath());
      SeqC.Append(Place.Section(false));
    }

    NCollection_Sequence<occ::handle<Geom_Curve>> NewSeq;
    if (CheckSense(SeqC, NewSeq))
      SeqC = NewSeq;

    bool play_again = true;
    while (play_again)
    {
      play_again = false;
      for (i = 1; i <= NSections.Length(); i++)
      {
        for (int j = i; j <= NSections.Length(); j++)
        {
          if (SeqP.Value(i) > SeqP.Value(j))
          {
            SeqP.Exchange(i, j);
            SeqC.Exchange(i, j);
            play_again = true;
          }
        }
      }
    }
    for (i = 1; i < NSections.Length(); i++)
    {
      if (std::abs(SeqP.Value(i + 1) - SeqP.Value(i)) < Precision::PConfusion())
      {
        throw Standard_ConstructionError("GeomFill_Pipe::Init with NSections : invalid parameters");
      }
    }

    double first = Path->FirstParameter(), last = Path->LastParameter();
    double deb, fin;
    deb   = SeqC.First()->FirstParameter();
    fin   = SeqC.First()->LastParameter();
    mySec = new (GeomFill_NSections)(SeqC, SeqP, deb, fin, first, last);
  }
}

void GeomFill_Pipe::Init(const occ::handle<Geom_Curve>& Path,
                         const occ::handle<Geom_Curve>& FirstSect,
                         const occ::handle<Geom_Curve>& LastSect)
{
  myType                                   = 3;
  myError                                  = 0;
  myRadius                                 = 0;
  double                             first = Path->FirstParameter(), last = Path->LastParameter();
  occ::handle<GeomFill_TrihedronLaw> TLaw;
  TLaw      = new (GeomFill_CorrectedFrenet)();
  myAdpPath = new (GeomAdaptor_Curve)(occ::down_cast<Geom_Curve>(Path->Copy()));

  if (!TLaw.IsNull())
  {
    myLoc = new (GeomFill_CurveAndTrihedron)(TLaw);

    if (!(myLoc->SetCurve(myAdpPath)))
    {
      myStatus = GeomFill_ImpossibleContact;
      return;
    }

    NCollection_Sequence<occ::handle<Geom_Curve>> SeqC;
    NCollection_Sequence<double>                  SeqP;
    SeqC.Clear();
    SeqP.Clear();

    GeomFill_SectionPlacement Pl1(myLoc, FirstSect);
    Pl1.Perform(first, Precision::Confusion());
    SeqC.Append(Pl1.Section(false));
    GeomFill_SectionPlacement Pl2(myLoc, LastSect);
    Pl2.Perform(first, Precision::Confusion());
    SeqC.Append(Pl2.Section(false));

    SeqP.Append(first);
    SeqP.Append(last);

    NCollection_Sequence<occ::handle<Geom_Curve>> NewSeq;
    if (CheckSense(SeqC, NewSeq))
      SeqC = NewSeq;

    double deb, fin;
    deb   = SeqC.First()->FirstParameter();
    fin   = SeqC.First()->LastParameter();
    mySec = new (GeomFill_NSections)(SeqC, SeqP, deb, fin, first, last);
  }
}

void GeomFill_Pipe::Init(const occ::handle<Adaptor3d_Curve>& Path,
                         const occ::handle<Adaptor3d_Curve>& Curve1,
                         const occ::handle<Adaptor3d_Curve>& Curve2,
                         const double                        Radius)
{
  myType         = 4;
  myError        = 0;
  myRadius       = Radius;
  myAdpPath      = Path;
  myAdpFirstSect = Curve1;
  myAdpLastSect  = Curve2;
}

void GeomFill_Pipe::Perform(const bool WithParameters, const bool Polynomial)
{

  if ((!myLoc.IsNull()) && (!mySec.IsNull()))
  {
    Perform(1.e-4, Polynomial);
    return;
  }

  myPolynomial = Polynomial;

  if (myPolynomial)
  {
    ApproxSurf(WithParameters);
    return;
  }
  if (!KPartT4())
    ApproxSurf(WithParameters);
}

void GeomFill_Pipe::Perform(const double        Tol,
                            const bool          Polynomial,
                            const GeomAbs_Shape Conti,
                            const int           DegMax,
                            const int           NbMaxSegment)
{
  if (myStatus == GeomFill_ImpossibleContact)
  {
    return;
  }

  GeomAbs_Shape TheConti;
  switch (Conti)
  {
    case GeomAbs_C0:
    {
      TheConti = GeomAbs_C0;
    }
    break;
    case GeomAbs_G1:
    case GeomAbs_C1:
    {
      TheConti = GeomAbs_C1;
    }
    break;
    case GeomAbs_G2:
    case GeomAbs_C2:
    {
      TheConti = GeomAbs_C2;
    }
    break;
    default:
      TheConti = GeomAbs_C2;
  }
  occ::handle<Approx_SweepFunction> Func;
  Func.Nullify();

  if (myType == 4)
  {
    if (!KPartT4())
    {
      Func = new (
        GeomFill_CircularBlendFunc)(myAdpPath, myAdpFirstSect, myAdpLastSect, myRadius, Polynomial);

      Approx_SweepApproximation App(Func);
      App.Perform(myAdpPath->FirstParameter(),
                  myAdpPath->LastParameter(),
                  Tol,
                  Tol,
                  0.,
                  0.01,
                  TheConti,
                  DegMax,
                  NbMaxSegment);
#ifdef OCCT_DEBUG
      std::cout << "Tuyau : ";
      App.Dump(std::cout);
      std::cout << std::endl;
#endif
      if (App.IsDone())
      {
        mySurface = new Geom_BSplineSurface(App.SurfPoles(),
                                            App.SurfWeights(),
                                            App.SurfUKnots(),
                                            App.SurfVKnots(),
                                            App.SurfUMults(),
                                            App.SurfVMults(),
                                            App.UDegree(),
                                            App.VDegree());
        myError   = App.MaxErrorOnSurf();
        myStatus  = GeomFill_PipeOk;
      }
    }
  }
  else if ((!myLoc.IsNull()) && (!mySec.IsNull()))
  {
    GeomFill_Sweep Sweep(myLoc, myKPart);
    Sweep.SetTolerance(Tol);
    Sweep.Build(mySec, GeomFill_Location, TheConti, DegMax, NbMaxSegment);
    if (Sweep.IsDone())
    {
      mySurface = Sweep.Surface();
      myError   = Sweep.ErrorOnSurface();
      myStatus  = GeomFill_PipeOk;
    }
  }
  else
  {
    Perform(true, Polynomial);
  }
}

bool GeomFill_Pipe::KPartT4()
{
  bool Ok = false;

  if (myAdpPath->GetType() == GeomAbs_Line && myAdpFirstSect->GetType() == GeomAbs_Line
      && myAdpLastSect->GetType() == GeomAbs_Line)
  {

    gp_Ax1 A0 = myAdpPath->Line().Position();
    gp_Ax1 A1 = myAdpFirstSect->Line().Position();
    gp_Ax1 A2 = myAdpLastSect->Line().Position();

    gp_Dir D0 = A0.Direction();
    gp_Dir D1 = A1.Direction();
    gp_Dir D2 = A2.Direction();
    if (!D0.IsEqual(D1, Precision::Angular()) || !D1.IsEqual(D2, Precision::Angular()))
    {
      return Ok;
    }

    double L0 = myAdpPath->LastParameter() - myAdpPath->FirstParameter();
    double L1 = myAdpFirstSect->LastParameter() - myAdpFirstSect->FirstParameter();
    double L2 = myAdpLastSect->LastParameter() - myAdpLastSect->FirstParameter();
    if (std::abs(L1 - L0) > Precision::Confusion() || std::abs(L2 - L0) > Precision::Confusion())
    {
      return Ok;
    }

    gp_Pnt P0 = myAdpPath->Value(myAdpPath->FirstParameter());
    gp_Pnt P1 = myAdpFirstSect->Value(myAdpFirstSect->FirstParameter());
    gp_Pnt P2 = myAdpLastSect->Value(myAdpLastSect->FirstParameter());
    gp_Dir V1(gp_Vec(P0, P1));
    gp_Dir V2(gp_Vec(P0, P2));
    if (std::abs(V1.Dot(D0)) > Precision::Confusion()
        || std::abs(V2.Dot(D0)) > Precision::Confusion())
      return Ok;

    gp_Dir X(V1), Y(V2), ZRef;
    ZRef = X.Crossed(Y);

    gp_Ax3 Axis(A0.Location(), D0, X);
    if (ZRef.Dot(D0) < 0.)
      Axis.YReverse();

    Axis.Rotate(gp_Ax1(P0, ZRef), -M_PI / 2.);

    mySurface    = new Geom_CylindricalSurface(Axis, myRadius);
    double Alpha = V1.AngleWithRef(V2, ZRef);
    mySurface    = new Geom_RectangularTrimmedSurface(mySurface,
                                                   M_PI / 2.,
                                                   M_PI / 2. + Alpha,
                                                   myAdpPath->FirstParameter(),
                                                   myAdpPath->LastParameter());
    Ok           = true;
    myStatus     = GeomFill_PipeOk;
  }

  else if (myAdpPath->GetType() == GeomAbs_Circle && myAdpFirstSect->GetType() == GeomAbs_Circle
           && myAdpLastSect->GetType() == GeomAbs_Circle)
  {

    double Alp0 = myAdpPath->FirstParameter() - myAdpPath->LastParameter();
    double Alp1 = myAdpFirstSect->FirstParameter() - myAdpFirstSect->LastParameter();
    double Alp2 = myAdpLastSect->FirstParameter() - myAdpLastSect->LastParameter();

    if (std::abs(Alp0 - Alp1) > Precision::Angular()
        || std::abs(Alp0 - Alp2) > Precision::Angular())
      return Ok;

    gp_Ax2 A0 = myAdpPath->Circle().Position();
    gp_Ax2 A1 = myAdpFirstSect->Circle().Position();
    gp_Ax2 A2 = myAdpLastSect->Circle().Position();
    gp_Dir D0 = A0.Direction();
    gp_Dir D1 = A1.Direction();
    gp_Dir D2 = A2.Direction();
    gp_Pnt P0 = myAdpPath->Value(myAdpPath->FirstParameter());
    gp_Pnt P1 = myAdpFirstSect->Value(myAdpFirstSect->FirstParameter());
    gp_Pnt P2 = myAdpLastSect->Value(myAdpLastSect->FirstParameter());

    if (!D0.IsEqual(D1, Precision::Angular()) || !D1.IsEqual(D2, Precision::Angular()))
      return Ok;

    gp_Lin L(A0.Axis());
    if (!L.Contains(A1.Location(), Precision::Confusion())
        || !L.Contains(A2.Location(), Precision::Confusion()))
      return Ok;

    gp_Dir  V1(gp_Vec(P0, P1));
    gp_Dir  V2(gp_Vec(P0, P2));
    gp_Circ Ci   = myAdpPath->Circle();
    gp_Vec  YRef = ElCLib::CircleDN(myAdpPath->FirstParameter(), A0, Ci.Radius(), 1);
    if (std::abs(V1.Dot(YRef)) > Precision::Confusion()
        || std::abs(V2.Dot(YRef)) > Precision::Confusion())
      return Ok;

    gp_Torus T(A0, Ci.Radius(), myRadius);
    gp_Vec   XRef(A0.Location(), P0);

    double VV1    = V1.AngleWithRef(XRef, YRef);
    double VV2    = V2.AngleWithRef(XRef, YRef);
    double deltaV = V2.AngleWithRef(V1, YRef);
    if (deltaV < 0.)
    {
      T.VReverse();
      VV1 = -VV1;
      VV2 = 2 * M_PI + VV1 - deltaV;
    }
    mySurface = new Geom_RectangularTrimmedSurface(new Geom_ToroidalSurface(T),
                                                   myAdpPath->FirstParameter(),
                                                   myAdpPath->LastParameter(),
                                                   VV1,
                                                   VV2);
    myExchUV  = true;
    Ok        = true;
    myStatus  = GeomFill_PipeOk;
  }

  return Ok;
}

void GeomFill_Pipe::ApproxSurf(const bool WithParameters)
{

  if (myType != 4)
    throw Standard_ConstructionError("GeomFill_Pipe");
  GeomFill_SweepSectionGenerator Section(myAdpPath, myAdpFirstSect, myAdpLastSect, myRadius);

  Section.Perform(myPolynomial);

#ifdef OCCT_DEBUG
  if (Affich)
  {
    int NbPoles, NbKnots, Degree, NbPoles2d;
    Section.GetShape(NbPoles, NbKnots, Degree, NbPoles2d);

    NCollection_Array1<gp_Pnt>   Poles(1, NbPoles);
    NCollection_Array1<gp_Pnt2d> Poles2d(1, NbPoles);
    NCollection_Array1<double>   Weights(1, NbPoles);
    NCollection_Array1<int>      Mults(1, NbKnots);
    NCollection_Array1<double>   Knots(1, NbKnots);
    Section.Knots(Knots);
    Section.Mults(Mults);

    for (int i = 1; i <= Section.NbSections(); i++)
    {
      NbSections++;
      Section.Section(i, Poles, Poles2d, Weights);
      occ::handle<Geom_BSplineCurve> BS =
        new Geom_BSplineCurve(Poles, Weights, Knots, Mults, Degree);
    }
  }
#endif

  occ::handle<GeomFill_Line> Line = new GeomFill_Line(Section.NbSections());
  int                        NbIt = 0;
  constexpr double           T3d  = Precision::Approximation();
  constexpr double           T2d  = Precision::PApproximation();
  GeomFill_AppSweep          App(4, 8, T3d, T2d, NbIt, WithParameters);

  App.Perform(Line, Section, 30);

  if (!App.IsDone())
  {
#ifdef OCCT_DEBUG

    int NbPoles, NbKnots, Degree, NbPoles2d;
    Section.GetShape(NbPoles, NbKnots, Degree, NbPoles2d);

    NCollection_Array1<gp_Pnt>   Poles(1, NbPoles);
    NCollection_Array1<gp_Pnt2d> Poles2d(1, NbPoles);
    NCollection_Array1<double>   Weights(1, NbPoles);
    NCollection_Array1<int>      Mults(1, NbKnots);
    NCollection_Array1<double>   Knots(1, NbKnots);
    Section.Knots(Knots);
    Section.Mults(Mults);

    for (int i = 1; i <= Section.NbSections(); i++)
    {
      Section.Section(i, Poles, Poles2d, Weights);
      occ::handle<Geom_BSplineCurve> BS =
        new Geom_BSplineCurve(Poles, Weights, Knots, Mults, Degree);
    }
#endif
  }
  else
  {
    int UDegree, VDegree, NbUPoles, NbVPoles, NbUKnots, NbVKnots;
    App.SurfShape(UDegree, VDegree, NbUPoles, NbVPoles, NbUKnots, NbVKnots);

    mySurface = new Geom_BSplineSurface(App.SurfPoles(),
                                        App.SurfWeights(),
                                        App.SurfUKnots(),
                                        App.SurfVKnots(),
                                        App.SurfUMults(),
                                        App.SurfVMults(),
                                        App.UDegree(),
                                        App.VDegree());
    double t2d;
    App.TolReached(myError, t2d);
    myStatus = GeomFill_PipeOk;
  }
}

#include <BRep_Builder.hpp>
#include <BRep_Tool.hpp>
#include <BRepTools.hpp>
#include <Draft_Modification.hpp>
#include <Draft_VertexInfo.hpp>
#include <Geom2d_Curve.hpp>
#include <Geom_Circle.hpp>
#include <Geom_ConicalSurface.hpp>
#include <Geom_Curve.hpp>
#include <Geom_CylindricalSurface.hpp>
#include <Geom_RectangularTrimmedSurface.hpp>
#include <Geom_SphericalSurface.hpp>
#include <Geom_Surface.hpp>
#include <Geom_SurfaceOfLinearExtrusion.hpp>
#include <Geom_TrimmedCurve.hpp>
#include <GeomProjLib.hpp>
#include <gp_Dir.hpp>
#include <gp_Pln.hpp>
#include <gp_Pnt.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Vec2d.hpp>
#include <Precision.hpp>
#include <Standard_ConstructionError.hpp>
#include <Standard_DomainError.hpp>
#include <Standard_NoSuchObject.hpp>
#include <Standard_Type.hpp>
#include <StdFail_NotDone.hpp>
#include <TopExp.hpp>
#include <TopLoc_Location.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDS_Vertex.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Draft_Modification, BRepTools_Modification)

Draft_Modification::Draft_Modification(const TopoDS_Shape& S)
    : myComp(false),
      myShape(S)
{
  TopExp::MapShapesAndAncestors(myShape, TopAbs_EDGE, TopAbs_FACE, myEFMap);
}

void Draft_Modification::Clear()
{
  myComp = false;
  myFMap.Clear();
  myEMap.Clear();
  myVMap.Clear();
  myEFMap.Clear();
  badShape.Nullify();
  errStat = Draft_NoError;
}

void Draft_Modification::Init(const TopoDS_Shape& S)
{
  myShape = S;
  Clear();
  TopExp::MapShapesAndAncestors(myShape, TopAbs_EDGE, TopAbs_FACE, myEFMap);
}

bool Draft_Modification::Add(const TopoDS_Face& F,
                             const gp_Dir&      Direction,
                             const double       Angle,
                             const gp_Pln&      NeutralPlane,
                             const bool         Flag)
{
  if (!badShape.IsNull())
  {
    throw Standard_ConstructionError();
  }

  if (myComp)
  {
    Clear();
  }
  curFace = F;
  return InternalAdd(F, Direction, Angle, NeutralPlane, Flag);
}

void Draft_Modification::Remove(const TopoDS_Face& F)
{
  if (!myFMap.Contains(F) || myComp)
  {
    throw Standard_NoSuchObject();
  }

  conneF.Clear();
  NCollection_List<TopoDS_Shape>::Iterator ltod;

  curFace = myFMap.FindFromKey(F).RootFace();
  for (int i = 1; i <= myFMap.Extent(); i++)
  {
    const TopoDS_Face& theF = myFMap.FindKey(i);
    if (myFMap.FindFromKey(theF).RootFace().IsSame(curFace))
    {
      conneF.Append(theF);
      if (theF.IsSame(badShape))
      {
        badShape.Nullify();
      }
    }
  }

  ltod.Initialize(conneF);
  while (ltod.More())
  {
    myFMap.RemoveKey(TopoDS::Face(ltod.Value()));
    ltod.Next();
  }

  conneF.Clear();
  for (int i = 1; i <= myEMap.Extent(); i++)
  {
    const TopoDS_Edge& theE = myEMap.FindKey(i);
    if (myEMap.FindFromKey(theE).RootFace().IsSame(curFace))
      conneF.Append(theE);
  }
  ltod.Initialize(conneF);
  while (ltod.More())
  {
    myEMap.RemoveKey(TopoDS::Edge(ltod.Value()));
    ltod.Next();
  }
}

bool Draft_Modification::IsDone() const
{
  return myComp && badShape.IsNull();
}

Draft_ErrorStatus Draft_Modification::Error() const
{
  return errStat;
}

const TopoDS_Shape& Draft_Modification::ProblematicShape() const
{
  return badShape;
}

const NCollection_List<TopoDS_Shape>& Draft_Modification::ConnectedFaces(const TopoDS_Face& F)
{
  if (!myFMap.Contains(F))
  {
    throw Standard_NoSuchObject();
  }
  if (!IsDone())
  {
    throw StdFail_NotDone();
  }
  conneF.Clear();
  curFace = myFMap.FindFromKey(F).RootFace();

  for (int i = 1; i <= myFMap.Extent(); i++)
  {
    const TopoDS_Face& theF = myFMap.FindKey(i);
    if (myFMap.FindFromKey(theF).RootFace().IsSame(curFace))
    {
      conneF.Append(theF);
    }
  }

  return conneF;
}

const NCollection_List<TopoDS_Shape>& Draft_Modification::ModifiedFaces()
{
  if (!badShape.IsNull())
  {
    throw StdFail_NotDone();
  }
  conneF.Clear();

  for (int i = 1; i <= myFMap.Extent(); i++)
  {
    const TopoDS_Face& theF = myFMap.FindKey(i);
    if (!myFMap.FindFromKey(theF).RootFace().IsNull())
    {
      conneF.Append(theF);
    }
  }

  return conneF;
}

bool Draft_Modification::NewSurface(const TopoDS_Face&         F,
                                    occ::handle<Geom_Surface>& S,
                                    TopLoc_Location&           L,
                                    double&                    Tol,
                                    bool&                      RevWires,
                                    bool&                      RevFace)
{
  if (!IsDone())
  {
    throw Standard_DomainError();
  }

  if (!myFMap.Contains(F) || !myFMap.FindFromKey(F).NewGeometry())
  {
    return false;
  }

  RevWires = false;
  RevFace  = false;
  Tol      = BRep_Tool::Tolerance(F);

  S = BRep_Tool::Surface(F, L);

  L.Identity();

  S = myFMap.FindFromKey(F).Geometry();

  return true;
}

bool Draft_Modification::NewCurve(const TopoDS_Edge&       E,
                                  occ::handle<Geom_Curve>& C,
                                  TopLoc_Location&         L,
                                  double&                  Tol)
{
  if (!IsDone())
  {
    throw Standard_DomainError();
  }

  if (!myEMap.Contains(E))
    return false;

  const Draft_EdgeInfo& Einf = myEMap.FindFromKey(E);
  if (!myEMap.FindFromKey(E).NewGeometry())
    return false;

  Tol = Einf.Tolerance();
  Tol = std::max(Tol, BRep_Tool::Tolerance(E));
  L.Identity();
  C = myEMap.FindFromKey(E).Geometry();

  return true;
}

bool Draft_Modification::NewPoint(const TopoDS_Vertex& V, gp_Pnt& P, double& Tol)
{
  if (!IsDone())
  {
    throw Standard_DomainError();
  };

  if (!myVMap.Contains(V))
  {
    return false;
  }

  Tol = BRep_Tool::Tolerance(V);
  P   = myVMap.FindFromKey(V).Geometry();
  return true;
}

bool Draft_Modification::NewCurve2d(const TopoDS_Edge& E,
                                    const TopoDS_Face& F,
                                    const TopoDS_Edge& NewE,
                                    const TopoDS_Face&,
                                    occ::handle<Geom2d_Curve>& C,
                                    double&                    Tol)
{

  if (!IsDone())
  {
    throw Standard_DomainError();
  };

  if (!myEMap.Contains(E))
  {
    return false;
  }

  double Fp, Lp;
  BRep_Tool::Range(NewE, Fp, Lp);

  occ::handle<Geom_Surface> SB = myFMap.FindFromKey(F).Geometry();

  Tol = BRep_Tool::Tolerance(E);

  const Draft_EdgeInfo& Einf = myEMap.FindFromKey(E);
  if (Einf.FirstFace().IsSame(F) && !Einf.FirstPC().IsNull())
  {
    C = Einf.FirstPC();
  }
  else if (Einf.SecondFace().IsSame(F) && !Einf.SecondPC().IsNull())
  {
    C = Einf.SecondPC();
  }
  else
  {

    if (!myEMap.FindFromKey(E).NewGeometry())
    {
      double Fpi, Lpi;
      BRep_Tool::Range(E, Fpi, Lpi);
      if (Fpi <= Fp && Fp <= Lpi && Fpi <= Lp && Lp <= Lpi)
      {
        return false;
      }
    }

    BRep_Tool::Range(NewE, Fp, Lp);
    occ::handle<Geom_TrimmedCurve> TC =
      new Geom_TrimmedCurve(myEMap.FindFromKey(E).Geometry(), Fp, Lp);
    Fp = TC->FirstParameter();
    Lp = TC->LastParameter();
    BRep_Builder B;
    B.Range(NewE, Fp, Lp);
    C = GeomProjLib::Curve2d(TC, Fp, Lp, SB, Tol);
  }

  occ::handle<Standard_Type> typs = SB->DynamicType();
  if (typs == STANDARD_TYPE(Geom_RectangularTrimmedSurface))
  {
    SB   = occ::down_cast<Geom_RectangularTrimmedSurface>(SB)->BasisSurface();
    typs = SB->DynamicType();
  }

  bool JeRecadre = false;
  if (typs == STANDARD_TYPE(Geom_SurfaceOfLinearExtrusion))
  {
    occ::handle<Geom_Curve>    aC = occ::down_cast<Geom_SurfaceOfLinearExtrusion>(SB)->BasisCurve();
    occ::handle<Standard_Type> typc = aC->DynamicType();
    if (typc == STANDARD_TYPE(Geom_Circle))
      JeRecadre = true;
  }

  JeRecadre = JeRecadre || (typs == STANDARD_TYPE(Geom_CylindricalSurface))
              || (typs == STANDARD_TYPE(Geom_SphericalSurface))
              || (typs == STANDARD_TYPE(Geom_ConicalSurface));

  if (JeRecadre)
  {
    bool                      bTranslate;
    double                    aD2, aT1, aT2;
    gp_Pnt2d                  PF, NewPF;
    gp_Vec2d                  aV2DT, vectra(2. * M_PI, 0.);
    occ::handle<Geom2d_Curve> aC2DE;

    aC2DE = BRep_Tool::CurveOnSurface(E, F, aT1, aT2);

    PF = aC2DE->Value(0.5 * (aT1 + aT2));

    NewPF = C->Value(0.5 * (Fp + Lp));

    aD2 = NewPF.SquareDistance(PF);

    bTranslate = false;
    if (NewPF.Translated(vectra).SquareDistance(PF) < aD2)
    {
      aV2DT      = vectra;
      bTranslate = !bTranslate;
    }
    else if (NewPF.Translated(-vectra).SquareDistance(PF) < aD2)
    {
      aV2DT      = -vectra;
      bTranslate = !bTranslate;
    }

    if (bTranslate)
    {
      C->Translate(aV2DT);
    }
  }

  occ::handle<Geom_Curve> aC3d = BRep_Tool::Curve(NewE, Fp, Lp);
  Tol                          = BRepTools::EvalAndUpdateTol(NewE, aC3d, C, SB, Fp, Lp);
  return true;
}

bool Draft_Modification::NewParameter(const TopoDS_Vertex& V,
                                      const TopoDS_Edge&   E,
                                      double&              P,
                                      double&              Tol)
{

  if (!IsDone())
  {
    throw Standard_DomainError();
  };

  if (!myVMap.Contains(V))
  {
    return false;
  }

  P                               = myVMap.ChangeFromKey(V).Parameter(E);
  occ::handle<Geom_Curve>    GC   = myEMap.FindFromKey(E).Geometry();
  occ::handle<Standard_Type> typc = GC->DynamicType();
  if (typc == STANDARD_TYPE(Geom_TrimmedCurve))
  {
    GC   = occ::down_cast<Geom_TrimmedCurve>(GC);
    typc = GC->DynamicType();
  }

  if (GC->IsClosed())
  {
    TopoDS_Vertex FV = TopExp::FirstVertex(E);
    double        paramf;
    if (myVMap.Contains(FV))
    {
      paramf = myVMap.ChangeFromKey(FV).Parameter(E);
    }
    else
    {
      paramf = BRep_Tool::Parameter(FV, E);
    }

    double           FirstPar = GC->FirstParameter(), LastPar = GC->LastParameter();
    constexpr double pconf = Precision::PConfusion();
    if (std::abs(paramf - LastPar) <= pconf)
    {
      paramf = FirstPar;
      FV.Orientation(E.Orientation());
      if (V.IsEqual(FV))
        P = paramf;
    }

    FV.Orientation(E.Orientation());
    if (!V.IsEqual(FV) && P <= paramf)
    {
      if (GC->IsPeriodic())
      {
        P += GC->Period();
      }
      else
      {
        P = GC->LastParameter();
      }
    }
  }

  Tol = std::max(BRep_Tool::Tolerance(V), BRep_Tool::Tolerance(E));
  return true;
}

GeomAbs_Shape Draft_Modification::Continuity(const TopoDS_Edge& E,
                                             const TopoDS_Face& F1,
                                             const TopoDS_Face& F2,
                                             const TopoDS_Edge&,
                                             const TopoDS_Face&,
                                             const TopoDS_Face&)
{
  return BRep_Tool::Continuity(E, F1, F2);
}

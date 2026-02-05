#include <BRep_Tool.hpp>
#include <BRepAdaptor_CompCurve.hpp>
#include <BRepExtrema_DistShapeShape.hpp>
#include <BRepFill_LocationLaw.hpp>
#include <BRepFill_SectionPlacement.hpp>
#include <Geom_BSplineCurve.hpp>
#include <Geom_CartesianPoint.hpp>
#include <Geom_Curve.hpp>
#include <Geom_TrimmedCurve.hpp>
#include <GeomAdaptor_Curve.hpp>
#include <GeomConvert_CompCurveToBSplineCurve.hpp>
#include <GeomFill_LocationLaw.hpp>
#include <GeomFill_SectionPlacement.hpp>
#include <gp_Trsf.hpp>
#include <Precision.hpp>
#include <Standard_ConstructionError.hpp>
#include <Standard_NotImplemented.hpp>
#include <NCollection_Array1.hpp>
#include <TopAbs_ShapeEnum.hpp>
#include <TopExp.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDS_Vertex.hpp>

static double SearchParam(const occ::handle<BRepFill_LocationLaw>& Law,
                          const int                                Ind,
                          const TopoDS_Vertex&                     TheV)
{
  double      t;
  TopoDS_Edge E;
  E = Law->Edge(Ind);
  t = BRep_Tool::Parameter(TheV, E);
  if (E.Orientation() == TopAbs_REVERSED)
  {
    double                  f, l, Lf, Ll;
    occ::handle<Geom_Curve> C;
    C  = BRep_Tool::Curve(E, f, l);
    Lf = Law->Law(Ind)->GetCurve()->FirstParameter();
    Ll = Law->Law(Ind)->GetCurve()->LastParameter();
    t  = Ll - (t - f) * (Ll - Lf) / (l - f);
  }
  return t;
}

BRepFill_SectionPlacement::BRepFill_SectionPlacement(const occ::handle<BRepFill_LocationLaw>& Law,
                                                     const TopoDS_Shape& Section,
                                                     const bool          WithContact,
                                                     const bool          WithCorrection)
    : myLaw(Law),
      mySection(Section)
{
  TopoDS_Vertex VNull;
  VNull.Nullify();
  Perform(WithContact, WithCorrection, VNull);
}

BRepFill_SectionPlacement::BRepFill_SectionPlacement(const occ::handle<BRepFill_LocationLaw>& Law,
                                                     const TopoDS_Shape& Section,
                                                     const TopoDS_Shape& Vertex,
                                                     const bool          WithContact,
                                                     const bool          WithCorrection)
    : myLaw(Law),
      mySection(Section)
{
  Perform(WithContact, WithCorrection, Vertex);
}

void BRepFill_SectionPlacement::Perform(const bool          WithContact,
                                        const bool          WithCorrection,
                                        const TopoDS_Shape& Vertex)
{
  double                  anEdgeStartParam = 0.;
  double                  anEdgeEndParam   = 0.;
  occ::handle<Geom_Curve> aCurve;

  // Here we are simply looking for the first valid curve in the section.
  TopExp_Explorer anEdgeExplorer(mySection, TopAbs_EDGE);
  for (; anEdgeExplorer.More(); anEdgeExplorer.Next())
  {
    const TopoDS_Edge anEdge = TopoDS::Edge(anEdgeExplorer.Current());
    if (anEdge.IsNull() || BRep_Tool::Degenerated(anEdge))
      continue;

    aCurve = BRep_Tool::Curve(anEdge, anEdgeStartParam, anEdgeEndParam);
    if (aCurve.IsNull())
      continue;

    break;
  }

  occ::handle<Geom_Geometry> aSection;
  if (aCurve.IsNull())
  {
    // No edge found : the section is a vertex
    TopExp_Explorer     aVertexExplorer(mySection, TopAbs_VERTEX);
    const TopoDS_Vertex aFirstVertex = TopoDS::Vertex(aVertexExplorer.Current());
    const gp_Pnt        aPoint       = BRep_Tool::Pnt(aFirstVertex);
    aSection                         = new Geom_CartesianPoint(aPoint);
  }
  else
  {
    occ::handle<Geom_TrimmedCurve> aTrimmedCurve =
      new Geom_TrimmedCurve(aCurve, anEdgeStartParam, anEdgeEndParam);
    anEdgeExplorer.Next();

    if (anEdgeExplorer.More())
    {
      constexpr double                    aPrecisionTolerance = Precision::Confusion();
      GeomConvert_CompCurveToBSplineCurve aBSplineConverter(aTrimmedCurve);
      for (; anEdgeExplorer.More(); anEdgeExplorer.Next())
      {
        TopoDS_Edge anEdge = TopoDS::Edge(anEdgeExplorer.Current());
        // avoid null, degenerated edges
        if (anEdge.IsNull() || BRep_Tool::Degenerated(anEdge))
          continue;

        aCurve = BRep_Tool::Curve(anEdge, anEdgeStartParam, anEdgeEndParam);
        if (aCurve.IsNull())
          continue;

        TopoDS_Vertex aFirstVertex;
        TopoDS_Vertex aLastVertex;
        TopExp::Vertices(anEdge, aFirstVertex, aLastVertex);
        const double aVertexTolerance =
          std::max(BRep_Tool::Tolerance(aFirstVertex), BRep_Tool::Tolerance(aLastVertex));

        aTrimmedCurve = new Geom_TrimmedCurve(aCurve, anEdgeStartParam, anEdgeEndParam);
        if (!aBSplineConverter.Add(aTrimmedCurve, std::min(aPrecisionTolerance, aVertexTolerance)))
        {
          aBSplineConverter.Add(aTrimmedCurve, std::max(aPrecisionTolerance, aVertexTolerance));
        }
      }
      aCurve = aBSplineConverter.BSplineCurve();
    }
    else
    {
      aCurve = aTrimmedCurve;
    }

    aSection = aCurve;
  }

  GeomFill_SectionPlacement          aSectionPlacement(myLaw->Law(1), aSection);
  occ::handle<BRepAdaptor_CompCurve> aWireAdaptor = new BRepAdaptor_CompCurve(myLaw->Wire());
  aSectionPlacement.Perform(aWireAdaptor, Precision::Confusion());

  const double     aSectionParam   = aSectionPlacement.ParameterOnPath();
  constexpr double aParamConfusion = Precision::PConfusion();

  int aLawIndex1 = 0;
  int aLawIndex2 = 0;
  // In the general case : Localisation via concatenation of the spine
  bool anIsIntervalFound = false;
  for (int aLawIndex = 1; aLawIndex <= myLaw->NbLaw() && !anIsIntervalFound; ++aLawIndex)
  {
    const double aCurrKnotParam = aLawIndex - 1;
    const double aNextKnotParam = aLawIndex;

    // Check if the section parameter is in the interval [aCurrKnotParam, aNextKnotParam]
    anIsIntervalFound = (aCurrKnotParam - aParamConfusion <= aSectionParam)
                        && (aNextKnotParam + aParamConfusion >= aSectionParam);
    if (!anIsIntervalFound)
    {
      continue;
    }

    aLawIndex1 = aLawIndex;
    if ((std::abs(aSectionParam - aCurrKnotParam) < aParamConfusion) && (aLawIndex > 1))
    {
      aLawIndex2 = aLawIndex - 1;
    }
    else if ((std::abs(aSectionParam - aNextKnotParam) < aParamConfusion)
             && (aLawIndex < myLaw->NbLaw()))
    {
      aLawIndex2 = aLawIndex + 1;
    }
  }

  if (!anIsIntervalFound)
  {
    throw Standard_ConstructionError("Interval is not found");
  }

  // Search of the <Ind1> by vertex <TheV>
  bool          anIsVertexOnLaw = false;
  TopoDS_Vertex aVertex         = TopoDS::Vertex(Vertex);
  if (!aVertex.IsNull())
  {
    for (int aCurrentLawIndex = 1; aCurrentLawIndex <= myLaw->NbLaw(); ++aCurrentLawIndex)
    {
      TopoDS_Edge   anEdge = myLaw->Edge(aCurrentLawIndex);
      TopoDS_Vertex V1, V2;
      TopExp::Vertices(anEdge, V1, V2);
      if (V1.IsSame(aVertex) || V2.IsSame(aVertex))
      {
        anIsVertexOnLaw = true;
        aLawIndex1      = aCurrentLawIndex;
        aLawIndex2      = 0;
        break;
      }
    }
  }
  ////////////////////

  // Positioning on the localized edge (or 2 Edges)

  aSectionPlacement.SetLocation(myLaw->Law(aLawIndex1));
  if (!anIsVertexOnLaw)
  {
    aSectionPlacement.Perform(Precision::Confusion());
  }
  else
  {
    aSectionPlacement.Perform(SearchParam(myLaw, aLawIndex1, aVertex), Precision::Confusion());
  }

  myTrsf       = aSectionPlacement.Transformation(WithContact, WithCorrection);
  myIndex      = aLawIndex1;
  myParam      = aSectionPlacement.ParameterOnPath();
  double Angle = aSectionPlacement.Angle();

  if (aLawIndex2)
  {
    aSectionPlacement.SetLocation(myLaw->Law(aLawIndex2));
    if (!anIsVertexOnLaw)
    {
      aSectionPlacement.Perform(Precision::Confusion());
    }
    else
    {
      if (aLawIndex1 == aLawIndex2)
        aVertex.Reverse();
      aSectionPlacement.Perform(SearchParam(myLaw, aLawIndex2, aVertex), Precision::Confusion());
    }
    if (aSectionPlacement.Angle() > Angle)
    {
      myTrsf  = aSectionPlacement.Transformation(WithContact, WithCorrection);
      myIndex = aLawIndex2;
      myParam = aSectionPlacement.ParameterOnPath();
    }
  }
}

const gp_Trsf& BRepFill_SectionPlacement::Transformation() const
{
  return myTrsf;
}

double BRepFill_SectionPlacement::AbscissaOnPath()
{
  return myLaw->Abscissa(myIndex, myParam);
}

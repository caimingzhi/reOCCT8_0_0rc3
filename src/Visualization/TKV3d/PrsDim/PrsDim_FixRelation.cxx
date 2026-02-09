#include <PrsDim_FixRelation.hpp>

#include <PrsDim.hpp>
#include <BRep_Tool.hpp>
#include <BRepAdaptor_Curve.hpp>
#include <DsgPrs_FixPresentation.hpp>
#include <ElCLib.hpp>
#include <Geom_Circle.hpp>
#include <Geom_Curve.hpp>
#include <Geom_Line.hpp>
#include <Geom_Plane.hpp>
#include <gp_Ax1.hpp>
#include <gp_Circ.hpp>
#include <gp_Dir.hpp>
#include <gp_Lin.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <gp_XYZ.hpp>
#include <Precision.hpp>
#include <Prs3d_Presentation.hpp>
#include <Select3D_SensitiveSegment.hpp>
#include <SelectMgr_EntityOwner.hpp>
#include <SelectMgr_Selection.hpp>
#include <Standard_Transient.hpp>
#include <NCollection_List.hpp>
#include <TopAbs_ShapeEnum.hpp>
#include <TopExp.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDS_Vertex.hpp>
#include <TopoDS_Wire.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <NCollection_IndexedMap.hpp>

IMPLEMENT_STANDARD_RTTIEXT(PrsDim_FixRelation, PrsDim_Relation)

static bool InDomain(const double fpar, const double lpar, const double para)
{
  if (fpar >= 0.)
  {
    return ((para >= fpar) && (para <= lpar));
  }
  if (para >= (fpar + 2 * M_PI))
    return true;
  if (para <= lpar)
    return true;
  return false;
}

PrsDim_FixRelation::PrsDim_FixRelation(const TopoDS_Shape&            aShape,
                                       const occ::handle<Geom_Plane>& aPlane,
                                       const TopoDS_Wire&             aWire)
    : myWire(aWire)
{
  myFShape            = aShape;
  myPlane             = aPlane;
  myAutomaticPosition = true;
  myArrowSize         = 5.;
}

PrsDim_FixRelation::PrsDim_FixRelation(const TopoDS_Shape&            aShape,
                                       const occ::handle<Geom_Plane>& aPlane,
                                       const TopoDS_Wire&             aWire,
                                       const gp_Pnt&                  aPosition,
                                       const double                   anArrowSize)
    : myWire(aWire)
{
  myFShape   = aShape;
  myPlane    = aPlane;
  myPosition = aPosition;
  SetArrowSize(anArrowSize);
  myAutomaticPosition = false;
}

PrsDim_FixRelation::PrsDim_FixRelation(const TopoDS_Shape&            aShape,
                                       const occ::handle<Geom_Plane>& aPlane)
{
  myFShape            = aShape;
  myPlane             = aPlane;
  myAutomaticPosition = true;
  myArrowSize         = 5.;
}

PrsDim_FixRelation::PrsDim_FixRelation(const TopoDS_Shape&            aShape,
                                       const occ::handle<Geom_Plane>& aPlane,
                                       const gp_Pnt&                  aPosition,
                                       const double                   anArrowSize)
{
  myFShape   = aShape;
  myPlane    = aPlane;
  myPosition = aPosition;
  SetArrowSize(anArrowSize);
  myAutomaticPosition = false;
}

void PrsDim_FixRelation::Compute(const occ::handle<PrsMgr_PresentationManager>&,
                                 const occ::handle<Prs3d_Presentation>& aPresentation,
                                 const int)
{

  gp_Pnt curpos;
  if (myFShape.ShapeType() == TopAbs_VERTEX)
    ComputeVertex(TopoDS::Vertex(myFShape), curpos);
  else if (myFShape.ShapeType() == TopAbs_EDGE)
    ComputeEdge(TopoDS::Edge(myFShape), curpos);

  const gp_Dir& nor = myPlane->Axis().Direction();

  if (!myArrowSizeIsDefined)
    myArrowSize = 5.;

  DsgPrs_FixPresentation::Add(aPresentation, myDrawer, myPntAttach, curpos, nor, myArrowSize);
}

void PrsDim_FixRelation::ComputeSelection(const occ::handle<SelectMgr_Selection>& aSelection,
                                          const int)
{
  occ::handle<SelectMgr_EntityOwner> own = new SelectMgr_EntityOwner(this, 7);

  occ::handle<Select3D_SensitiveSegment> seg;
  seg = new Select3D_SensitiveSegment(own, myPntAttach, myPosition);
  aSelection->Add(seg);

  gp_Dir norm = myPlane->Axis().Direction();

  gp_Vec dirac(myPntAttach, myPosition);
  dirac.Normalize();
  gp_Vec norac = dirac.Crossed(gp_Vec(norm));
  gp_Ax1 ax(myPosition, norm);
  norac.Rotate(ax, M_PI / 8);

  norac *= (myArrowSize / 2);
  gp_Pnt P1 = myPosition.Translated(norac);
  gp_Pnt P2 = myPosition.Translated(-norac);
  seg       = new Select3D_SensitiveSegment(own, P1, P2);
  aSelection->Add(seg);

  norac *= 0.8;
  P1 = myPosition.Translated(norac);
  P2 = myPosition.Translated(-norac);
  dirac *= (myArrowSize / 2);
  gp_Pnt PF(P1.XYZ());
  gp_Pnt PL = PF.Translated(dirac);
  PL.Translate(norac);
  seg = new Select3D_SensitiveSegment(own, PF, PL);
  aSelection->Add(seg);

  PF.SetXYZ(P2.XYZ());
  PL = PF.Translated(dirac);
  PL.Translate(norac);
  seg = new Select3D_SensitiveSegment(own, PF, PL);
  aSelection->Add(seg);

  PF.SetXYZ((P1.XYZ() + P2.XYZ()) / 2);
  PL = PF.Translated(dirac);
  PL.Translate(norac);
  seg = new Select3D_SensitiveSegment(own, PF, PL);
}

void PrsDim_FixRelation::ComputeVertex(const TopoDS_Vertex&, gp_Pnt& curpos)
{
  myPntAttach = BRep_Tool::Pnt(TopoDS::Vertex(myFShape));
  curpos      = myPosition;
  if (myAutomaticPosition)
  {
    gp_Pln pln(myPlane->Pln());
    gp_Dir dir(pln.XAxis().Direction());
    gp_Vec transvec     = gp_Vec(dir) * myArrowSize;
    curpos              = myPntAttach.Translated(transvec);
    myPosition          = curpos;
    myAutomaticPosition = true;
  }
}

gp_Pnt PrsDim_FixRelation::ComputePosition(const occ::handle<Geom_Curve>& curv1,
                                           const occ::handle<Geom_Curve>& curv2,
                                           const gp_Pnt&                  firstp1,
                                           const gp_Pnt&                  lastp1,
                                           const gp_Pnt&                  firstp2,
                                           const gp_Pnt&                  lastp2) const
{

  gp_Pnt curpos;

  if (curv1->IsInstance(STANDARD_TYPE(Geom_Circle))
      || curv2->IsInstance(STANDARD_TYPE(Geom_Circle)))
  {
    occ::handle<Geom_Circle> gcirc = occ::down_cast<Geom_Circle>(curv1);
    if (gcirc.IsNull())
      gcirc = occ::down_cast<Geom_Circle>(curv2);
    gp_Dir dir(gcirc->Location().XYZ() + myPntAttach.XYZ());
    gp_Vec transvec = gp_Vec(dir) * myArrowSize;
    curpos          = myPntAttach.Translated(transvec);
  }

  else
  {
    gp_Vec vec1(firstp1, lastp1);
    gp_Vec vec2(firstp2, lastp2);

    if (!vec1.IsParallel(vec2, Precision::Angular()))
    {
      gp_Dir           dir;
      constexpr double conf = Precision::Confusion();
      if (lastp1.IsEqual(firstp2, conf) || firstp1.IsEqual(lastp2, conf))
        dir.SetXYZ(vec1.XYZ() - vec2.XYZ());
      else
        dir.SetXYZ(vec1.XYZ() + vec2.XYZ());
      gp_Vec transvec = gp_Vec(dir) * myArrowSize;
      curpos          = myPntAttach.Translated(transvec);
    }
    else
    {
      gp_Vec crossvec = vec1.Crossed(vec2);
      vec1.Cross(crossvec);
      gp_Dir dir(vec1);
      curpos = myPntAttach.Translated(gp_Vec(dir) * myArrowSize);
    }
  }

  return curpos;
}

gp_Pnt PrsDim_FixRelation::ComputePosition(const occ::handle<Geom_Curve>& curv,
                                           const gp_Pnt&                  firstp,
                                           const gp_Pnt&                  lastp) const
{

  gp_Pnt curpos;

  if (curv->IsKind(STANDARD_TYPE(Geom_Circle)))
  {

    occ::handle<Geom_Circle> gcirc = occ::down_cast<Geom_Circle>(curv);
    gp_Dir                   dir(gcirc->Location().XYZ() + myPntAttach.XYZ());
    gp_Vec                   transvec = gp_Vec(dir) * myArrowSize;
    curpos                            = myPntAttach.Translated(transvec);
  }

  else
  {

    gp_Pln pln(myPlane->Pln());
    gp_Dir NormPln = pln.Axis().Direction();
    gp_Vec vec(firstp, lastp);
    vec.Cross(gp_Vec(NormPln));
    vec.Normalize();
    gp_Vec transvec = vec * myArrowSize;
    curpos          = myPntAttach.Translated(transvec);
    gp_Ax1 RotAx(myPntAttach, NormPln);
    curpos.Rotate(RotAx, M_PI / 10);
  }

  return curpos;
}

void PrsDim_FixRelation::ComputeEdge(const TopoDS_Edge& FixEdge, gp_Pnt& curpos)
{
  occ::handle<Geom_Curve> curEdge;
  gp_Pnt                  ptbeg, ptend;
  if (!PrsDim::ComputeGeometry(FixEdge, curEdge, ptbeg, ptend))
    return;

  if (curEdge->IsKind(STANDARD_TYPE(Geom_Line)))
  {
    gp_Lin glin = occ::down_cast<Geom_Line>(curEdge)->Lin();
    double pfirst(ElCLib::Parameter(glin, ptbeg));
    double plast(ElCLib::Parameter(glin, ptend));
    ComputeLinePosition(glin, curpos, pfirst, plast);
  }

  else if (curEdge->IsKind(STANDARD_TYPE(Geom_Circle)))
  {
    gp_Circ           gcirc = occ::down_cast<Geom_Circle>(curEdge)->Circ();
    double            pfirst, plast;
    BRepAdaptor_Curve cu(FixEdge);
    pfirst = cu.FirstParameter();
    plast  = cu.LastParameter();
    ComputeCirclePosition(gcirc, curpos, pfirst, plast);
  }

  else
    return;
}

void PrsDim_FixRelation::ComputeLinePosition(const gp_Lin& glin,
                                             gp_Pnt&       pos,
                                             double&       pfirst,
                                             double&       plast)
{
  if (myAutomaticPosition)
  {

    myPntAttach = ElCLib::Value((pfirst + plast) / 2, glin);

    gp_Dir norm = myPlane->Axis().Direction();

    norm.Cross(glin.Position().Direction());
    pos                 = myPntAttach.Translated(gp_Vec(norm) * myArrowSize);
    myAutomaticPosition = true;
  }

  else
  {
    pos             = myPosition;
    double linparam = ElCLib::Parameter(glin, pos);

    if ((linparam >= pfirst) && (linparam <= plast))
      myPntAttach = ElCLib::Value(linparam, glin);

    else
    {
      double pOnLin;
      if (linparam > plast)
        pOnLin = plast;
      else
        pOnLin = pfirst;
      myPntAttach = ElCLib::Value(pOnLin, glin);
      gp_Dir norm = myPlane->Axis().Direction();

      norm.Cross(glin.Position().Direction());
      gp_Lin lsup(myPntAttach, norm);
      double parpos = ElCLib::Parameter(lsup, myPosition);
      pos           = ElCLib::Value(parpos, lsup);
    }
  }
  myPosition = pos;
}

void PrsDim_FixRelation::ComputeCirclePosition(const gp_Circ& gcirc,
                                               gp_Pnt&        pos,
                                               double&        pfirst,
                                               double&        plast)
{

  if (plast > 2 * M_PI)
  {
    double nbtours = std::floor(plast / (2 * M_PI));
    plast -= nbtours * 2 * M_PI;
    pfirst -= nbtours * 2 * M_PI;
  }

  if (myAutomaticPosition)
  {

    double circparam = (pfirst + plast) / 2.;

    if (!InDomain(pfirst, plast, circparam))
    {
      double otherpar = circparam + M_PI;
      if (otherpar > 2 * M_PI)
        otherpar -= 2 * M_PI;
      circparam = otherpar;
    }

    myPntAttach = ElCLib::Value(circparam, gcirc);

    gp_Vec dir(gcirc.Location().XYZ(), myPntAttach.XYZ());
    dir.Normalize();
    gp_Vec transvec     = dir * myArrowSize;
    pos                 = myPntAttach.Translated(transvec);
    myPosition          = pos;
    myAutomaticPosition = true;
  }

  else
  {

    pos = myPosition;

    double circparam = ElCLib::Parameter(gcirc, pos);

    if (!InDomain(pfirst, plast, circparam))
    {
      double otherpar = circparam + M_PI;
      if (otherpar > 2 * M_PI)
        otherpar -= 2 * M_PI;
      circparam = otherpar;
    }

    myPntAttach = ElCLib::Value(circparam, gcirc);
  }
}

bool PrsDim_FixRelation::ConnectedEdges(const TopoDS_Wire&   WIRE,
                                        const TopoDS_Vertex& V,
                                        TopoDS_Edge&         E1,
                                        TopoDS_Edge&         E2)
{
  NCollection_IndexedDataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
    vertexMap;
  TopExp::MapShapesAndAncestors(WIRE, TopAbs_VERTEX, TopAbs_EDGE, vertexMap);

  bool          found(false);
  TopoDS_Vertex theVertex;
  for (int i = 1; i <= vertexMap.Extent() && !found; i++)
  {
    if (vertexMap.FindKey(i).IsSame(V))
    {
      theVertex = TopoDS::Vertex(vertexMap.FindKey(i));
      found     = true;
    }
  }
  if (!found)
  {
    E1.Nullify();
    E2.Nullify();
    return false;
  }

  NCollection_List<TopoDS_Shape>::Iterator iterator(vertexMap.FindFromKey(theVertex));
  if (iterator.More())
  {
    E1 = TopoDS::Edge(iterator.Value());
    BRepAdaptor_Curve curv(E1);
    iterator.Next();
  }
  else
  {
    E1.Nullify();
    return false;
  }

  if (iterator.More())
  {
    E2 = TopoDS::Edge(iterator.Value());
    BRepAdaptor_Curve curv(E2);
    iterator.Next();
  }
  else
  {
    E2.Nullify();
    return false;
  }

  if (iterator.More())
  {
    E1.Nullify();
    E2.Nullify();
    return false;
  }
  return true;
}

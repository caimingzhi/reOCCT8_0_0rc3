#include <PrsDim_TangentRelation.hpp>

#include <PrsDim.hpp>
#include <BRep_Tool.hpp>
#include <BRepAdaptor_Surface.hpp>
#include <BRepBuilderAPI_MakeFace.hpp>
#include <DsgPrs_TangentPresentation.hpp>
#include <ElCLib.hpp>
#include <Geom_Circle.hpp>
#include <Geom_Ellipse.hpp>
#include <Geom_Line.hpp>
#include <Geom_Plane.hpp>
#include <GeomAPI_ExtremaCurveCurve.hpp>
#include <gp_Lin.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <Precision.hpp>
#include <Prs3d_Presentation.hpp>
#include <Select3D_SensitiveSegment.hpp>
#include <SelectMgr_EntityOwner.hpp>
#include <SelectMgr_Selection.hpp>
#include <TopAbs_ShapeEnum.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDS_Vertex.hpp>

IMPLEMENT_STANDARD_RTTIEXT(PrsDim_TangentRelation, PrsDim_Relation)

PrsDim_TangentRelation::PrsDim_TangentRelation(const TopoDS_Shape&            aFShape,
                                               const TopoDS_Shape&            aSShape,
                                               const occ::handle<Geom_Plane>& aPlane,
                                               const int                      anExternRef)
    : myExternRef(anExternRef)
{
  myFShape            = aFShape;
  mySShape            = aSShape;
  myPlane             = aPlane;
  myAutomaticPosition = false;
}

void PrsDim_TangentRelation::Compute(const occ::handle<PrsMgr_PresentationManager>&,
                                     const occ::handle<Prs3d_Presentation>& aPresentation,
                                     const int)
{
  switch (myFShape.ShapeType())
  {
    case TopAbs_FACE:
    {
      ComputeTwoFacesTangent(aPresentation);
    }
    break;
    case TopAbs_EDGE:
    {
      ComputeTwoEdgesTangent(aPresentation);
    }
    break;
    default:
      break;
  }
}

void PrsDim_TangentRelation::ComputeSelection(const occ::handle<SelectMgr_Selection>& aSelection,
                                              const int)
{
  gp_Vec vec(myDir);
  gp_Vec vec1 = vec.Multiplied(myLength);
  gp_Vec vec2 = vec.Multiplied(-myLength);
  gp_Pnt p1   = myPosition.Translated(vec1);
  gp_Pnt p2   = myPosition.Translated(vec2);

  occ::handle<SelectMgr_EntityOwner>     own = new SelectMgr_EntityOwner(this, 7);
  occ::handle<Select3D_SensitiveSegment> seg = new Select3D_SensitiveSegment(own, p1, p2);
  aSelection->Add(seg);
}

void PrsDim_TangentRelation::ComputeTwoFacesTangent(const occ::handle<Prs3d_Presentation>&) {}

static bool ComputeTangencyPoint(const occ::handle<Geom_Curve>& GC1,
                                 const occ::handle<Geom_Curve>& GC2,
                                 gp_Pnt&                        aPoint)
{
  double U1f = GC1->FirstParameter();
  double U1l = GC1->LastParameter();
  double U2f = GC2->FirstParameter();
  double U2l = GC2->LastParameter();

  gp_Pnt                    PC1;
  double                    mindist = 0;
  GeomAPI_ExtremaCurveCurve Ex(GC1, GC2, U1f, U1l, U2f, U2l);
  for (int i = 1; i <= Ex.NbExtrema(); i++)
  {
    gp_Pnt P1, P2;
    Ex.Points(i, P1, P2);
    double dist = P1.Distance(P2);
    if (i == 1)
    {
      mindist = dist;
      PC1     = P1;
    }
    else
    {
      if ((dist < mindist) || (dist < Precision::Confusion()))
      {
        mindist = dist;
        PC1     = P1;
      }
    }
    if (dist < Precision::Confusion())
    {
      if (GC1->IsInstance(STANDARD_TYPE(Geom_Line)))
      {
        continue;
      }
      gp_Vec aVector1, aVector2;
      if (GC1->IsInstance(STANDARD_TYPE(Geom_Circle)))
      {
        occ::handle<Geom_Circle> circle(occ::down_cast<Geom_Circle>(GC1));
        double                   par_inter = ElCLib::Parameter(circle->Circ(), P1);
        ElCLib::D1(par_inter, circle->Circ(), P1, aVector1);
      }
      else if (GC1->IsInstance(STANDARD_TYPE(Geom_Ellipse)))
      {
        occ::handle<Geom_Ellipse> ellipse(occ::down_cast<Geom_Ellipse>(GC1));
        double                    par_inter = ElCLib::Parameter(ellipse->Elips(), P1);
        ElCLib::D1(par_inter, ellipse->Elips(), P1, aVector1);
      }
      if (GC2->IsInstance(STANDARD_TYPE(Geom_Circle)))
      {
        occ::handle<Geom_Circle> circle(occ::down_cast<Geom_Circle>(GC2));
        double                   par_inter = ElCLib::Parameter(circle->Circ(), P2);
        ElCLib::D1(par_inter, circle->Circ(), P2, aVector2);
      }
      else if (GC2->IsInstance(STANDARD_TYPE(Geom_Ellipse)))
      {
        occ::handle<Geom_Ellipse> ellipse(occ::down_cast<Geom_Ellipse>(GC2));
        double                    par_inter = ElCLib::Parameter(ellipse->Elips(), P2);
        ElCLib::D1(par_inter, ellipse->Elips(), P2, aVector2);
      }

      if (aVector1.IsParallel(aVector2, M_PI / 360.0))
        break;
    }
  }
  aPoint = PC1;
  return true;
}

void PrsDim_TangentRelation::ComputeTwoEdgesTangent(
  const occ::handle<Prs3d_Presentation>& aPresentation)
{
  occ::handle<Geom_Curve> copy1, copy2;
  gp_Pnt                  ptat11, ptat12, ptat21, ptat22;
  bool                    isInfinite1, isInfinite2;
  occ::handle<Geom_Curve> extCurv;
  if (!PrsDim::ComputeGeometry(TopoDS::Edge(myFShape),
                               TopoDS::Edge(mySShape),
                               myExtShape,
                               copy1,
                               copy2,
                               ptat11,
                               ptat12,
                               ptat21,
                               ptat22,
                               extCurv,
                               isInfinite1,
                               isInfinite2,
                               myPlane))
  {
    return;
  }

  aPresentation->SetInfiniteState(isInfinite1 || isInfinite2);

  BRepBuilderAPI_MakeFace makeface(myPlane->Pln());
  BRepAdaptor_Surface     adp(makeface.Face());

  int typArg(0);

  if (copy1->IsInstance(STANDARD_TYPE(Geom_Line)))
  {
    typArg = 10;
  }
  else if (copy1->IsInstance(STANDARD_TYPE(Geom_Circle)))
  {
    typArg = 20;
  }
  else if (copy1->IsInstance(STANDARD_TYPE(Geom_Ellipse)))
  {
    typArg = 30;
  }
  else
    return;

  if (copy2->IsInstance(STANDARD_TYPE(Geom_Line)))
  {
    typArg += 1;
  }
  else if (copy2->IsInstance(STANDARD_TYPE(Geom_Circle)))
  {
    typArg += 2;
  }
  else if (copy2->IsInstance(STANDARD_TYPE(Geom_Ellipse)))
  {
    typArg += 3;
  }
  else
    return;

  TopoDS_Vertex   VCom;
  TopExp_Explorer expF(TopoDS::Edge(myFShape), TopAbs_VERTEX);
  TopExp_Explorer expS(TopoDS::Edge(mySShape), TopAbs_VERTEX);
  TopoDS_Shape    tab[2];
  int             p;
  for (p = 0; expF.More(); expF.Next(), p++)
  {
    tab[p] = TopoDS::Vertex(expF.Current());
  }
  bool found(false);
  for (; expS.More() && !found; expS.Next())
  {
    for (int l = 0; l <= p && !found; l++)
    {
      found = (expS.Current().IsSame(tab[l]));
      if (found)
        VCom = TopoDS::Vertex(expS.Current());
    }
  }

  gp_Vec theVector;
  gp_Pnt pint3d;
  gp_Dir theDir;
  double par_inter = 0.0;

  if (found)
  {
    pint3d = BRep_Tool::Pnt(VCom);
  }

  switch (typArg)
  {
    case 12:
    {
      occ::handle<Geom_Line>   line(occ::down_cast<Geom_Line>(copy1));
      occ::handle<Geom_Circle> circle(occ::down_cast<Geom_Circle>(copy2));

      if (!found)
      {

        par_inter = ElCLib::Parameter(line->Lin(), circle->Location());
        pint3d    = ElCLib::Value(par_inter, line->Lin());
      }

      theDir   = line->Lin().Direction();
      myLength = circle->Radius() / 5.;
      if (!isInfinite1)
      {
        double copy1Length = ptat12.Distance(ptat11);
        if (copy1Length < myLength)
          myLength = copy1Length / 3.;
      }
    }
    break;
    case 21:
    {
      occ::handle<Geom_Circle> circle(occ::down_cast<Geom_Circle>(copy1));
      occ::handle<Geom_Line>   line(occ::down_cast<Geom_Line>(copy2));

      if (!found)
      {

        par_inter = ElCLib::Parameter(line->Lin(), circle->Location());
        pint3d    = ElCLib::Value(par_inter, line->Lin());
      }

      theDir   = line->Lin().Direction();
      myLength = circle->Radius() / 5.;
      if (!isInfinite2)
      {
        double copy2Length = ptat21.Distance(ptat22);
        if (copy2Length < myLength)
          myLength = copy2Length / 3.;
      }
    }
    break;

    case 13:
    {
      occ::handle<Geom_Line>    line(occ::down_cast<Geom_Line>(copy1));
      occ::handle<Geom_Ellipse> ellipse(occ::down_cast<Geom_Ellipse>(copy2));

      if (!found)
      {
        ComputeTangencyPoint(line, ellipse, pint3d);
      }

      theDir   = line->Lin().Direction();
      myLength = ellipse->MajorRadius() / 5.;

      if (!isInfinite1)
      {
        double copy1Length = ptat12.Distance(ptat11);
        if (copy1Length < myLength)
          myLength = copy1Length / 3.;
      }
    }
    break;
    case 31:
    {
      occ::handle<Geom_Ellipse> ellipse(occ::down_cast<Geom_Ellipse>(copy1));
      occ::handle<Geom_Line>    line(occ::down_cast<Geom_Line>(copy2));

      if (!found)
      {
        ComputeTangencyPoint(line, ellipse, pint3d);
      }

      theDir   = line->Lin().Direction();
      myLength = ellipse->MajorRadius() / 5.;

      if (!isInfinite2)
      {
        double copy2Length = ptat21.Distance(ptat22);
        if (copy2Length < myLength)
          myLength = copy2Length / 3.;
      }
    }
    break;
    case 22:
    {
      occ::handle<Geom_Circle> circle1(occ::down_cast<Geom_Circle>(copy1));
      occ::handle<Geom_Circle> circle2(occ::down_cast<Geom_Circle>(copy2));
      double                   R1 = circle1->Radius();
      double                   R2 = circle2->Radius();
      myLength                    = std::max(R1, R2) / 5.0;
      if (!found)
      {
        if ((circle1->Location()).IsEqual(circle2->Location(), Precision::Confusion()))
        {
          if (R1 >= R2)
          {
            ElCLib::D1(par_inter, circle1->Circ(), pint3d, theVector);
          }
          else
          {
            ElCLib::D1(par_inter, circle2->Circ(), pint3d, theVector);
          }
        }
        else
        {
          if (R1 >= R2)
          {
            par_inter = ElCLib::Parameter(circle1->Circ(), circle2->Location());
            ElCLib::D1(par_inter, circle1->Circ(), pint3d, theVector);
          }
          else
          {
            par_inter = ElCLib::Parameter(circle2->Circ(), circle1->Location());
            ElCLib::D1(par_inter, circle2->Circ(), pint3d, theVector);
          }
        }
      }
      else
      {
        par_inter = ElCLib::Parameter(circle1->Circ(), pint3d);
        ElCLib::D1(par_inter, circle1->Circ(), pint3d, theVector);
      }
      theDir = gp_Dir(theVector);
    }
    break;
    case 23:
    {
      occ::handle<Geom_Circle>  circle(occ::down_cast<Geom_Circle>(copy1));
      occ::handle<Geom_Ellipse> ellipse(occ::down_cast<Geom_Ellipse>(copy2));
      double                    R1 = circle->Radius();
      double                    R2 = ellipse->MajorRadius();
      myLength                     = std::max(R1, R2) / 5.0;
      if (!found)
      {
        if (R1 >= R2)
        {
          ComputeTangencyPoint(circle, ellipse, pint3d);
          par_inter = ElCLib::Parameter(circle->Circ(), pint3d);
          ElCLib::D1(par_inter, circle->Circ(), pint3d, theVector);
        }
        else
        {
          ComputeTangencyPoint(ellipse, circle, pint3d);
          par_inter = ElCLib::Parameter(ellipse->Elips(), pint3d);
          ElCLib::D1(par_inter, ellipse->Elips(), pint3d, theVector);
        }
      }
      else
      {
        par_inter = ElCLib::Parameter(circle->Circ(), pint3d);
        ElCLib::D1(par_inter, circle->Circ(), pint3d, theVector);
      }
      theDir = gp_Dir(theVector);
    }
    break;
    case 32:
    {
      occ::handle<Geom_Ellipse> ellipse(occ::down_cast<Geom_Ellipse>(copy1));
      occ::handle<Geom_Circle>  circle(occ::down_cast<Geom_Circle>(copy2));
      double                    R1 = ellipse->MajorRadius();
      double                    R2 = circle->Radius();
      myLength                     = std::max(R1, R2) / 5.0;
      if (!found)
      {
        if (R1 >= R2)
        {
          ComputeTangencyPoint(ellipse, circle, pint3d);
          par_inter = ElCLib::Parameter(ellipse->Elips(), pint3d);
          ElCLib::D1(par_inter, ellipse->Elips(), pint3d, theVector);
        }
        else
        {
          ComputeTangencyPoint(circle, ellipse, pint3d);
          par_inter = ElCLib::Parameter(circle->Circ(), pint3d);
          ElCLib::D1(par_inter, circle->Circ(), pint3d, theVector);
        }
      }
      else
      {
        par_inter = ElCLib::Parameter(circle->Circ(), pint3d);
        ElCLib::D1(par_inter, circle->Circ(), pint3d, theVector);
      }
      theDir = gp_Dir(theVector);
    }
    break;
    case 33:
    {
      occ::handle<Geom_Ellipse> ellipse1(occ::down_cast<Geom_Ellipse>(copy1));
      occ::handle<Geom_Ellipse> ellipse2(occ::down_cast<Geom_Ellipse>(copy2));
      double                    R1 = ellipse1->MajorRadius();
      double                    R2 = ellipse2->MajorRadius();
      myLength                     = std::max(R1, R2) / 5.0;
      if (!found)
      {
        if (R1 > R2)
        {
          ComputeTangencyPoint(ellipse1, ellipse2, pint3d);
          par_inter = ElCLib::Parameter(ellipse1->Elips(), pint3d);
          ElCLib::D1(par_inter, ellipse1->Elips(), pint3d, theVector);
        }
        else
        {
          ComputeTangencyPoint(ellipse2, ellipse1, pint3d);
          par_inter = ElCLib::Parameter(ellipse2->Elips(), pint3d);
          ElCLib::D1(par_inter, ellipse2->Elips(), pint3d, theVector);
        }
      }
      else
      {
        par_inter = ElCLib::Parameter(ellipse1->Elips(), pint3d);
        ElCLib::D1(par_inter, ellipse1->Elips(), pint3d, theVector);
      }
      theDir = gp_Dir(theVector);
    }
    break;

    default:
      return;
  }

  myAttach   = pint3d;
  myDir      = theDir;
  myPosition = pint3d;
  myLength   = std::min(myLength, myArrowSize);

  DsgPrs_TangentPresentation::Add(aPresentation, myDrawer, myAttach, myDir, myLength);
  if ((myExtShape != 0) && !extCurv.IsNull())
  {
    gp_Pnt pf, pl;
    if (myExtShape == 1)
    {
      if (!isInfinite1)
      {
        pf = ptat11;
        pl = ptat12;
      }
      ComputeProjEdgePresentation(aPresentation, TopoDS::Edge(myFShape), copy1, pf, pl);
    }
    else
    {
      if (!isInfinite2)
      {
        pf = ptat21;
        pl = ptat22;
      }
      ComputeProjEdgePresentation(aPresentation, TopoDS::Edge(mySShape), copy2, pf, pl);
    }
  }
}

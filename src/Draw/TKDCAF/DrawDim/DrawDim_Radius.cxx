#include <BRepAdaptor_Surface.hpp>
#include <Draw_Display.hpp>
#include <DrawDim_Radius.hpp>
#include <GC_MakeCircle.hpp>
#include <Geom_Circle.hpp>
#include <Geom_Curve.hpp>
#include <Geom_Surface.hpp>
#include <Geom_ToroidalSurface.hpp>
#include <gp_Circ.hpp>
#include <gp_Pnt.hpp>
#include <Standard_Type.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Face.hpp>

IMPLEMENT_STANDARD_RTTIEXT(DrawDim_Radius, DrawDim_Dimension)

DrawDim_Radius::DrawDim_Radius(const TopoDS_Face& cylinder)
{
  myCylinder = cylinder;
}

const TopoDS_Face& DrawDim_Radius::Cylinder() const
{
  return myCylinder;
}

void DrawDim_Radius::Cylinder(const TopoDS_Face& face)
{
  myCylinder = face;
}

void DrawDim_Radius::DrawOn(Draw_Display& dis) const
{

  TopoDS_Shape myFShape = myCylinder;

  gp_Pnt  myPosition;
  gp_Circ myCircle;

#ifdef OCCT_DEBUG
  std::cout << "entree dans computeonefaceradius" << std::endl;
#endif
  BRepAdaptor_Surface surfAlgo(TopoDS::Face(myFShape));
  double              uFirst, uLast, vFirst, vLast;
  uFirst      = surfAlgo.FirstUParameter();
  uLast       = surfAlgo.LastUParameter();
  vFirst      = surfAlgo.FirstVParameter();
  vLast       = surfAlgo.LastVParameter();
  double uMoy = (uFirst + uLast) / 2;
  double vMoy = (vFirst + vLast) / 2;
  gp_Pnt curpos;
  surfAlgo.D0(uMoy, vMoy, curpos);
  const occ::handle<Geom_Surface>& surf = surfAlgo.Surface().Surface();
  occ::handle<Geom_Curve>          aCurve;
  if (surf->DynamicType() == STANDARD_TYPE(Geom_ToroidalSurface))
  {
    aCurve = surf->UIso(uMoy);
    uFirst = vFirst;
    uLast  = vLast;
  }
  else
  {
    aCurve = surf->VIso(vMoy);
  }

  if (aCurve->DynamicType() == STANDARD_TYPE(Geom_Circle))
  {
    myCircle = occ::down_cast<Geom_Circle>(aCurve)->Circ();
  }

  else
  {

    gp_Pnt P1, P2;
    surfAlgo.D0(uFirst, vMoy, P1);
    surfAlgo.D0(uLast, vMoy, P2);
    GC_MakeCircle mkCirc(P1, curpos, P2);
    myCircle = mkCirc.Value()->Circ();
  }

  myPosition = curpos;

  dis.Draw(myCircle, uFirst, uLast);
  dis.DrawMarker(myPosition, Draw_Losange);
}

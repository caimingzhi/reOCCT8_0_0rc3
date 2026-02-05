#include <BRepPrimAPI_MakeWedge.hpp>
#include <gp_Ax2.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Shell.hpp>
#include <TopoDS_Solid.hpp>

//=================================================================================================

BRepPrimAPI_MakeWedge::BRepPrimAPI_MakeWedge(const double dx,
                                             const double dy,
                                             const double dz,
                                             const double ltx)
    : myWedge(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(gp_Dir::D::Z), gp_Dir(gp_Dir::D::X)), dx, dy, dz, ltx)
{
}

//=================================================================================================

BRepPrimAPI_MakeWedge::BRepPrimAPI_MakeWedge(const gp_Ax2& Axes,
                                             const double  dx,
                                             const double  dy,
                                             const double  dz,
                                             const double  ltx)
    : myWedge(Axes, dx, dy, dz, ltx)
{
}

//=================================================================================================

BRepPrimAPI_MakeWedge::BRepPrimAPI_MakeWedge(const double dx,
                                             const double dy,
                                             const double dz,
                                             const double xmin,
                                             const double zmin,
                                             const double xmax,
                                             const double zmax)
    : myWedge(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(gp_Dir::D::Z), gp_Dir(gp_Dir::D::X)),
              0,
              0,
              0,
              zmin,
              xmin,
              dx,
              dy,
              dz,
              zmax,
              xmax)
{
}

//=================================================================================================

BRepPrimAPI_MakeWedge::BRepPrimAPI_MakeWedge(const gp_Ax2& Axes,
                                             const double  dx,
                                             const double  dy,
                                             const double  dz,
                                             const double  xmin,
                                             const double  zmin,
                                             const double  xmax,
                                             const double  zmax)
    : myWedge(Axes, 0, 0, 0, zmin, xmin, dx, dy, dz, zmax, xmax)
{
}

//=================================================================================================

BRepPrim_Wedge& BRepPrimAPI_MakeWedge::Wedge()
{
  return myWedge;
}

//=================================================================================================

const TopoDS_Shell& BRepPrimAPI_MakeWedge::Shell()
{
  Build();
  return myWedge.Shell();
}

//=================================================================================================

void BRepPrimAPI_MakeWedge::Build(const Message_ProgressRange& /*theRange*/)
{
  BRep_Builder B;
  B.MakeSolid(TopoDS::Solid(myShape));
  B.Add(myShape, myWedge.Shell());
  Done();
}

//=================================================================================================

const TopoDS_Solid& BRepPrimAPI_MakeWedge::Solid()
{
  Build();
  return TopoDS::Solid(myShape);
}

//=================================================================================================

BRepPrimAPI_MakeWedge::operator TopoDS_Shell()
{
  return Shell();
}

//=================================================================================================

BRepPrimAPI_MakeWedge::operator TopoDS_Solid()
{
  return Solid();
}

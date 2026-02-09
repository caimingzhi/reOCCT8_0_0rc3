

#include <BRepAdaptor_Curve.hpp>
#include <BRepGProp_Cinert.hpp>
#include <BRepGProp_EdgeTool.hpp>
#include <gp_Pnt.hpp>
#include <math.hpp>
#include <NCollection_Array1.hpp>

BRepGProp_Cinert::BRepGProp_Cinert() = default;

void BRepGProp_Cinert::SetLocation(const gp_Pnt& CLocation)
{
  loc = CLocation;
}

void BRepGProp_Cinert::Perform(const BRepAdaptor_Curve& C)
{

  double Ix, Iy, Iz, Ixx, Iyy, Izz, Ixy, Ixz, Iyz;
  dim = Ix = Iy = Iz = Ixx = Iyy = Izz = Ixy = Ixz = Iyz = 0.0;

  double Lower = BRepGProp_EdgeTool::FirstParameter(C);
  double Upper = BRepGProp_EdgeTool::LastParameter(C);
  int    Order = std::min(BRepGProp_EdgeTool::IntegrationOrder(C), math::GaussPointsMax());

  gp_Pnt P;
  gp_Vec V1;
  double ds;
  double ur, um, u;
  double x, y, z;
  double xloc, yloc, zloc;

  math_Vector GaussP(1, Order);
  math_Vector GaussW(1, Order);

  math::GaussPoints(Order, GaussP);
  math::GaussWeights(Order, GaussW);

  int                        nbIntervals   = BRepGProp_EdgeTool::NbIntervals(C, GeomAbs_CN);
  bool                       bHasIntervals = (nbIntervals > 1);
  NCollection_Array1<double> TI(1, nbIntervals + 1);

  if (bHasIntervals)
  {
    BRepGProp_EdgeTool::Intervals(C, TI, GeomAbs_CN);
  }
  else
  {
    nbIntervals = 1;
  }
  int    nIndex = 0;
  double UU1    = std::min(Lower, Upper);
  double UU2    = std::max(Lower, Upper);

  for (nIndex = 1; nIndex <= nbIntervals; nIndex++)
  {
    if (bHasIntervals)
    {
      Lower = std::max(TI(nIndex), UU1);
      Upper = std::min(TI(nIndex + 1), UU2);
    }
    else
    {
      Lower = UU1;
      Upper = UU2;
    }

    double dimLocal, IxLocal, IyLocal, IzLocal, IxxLocal, IyyLocal, IzzLocal, IxyLocal, IxzLocal,
      IyzLocal;
    dimLocal = IxLocal = IyLocal = IzLocal = IxxLocal = IyyLocal = IzzLocal = IxyLocal = IxzLocal =
      IyzLocal                                                                         = 0.0;

    loc.Coord(xloc, yloc, zloc);

    int i;

    um = 0.5 * (Upper + Lower);
    ur = 0.5 * (Upper - Lower);

    for (i = 1; i <= Order; i++)
    {
      u = um + ur * GaussP(i);
      BRepGProp_EdgeTool::D1(C, u, P, V1);
      ds = V1.Magnitude();
      P.Coord(x, y, z);
      x -= xloc;
      y -= yloc;
      z -= zloc;
      ds *= GaussW(i);
      dimLocal += ds;
      IxLocal += x * ds;
      IyLocal += y * ds;
      IzLocal += z * ds;
      IxyLocal += x * y * ds;
      IyzLocal += y * z * ds;
      IxzLocal += x * z * ds;
      x *= x;
      y *= y;
      z *= z;
      IxxLocal += (y + z) * ds;
      IyyLocal += (x + z) * ds;
      IzzLocal += (x + y) * ds;
    }

    dimLocal *= ur;
    IxLocal *= ur;
    IyLocal *= ur;
    IzLocal *= ur;
    IxxLocal *= ur;
    IyyLocal *= ur;
    IzzLocal *= ur;
    IxyLocal *= ur;
    IxzLocal *= ur;
    IyzLocal *= ur;

    dim += dimLocal;
    Ix += IxLocal;
    Iy += IyLocal;
    Iz += IzLocal;
    Ixx += IxxLocal;
    Iyy += IyyLocal;
    Izz += IzzLocal;
    Ixy += IxyLocal;
    Ixz += IxzLocal;
    Iyz += IyzLocal;
  }

  inertia = gp_Mat(gp_XYZ(Ixx, -Ixy, -Ixz), gp_XYZ(-Ixy, Iyy, -Iyz), gp_XYZ(-Ixz, -Iyz, Izz));

  if (std::abs(dim) < gp::Resolution())
    g = P;
  else
    g.SetCoord(Ix / dim, Iy / dim, Iz / dim);
}

BRepGProp_Cinert::BRepGProp_Cinert(const BRepAdaptor_Curve& C, const gp_Pnt& CLocation)
{
  SetLocation(CLocation);
  Perform(C);
}

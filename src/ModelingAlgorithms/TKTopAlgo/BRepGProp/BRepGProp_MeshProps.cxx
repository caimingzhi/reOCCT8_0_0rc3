

#include <BRepGProp_MeshProps.hpp>

#include <BRepGProp.hpp>
#include <ElSLib.hpp>
#include <gp_Ax3.hpp>
#include <gp_Pnt.hpp>
#include <GProp.hpp>
#include <Poly_Triangulation.hpp>
#include <Poly_Triangle.hpp>
#include <TopLoc_Location.hpp>

static void CalculateElSProps(const double x,
                              const double y,
                              const double z,
                              const double ds,
                              double*      GProps)
{

  double x2, y2, z2;
  x2 = x * x;
  y2 = y * y;
  z2 = z * z;

  GProps[0] += ds;
  GProps[1] += x * ds;
  GProps[2] += y * ds;
  GProps[3] += z * ds;

  GProps[7] += x * y * ds;
  GProps[8] += x * z * ds;
  GProps[9] += y * z * ds;
  GProps[4] += (y2 + z2) * ds;
  GProps[5] += (x2 + z2) * ds;
  GProps[6] += (x2 + y2) * ds;
}

static void CalculateElVProps(const double x,
                              const double y,
                              const double z,
                              const double dv,
                              double*      GProps)
{
  double x2, y2, z2;
  x2 = x * x;
  y2 = y * y;
  z2 = z * z;
  GProps[0] += dv / 3.0;
  GProps[1] += 0.25 * x * dv;
  GProps[2] += 0.25 * y * dv;
  GProps[3] += 0.25 * z * dv;
  double dv1 = 0.2 * dv;
  GProps[7] += x * y * dv1;
  GProps[8] += x * z * dv1;
  GProps[9] += y * z * dv1;
  GProps[4] += (y2 + z2) * dv1;
  GProps[5] += (x2 + z2) * dv1;
  GProps[6] += (x2 + y2) * dv1;
}

void BRepGProp_MeshProps::CalculateProps(const gp_Pnt& p1,
                                         const gp_Pnt& p2,
                                         const gp_Pnt& p3,
                                         const gp_Pnt& Apex,
                                         const bool    isVolume,
                                         double        GProps[10],
                                         const int     NbGaussPoints,
                                         const double* GaussPnts)
{

  gp_Vec aV12(p2, p1);
  gp_Vec aV23(p3, p2);
  gp_Vec aNorm = aV12 ^ aV23;
  double aDet  = aNorm.Magnitude();
  if (aDet <= gp::Resolution())
  {
    return;
  }
  gp_XYZ aCenter = (p1.XYZ() + p2.XYZ() + p3.XYZ()) / 3.;
  gp_Pnt aPC(aCenter);
  gp_Dir aDN(aNorm);
  gp_Ax3 aPosPln(aPC, aDN);

  double x1, y1, x2, y2, x3, y3;
  ElSLib::PlaneParameters(aPosPln, p1, x1, y1);
  ElSLib::PlaneParameters(aPosPln, p2, x2, y2);
  ElSLib::PlaneParameters(aPosPln, p3, x3, y3);

  double l1, l2;
  double x, y, z;
  double w;
  int    i;
  for (i = 0; i < NbGaussPoints; ++i)
  {
    int ind = 3 * i;
    l1      = GaussPnts[ind];
    l2      = GaussPnts[ind + 1];
    w       = GaussPnts[ind + 2];
    w *= aDet;
    x         = l1 * (x1 - x3) + l2 * (x2 - x3) + x3;
    y         = l1 * (y1 - y3) + l2 * (y2 - y3) + y3;
    gp_Pnt aP = ElSLib::PlaneValue(x, y, aPosPln);
    x         = aP.X() - Apex.X();
    y         = aP.Y() - Apex.Y();
    z         = aP.Z() - Apex.Z();

    if (isVolume)
    {
      double xn = aDN.X() * w;
      double yn = aDN.Y() * w;
      double zn = aDN.Z() * w;
      double dv = x * xn + y * yn + z * zn;
      CalculateElVProps(x, y, z, dv, GProps);
    }
    else
    {
      double ds = w;
      CalculateElSProps(x, y, z, ds, GProps);
    }
  }
}

void BRepGProp_MeshProps::Perform(const occ::handle<Poly_Triangulation>& theMesh,
                                  const TopLoc_Location&                 theLoc,
                                  const TopAbs_Orientation               theOri)
{
  if (theMesh.IsNull() || theMesh->NbNodes() == 0 || theMesh->NbTriangles() == 0)
  {
    return;
  }
  if (theLoc.IsIdentity())
  {
    Perform(theMesh, theOri);
  }
  else
  {
    const gp_Trsf& aTr = theLoc.Transformation();

    bool isToCopy = aTr.ScaleFactor() * aTr.HVectorialPart().Determinant() < 0.
                    || std::abs(std::abs(aTr.ScaleFactor()) - 1.) > gp::Resolution();
    if (isToCopy)
    {
      occ::handle<Poly_Triangulation> aCopy =
        new Poly_Triangulation(theMesh->NbNodes(), theMesh->NbTriangles(), false);
      NCollection_Array1<gp_Pnt> aNodes(1, theMesh->NbNodes());
      for (int i = 1; i <= theMesh->NbNodes(); ++i)
      {
        aCopy->SetNode(i, theMesh->Node(i).Transformed(aTr));
      }
      for (int i = 1; i <= theMesh->NbTriangles(); ++i)
      {
        aCopy->SetTriangle(i, theMesh->Triangle(i));
      }
      Perform(aCopy, theOri);
      return;
    }

    gp_Trsf aTrInv   = aTr.Inverted();
    gp_Pnt  loc_save = loc;
    loc.Transform(aTrInv);
    Perform(theMesh, theOri);

    gp_Mat HMat, inertia0;
    gp_Pnt g0 = g;
    g.SetXYZ(g.XYZ() + loc.XYZ());
    if (g0.XYZ().Modulus() > gp::Resolution())
    {
      GProp::HOperator(g, loc, dim, HMat);
      inertia0 = inertia - HMat;
    }
    else
    {
      inertia0 = inertia;
    }

    gp_Mat HVec  = aTrInv.HVectorialPart();
    gp_Mat HVecT = HVec.Transposed();
    HVecT.Multiply(inertia0);
    inertia0 = HVecT.Multiplied(HVec);

    g.Transform(aTr);
    g0 = g;
    g.SetXYZ(g.XYZ() - loc_save.XYZ());
    loc = loc_save;

    GProp::HOperator(g0, loc, dim, HMat);
    inertia = inertia0 + HMat;
  }
}

void BRepGProp_MeshProps::Perform(const occ::handle<Poly_Triangulation>& theMesh,
                                  const TopAbs_Orientation               theOri)
{
  if (theMesh.IsNull() || theMesh->NbNodes() == 0 || theMesh->NbTriangles() == 0)
  {
    return;
  }

  static const double GPtsWg[] =
    {1. / 6., 1. / 6., 1. / 6., 2. / 3., 1. / 6., 1. / 6., 1. / 6., 2. / 3., 1. / 6.};

  int aNbGaussPoints = 3;

  double aGProps[10] = {0., 0., 0., 0., 0., 0., 0., 0., 0., 0};

  bool isVolume = myType == Vinert;
  int  n1, n2, n3;
  for (int i = 1; i <= theMesh->NbTriangles(); ++i)
  {
    const Poly_Triangle aTri = theMesh->Triangle(i);
    aTri.Get(n1, n2, n3);
    if (theOri == TopAbs_REVERSED)
    {
      std::swap(n2, n3);
    }

    const gp_Pnt p1 = theMesh->Node(n1);
    const gp_Pnt p2 = theMesh->Node(n2);
    const gp_Pnt p3 = theMesh->Node(n3);
    CalculateProps(p1, p2, p3, loc, isVolume, aGProps, aNbGaussPoints, GPtsWg);
  }

  dim = aGProps[0];
  if (std::abs(dim) >= 1.e-20)
  {
    g.SetX(aGProps[1] / dim);
    g.SetY(aGProps[2] / dim);
    g.SetZ(aGProps[3] / dim);
  }
  else
  {
    g.SetX(aGProps[1]);
    g.SetY(aGProps[2]);
    g.SetZ(aGProps[3]);
  }
  inertia(1, 1) = aGProps[4];
  inertia(1, 2) = -aGProps[7];
  inertia(1, 3) = -aGProps[8];
  inertia(2, 1) = -aGProps[7];
  inertia(2, 2) = aGProps[5];
  inertia(2, 3) = -aGProps[9];
  inertia(3, 1) = -aGProps[8];
  inertia(3, 2) = -aGProps[9];
  inertia(3, 3) = aGProps[6];
}

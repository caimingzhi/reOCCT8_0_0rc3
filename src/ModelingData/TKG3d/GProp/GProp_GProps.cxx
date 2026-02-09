

#include <gp_Ax1.hpp>
#include <gp_Mat.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <gp_XYZ.hpp>
#include <GProp.hpp>
#include <GProp_GProps.hpp>
#include <GProp_PrincipalProps.hpp>
#include <math_Jacobi.hpp>
#include <Standard_DomainError.hpp>

GProp_GProps::GProp_GProps()
    : g(gp::Origin()),
      loc(gp::Origin()),
      dim(0.0)
{
  inertia = gp_Mat(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
}

GProp_GProps::GProp_GProps(const gp_Pnt& SystemLocation)
    : g(gp::Origin()),
      loc(SystemLocation),
      dim(0.0)
{
  inertia = gp_Mat(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
}

void GProp_GProps::Add(const GProp_GProps& Item, const double Density)
{
  if (Density <= gp::Resolution())
    throw Standard_DomainError();
  if (loc.Distance(Item.loc) <= gp::Resolution())
  {
    gp_XYZ GXYZ = (Item.g.XYZ()).Multiplied(Item.dim * Density);
    g.SetXYZ(g.XYZ().Multiplied(dim));
    GXYZ.Add(g.XYZ());
    dim = dim + Item.dim * Density;
    if (std::abs(dim) >= 1.e-20)
    {
      GXYZ.Divide(dim);
      g.SetXYZ(GXYZ);
    }
    else
    {
      g.SetCoord(0., 0., 0.);
    }
    inertia = inertia + Item.inertia * Density;
  }
  else
  {
    gp_XYZ Itemloc = loc.XYZ() - Item.loc.XYZ();
    gp_XYZ Itemg   = Item.loc.XYZ() + Item.g.XYZ();
    gp_XYZ GXYZ    = Item.g.XYZ() - Itemloc;
    GXYZ           = GXYZ.Multiplied(Item.dim * Density);
    g.SetXYZ(g.XYZ().Multiplied(dim));
    GXYZ.Add(g.XYZ());
    dim = dim + Item.dim * Density;
    if (std::abs(dim) >= 1.e-20)
    {
      GXYZ.Divide(dim);
      g.SetXYZ(GXYZ);
    }
    else
    {
      g.SetCoord(0., 0., 0.);
    }

    gp_Mat HMat;
    gp_Mat ItemInertia = Item.inertia;
    if (Item.g.XYZ().Modulus() > gp::Resolution())
    {

      GProp::HOperator(Itemg, Item.loc, Item.dim, HMat);
      ItemInertia = ItemInertia - HMat;
    }

    GProp::HOperator(Itemg, loc, Item.dim, HMat);
    ItemInertia = ItemInertia + HMat;
    inertia     = inertia + ItemInertia * Density;
  }
}

double GProp_GProps::Mass() const
{
  return dim;
}

gp_Pnt GProp_GProps::CentreOfMass() const
{
  return gp_Pnt(loc.XYZ() + g.XYZ());
}

gp_Mat GProp_GProps::MatrixOfInertia() const
{
  gp_Mat HMat;
  GProp::HOperator(g, gp::Origin(), dim, HMat);
  return inertia - HMat;
}

void GProp_GProps::StaticMoments(double& Ix, double& Iy, double& Iz) const
{

  gp_XYZ G = loc.XYZ() + g.XYZ();
  Ix       = G.X() * dim;
  Iy       = G.Y() * dim;
  Iz       = G.Z() * dim;
}

double GProp_GProps::MomentOfInertia(const gp_Ax1& A) const
{

  if (loc.Distance(A.Location()) <= gp::Resolution())
  {
    return (A.Direction().XYZ()).Dot((A.Direction().XYZ()).Multiplied(inertia));
  }
  else
  {
    gp_Mat HMat;
    gp_Mat AxisInertia = MatrixOfInertia();
    GProp::HOperator(gp_Pnt(loc.XYZ() + g.XYZ()), A.Location(), dim, HMat);
    AxisInertia = AxisInertia + HMat;
    return (A.Direction().XYZ()).Dot((A.Direction().XYZ()).Multiplied(AxisInertia));
  }
}

double GProp_GProps::RadiusOfGyration(const gp_Ax1& A) const
{

  return std::sqrt(MomentOfInertia(A) / dim);
}

GProp_PrincipalProps GProp_GProps::PrincipalProperties() const
{

  math_Matrix DiagMat(1, 3, 1, 3);
  int         i, j;
  gp_Mat      AxisInertia = MatrixOfInertia();
  for (j = 1; j <= 3; j++)
  {
    for (i = 1; i <= 3; i++)
    {
      DiagMat(i, j) = AxisInertia.Value(i, j);
    }
  }
  math_Jacobi J(DiagMat);
  double      Ixx = J.Value(1);
  double      Iyy = J.Value(2);
  double      Izz = J.Value(3);
  DiagMat         = J.Vectors();
  gp_Vec Vxx(DiagMat(1, 1), DiagMat(2, 1), DiagMat(3, 1));
  gp_Vec Vyy(DiagMat(1, 2), DiagMat(2, 2), DiagMat(3, 2));
  gp_Vec Vzz(DiagMat(1, 3), DiagMat(2, 3), DiagMat(3, 3));

  double Rxx = 0.0e0;
  double Ryy = 0.0e0;
  double Rzz = 0.0e0;
  if (0.0e0 != dim)
  {
    Rxx = std::sqrt(std::abs(Ixx / dim));
    Ryy = std::sqrt(std::abs(Iyy / dim));
    Rzz = std::sqrt(std::abs(Izz / dim));
  }
  return GProp_PrincipalProps(Ixx,
                              Iyy,
                              Izz,
                              Rxx,
                              Ryy,
                              Rzz,
                              Vxx,
                              Vyy,
                              Vzz,
                              gp_Pnt(g.XYZ() + loc.XYZ()));
}

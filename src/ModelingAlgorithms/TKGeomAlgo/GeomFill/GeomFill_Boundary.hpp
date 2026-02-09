#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Real.hpp>
#include <Standard_Transient.hpp>
class gp_Pnt;
class gp_Vec;

class GeomFill_Boundary : public Standard_Transient
{

public:
  Standard_EXPORT virtual gp_Pnt Value(const double U) const = 0;

  Standard_EXPORT virtual void D1(const double U, gp_Pnt& P, gp_Vec& V) const = 0;

  Standard_EXPORT virtual bool HasNormals() const;

  Standard_EXPORT virtual gp_Vec Norm(const double U) const;

  Standard_EXPORT virtual void D1Norm(const double U, gp_Vec& N, gp_Vec& DN) const;

  Standard_EXPORT virtual void Reparametrize(const double First,
                                             const double Last,
                                             const bool   HasDF,
                                             const bool   HasDL,
                                             const double DF,
                                             const double DL,
                                             const bool   Rev) = 0;

  Standard_EXPORT void Points(gp_Pnt& PFirst, gp_Pnt& PLast) const;

  Standard_EXPORT virtual void Bounds(double& First, double& Last) const = 0;

  Standard_EXPORT virtual bool IsDegenerated() const = 0;

  Standard_EXPORT double Tol3d() const;

  Standard_EXPORT void Tol3d(const double Tol);

  Standard_EXPORT double Tolang() const;

  Standard_EXPORT void Tolang(const double Tol);

  DEFINE_STANDARD_RTTIEXT(GeomFill_Boundary, Standard_Transient)

protected:
  Standard_EXPORT GeomFill_Boundary(const double Tol3d, const double Tolang);

private:
  double myT3d;
  double myTang;
};

#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <GeomAbs_SurfaceType.hpp>
#include <gp_Ax3.hpp>
#include <NCollection_List.hpp>

class gp_Cone;
class gp_Cylinder;

class IntAna_Curve
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IntAna_Curve();

  Standard_EXPORT void SetCylinderQuadValues(const gp_Cylinder& Cylinder,
                                             const double       Qxx,
                                             const double       Qyy,
                                             const double       Qzz,
                                             const double       Qxy,
                                             const double       Qxz,
                                             const double       Qyz,
                                             const double       Qx,
                                             const double       Qy,
                                             const double       Qz,
                                             const double       Q1,
                                             const double       Tol,
                                             const double       DomInf,
                                             const double       DomSup,
                                             const bool         TwoZForATheta,
                                             const bool         ZIsPositive);

  Standard_EXPORT void SetConeQuadValues(const gp_Cone& Cone,
                                         const double   Qxx,
                                         const double   Qyy,
                                         const double   Qzz,
                                         const double   Qxy,
                                         const double   Qxz,
                                         const double   Qyz,
                                         const double   Qx,
                                         const double   Qy,
                                         const double   Qz,
                                         const double   Q1,
                                         const double   Tol,
                                         const double   DomInf,
                                         const double   DomSup,
                                         const bool     TwoZForATheta,
                                         const bool     ZIsPositive);

  Standard_EXPORT bool IsOpen() const;

  Standard_EXPORT void Domain(double& theFirst, double& theLast) const;

  Standard_EXPORT bool IsConstant() const;

  Standard_EXPORT bool IsFirstOpen() const;

  Standard_EXPORT bool IsLastOpen() const;

  Standard_EXPORT gp_Pnt Value(const double Theta);

  Standard_EXPORT bool D1u(const double Theta, gp_Pnt& P, gp_Vec& V);

  Standard_EXPORT void FindParameter(const gp_Pnt& P, NCollection_List<double>& theParams) const;

  Standard_EXPORT void SetIsFirstOpen(const bool Flag);

  Standard_EXPORT void SetIsLastOpen(const bool Flag);

  Standard_EXPORT void SetDomain(const double theFirst, const double theLast);

protected:
  Standard_EXPORT gp_Pnt InternalValue(const double Theta1, const double Theta2) const;

  Standard_EXPORT void InternalUVValue(const double Param,
                                       double&      U,
                                       double&      V,
                                       double&      A,
                                       double&      B,
                                       double&      C,
                                       double&      Co,
                                       double&      Si,
                                       double&      Di) const;

private:
  double Z0Cte;
  double Z0Sin;
  double Z0Cos;
  double Z0SinSin;
  double Z0CosCos;
  double Z0CosSin;
  double Z1Cte;
  double Z1Sin;
  double Z1Cos;
  double Z1SinSin;
  double Z1CosCos;
  double Z1CosSin;
  double Z2Cte;
  double Z2Sin;
  double Z2Cos;
  double Z2SinSin;
  double Z2CosCos;
  double Z2CosSin;
  bool   TwoCurves;
  bool   TakeZPositive;
  double Tolerance;

  double              DomainInf, DomainSup;
  bool                RestrictedInf;
  bool                RestrictedSup;
  bool                firstbounded;
  bool                lastbounded;
  GeomAbs_SurfaceType typequadric;
  double              RCyl;
  double              Angle;
  gp_Ax3              Ax3;

  double myFirstParameter, myLastParameter;
};

#pragma once

#include <Adaptor3d_Surface.hpp>
#include <BlendFunc_GenChamfer.hpp>
#include <math_Vector.hpp>
#include <NCollection_Array1.hpp>
#include <Standard_Integer.hpp>
#include <gp_Vec2d.hpp>

class math_Matrix;

class BlendFunc_ConstThroat : public BlendFunc_GenChamfer
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BlendFunc_ConstThroat(const occ::handle<Adaptor3d_Surface>& S1,
                                        const occ::handle<Adaptor3d_Surface>& S2,
                                        const occ::handle<Adaptor3d_Curve>&   C);

  Standard_EXPORT bool Value(const math_Vector& X, math_Vector& F) override;

  Standard_EXPORT bool Derivatives(const math_Vector& X, math_Matrix& D) override;

  Standard_EXPORT void Set(const double Param) override;

  Standard_EXPORT bool IsSolution(const math_Vector& Sol, const double Tol) override;

  Standard_EXPORT const gp_Pnt& PointOnS1() const override;

  Standard_EXPORT const gp_Pnt& PointOnS2() const override;

  Standard_EXPORT bool IsTangencyPoint() const override;

  Standard_EXPORT const gp_Vec& TangentOnS1() const override;

  Standard_EXPORT const gp_Vec2d& Tangent2dOnS1() const override;

  Standard_EXPORT const gp_Vec& TangentOnS2() const override;

  Standard_EXPORT const gp_Vec2d& Tangent2dOnS2() const override;

  Standard_EXPORT void Tangent(const double U1,
                               const double V1,
                               const double U2,
                               const double V2,
                               gp_Vec&      TgFirst,
                               gp_Vec&      TgLast,
                               gp_Vec&      NormFirst,
                               gp_Vec&      NormLast) const override;

  Standard_EXPORT void Set(const double aThroat, const double, const int Choix) override;

  Standard_EXPORT double GetSectionSize() const override;

protected:
  gp_Pnt   pts1;
  gp_Pnt   pts2;
  gp_Vec   d1u1;
  gp_Vec   d1v1;
  gp_Vec   d1u2;
  gp_Vec   d1v2;
  bool     istangent;
  gp_Vec   tg1;
  gp_Vec2d tg12d;
  gp_Vec   tg2;
  gp_Vec2d tg22d;
  double   param;
  double   Throat;

  gp_Pnt ptgui;
  gp_Vec nplan;
  double normtg;
  double theD;
  gp_Vec d1gui;
  gp_Vec d2gui;
};

#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <math_Matrix.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array1.hpp>
#include <gp_Vec.hpp>
class gp_Pnt;
class gp_Vec;

//! To convert circular section in polynome
class GeomFill_PolynomialConvertor
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomFill_PolynomialConvertor();

  //! say if <me> is Initialized
  Standard_EXPORT bool Initialized() const;

  Standard_EXPORT void Init();

  Standard_EXPORT void Section(const gp_Pnt&               FirstPnt,
                               const gp_Pnt&               Center,
                               const gp_Vec&               Dir,
                               const double                Angle,
                               NCollection_Array1<gp_Pnt>& Poles) const;

  Standard_EXPORT void Section(const gp_Pnt&               FirstPnt,
                               const gp_Vec&               DFirstPnt,
                               const gp_Pnt&               Center,
                               const gp_Vec&               DCenter,
                               const gp_Vec&               Dir,
                               const gp_Vec&               DDir,
                               const double                Angle,
                               const double                DAngle,
                               NCollection_Array1<gp_Pnt>& Poles,
                               NCollection_Array1<gp_Vec>& DPoles) const;

  Standard_EXPORT void Section(const gp_Pnt&               FirstPnt,
                               const gp_Vec&               DFirstPnt,
                               const gp_Vec&               D2FirstPnt,
                               const gp_Pnt&               Center,
                               const gp_Vec&               DCenter,
                               const gp_Vec&               D2Center,
                               const gp_Vec&               Dir,
                               const gp_Vec&               DDir,
                               const gp_Vec&               D2Dir,
                               const double                Angle,
                               const double                DAngle,
                               const double                D2Angle,
                               NCollection_Array1<gp_Pnt>& Poles,
                               NCollection_Array1<gp_Vec>& DPoles,
                               NCollection_Array1<gp_Vec>& D2Poles) const;

private:
  int         Ordre;
  bool        myinit;
  math_Matrix BH;
};

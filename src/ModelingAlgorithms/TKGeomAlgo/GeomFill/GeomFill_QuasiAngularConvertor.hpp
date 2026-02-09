#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <math_Matrix.hpp>
#include <math_Vector.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array1.hpp>
#include <gp_Vec.hpp>
class gp_Pnt;
class gp_Vec;

class GeomFill_QuasiAngularConvertor
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomFill_QuasiAngularConvertor();

  Standard_EXPORT bool Initialized() const;

  Standard_EXPORT void Init();

  Standard_EXPORT void Section(const gp_Pnt&               FirstPnt,
                               const gp_Pnt&               Center,
                               const gp_Vec&               Dir,
                               const double                Angle,
                               NCollection_Array1<gp_Pnt>& Poles,
                               NCollection_Array1<double>& Weights);

  Standard_EXPORT void Section(const gp_Pnt&               FirstPnt,
                               const gp_Vec&               DFirstPnt,
                               const gp_Pnt&               Center,
                               const gp_Vec&               DCenter,
                               const gp_Vec&               Dir,
                               const gp_Vec&               DDir,
                               const double                Angle,
                               const double                DAngle,
                               NCollection_Array1<gp_Pnt>& Poles,
                               NCollection_Array1<gp_Vec>& DPoles,
                               NCollection_Array1<double>& Weights,
                               NCollection_Array1<double>& DWeights);

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
                               NCollection_Array1<gp_Vec>& D2Poles,
                               NCollection_Array1<double>& Weights,
                               NCollection_Array1<double>& DWeights,
                               NCollection_Array1<double>& D2Weights);

private:
  bool        myinit;
  math_Matrix B;
  math_Vector Px;
  math_Vector Py;
  math_Vector W;
  math_Vector Vx;
  math_Vector Vy;
  math_Vector Vw;
};

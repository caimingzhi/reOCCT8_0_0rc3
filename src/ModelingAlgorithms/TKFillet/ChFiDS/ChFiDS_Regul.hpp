#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>

class ChFiDS_Regul
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT ChFiDS_Regul();

  Standard_EXPORT void SetCurve(const int IC);

  Standard_EXPORT void SetS1(const int IS1, const bool IsFace = true);

  Standard_EXPORT void SetS2(const int IS2, const bool IsFace = true);

  Standard_EXPORT bool IsSurface1() const;

  Standard_EXPORT bool IsSurface2() const;

  Standard_EXPORT int Curve() const;

  Standard_EXPORT int S1() const;

  Standard_EXPORT int S2() const;

private:
  int icurv;
  int is1;
  int is2;
};

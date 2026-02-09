#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <LProp_CurAndInf.hpp>
class Geom2d_Curve;

class Geom2dLProp_CurAndInf2d : public LProp_CurAndInf
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Geom2dLProp_CurAndInf2d();

  Standard_EXPORT void Perform(const occ::handle<Geom2d_Curve>& C);

  Standard_EXPORT void PerformCurExt(const occ::handle<Geom2d_Curve>& C);

  Standard_EXPORT void PerformInf(const occ::handle<Geom2d_Curve>& C);

  Standard_EXPORT bool IsDone() const;

private:
  bool isDone;
};

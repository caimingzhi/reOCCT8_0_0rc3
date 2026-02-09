#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_Trsf.hpp>
class gp_Pnt;

class gce_MakeScale
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT gce_MakeScale(const gp_Pnt& Point, const double Scale);

  Standard_EXPORT const gp_Trsf& Value() const;

  Standard_EXPORT const gp_Trsf& Operator() const;
  Standard_EXPORT                operator gp_Trsf() const;

private:
  gp_Trsf TheScale;
};

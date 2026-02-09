#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_Trsf.hpp>
class gp_Vec;
class gp_Pnt;

class gce_MakeTranslation
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT gce_MakeTranslation(const gp_Vec& Vect);

  Standard_EXPORT gce_MakeTranslation(const gp_Pnt& Point1, const gp_Pnt& Point2);

  Standard_EXPORT const gp_Trsf& Value() const;

  Standard_EXPORT const gp_Trsf& Operator() const;
  Standard_EXPORT                operator gp_Trsf() const;

private:
  gp_Trsf TheTranslation;
};

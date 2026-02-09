#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <GProp_GProps.hpp>
class BRepGProp_Face;
class gp_Pnt;
class BRepGProp_Domain;

class BRepGProp_Sinert : public GProp_GProps
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepGProp_Sinert();

  Standard_EXPORT BRepGProp_Sinert(const BRepGProp_Face& S, const gp_Pnt& SLocation);

  Standard_EXPORT BRepGProp_Sinert(BRepGProp_Face& S, BRepGProp_Domain& D, const gp_Pnt& SLocation);

  Standard_EXPORT BRepGProp_Sinert(BRepGProp_Face& S, const gp_Pnt& SLocation, const double Eps);

  Standard_EXPORT BRepGProp_Sinert(BRepGProp_Face&   S,
                                   BRepGProp_Domain& D,
                                   const gp_Pnt&     SLocation,
                                   const double      Eps);

  Standard_EXPORT void SetLocation(const gp_Pnt& SLocation);

  Standard_EXPORT void Perform(const BRepGProp_Face& S);

  Standard_EXPORT void Perform(BRepGProp_Face& S, BRepGProp_Domain& D);

  Standard_EXPORT double Perform(BRepGProp_Face& S, const double Eps);

  Standard_EXPORT double Perform(BRepGProp_Face& S, BRepGProp_Domain& D, const double Eps);

  Standard_EXPORT double GetEpsilon();

private:
  double myEpsilon;
};

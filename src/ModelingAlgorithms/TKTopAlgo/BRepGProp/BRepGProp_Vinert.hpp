#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <GProp_GProps.hpp>
class BRepGProp_Face;
class gp_Pnt;
class gp_Pln;
class BRepGProp_Domain;

class BRepGProp_Vinert : public GProp_GProps
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepGProp_Vinert();

  Standard_EXPORT BRepGProp_Vinert(const BRepGProp_Face& S, const gp_Pnt& VLocation);

  Standard_EXPORT BRepGProp_Vinert(BRepGProp_Face& S, const gp_Pnt& VLocation, const double Eps);

  Standard_EXPORT BRepGProp_Vinert(const BRepGProp_Face& S,
                                   const gp_Pnt&         O,
                                   const gp_Pnt&         VLocation);

  Standard_EXPORT BRepGProp_Vinert(BRepGProp_Face& S,
                                   const gp_Pnt&   O,
                                   const gp_Pnt&   VLocation,
                                   const double    Eps);

  Standard_EXPORT BRepGProp_Vinert(const BRepGProp_Face& S,
                                   const gp_Pln&         Pl,
                                   const gp_Pnt&         VLocation);

  Standard_EXPORT BRepGProp_Vinert(BRepGProp_Face& S,
                                   const gp_Pln&   Pl,
                                   const gp_Pnt&   VLocation,
                                   const double    Eps);

  Standard_EXPORT BRepGProp_Vinert(BRepGProp_Face& S, BRepGProp_Domain& D, const gp_Pnt& VLocation);

  Standard_EXPORT BRepGProp_Vinert(BRepGProp_Face&   S,
                                   BRepGProp_Domain& D,
                                   const gp_Pnt&     VLocation,
                                   const double      Eps);

  Standard_EXPORT BRepGProp_Vinert(BRepGProp_Face&   S,
                                   BRepGProp_Domain& D,
                                   const gp_Pnt&     O,
                                   const gp_Pnt&     VLocation);

  Standard_EXPORT BRepGProp_Vinert(BRepGProp_Face&   S,
                                   BRepGProp_Domain& D,
                                   const gp_Pnt&     O,
                                   const gp_Pnt&     VLocation,
                                   const double      Eps);

  Standard_EXPORT BRepGProp_Vinert(BRepGProp_Face&   S,
                                   BRepGProp_Domain& D,
                                   const gp_Pln&     Pl,
                                   const gp_Pnt&     VLocation);

  Standard_EXPORT BRepGProp_Vinert(BRepGProp_Face&   S,
                                   BRepGProp_Domain& D,
                                   const gp_Pln&     Pl,
                                   const gp_Pnt&     VLocation,
                                   const double      Eps);

  Standard_EXPORT void SetLocation(const gp_Pnt& VLocation);

  Standard_EXPORT void Perform(const BRepGProp_Face& S);

  Standard_EXPORT double Perform(BRepGProp_Face& S, const double Eps);

  Standard_EXPORT void Perform(const BRepGProp_Face& S, const gp_Pnt& O);

  Standard_EXPORT double Perform(BRepGProp_Face& S, const gp_Pnt& O, const double Eps);

  Standard_EXPORT void Perform(const BRepGProp_Face& S, const gp_Pln& Pl);

  Standard_EXPORT double Perform(BRepGProp_Face& S, const gp_Pln& Pl, const double Eps);

  Standard_EXPORT void Perform(BRepGProp_Face& S, BRepGProp_Domain& D);

  Standard_EXPORT double Perform(BRepGProp_Face& S, BRepGProp_Domain& D, const double Eps);

  Standard_EXPORT void Perform(BRepGProp_Face& S, BRepGProp_Domain& D, const gp_Pnt& O);

  Standard_EXPORT double Perform(BRepGProp_Face&   S,
                                 BRepGProp_Domain& D,
                                 const gp_Pnt&     O,
                                 const double      Eps);

  Standard_EXPORT void Perform(BRepGProp_Face& S, BRepGProp_Domain& D, const gp_Pln& Pl);

  Standard_EXPORT double Perform(BRepGProp_Face&   S,
                                 BRepGProp_Domain& D,
                                 const gp_Pln&     Pl,
                                 const double      Eps);

  Standard_EXPORT double GetEpsilon();

private:
  double myEpsilon;
};

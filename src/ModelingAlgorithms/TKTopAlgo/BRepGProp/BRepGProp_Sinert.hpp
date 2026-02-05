#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <GProp_GProps.hpp>
class BRepGProp_Face;
class gp_Pnt;
class BRepGProp_Domain;

//! Computes the global properties of a face in 3D space.
//! The face 's requirements to evaluate the global properties
//! are defined in the template FaceTool from package GProp.
class BRepGProp_Sinert : public GProp_GProps
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepGProp_Sinert();

  Standard_EXPORT BRepGProp_Sinert(const BRepGProp_Face& S, const gp_Pnt& SLocation);

  //! Builds a Sinert to evaluate the global properties of
  //! the face <S>. If isNaturalRestriction is true the domain of S is defined
  //! with the natural bounds, else it defined with an iterator
  //! of Edge from TopoDS (see DomainTool from GProp)
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

  //! If previously used method contained Eps parameter
  //! get actual relative error of the computation, else return 1.0.
  Standard_EXPORT double GetEpsilon();

private:
  double myEpsilon;
};

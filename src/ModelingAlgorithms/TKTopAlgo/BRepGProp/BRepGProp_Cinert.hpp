#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <GProp_GProps.hpp>
class BRepAdaptor_Curve;
class gp_Pnt;

//! Computes the global properties of bounded curves
//! in 3D space. The curve must have at least a continuity C1.
//! It can be a curve as defined in the template CurveTool from
//! package GProp. This template gives the minimum of methods
//! required to evaluate the global properties of a curve 3D with
//! the algorithms of GProp.
class BRepGProp_Cinert : public GProp_GProps
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepGProp_Cinert();

  Standard_EXPORT BRepGProp_Cinert(const BRepAdaptor_Curve& C, const gp_Pnt& CLocation);

  Standard_EXPORT void SetLocation(const gp_Pnt& CLocation);

  Standard_EXPORT void Perform(const BRepAdaptor_Curve& C);
};

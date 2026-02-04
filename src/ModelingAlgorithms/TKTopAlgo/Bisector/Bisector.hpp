#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>
#include <Standard_Real.hpp>
class Geom2d_Curve;

//! This package provides the bisecting line between two
//! geometric elements.
class Bisector
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static bool IsConvex(const occ::handle<Geom2d_Curve>& Cu, const double Sign);
};


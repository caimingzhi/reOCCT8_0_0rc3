#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <ShapeExtend_Status.hpp>
#include <Standard_Boolean.hpp>

//! This package provides general tools and data structures common
//! for other packages in SHAPEWORKS and extending CAS.CADE
//! structures.
//! The following items are provided by this package:
//! - enumeration Status used for coding status flags in methods
//! inside the SHAPEWORKS
//! - enumeration Parametrisation used for setting global parametrisation
//! on the composite surface
//! - class CompositeSurface representing a composite surface
//! made of a grid of surface patches
//! - class WireData representing a wire in the form of ordered
//! list of edges
//! - class MsgRegistrator for attaching messages to the objects
//! - tools for exploring the shapes
//! - tools for creating new shapes
class ShapeExtend
{
public:
  DEFINE_STANDARD_ALLOC

  //! Inits using of ShapeExtend.
  //! Currently, loads messages output by ShapeHealing algorithms.
  Standard_EXPORT static void Init();

  //! Encodes status (enumeration) to a bit flag
  Standard_EXPORT static int EncodeStatus(const ShapeExtend_Status status);

  //! Tells if a bit flag contains bit corresponding to enumerated status
  Standard_EXPORT static bool DecodeStatus(const int flag, const ShapeExtend_Status status);
};

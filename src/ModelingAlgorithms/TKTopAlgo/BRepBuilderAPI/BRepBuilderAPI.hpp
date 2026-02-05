#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Real.hpp>
class Geom_Plane;

//! The BRepBuilderAPI package provides an Application
//! Programming Interface for the BRep topology data
//! structure.
//!
//! The API is a set of classes aiming to provide:
//!
//! * High level and simple calls for the most common
//! operations.
//!
//! * Keeping an access on the low-level
//! implementation of high-level calls.
//!
//! * Examples of programming of high-level operations
//! from low-level operations.
//!
//! * A complete coverage of modelling:
//!
//! - Creating vertices ,edges, faces, solids.
//!
//! - Sweeping operations.
//!
//! - Boolean operations.
//!
//! - Global properties computation.
//!
//! The API provides classes to build objects:
//!
//! * The constructors of the classes provides the
//! different constructions methods.
//!
//! * The class keeps as fields the different tools
//! used to build the object.
//!
//! * The class provides a casting method to get
//! automatically the result with a function-like
//! call.
//!
//! For example to make a vertex <V> from a point <P>
//! one can write:
//!
//! V = BRepBuilderAPI_MakeVertex(P);
//!
//! or
//!
//! BRepBuilderAPI_MakeVertex MV(P);
//! V = MV.Vertex();
//!
//! For tolerances a default precision is used which
//! can be changed by the packahe method
//! BRepBuilderAPI::Precision.
//!
//! For error handling the BRepBuilderAPI commands raise only
//! the NotDone error. When Done is false on a command
//! the error description can be asked to the command.
//!
//! In theory the commands can be called with any
//! arguments, argument checking is performed by the
//! command.
class BRepBuilderAPI
{
public:
  DEFINE_STANDARD_ALLOC

  //! Sets the current plane.
  Standard_EXPORT static void Plane(const occ::handle<Geom_Plane>& P);

  //! Returns the current plane.
  Standard_EXPORT static const occ::handle<Geom_Plane>& Plane();

  //! Sets the default precision. The current Precision
  //! is returned.
  Standard_EXPORT static void Precision(const double P);

  //! Returns the default precision.
  Standard_EXPORT static double Precision();
};

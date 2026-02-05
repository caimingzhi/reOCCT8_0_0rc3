#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_OStream.hpp>
class TopoDS_Shape;

//! The TopTools package provides utilities for the
//! topological data structure.
//!
//! * ShapeMapHasher. Hash a Shape base on the TShape
//! and the Location. The Orientation is not used.
//!
//! * OrientedShapeMapHasher. Hash a Shape base on the
//! TShape ,the Location and the Orientation.
//!
//! * Instantiations of TCollection for Shapes :
//! MapOfShape
//! IndexedMapOfShape
//! DataMapOfIntegerShape
//! DataMapOfShapeInteger
//! DataMapOfShapeReal
//! Array1OfShape
//! HArray1OfShape
//! SequenceOfShape
//! HSequenceOfShape
//! ListOfShape
//! Array1OfListShape
//! HArray1OfListShape
//! DataMapOfIntegerListOfShape
//! DataMapOfShapeListOfShape
//! DataMapOfShapeListOfInteger
//! IndexedDataMapOfShapeShape
//! IndexedDataMapOfShapeListOfShape
//! DataMapOfShapeShape
//! IndexedMapOfOrientedShape
//! DataMapOfShapeSequenceOfShape
//! IndexedDataMapOfShapeAddress
//! DataMapOfOrientedShapeShape
//!
//! * LocationSet: to write sets of locations.
//!
//! * ShapeSet: to writes sets of TShapes.
//!
//! Package Methods:
//!
//! Dump: To dump the topology of a Shape.
class TopTools
{
public:
  DEFINE_STANDARD_ALLOC

  //! A set of Shapes. Can be dump, wrote or read.
  //! Dumps the topological structure of <Sh> on the
  //! stream <S>.
  Standard_EXPORT static void Dump(const TopoDS_Shape& Sh, Standard_OStream& S);

  //! This is to bypass an extraction bug. It will force
  //! the inclusion of int.hxx itself
  //! including Standard_OStream.hpp at the correct
  //! position.
  Standard_EXPORT static void Dummy(const int I);
};

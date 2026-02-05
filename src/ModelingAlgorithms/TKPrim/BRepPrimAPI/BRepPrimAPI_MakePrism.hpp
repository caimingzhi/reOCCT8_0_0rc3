#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <BRepSweep_Prism.hpp>
#include <BRepPrimAPI_MakeSweep.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
class TopoDS_Shape;
class gp_Vec;
class gp_Dir;

//! Describes functions to build linear swept topologies, called prisms.
//! A prism is defined by:
//! -   a basis shape, which is swept, and
//! -   a sweeping direction, which is:
//! -   a vector for finite prisms, or
//! -   a direction for infinite or semi-infinite prisms.
//! The basis shape must not contain any solids.
//! The profile generates objects according to the following rules:
//! -   Vertices generate Edges
//! -   Edges generate Faces.
//! -   Wires generate Shells.
//! -   Faces generate Solids.
//! -   Shells generate Composite Solids
//! A MakePrism object provides a framework for:
//! -   defining the construction of a prism,
//! -   implementing the construction algorithm, and
//! -   consulting the result.
class BRepPrimAPI_MakePrism : public BRepPrimAPI_MakeSweep
{
public:
  DEFINE_STANDARD_ALLOC

  //! Builds the prism of base S and vector V. If C is true,
  //! S is copied. If Canonize is true then generated surfaces
  //! are attempted to be canonized in simple types
  Standard_EXPORT BRepPrimAPI_MakePrism(const TopoDS_Shape& S,
                                        const gp_Vec&       V,
                                        const bool          Copy     = false,
                                        const bool          Canonize = true);

  //! Builds a semi-infinite or an infinite prism of base S.
  //! If Inf is true the prism is infinite, if Inf is false
  //! the prism is semi-infinite (in the direction D). If C
  //! is true S is copied (for semi-infinite prisms).
  //! If Canonize is true then generated surfaces
  //! are attempted to be canonized in simple types
  Standard_EXPORT BRepPrimAPI_MakePrism(const TopoDS_Shape& S,
                                        const gp_Dir&       D,
                                        const bool          Inf      = true,
                                        const bool          Copy     = false,
                                        const bool          Canonize = true);

  //! Returns the internal sweeping algorithm.
  Standard_EXPORT const BRepSweep_Prism& Prism() const;

  //! Builds the resulting shape (redefined from MakeShape).
  Standard_EXPORT void Build(
    const Message_ProgressRange& theRange = Message_ProgressRange()) override;

  //! Returns the TopoDS Shape of the bottom of the prism.
  Standard_EXPORT TopoDS_Shape FirstShape() override;

  //! Returns the TopoDS Shape of the top of the prism.
  //! In the case of a finite prism, FirstShape returns the
  //! basis of the prism, in other words, S if Copy is false;
  //! otherwise, the copy of S belonging to the prism.
  //! LastShape returns the copy of S translated by V at the
  //! time of construction.
  Standard_EXPORT TopoDS_Shape LastShape() override;

  //! Returns ListOfShape from TopTools.
  Standard_EXPORT const NCollection_List<TopoDS_Shape>& Generated(const TopoDS_Shape& S) override;

  //! Returns true if the shape S has been deleted.
  Standard_EXPORT bool IsDeleted(const TopoDS_Shape& S) override;

  //! Returns the TopoDS Shape of the bottom of the prism.
  //! generated with theShape (subShape of the generating shape).
  Standard_EXPORT TopoDS_Shape FirstShape(const TopoDS_Shape& theShape);

  //! Returns the TopoDS Shape of the top of the prism.
  //! generated with theShape (subShape of the generating shape).
  Standard_EXPORT TopoDS_Shape LastShape(const TopoDS_Shape& theShape);

private:
  BRepSweep_Prism myPrism;
};

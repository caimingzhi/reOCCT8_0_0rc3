#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <BRepSweep_Revol.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <BRepPrimAPI_MakeSweep.hpp>
#include <BRepTools_History.hpp>
class TopoDS_Shape;
class gp_Ax1;

//! Class to make revolved sweep topologies.
//!
//! a revolved sweep is defined by :
//!
//! * A basis topology which is swept.
//!
//! The basis topology must not contain solids
//! (neither composite solids.).
//!
//! The basis topology may be copied or shared in
//! the result.
//!
//! * A rotation axis and angle :
//!
//! - The axis is an Ax1 from gp.
//!
//! - The angle is in [0, 2*Pi].
//!
//! - The angle default value is 2*Pi.
//!
//! The result is a topology with a higher dimension :
//!
//! - Vertex -> Edge.
//! - Edge   -> Face.
//! - Wire   -> Shell.
//! - Face   -> Solid.
//! - Shell  -> CompSolid.
//!
//! Sweeping a Compound sweeps the elements of the
//! compound and creates a compound with the
//! results.
class BRepPrimAPI_MakeRevol : public BRepPrimAPI_MakeSweep
{
public:
  DEFINE_STANDARD_ALLOC

  //! Builds the Revol of base S, axis A and angle D. If C
  //! is true, S is copied.
  Standard_EXPORT BRepPrimAPI_MakeRevol(const TopoDS_Shape& S,
                                        const gp_Ax1&       A,
                                        const double        D,
                                        const bool          Copy = false);

  //! Builds the Revol of base S, axis A and angle 2*Pi. If
  //! C is true, S is copied.
  Standard_EXPORT BRepPrimAPI_MakeRevol(const TopoDS_Shape& S,
                                        const gp_Ax1&       A,
                                        const bool          Copy = false);

  //! Returns the internal sweeping algorithm.
  Standard_EXPORT const BRepSweep_Revol& Revol() const;

  //! Builds the resulting shape (redefined from MakeShape).
  Standard_EXPORT void Build(
    const Message_ProgressRange& theRange = Message_ProgressRange()) override;

  //! Returns the first shape of the revol (coinciding with
  //! the generating shape).
  Standard_EXPORT TopoDS_Shape FirstShape() override;

  //! Returns the TopoDS Shape of the end of the revol.
  Standard_EXPORT TopoDS_Shape LastShape() override;

  //! Returns list of shape generated from shape S
  //! Warning: shape S must be shape of type VERTEX, EDGE, FACE, SOLID.
  //! For shapes of other types method always returns empty list
  Standard_EXPORT const NCollection_List<TopoDS_Shape>& Generated(const TopoDS_Shape& S) override;

  //! Returns true if the shape S has been deleted.
  Standard_EXPORT bool IsDeleted(const TopoDS_Shape& S) override;

  //! Returns the TopoDS Shape of the beginning of the revolution,
  //! generated with theShape (subShape of the generating shape).
  Standard_EXPORT TopoDS_Shape FirstShape(const TopoDS_Shape& theShape);

  //! Returns the TopoDS Shape of the end of the revolution,
  //! generated with theShape (subShape of the generating shape).
  Standard_EXPORT TopoDS_Shape LastShape(const TopoDS_Shape& theShape);

  //! Check if there are degenerated edges in the result.
  Standard_EXPORT bool HasDegenerated() const;

  //! Returns the list of degenerated edges
  Standard_EXPORT const NCollection_List<TopoDS_Shape>& Degenerated() const;

protected:
  //! Checks possibilities of producing self-intersection surface
  //! returns true if all surfaces are valid
  Standard_EXPORT bool CheckValidity(const TopoDS_Shape& theShape, const gp_Ax1& theA);

private:
  BRepSweep_Revol                myRevol;
  NCollection_List<TopoDS_Shape> myDegenerated;
  occ::handle<BRepTools_History> myHist;
  bool                           myIsBuild;
};


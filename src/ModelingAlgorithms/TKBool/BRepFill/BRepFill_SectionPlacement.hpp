#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDS_Shape.hpp>
#include <gp_Trsf.hpp>
#include <Standard_Integer.hpp>
class BRepFill_LocationLaw;

//! Place a shape in a local axis coordinate
class BRepFill_SectionPlacement
{
public:
  DEFINE_STANDARD_ALLOC

  //! Automatic placement
  Standard_EXPORT BRepFill_SectionPlacement(const occ::handle<BRepFill_LocationLaw>& Law,
                                            const TopoDS_Shape&                      Section,
                                            const bool WithContact    = false,
                                            const bool WithCorrection = false);

  //! Placement on vertex
  Standard_EXPORT BRepFill_SectionPlacement(const occ::handle<BRepFill_LocationLaw>& Law,
                                            const TopoDS_Shape&                      Section,
                                            const TopoDS_Shape&                      Vertex,
                                            const bool WithContact    = false,
                                            const bool WithCorrection = false);

  Standard_EXPORT const gp_Trsf& Transformation() const;

  Standard_EXPORT double AbscissaOnPath();

private:
  Standard_EXPORT void Perform(const bool          WithContact,
                               const bool          WithCorrection,
                               const TopoDS_Shape& Vertex);

  occ::handle<BRepFill_LocationLaw> myLaw;
  TopoDS_Shape                      mySection;
  gp_Trsf                           myTrsf;
  double                            myParam;
  int                               myIndex;
};

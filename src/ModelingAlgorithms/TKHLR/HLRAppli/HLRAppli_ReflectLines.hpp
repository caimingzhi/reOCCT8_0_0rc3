#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <HLRAlgo_Projector.hpp>
#include <HLRBRep_Algo.hpp>
#include <HLRBRep_TypeOfResultingEdge.hpp>
#include <TopoDS_Shape.hpp>
#include <Standard_Real.hpp>

//! This class builds reflect lines on a shape
//! according to the axes of view defined by user.
//! Reflect lines are represented by edges in 3d.
class HLRAppli_ReflectLines
{
public:
  DEFINE_STANDARD_ALLOC

  //! Constructor
  Standard_EXPORT HLRAppli_ReflectLines(const TopoDS_Shape& aShape);

  //! Sets the normal to the plane of visualisation,
  //! the coordinates of the view point and
  //! the coordinates of the vertical direction vector.
  Standard_EXPORT void SetAxes(const double Nx,
                               const double Ny,
                               const double Nz,
                               const double XAt,
                               const double YAt,
                               const double ZAt,
                               const double XUp,
                               const double YUp,
                               const double ZUp);

  Standard_EXPORT void Perform();

  //! returns resulting compound of reflect lines
  //! represented by edges in 3d
  Standard_EXPORT TopoDS_Shape GetResult() const;

  //! returns resulting compound of lines
  //! of specified type and visibility
  //! represented by edges in 3d or 2d
  Standard_EXPORT TopoDS_Shape GetCompoundOf3dEdges(const HLRBRep_TypeOfResultingEdge type,
                                                    const bool                        visible,
                                                    const bool                        In3d) const;

private:
  HLRAlgo_Projector         myProjector;
  occ::handle<HLRBRep_Algo> myHLRAlgo;
  TopoDS_Shape              myShape;
  // TopoDS_Shape myCompound;
};

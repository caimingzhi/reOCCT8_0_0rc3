#pragma once

#include <BRepMesh_NURBSRangeSplitter.hpp>

//! Auxiliary class extending UV range splitter in order to generate
//! internal nodes for NURBS surface.
class BRepMesh_BoundaryParamsRangeSplitter : public BRepMesh_NURBSRangeSplitter
{
public:
  //! Constructor.
  BRepMesh_BoundaryParamsRangeSplitter() = default;

  //! Destructor.
  ~BRepMesh_BoundaryParamsRangeSplitter() override = default;

  //! Registers border point.
  void AddPoint(const gp_Pnt2d& thePoint) override
  {
    BRepMesh_NURBSRangeSplitter::AddPoint(thePoint);
    GetParametersU().Add(thePoint.X());
    GetParametersV().Add(thePoint.Y());
  }

protected:
  //! Initializes U and V parameters lists using CN continuity intervals.
  bool initParameters() const override { return true; }
};

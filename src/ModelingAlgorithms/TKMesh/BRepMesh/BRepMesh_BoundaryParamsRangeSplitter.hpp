#pragma once

#include <BRepMesh_NURBSRangeSplitter.hpp>

class BRepMesh_BoundaryParamsRangeSplitter : public BRepMesh_NURBSRangeSplitter
{
public:
  BRepMesh_BoundaryParamsRangeSplitter() = default;

  ~BRepMesh_BoundaryParamsRangeSplitter() override = default;

  void AddPoint(const gp_Pnt2d& thePoint) override
  {
    BRepMesh_NURBSRangeSplitter::AddPoint(thePoint);
    GetParametersU().Add(thePoint.X());
    GetParametersV().Add(thePoint.Y());
  }

protected:
  bool initParameters() const override { return true; }
};

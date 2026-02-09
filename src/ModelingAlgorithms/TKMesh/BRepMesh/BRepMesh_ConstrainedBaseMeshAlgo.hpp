#pragma once

#include <BRepMesh_BaseMeshAlgo.hpp>

class BRepMesh_Delaun;

class BRepMesh_ConstrainedBaseMeshAlgo : public BRepMesh_BaseMeshAlgo
{
public:
  BRepMesh_ConstrainedBaseMeshAlgo() = default;

  ~BRepMesh_ConstrainedBaseMeshAlgo() override = default;

  DEFINE_STANDARD_RTTIEXT(BRepMesh_ConstrainedBaseMeshAlgo, BRepMesh_BaseMeshAlgo)

protected:
  virtual std::pair<int, int> getCellsCount(const int) { return std::pair<int, int>(-1, -1); }

  virtual void postProcessMesh(BRepMesh_Delaun&, const Message_ProgressRange&) {}
};

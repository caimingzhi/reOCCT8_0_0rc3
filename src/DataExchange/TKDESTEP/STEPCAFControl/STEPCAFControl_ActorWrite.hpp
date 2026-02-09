#pragma once

#include <Standard.hpp>

#include <Standard_Boolean.hpp>
#include <TopoDS_Shape.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_Map.hpp>
#include <STEPControl_ActorWrite.hpp>
class TopoDS_Shape;

class STEPCAFControl_ActorWrite : public STEPControl_ActorWrite
{

public:
  Standard_EXPORT STEPCAFControl_ActorWrite();

  Standard_EXPORT bool IsAssembly(const occ::handle<StepData_StepModel>& theModel,
                                  TopoDS_Shape&                          S) const override;

  Standard_EXPORT void SetStdMode(const bool stdmode = true);

  Standard_EXPORT void ClearMap();

  Standard_EXPORT void RegisterAssembly(const TopoDS_Shape& S);

  DEFINE_STANDARD_RTTIEXT(STEPCAFControl_ActorWrite, STEPControl_ActorWrite)

private:
  bool                                                   myStdMode;
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> myMap;
};

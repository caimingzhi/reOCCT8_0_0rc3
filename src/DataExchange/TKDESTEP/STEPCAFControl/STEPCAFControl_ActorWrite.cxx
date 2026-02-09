#include <STEPCAFControl_ActorWrite.hpp>
#include <TopoDS_Shape.hpp>

IMPLEMENT_STANDARD_RTTIEXT(STEPCAFControl_ActorWrite, STEPControl_ActorWrite)

STEPCAFControl_ActorWrite::STEPCAFControl_ActorWrite()
    : myStdMode(true)
{
}

void STEPCAFControl_ActorWrite::SetStdMode(const bool stdmode)
{
  myStdMode = stdmode;
  if (myStdMode)
    ClearMap();
}

void STEPCAFControl_ActorWrite::ClearMap()
{
  myMap.Clear();
}

void STEPCAFControl_ActorWrite::RegisterAssembly(const TopoDS_Shape& S)
{
  if (!myStdMode && S.ShapeType() == TopAbs_COMPOUND)
    myMap.Add(S);
}

bool STEPCAFControl_ActorWrite::IsAssembly(const occ::handle<StepData_StepModel>& theModel,
                                           TopoDS_Shape&                          S) const
{
  if (myStdMode)
    return STEPControl_ActorWrite::IsAssembly(theModel, S);
  return myMap.Contains(S);
}

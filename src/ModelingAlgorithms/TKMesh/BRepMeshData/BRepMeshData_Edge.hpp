#pragma once

#include <IMeshData_Edge.hpp>
#include <NCollection_IncAllocator.hpp>
#include <IMeshData_Types.hpp>

class BRepMeshData_Edge : public IMeshData_Edge
{
public:
  DEFINE_INC_ALLOC

  Standard_EXPORT BRepMeshData_Edge(const TopoDS_Edge&                           theEdge,
                                    const occ::handle<NCollection_IncAllocator>& theAllocator);

  Standard_EXPORT ~BRepMeshData_Edge() override;

  Standard_EXPORT int PCurvesNb() const override;

  Standard_EXPORT const IMeshData::IPCurveHandle& AddPCurve(
    const IMeshData::IFacePtr& theDFace,
    const TopAbs_Orientation   theOrientation) override;

  Standard_EXPORT const IMeshData::IPCurveHandle& GetPCurve(
    const IMeshData::IFacePtr& theDFace,
    const TopAbs_Orientation   theOrientation) const override;

  Standard_EXPORT const IMeshData::IPCurveHandle& GetPCurve(const int theIndex) const override;

  Standard_EXPORT const IMeshData::ListOfInteger& GetPCurves(
    const IMeshData::IFacePtr& theDFace) const override;

  DEFINE_STANDARD_RTTIEXT(BRepMeshData_Edge, IMeshData_Edge)

private:
  occ::handle<NCollection_IncAllocator>   myAllocator;
  IMeshData::VectorOfIPCurveHandles       myPCurves;
  IMeshData::DMapOfIFacePtrsListOfInteger myPCurvesMap;
};

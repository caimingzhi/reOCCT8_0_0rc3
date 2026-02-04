#pragma once


#include <IMeshData_Edge.hpp>
#include <NCollection_IncAllocator.hpp>
#include <IMeshData_Types.hpp>

//! Default implementation of edge data model entity.
class BRepMeshData_Edge : public IMeshData_Edge
{
public:
  DEFINE_INC_ALLOC

  //! Constructor.
  Standard_EXPORT BRepMeshData_Edge(const TopoDS_Edge&                           theEdge,
                                    const occ::handle<NCollection_IncAllocator>& theAllocator);

  //! Destructor.
  Standard_EXPORT ~BRepMeshData_Edge() override;

  //! Returns number of pcurves assigned to current edge.
  Standard_EXPORT int PCurvesNb() const override;

  //! Adds discrete pcurve for the specified discrete face.
  Standard_EXPORT const IMeshData::IPCurveHandle& AddPCurve(
    const IMeshData::IFacePtr& theDFace,
    const TopAbs_Orientation   theOrientation) override;

  //! Returns pcurve for the specified discrete face.
  Standard_EXPORT const IMeshData::IPCurveHandle& GetPCurve(
    const IMeshData::IFacePtr& theDFace,
    const TopAbs_Orientation   theOrientation) const override;

  //! Returns pcurve with the given index.
  Standard_EXPORT const IMeshData::IPCurveHandle& GetPCurve(const int theIndex) const override;

  //! Returns an array of pcurves indices for the specified discrete face.
  Standard_EXPORT const IMeshData::ListOfInteger& GetPCurves(
    const IMeshData::IFacePtr& theDFace) const override;

  DEFINE_STANDARD_RTTIEXT(BRepMeshData_Edge, IMeshData_Edge)

private:
  occ::handle<NCollection_IncAllocator>   myAllocator;
  IMeshData::VectorOfIPCurveHandles       myPCurves;
  IMeshData::DMapOfIFacePtrsListOfInteger myPCurvesMap;
};


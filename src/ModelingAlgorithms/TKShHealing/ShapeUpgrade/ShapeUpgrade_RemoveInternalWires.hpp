#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <NCollection_DataMap.hpp>
#include <NCollection_Sequence.hpp>
#include <Standard_Integer.hpp>
#include <ShapeUpgrade_Tool.hpp>
#include <ShapeExtend_Status.hpp>

#ifdef Status
  #undef Status
#endif

class ShapeUpgrade_RemoveInternalWires : public ShapeUpgrade_Tool
{

public:
  Standard_EXPORT ShapeUpgrade_RemoveInternalWires();

  Standard_EXPORT ShapeUpgrade_RemoveInternalWires(const TopoDS_Shape& theShape);

  Standard_EXPORT void Init(const TopoDS_Shape& theShape);

  Standard_EXPORT bool Perform();

  Standard_EXPORT bool Perform(const NCollection_Sequence<TopoDS_Shape>& theSeqShapes);

  TopoDS_Shape GetResult() const;

  double& MinArea();

  bool& RemoveFaceMode();

  const NCollection_Sequence<TopoDS_Shape>& RemovedFaces() const;

  const NCollection_Sequence<TopoDS_Shape>& RemovedWires() const;

  bool Status(const ShapeExtend_Status theStatus) const;

  DEFINE_STANDARD_RTTIEXT(ShapeUpgrade_RemoveInternalWires, ShapeUpgrade_Tool)

protected:
  Standard_EXPORT void Clear();

  int myStatus;

private:
  Standard_EXPORT void removeSmallWire(const TopoDS_Shape& theFace, const TopoDS_Shape& theWire);

  Standard_EXPORT void removeSmallFaces();

  TopoDS_Shape myShape;
  TopoDS_Shape myResult;
  double       myMinArea;
  bool         myRemoveFacesMode;
  NCollection_IndexedDataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
    myEdgeFaces;
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
                                     myRemoveEdges;
  NCollection_Sequence<TopoDS_Shape> myRemovedFaces;
  NCollection_Sequence<TopoDS_Shape> myRemoveWires;
};

#include <ShapeExtend.hpp>

inline double& ShapeUpgrade_RemoveInternalWires::MinArea()
{
  return myMinArea;
}

inline bool& ShapeUpgrade_RemoveInternalWires::RemoveFaceMode()
{
  return myRemoveFacesMode;
}

inline const NCollection_Sequence<TopoDS_Shape>& ShapeUpgrade_RemoveInternalWires::RemovedFaces()
  const
{
  return myRemovedFaces;
}

inline const NCollection_Sequence<TopoDS_Shape>& ShapeUpgrade_RemoveInternalWires::RemovedWires()
  const
{
  return myRemoveWires;
}

inline TopoDS_Shape ShapeUpgrade_RemoveInternalWires::GetResult() const
{
  return myResult;
}

inline bool ShapeUpgrade_RemoveInternalWires::Status(const ShapeExtend_Status theStatus) const
{
  return ShapeExtend::DecodeStatus(myStatus, theStatus);
}

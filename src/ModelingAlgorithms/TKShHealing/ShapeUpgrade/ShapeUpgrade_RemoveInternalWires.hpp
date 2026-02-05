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

// resolve name collisions with X11 headers
#ifdef Status
  #undef Status
#endif

//! Removes all internal wires having area less than specified min area
class ShapeUpgrade_RemoveInternalWires : public ShapeUpgrade_Tool
{

public:
  //! Creates empty constructor.
  Standard_EXPORT ShapeUpgrade_RemoveInternalWires();

  Standard_EXPORT ShapeUpgrade_RemoveInternalWires(const TopoDS_Shape& theShape);

  //! Initialize by a Shape.
  Standard_EXPORT void Init(const TopoDS_Shape& theShape);

  //! Removes all internal wires having area less than area specified as minimal allowed area
  Standard_EXPORT bool Perform();

  //! If specified sequence of shape contains -
  //! 1.wires then these wires will be removed if they have area less than allowed min area.
  //! 2.faces than internal wires from these faces will be removed if they have area less than
  //! allowed min area.
  Standard_EXPORT bool Perform(const NCollection_Sequence<TopoDS_Shape>& theSeqShapes);

  //! Get result shape
  TopoDS_Shape GetResult() const;

  //! Set min area allowed for holes( all holes having area less than mi area will be removed)
  double& MinArea();

  //! Set mode which manage removing faces which have outer wires consisting only from edges
  //! belonginig to removed internal wires.
  //! By default it is equal to true.
  bool& RemoveFaceMode();

  //! Returns sequence of removed faces.
  const NCollection_Sequence<TopoDS_Shape>& RemovedFaces() const;

  //! Returns sequence of removed faces.
  const NCollection_Sequence<TopoDS_Shape>& RemovedWires() const;

  //! Queries status of last call to Perform()
  //! : OK - nothing was done
  //! :DONE1 - internal wires were removed
  //! :DONE2 - small faces were removed.
  //! :FAIL1 - initial shape is not specified
  //! :FAIL2 - specified sub-shape is not belonged to inotial shape.
  bool Status(const ShapeExtend_Status theStatus) const;

  DEFINE_STANDARD_RTTIEXT(ShapeUpgrade_RemoveInternalWires, ShapeUpgrade_Tool)

protected:
  //! Clear all sequences and temporary map;
  Standard_EXPORT void Clear();

  int myStatus;

private:
  //! Removes internal wires having area of contour less than specified MinArea
  Standard_EXPORT void removeSmallWire(const TopoDS_Shape& theFace, const TopoDS_Shape& theWire);

  //! Removes faces having outer wire consisting
  //! from removed edges(belonging small internal wires)
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

// Copyright (c) 1999-2014 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.

#include <ShapeExtend.hpp>

//=================================================================================================

inline double& ShapeUpgrade_RemoveInternalWires::MinArea()
{
  return myMinArea;
}

//=================================================================================================

inline bool& ShapeUpgrade_RemoveInternalWires::RemoveFaceMode()
{
  return myRemoveFacesMode;
}

//=================================================================================================

inline const NCollection_Sequence<TopoDS_Shape>& ShapeUpgrade_RemoveInternalWires::RemovedFaces()
  const
{
  return myRemovedFaces;
}

//=================================================================================================

inline const NCollection_Sequence<TopoDS_Shape>& ShapeUpgrade_RemoveInternalWires::RemovedWires()
  const
{
  return myRemoveWires;
}

//=================================================================================================

inline TopoDS_Shape ShapeUpgrade_RemoveInternalWires::GetResult() const
{
  return myResult;
}

//=================================================================================================

inline bool ShapeUpgrade_RemoveInternalWires::Status(const ShapeExtend_Status theStatus) const
{
  return ShapeExtend::DecodeStatus(myStatus, theStatus);
}

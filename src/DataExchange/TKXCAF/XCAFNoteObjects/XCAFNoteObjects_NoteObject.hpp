#pragma once

#include <gp_Ax2.hpp>
#include <gp_Pnt.hpp>
#include <Standard.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>
#include <TopoDS_Shape.hpp>

class XCAFNoteObjects_NoteObject : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(XCAFNoteObjects_NoteObject, Standard_Transient)
public:
  Standard_EXPORT XCAFNoteObjects_NoteObject();

  Standard_EXPORT XCAFNoteObjects_NoteObject(const occ::handle<XCAFNoteObjects_NoteObject>& theObj);

  bool HasPlane() const { return myHasPlane; }

  const gp_Ax2& GetPlane() const { return myPlane; }

  Standard_EXPORT void SetPlane(const gp_Ax2& thePlane);

  bool HasPoint() const { return myHasPnt; }

  const gp_Pnt& GetPoint() const { return myPnt; }

  Standard_EXPORT void SetPoint(const gp_Pnt& thePnt);

  bool HasPointText() const { return myHasPntTxt; }

  const gp_Pnt& GetPointText() const { return myPntTxt; }

  Standard_EXPORT void SetPointText(const gp_Pnt& thePnt);

  const TopoDS_Shape& GetPresentation() const { return myPresentation; }

  Standard_EXPORT void SetPresentation(const TopoDS_Shape& thePresentation);

  Standard_EXPORT void Reset();

private:
  gp_Ax2       myPlane;
  gp_Pnt       myPnt;
  gp_Pnt       myPntTxt;
  TopoDS_Shape myPresentation;
  bool         myHasPlane;
  bool         myHasPnt;
  bool         myHasPntTxt;
};

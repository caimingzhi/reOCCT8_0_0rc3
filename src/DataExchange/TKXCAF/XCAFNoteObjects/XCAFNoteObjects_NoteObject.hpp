#pragma once

#include <gp_Ax2.hpp>
#include <gp_Pnt.hpp>
#include <Standard.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>
#include <TopoDS_Shape.hpp>

//! object to store note auxiliary data
class XCAFNoteObjects_NoteObject : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(XCAFNoteObjects_NoteObject, Standard_Transient)
public:
  //! Empty object
  Standard_EXPORT XCAFNoteObjects_NoteObject();

  //! Copy constructor.
  Standard_EXPORT XCAFNoteObjects_NoteObject(const occ::handle<XCAFNoteObjects_NoteObject>& theObj);

  //! Returns True if plane is specified
  bool HasPlane() const { return myHasPlane; }

  //! Returns a right-handed coordinate system of the plane
  const gp_Ax2& GetPlane() const { return myPlane; }

  //! Sets a right-handed coordinate system of the plane
  Standard_EXPORT void SetPlane(const gp_Ax2& thePlane);

  //! Returns True if the attachment point on the annotated object is specified
  bool HasPoint() const { return myHasPnt; }

  //! Returns the attachment point on the annotated object
  const gp_Pnt& GetPoint() const { return myPnt; }

  //! Sets the anchor point on the annotated object
  Standard_EXPORT void SetPoint(const gp_Pnt& thePnt);

  //! Returns True if the text position is specified
  bool HasPointText() const { return myHasPntTxt; }

  //! Returns the text position
  const gp_Pnt& GetPointText() const { return myPntTxt; }

  //! Sets the text position
  Standard_EXPORT void SetPointText(const gp_Pnt& thePnt);

  //! Returns a tessellated annotation if specified
  const TopoDS_Shape& GetPresentation() const { return myPresentation; }

  //! Sets a tessellated annotation
  Standard_EXPORT void SetPresentation(const TopoDS_Shape& thePresentation);

  //! Resets data to the state after calling the default constructor
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

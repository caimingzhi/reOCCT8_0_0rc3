

#include <XCAFNoteObjects_NoteObject.hpp>

IMPLEMENT_STANDARD_RTTIEXT(XCAFNoteObjects_NoteObject, Standard_Transient)

XCAFNoteObjects_NoteObject::XCAFNoteObjects_NoteObject()
    : myHasPlane(false),
      myHasPnt(false),
      myHasPntTxt(false)
{
}

XCAFNoteObjects_NoteObject::XCAFNoteObjects_NoteObject(
  const occ::handle<XCAFNoteObjects_NoteObject>& theObj)
    : myPlane(theObj->myPlane),
      myPnt(theObj->myPnt),
      myPntTxt(theObj->myPntTxt),
      myPresentation(theObj->myPresentation),
      myHasPlane(theObj->myHasPlane),
      myHasPnt(theObj->myHasPnt),
      myHasPntTxt(theObj->myHasPntTxt)
{
}

void XCAFNoteObjects_NoteObject::SetPlane(const gp_Ax2& thePlane)
{
  myPlane    = thePlane;
  myHasPlane = true;
}

void XCAFNoteObjects_NoteObject::SetPoint(const gp_Pnt& thePnt)
{
  myPnt    = thePnt;
  myHasPnt = true;
}

void XCAFNoteObjects_NoteObject::SetPointText(const gp_Pnt& thePnt)
{
  myPntTxt    = thePnt;
  myHasPntTxt = true;
}

void XCAFNoteObjects_NoteObject::SetPresentation(const TopoDS_Shape& thePresentation)
{
  myPresentation = thePresentation;
}

void XCAFNoteObjects_NoteObject::Reset()
{
  myHasPlane  = false;
  myHasPnt    = false;
  myHasPntTxt = false;
  myPresentation.Nullify();
}



#include <XCAFDoc_NoteBalloon.hpp>

#include <Standard_GUID.hpp>
#include <TDF_Label.hpp>

IMPLEMENT_DERIVED_ATTRIBUTE(XCAFDoc_NoteBalloon, XCAFDoc_NoteComment)

const Standard_GUID& XCAFDoc_NoteBalloon::GetID()
{
  static Standard_GUID s_ID("1127951D-87D5-4ecc-89D5-D1406576C43F");
  return s_ID;
}

occ::handle<XCAFDoc_NoteBalloon> XCAFDoc_NoteBalloon::Get(const TDF_Label& theLabel)
{
  occ::handle<XCAFDoc_NoteBalloon> aThis;
  theLabel.FindAttribute(XCAFDoc_NoteBalloon::GetID(), aThis);
  return aThis;
}

occ::handle<XCAFDoc_NoteBalloon> XCAFDoc_NoteBalloon::Set(
  const TDF_Label&                  theLabel,
  const TCollection_ExtendedString& theUserName,
  const TCollection_ExtendedString& theTimeStamp,
  const TCollection_ExtendedString& theComment)
{
  occ::handle<XCAFDoc_NoteBalloon> aNoteBalloon;
  if (!theLabel.IsNull() && !theLabel.FindAttribute(XCAFDoc_NoteBalloon::GetID(), aNoteBalloon))
  {
    aNoteBalloon = new XCAFDoc_NoteBalloon();
    aNoteBalloon->XCAFDoc_Note::Set(theUserName, theTimeStamp);
    aNoteBalloon->XCAFDoc_NoteComment::Set(theComment);
    theLabel.AddAttribute(aNoteBalloon);
  }
  return aNoteBalloon;
}

XCAFDoc_NoteBalloon::XCAFDoc_NoteBalloon() = default;

const Standard_GUID& XCAFDoc_NoteBalloon::ID() const
{
  return GetID();
}

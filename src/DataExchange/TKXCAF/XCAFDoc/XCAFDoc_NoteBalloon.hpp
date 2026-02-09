#pragma once

#include <XCAFDoc_NoteComment.hpp>

class XCAFDoc_NoteBalloon : public XCAFDoc_NoteComment
{
public:
  DEFINE_DERIVED_ATTRIBUTE(XCAFDoc_NoteBalloon, XCAFDoc_NoteComment)

  Standard_EXPORT static const Standard_GUID& GetID();

  Standard_EXPORT static occ::handle<XCAFDoc_NoteBalloon> Get(const TDF_Label& theLabel);

  Standard_EXPORT static occ::handle<XCAFDoc_NoteBalloon> Set(
    const TDF_Label&                  theLabel,
    const TCollection_ExtendedString& theUserName,
    const TCollection_ExtendedString& theTimeStamp,
    const TCollection_ExtendedString& theComment);

  Standard_EXPORT XCAFDoc_NoteBalloon();

public:
  Standard_EXPORT const Standard_GUID& ID() const override;
};

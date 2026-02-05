#pragma once

#include <XCAFDoc_NoteComment.hpp>

//! A comment note attribute.
//! Contains a textual comment.
class XCAFDoc_NoteBalloon : public XCAFDoc_NoteComment
{
public:
  DEFINE_DERIVED_ATTRIBUTE(XCAFDoc_NoteBalloon, XCAFDoc_NoteComment)

  //! Returns default attribute GUID
  Standard_EXPORT static const Standard_GUID& GetID();

  //! Finds a reference attribute on the given label and returns it, if it is found
  Standard_EXPORT static occ::handle<XCAFDoc_NoteBalloon> Get(const TDF_Label& theLabel);

  //! Create (if not exist) a comment note on the given label.
  //! \param[in]  theLabel     - note label.
  //! \param[in]  theUserName  - the name of the user, who created the note.
  //! \param[in]  theTimeStamp - creation timestamp of the note.
  //! \param[in]  theComment   - comment text.
  Standard_EXPORT static occ::handle<XCAFDoc_NoteBalloon> Set(
    const TDF_Label&                  theLabel,
    const TCollection_ExtendedString& theUserName,
    const TCollection_ExtendedString& theTimeStamp,
    const TCollection_ExtendedString& theComment);

  //! Creates an empty comment note.
  Standard_EXPORT XCAFDoc_NoteBalloon();

public:
  // Overrides TDF_Attribute virtuals
  Standard_EXPORT const Standard_GUID& ID() const override;
};

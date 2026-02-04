#pragma once


#include <XCAFDoc_Note.hpp>

//! A comment note attribute.
//! Contains a textual comment.
class XCAFDoc_NoteComment : public XCAFDoc_Note
{
public:
  DEFINE_STANDARD_RTTIEXT(XCAFDoc_NoteComment, XCAFDoc_Note)

  //! Returns default attribute GUID
  Standard_EXPORT static const Standard_GUID& GetID();

  //! Finds a reference attribute on the given label and returns it, if it is found
  Standard_EXPORT static occ::handle<XCAFDoc_NoteComment> Get(const TDF_Label& theLabel);

  //! Create (if not exist) a comment note on the given label.
  //! \param[in]  theLabel     - note label.
  //! \param[in]  theUserName  - the name of the user, who created the note.
  //! \param[in]  theTimeStamp - creation timestamp of the note.
  //! \param[in]  theComment   - comment text.
  Standard_EXPORT static occ::handle<XCAFDoc_NoteComment> Set(
    const TDF_Label&                  theLabel,
    const TCollection_ExtendedString& theUserName,
    const TCollection_ExtendedString& theTimeStamp,
    const TCollection_ExtendedString& theComment);

  //! Creates an empty comment note.
  Standard_EXPORT XCAFDoc_NoteComment();

  //! Sets the comment text.
  Standard_EXPORT void Set(const TCollection_ExtendedString& theComment);

  //! Returns the comment text.
  const TCollection_ExtendedString& Comment() const { return myComment; }

public:
  // Overrides TDF_Attribute virtuals
  Standard_EXPORT const Standard_GUID& ID() const override;
  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;
  Standard_EXPORT void              Restore(const occ::handle<TDF_Attribute>& theAttrFrom) override;
  Standard_EXPORT void              Paste(const occ::handle<TDF_Attribute>&       theAttrInto,
                                          const occ::handle<TDF_RelocationTable>& theRT) const override;
  Standard_EXPORT Standard_OStream& Dump(Standard_OStream& theOS) const override;

protected:
  TCollection_ExtendedString myComment; ///< Comment text.
};


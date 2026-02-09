#pragma once

#include <XCAFDoc_Note.hpp>

class XCAFDoc_NoteComment : public XCAFDoc_Note
{
public:
  DEFINE_STANDARD_RTTIEXT(XCAFDoc_NoteComment, XCAFDoc_Note)

  Standard_EXPORT static const Standard_GUID& GetID();

  Standard_EXPORT static occ::handle<XCAFDoc_NoteComment> Get(const TDF_Label& theLabel);

  Standard_EXPORT static occ::handle<XCAFDoc_NoteComment> Set(
    const TDF_Label&                  theLabel,
    const TCollection_ExtendedString& theUserName,
    const TCollection_ExtendedString& theTimeStamp,
    const TCollection_ExtendedString& theComment);

  Standard_EXPORT XCAFDoc_NoteComment();

  Standard_EXPORT void Set(const TCollection_ExtendedString& theComment);

  const TCollection_ExtendedString& Comment() const { return myComment; }

public:
  Standard_EXPORT const Standard_GUID& ID() const override;
  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;
  Standard_EXPORT void              Restore(const occ::handle<TDF_Attribute>& theAttrFrom) override;
  Standard_EXPORT void              Paste(const occ::handle<TDF_Attribute>&       theAttrInto,
                                          const occ::handle<TDF_RelocationTable>& theRT) const override;
  Standard_EXPORT Standard_OStream& Dump(Standard_OStream& theOS) const override;

protected:
  TCollection_ExtendedString myComment;
};

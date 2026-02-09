#pragma once

#include <Standard.hpp>
#include <TCollection_ExtendedString.hpp>
#include <TDF_DerivedAttribute.hpp>
#include <TDF_Label.hpp>
#include <NCollection_Sequence.hpp>
#include <XCAFNoteObjects_NoteObject.hpp>

class TDF_RelocationTable;

class XCAFDoc_Note : public TDF_Attribute
{
public:
  DEFINE_STANDARD_RTTIEXT(XCAFDoc_Note, TDF_Attribute)

  Standard_EXPORT static bool IsMine(const TDF_Label& theLabel);

  Standard_EXPORT static occ::handle<XCAFDoc_Note> Get(const TDF_Label& theLabel);

  Standard_EXPORT void Set(const TCollection_ExtendedString& theUserName,
                           const TCollection_ExtendedString& theTimeStamp);

  const TCollection_ExtendedString& UserName() const { return myUserName; }

  const TCollection_ExtendedString& TimeStamp() const { return myTimeStamp; }

  Standard_EXPORT bool IsOrphan() const;

  Standard_EXPORT occ::handle<XCAFNoteObjects_NoteObject> GetObject() const;

  Standard_EXPORT void SetObject(const occ::handle<XCAFNoteObjects_NoteObject>& theObject);

public:
  Standard_EXPORT void              Restore(const occ::handle<TDF_Attribute>& theAttrFrom) override;
  Standard_EXPORT void              Paste(const occ::handle<TDF_Attribute>&       theAttrInto,
                                          const occ::handle<TDF_RelocationTable>& theRT) const override;
  Standard_EXPORT Standard_OStream& Dump(Standard_OStream& theOS) const override;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

protected:
  Standard_EXPORT XCAFDoc_Note();

private:
  TCollection_ExtendedString myUserName;
  TCollection_ExtendedString myTimeStamp;
};

#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TDF_Attribute.hpp>
#include <Standard_OStream.hpp>
class TDocStd_Document;
class Standard_GUID;
class TDF_Data;
class TDF_RelocationTable;

//! This attribute located at the root label of the
//! framework contains a back reference to the owner
//! TDocStd_Document, providing access to the document
//! from any label. private class Owner;
class TDocStd_Owner : public TDF_Attribute
{

public:
  //! class methods
  //! =============
  Standard_EXPORT static const Standard_GUID& GetID();

  Standard_EXPORT static void SetDocument(const occ::handle<TDF_Data>&         indata,
                                          const occ::handle<TDocStd_Document>& doc);

  Standard_EXPORT static void SetDocument(const occ::handle<TDF_Data>& indata,
                                          TDocStd_Document*            doc);

  //! Owner methods
  //! ===============
  Standard_EXPORT static occ::handle<TDocStd_Document> GetDocument(
    const occ::handle<TDF_Data>& ofdata);

  Standard_EXPORT TDocStd_Owner();

  Standard_EXPORT void SetDocument(const occ::handle<TDocStd_Document>& document);

  Standard_EXPORT void SetDocument(TDocStd_Document* document);

  Standard_EXPORT occ::handle<TDocStd_Document> GetDocument() const;

  Standard_EXPORT const Standard_GUID& ID() const override;

  Standard_EXPORT void Restore(const occ::handle<TDF_Attribute>& With) override;

  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;

  Standard_EXPORT void Paste(const occ::handle<TDF_Attribute>&       Into,
                             const occ::handle<TDF_RelocationTable>& RT) const override;

  Standard_EXPORT Standard_OStream& Dump(Standard_OStream& anOS) const override;

  //! Dumps the content of me into the stream
  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_STANDARD_RTTIEXT(TDocStd_Owner, TDF_Attribute)

private:
  //! It keeps pointer to the document to avoid handles cyclic dependency
  TDocStd_Document* myDocument;
};

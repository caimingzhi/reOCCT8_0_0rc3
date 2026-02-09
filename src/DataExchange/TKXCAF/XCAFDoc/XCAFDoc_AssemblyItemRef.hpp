#pragma once

#include <Standard.hpp>
#include <TDF_Attribute.hpp>
#include <XCAFDoc_AssemblyItemId.hpp>

class TDF_RelocationTable;

class XCAFDoc_AssemblyItemRef : public TDF_Attribute
{

public:
  DEFINE_STANDARD_RTTIEXT(XCAFDoc_AssemblyItemRef, TDF_Attribute)

  Standard_EXPORT static const Standard_GUID& GetID();

  Standard_EXPORT static occ::handle<XCAFDoc_AssemblyItemRef> Get(const TDF_Label& theLabel);

  Standard_EXPORT static occ::handle<XCAFDoc_AssemblyItemRef> Set(
    const TDF_Label&              theLabel,
    const XCAFDoc_AssemblyItemId& theItemId);

  Standard_EXPORT static occ::handle<XCAFDoc_AssemblyItemRef> Set(
    const TDF_Label&              theLabel,
    const XCAFDoc_AssemblyItemId& theItemId,
    const Standard_GUID&          theGUID);

  Standard_EXPORT static occ::handle<XCAFDoc_AssemblyItemRef> Set(
    const TDF_Label&              theLabel,
    const XCAFDoc_AssemblyItemId& theItemId,
    const int                     theShapeIndex);

  Standard_EXPORT XCAFDoc_AssemblyItemRef();

  Standard_EXPORT bool IsOrphan() const;

  Standard_EXPORT bool HasExtraRef() const;

  Standard_EXPORT bool IsGUID() const;

  Standard_EXPORT bool IsSubshapeIndex() const;

  Standard_EXPORT Standard_GUID GetGUID() const;

  Standard_EXPORT int GetSubshapeIndex() const;

  Standard_EXPORT const XCAFDoc_AssemblyItemId& GetItem() const;

  Standard_EXPORT void SetItem(const XCAFDoc_AssemblyItemId& theItemId);

  Standard_EXPORT void SetItem(const NCollection_List<TCollection_AsciiString>& thePath);

  Standard_EXPORT void SetItem(const TCollection_AsciiString& theString);

  Standard_EXPORT void SetGUID(const Standard_GUID& theAttrGUID);

  Standard_EXPORT void SetSubshapeIndex(int theShapeIndex);

  Standard_EXPORT void ClearExtraRef();

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

public:
  Standard_EXPORT const Standard_GUID& ID() const override;
  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;
  Standard_EXPORT void              Restore(const occ::handle<TDF_Attribute>& theAttrFrom) override;
  Standard_EXPORT void              Paste(const occ::handle<TDF_Attribute>&       theAttrInto,
                                          const occ::handle<TDF_RelocationTable>& theRT) const override;
  Standard_EXPORT Standard_OStream& Dump(Standard_OStream& theOS) const override;

private:
  XCAFDoc_AssemblyItemId  myItemId;
  int                     myExtraRef;
  TCollection_AsciiString myExtraId;
};

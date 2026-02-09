#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Transient.hpp>
#include <IGESData_IGESEntity.hpp>
class TCollection_HAsciiString;
class IGESDefs_HArray1OfHArray1OfTextDisplayTemplate;
class IGESGraph_TextDisplayTemplate;
class Standard_Transient;

class IGESDefs_AttributeDef : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESDefs_AttributeDef();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&                             aName,
    const int                                                                aListType,
    const occ::handle<NCollection_HArray1<int>>&                             attrTypes,
    const occ::handle<NCollection_HArray1<int>>&                             attrValueDataTypes,
    const occ::handle<NCollection_HArray1<int>>&                             attrValueCounts,
    const occ::handle<NCollection_HArray1<occ::handle<Standard_Transient>>>& attrValues,
    const occ::handle<IGESDefs_HArray1OfHArray1OfTextDisplayTemplate>&       attrValuePointers);

  Standard_EXPORT bool HasTableName() const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> TableName() const;

  Standard_EXPORT int ListType() const;

  Standard_EXPORT int NbAttributes() const;

  Standard_EXPORT int AttributeType(const int num) const;

  Standard_EXPORT int AttributeValueDataType(const int num) const;

  Standard_EXPORT int AttributeValueCount(const int num) const;

  Standard_EXPORT bool HasValues() const;

  Standard_EXPORT bool HasTextDisplay() const;

  Standard_EXPORT occ::handle<IGESGraph_TextDisplayTemplate> AttributeTextDisplay(
    const int AttrNum,
    const int PointerNum) const;

  Standard_EXPORT occ::handle<Standard_Transient> AttributeList(const int AttrNum) const;

  Standard_EXPORT int AttributeAsInteger(const int AttrNum, const int ValueNum) const;

  Standard_EXPORT double AttributeAsReal(const int AttrNum, const int ValueNum) const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> AttributeAsString(const int AttrNum,
                                                                          const int ValueNum) const;

  Standard_EXPORT occ::handle<IGESData_IGESEntity> AttributeAsEntity(const int AttrNum,
                                                                     const int ValueNum) const;

  Standard_EXPORT bool AttributeAsLogical(const int AttrNum, const int ValueNum) const;

  DEFINE_STANDARD_RTTIEXT(IGESDefs_AttributeDef, IGESData_IGESEntity)

private:
  occ::handle<TCollection_HAsciiString>                             theName;
  int                                                               theListType;
  occ::handle<NCollection_HArray1<int>>                             theAttrTypes;
  occ::handle<NCollection_HArray1<int>>                             theAttrValueDataTypes;
  occ::handle<NCollection_HArray1<int>>                             theAttrValueCounts;
  occ::handle<NCollection_HArray1<occ::handle<Standard_Transient>>> theAttrValues;
  occ::handle<IGESDefs_HArray1OfHArray1OfTextDisplayTemplate>       theAttrValuePointers;
};

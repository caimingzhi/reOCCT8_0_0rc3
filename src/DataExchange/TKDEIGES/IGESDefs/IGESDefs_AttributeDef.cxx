#include <IGESData_IGESEntity.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <IGESDefs_AttributeDef.hpp>
#include <IGESDefs_HArray1OfHArray1OfTextDisplayTemplate.hpp>
#include <IGESGraph_TextDisplayTemplate.hpp>
#include <TCollection_HAsciiString.hpp>
#include <MoniTool_Macros.hpp>
#include <Standard_DimensionMismatch.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>
#include <Standard_Integer.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESDefs_AttributeDef, IGESData_IGESEntity)

IGESDefs_AttributeDef::IGESDefs_AttributeDef() = default;

void IGESDefs_AttributeDef::Init(
  const occ::handle<TCollection_HAsciiString>&                             aName,
  const int                                                                aListType,
  const occ::handle<NCollection_HArray1<int>>&                             attrTypes,
  const occ::handle<NCollection_HArray1<int>>&                             attrValueDataTypes,
  const occ::handle<NCollection_HArray1<int>>&                             attrValueCounts,
  const occ::handle<NCollection_HArray1<occ::handle<Standard_Transient>>>& attrValues,
  const occ::handle<IGESDefs_HArray1OfHArray1OfTextDisplayTemplate>&       attrValuePointers)
{
  int nb = attrTypes->Length();
  if (attrTypes->Lower() != 1 || attrValueDataTypes->Lower() != 1
      || attrValueDataTypes->Length() != nb || attrValueCounts->Lower() != 1
      || attrValueCounts->Length() != nb)
    throw Standard_DimensionMismatch("IGESDefs_AttributeDef : Init");

  if (FormNumber() >= 1)
    if (attrValues->Lower() != 1 || attrValues->Length() != nb)
      throw Standard_DimensionMismatch("IGESDefs_AttributeDef : Init");

  if (FormNumber() == 2)
    if (attrValuePointers->Lower() != 1 || attrValuePointers->Length() != nb)
      throw Standard_DimensionMismatch("IGESDefs_AttributeDef : Init");

  theName               = aName;
  theListType           = aListType;
  theAttrTypes          = attrTypes;
  theAttrValueDataTypes = attrValueDataTypes;
  theAttrValueCounts    = attrValueCounts;
  theAttrValues         = attrValues;
  theAttrValuePointers  = attrValuePointers;
  if (attrValues.IsNull())
    InitTypeAndForm(322, 0);
  else if (attrValuePointers.IsNull())
    InitTypeAndForm(322, 1);
  else
    InitTypeAndForm(322, 2);
}

bool IGESDefs_AttributeDef::HasTableName() const
{
  return (!theName.IsNull());
}

occ::handle<TCollection_HAsciiString> IGESDefs_AttributeDef::TableName() const
{
  return theName;
}

int IGESDefs_AttributeDef::ListType() const
{
  return theListType;
}

int IGESDefs_AttributeDef::NbAttributes() const
{
  return theAttrTypes->Length();
}

int IGESDefs_AttributeDef::AttributeType(const int num) const
{
  return theAttrTypes->Value(num);
}

int IGESDefs_AttributeDef::AttributeValueDataType(const int num) const
{
  return theAttrValueDataTypes->Value(num);
}

int IGESDefs_AttributeDef::AttributeValueCount(const int num) const
{
  return theAttrValueCounts->Value(num);
}

bool IGESDefs_AttributeDef::HasValues() const
{
  return (!theAttrValues.IsNull());
}

bool IGESDefs_AttributeDef::HasTextDisplay() const
{
  return (!theAttrValuePointers.IsNull());
}

occ::handle<IGESGraph_TextDisplayTemplate> IGESDefs_AttributeDef::AttributeTextDisplay(
  const int AttrNum,
  const int PointerNum) const
{
  occ::handle<IGESGraph_TextDisplayTemplate> res;
  if (HasTextDisplay())
    res = theAttrValuePointers->Value(AttrNum)->Value(PointerNum);
  return res;
}

occ::handle<Standard_Transient> IGESDefs_AttributeDef::AttributeList(const int AttrNum) const
{
  occ::handle<Standard_Transient> nulres;
  if (!HasValues())
    return nulres;
  return theAttrValues->Value(AttrNum);
}

int IGESDefs_AttributeDef::AttributeAsInteger(const int AttrNum, const int ValueNum) const
{
  return GetCasted(NCollection_HArray1<int>, theAttrValues->Value(AttrNum))->Value(ValueNum);
}

double IGESDefs_AttributeDef::AttributeAsReal(const int AttrNum, const int ValueNum) const
{
  return GetCasted(NCollection_HArray1<double>, theAttrValues->Value(AttrNum))->Value(ValueNum);
}

occ::handle<TCollection_HAsciiString> IGESDefs_AttributeDef::AttributeAsString(
  const int AttrNum,
  const int ValueNum) const
{
  return GetCasted(NCollection_HArray1<occ::handle<TCollection_HAsciiString>>,
                   theAttrValues->Value(AttrNum))
    ->Value(ValueNum);
}

occ::handle<IGESData_IGESEntity> IGESDefs_AttributeDef::AttributeAsEntity(const int AttrNum,
                                                                          const int ValueNum) const
{
  return GetCasted(NCollection_HArray1<occ::handle<IGESData_IGESEntity>>,
                   theAttrValues->Value(AttrNum))
    ->Value(ValueNum);
}

bool IGESDefs_AttributeDef::AttributeAsLogical(const int AttrNum, const int ValueNum) const
{
  return (GetCasted(NCollection_HArray1<int>, theAttrValues->Value(AttrNum))->Value(ValueNum) != 0);
}

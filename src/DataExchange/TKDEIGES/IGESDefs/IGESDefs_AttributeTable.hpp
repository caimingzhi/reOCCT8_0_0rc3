#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
#include <NCollection_Array2.hpp>
#include <NCollection_HArray2.hpp>
#include <IGESData_IGESEntity.hpp>
#include <Standard_Integer.hpp>
class IGESDefs_AttributeDef;
class Standard_Transient;
class TCollection_HAsciiString;

class IGESDefs_AttributeTable : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESDefs_AttributeTable();

  Standard_EXPORT void Init(
    const occ::handle<NCollection_HArray2<occ::handle<Standard_Transient>>>& attributes);

  Standard_EXPORT void SetDefinition(const occ::handle<IGESDefs_AttributeDef>& def);

  Standard_EXPORT occ::handle<IGESDefs_AttributeDef> Definition() const;

  Standard_EXPORT int NbRows() const;

  Standard_EXPORT int NbAttributes() const;

  Standard_EXPORT int DataType(const int Atnum) const;

  Standard_EXPORT int ValueCount(const int Atnum) const;

  Standard_EXPORT occ::handle<Standard_Transient> AttributeList(const int Attribnum,
                                                                const int Rownum) const;

  Standard_EXPORT int AttributeAsInteger(const int AtNum, const int Rownum, const int ValNum) const;

  Standard_EXPORT double AttributeAsReal(const int AtNum, const int Rownum, const int ValNum) const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> AttributeAsString(const int AtNum,
                                                                          const int Rownum,
                                                                          const int ValNum) const;

  Standard_EXPORT occ::handle<IGESData_IGESEntity> AttributeAsEntity(const int AtNum,
                                                                     const int Rownum,
                                                                     const int ValNum) const;

  Standard_EXPORT bool AttributeAsLogical(const int AtNum,
                                          const int Rownum,
                                          const int ValNum) const;

  DEFINE_STANDARD_RTTIEXT(IGESDefs_AttributeTable, IGESData_IGESEntity)

private:
  occ::handle<NCollection_HArray2<occ::handle<Standard_Transient>>> theAttributes;
};

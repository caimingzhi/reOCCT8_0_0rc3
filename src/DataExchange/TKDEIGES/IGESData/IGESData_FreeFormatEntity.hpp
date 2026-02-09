#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <IGESData_UndefinedEntity.hpp>
#include <Interface_ParamType.hpp>
#include <IGESData_IGESEntity.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
class IGESData_IGESEntity;
class TCollection_HAsciiString;
class IGESData_IGESWriter;

class IGESData_FreeFormatEntity : public IGESData_UndefinedEntity
{

public:
  Standard_EXPORT IGESData_FreeFormatEntity();

  Standard_EXPORT void SetTypeNumber(const int typenum);

  Standard_EXPORT void SetFormNumber(const int formnum);

  Standard_EXPORT int NbParams() const;

  Standard_EXPORT bool ParamData(const int                              num,
                                 Interface_ParamType&                   ptype,
                                 occ::handle<IGESData_IGESEntity>&      ent,
                                 occ::handle<TCollection_HAsciiString>& val) const;

  Standard_EXPORT Interface_ParamType ParamType(const int num) const;

  Standard_EXPORT bool IsParamEntity(const int num) const;

  Standard_EXPORT occ::handle<IGESData_IGESEntity> ParamEntity(const int num) const;

  Standard_EXPORT bool IsNegativePointer(const int num) const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> ParamValue(const int num) const;

  Standard_EXPORT occ::handle<NCollection_HSequence<int>> NegativePointers() const;

  Standard_EXPORT void AddLiteral(const Interface_ParamType                    ptype,
                                  const occ::handle<TCollection_HAsciiString>& val);

  Standard_EXPORT void AddLiteral(const Interface_ParamType ptype, const char* val);

  Standard_EXPORT void AddEntity(const Interface_ParamType               ptype,
                                 const occ::handle<IGESData_IGESEntity>& ent,
                                 const bool                              negative = false);

  Standard_EXPORT void AddEntities(
    const occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>& ents);

  Standard_EXPORT void AddNegativePointers(const occ::handle<NCollection_HSequence<int>>& list);

  Standard_EXPORT void ClearNegativePointers();

  Standard_EXPORT void WriteOwnParams(IGESData_IGESWriter& IW) const override;

  DEFINE_STANDARD_RTTIEXT(IGESData_FreeFormatEntity, IGESData_UndefinedEntity)

private:
  occ::handle<NCollection_HSequence<int>> thenegptrs;
};

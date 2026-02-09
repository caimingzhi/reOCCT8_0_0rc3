#pragma once

#include <Standard.hpp>

#include <IGESData_IGESEntity.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;

class IGESBasic_Group : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESBasic_Group();

  Standard_EXPORT IGESBasic_Group(const int nb);

  Standard_EXPORT void Init(
    const occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>& allEntities);

  Standard_EXPORT void SetOrdered(const bool mode);

  Standard_EXPORT void SetWithoutBackP(const bool mode);

  Standard_EXPORT bool IsOrdered() const;

  Standard_EXPORT bool IsWithoutBackP() const;

  Standard_EXPORT void SetUser(const int type, const int form);

  Standard_EXPORT void SetNb(const int nb);

  Standard_EXPORT int NbEntities() const;

  Standard_EXPORT occ::handle<IGESData_IGESEntity> Entity(const int Index) const;

  Standard_EXPORT occ::handle<Standard_Transient> Value(const int Index) const;

  Standard_EXPORT void SetValue(const int Index, const occ::handle<IGESData_IGESEntity>& ent);

  DEFINE_STANDARD_RTTIEXT(IGESBasic_Group, IGESData_IGESEntity)

private:
  occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>> theEntities;
};

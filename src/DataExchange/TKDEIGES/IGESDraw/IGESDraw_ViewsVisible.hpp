#pragma once

#include <Standard.hpp>

#include <IGESData_ViewKindEntity.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <IGESData_IGESEntity.hpp>
#include <Standard_Integer.hpp>
class IGESData_IGESEntity;

class IGESDraw_ViewsVisible : public IGESData_ViewKindEntity
{

public:
  Standard_EXPORT IGESDraw_ViewsVisible();

  Standard_EXPORT void Init(
    const occ::handle<NCollection_HArray1<occ::handle<IGESData_ViewKindEntity>>>& allViewEntities,
    const occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>&     allDisplayEntity);

  Standard_EXPORT void InitImplied(
    const occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>& allDisplayEntity);

  Standard_EXPORT bool IsSingle() const override;

  Standard_EXPORT int NbViews() const override;

  Standard_EXPORT int NbDisplayedEntities() const;

  Standard_EXPORT occ::handle<IGESData_ViewKindEntity> ViewItem(const int Index) const override;

  Standard_EXPORT occ::handle<IGESData_IGESEntity> DisplayedEntity(const int Index) const;

  DEFINE_STANDARD_RTTIEXT(IGESDraw_ViewsVisible, IGESData_ViewKindEntity)

private:
  occ::handle<NCollection_HArray1<occ::handle<IGESData_ViewKindEntity>>> theViewEntities;
  occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>     theDisplayEntity;
};

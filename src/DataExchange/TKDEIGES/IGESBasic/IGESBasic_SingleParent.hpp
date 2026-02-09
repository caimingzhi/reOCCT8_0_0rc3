#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <IGESData_IGESEntity.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <IGESData_SingleParentEntity.hpp>
class IGESData_IGESEntity;

class IGESBasic_SingleParent : public IGESData_SingleParentEntity
{

public:
  Standard_EXPORT IGESBasic_SingleParent();

  Standard_EXPORT void Init(
    const int                                                                 nbParentEntities,
    const occ::handle<IGESData_IGESEntity>&                                   aParentEntity,
    const occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>& allChildren);

  Standard_EXPORT int NbParentEntities() const;

  Standard_EXPORT occ::handle<IGESData_IGESEntity> SingleParent() const override;

  Standard_EXPORT int NbChildren() const override;

  Standard_EXPORT occ::handle<IGESData_IGESEntity> Child(const int Index) const override;

  DEFINE_STANDARD_RTTIEXT(IGESBasic_SingleParent, IGESData_SingleParentEntity)

private:
  int                                                                theNbParentEntities;
  occ::handle<IGESData_IGESEntity>                                   theParentEntity;
  occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>> theChildren;
};

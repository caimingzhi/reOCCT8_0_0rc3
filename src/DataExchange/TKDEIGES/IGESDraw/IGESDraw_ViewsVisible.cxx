#include <IGESDraw_ViewsVisible.hpp>
#include <Standard_DimensionMismatch.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESDraw_ViewsVisible, IGESData_ViewKindEntity)

IGESDraw_ViewsVisible::IGESDraw_ViewsVisible() = default;

void IGESDraw_ViewsVisible::Init(
  const occ::handle<NCollection_HArray1<occ::handle<IGESData_ViewKindEntity>>>& allViewEntities,
  const occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>&     allDisplayEntity)
{
  if (!allDisplayEntity.IsNull())
    if (allDisplayEntity->Lower() != 1)
      throw Standard_DimensionMismatch("IGESDraw_ViewsVisible : Init");
  if (!allViewEntities.IsNull())
    if (allViewEntities->Lower() != 1)
      throw Standard_DimensionMismatch("IGESDraw_ViewsVisible : Init");
  theViewEntities  = allViewEntities;
  theDisplayEntity = allDisplayEntity;
  InitTypeAndForm(402, 3);
}

void IGESDraw_ViewsVisible::InitImplied(
  const occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>& allDisplayEntity)
{
  if (!allDisplayEntity.IsNull())
    if (allDisplayEntity->Lower() != 1)
      throw Standard_DimensionMismatch("IGESDraw_ViewsVisible : InitImplied");
  theDisplayEntity = allDisplayEntity;
}

bool IGESDraw_ViewsVisible::IsSingle() const
{
  return false;
}

int IGESDraw_ViewsVisible::NbViews() const
{
  return (theViewEntities.IsNull() ? 0 : theViewEntities->Length());
}

int IGESDraw_ViewsVisible::NbDisplayedEntities() const
{
  return (theDisplayEntity.IsNull() ? 0 : theDisplayEntity->Length());
}

occ::handle<IGESData_ViewKindEntity> IGESDraw_ViewsVisible::ViewItem(const int Index) const
{
  return theViewEntities->Value(Index);
}

occ::handle<IGESData_IGESEntity> IGESDraw_ViewsVisible::DisplayedEntity(const int Index) const
{
  return theDisplayEntity->Value(Index);
}

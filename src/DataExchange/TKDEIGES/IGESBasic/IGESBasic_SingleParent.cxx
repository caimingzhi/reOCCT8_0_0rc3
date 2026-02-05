#include <IGESBasic_SingleParent.hpp>
#include <IGESData_IGESEntity.hpp>
#include <Standard_DimensionMismatch.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESBasic_SingleParent, IGESData_SingleParentEntity)

IGESBasic_SingleParent::IGESBasic_SingleParent() = default;

void IGESBasic_SingleParent::Init(
  const int                                                                 nbParentEntities,
  const occ::handle<IGESData_IGESEntity>&                                   aParentEntity,
  const occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>& allChildren)
{
  if (!allChildren.IsNull() && allChildren->Lower() != 1)
    throw Standard_DimensionMismatch("IGESBasic_SingleParent : Init");
  theParentEntity     = aParentEntity;
  theChildren         = allChildren;
  theNbParentEntities = nbParentEntities;
  InitTypeAndForm(402, 9);
}

int IGESBasic_SingleParent::NbChildren() const
{
  return (theChildren.IsNull() ? 0 : theChildren->Length());
}

occ::handle<IGESData_IGESEntity> IGESBasic_SingleParent::Child(const int Index) const
{
  return theChildren->Value(Index);
}

int IGESBasic_SingleParent::NbParentEntities() const
{
  return theNbParentEntities;
}

occ::handle<IGESData_IGESEntity> IGESBasic_SingleParent::SingleParent() const
{
  return theParentEntity;
}

#include <IGESBasic_SubfigureDef.hpp>
#include <IGESData_IGESEntity.hpp>
#include <Standard_DimensionMismatch.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESBasic_SubfigureDef, IGESData_IGESEntity)

IGESBasic_SubfigureDef::IGESBasic_SubfigureDef() = default;

void IGESBasic_SubfigureDef::Init(
  const int                                                                 aDepth,
  const occ::handle<TCollection_HAsciiString>&                              aName,
  const occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>& allAssocEntities)
{
  if (!allAssocEntities.IsNull() && allAssocEntities->Lower() != 1)
    throw Standard_DimensionMismatch("IGESBasic_SubfigureDef : Init");
  theDepth         = aDepth;
  theName          = aName;
  theAssocEntities = allAssocEntities;
  InitTypeAndForm(308, 0);
}

int IGESBasic_SubfigureDef::Depth() const
{
  return theDepth;
}

occ::handle<TCollection_HAsciiString> IGESBasic_SubfigureDef::Name() const
{
  return theName;
}

int IGESBasic_SubfigureDef::NbEntities() const
{
  return (theAssocEntities.IsNull() ? 0 : theAssocEntities->Length());
}

occ::handle<IGESData_IGESEntity> IGESBasic_SubfigureDef::AssociatedEntity(const int Index) const
{
  return theAssocEntities->Value(Index);
}

occ::handle<Standard_Transient> IGESBasic_SubfigureDef::Value(const int Index) const
{
  return occ::handle<Standard_Transient>(theAssocEntities->Value(Index));
}

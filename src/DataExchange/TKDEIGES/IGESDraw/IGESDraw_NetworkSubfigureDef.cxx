#include <IGESDraw_NetworkSubfigureDef.hpp>
#include <IGESGraph_TextDisplayTemplate.hpp>
#include <Standard_DimensionMismatch.hpp>
#include <Standard_Type.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESDraw_NetworkSubfigureDef, IGESData_IGESEntity)

IGESDraw_NetworkSubfigureDef::IGESDraw_NetworkSubfigureDef() = default;

void IGESDraw_NetworkSubfigureDef::Init(
  const int                                                                   aDepth,
  const occ::handle<TCollection_HAsciiString>&                                aName,
  const occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>&   allEntities,
  const int                                                                   aTypeFlag,
  const occ::handle<TCollection_HAsciiString>&                                aDesignator,
  const occ::handle<IGESGraph_TextDisplayTemplate>&                           aTemplate,
  const occ::handle<NCollection_HArray1<occ::handle<IGESDraw_ConnectPoint>>>& allPointEntities)
{
  if (!allPointEntities.IsNull())
    if (allPointEntities->Lower() != 1 || allEntities->Lower() != 1)
      throw Standard_DimensionMismatch("IGESDraw_NetworkSubfigureDef : Init");
  theDepth              = aDepth;
  theName               = aName;
  theEntities           = allEntities;
  theTypeFlag           = aTypeFlag;
  theDesignator         = aDesignator;
  theDesignatorTemplate = aTemplate;
  thePointEntities      = allPointEntities;
  InitTypeAndForm(320, 0);
}

int IGESDraw_NetworkSubfigureDef::Depth() const
{
  return theDepth;
}

occ::handle<TCollection_HAsciiString> IGESDraw_NetworkSubfigureDef::Name() const
{
  return theName;
}

int IGESDraw_NetworkSubfigureDef::NbEntities() const
{
  return theEntities->Length();
}

occ::handle<IGESData_IGESEntity> IGESDraw_NetworkSubfigureDef::Entity(const int Index) const
{
  return theEntities->Value(Index);
  // if Index is out of bound HArray1 will raise OutOfRange exception
}

int IGESDraw_NetworkSubfigureDef::TypeFlag() const
{
  return theTypeFlag;
}

occ::handle<TCollection_HAsciiString> IGESDraw_NetworkSubfigureDef::Designator() const
{
  return theDesignator;
}

bool IGESDraw_NetworkSubfigureDef::HasDesignatorTemplate() const
{
  return (!theDesignatorTemplate.IsNull());
}

occ::handle<IGESGraph_TextDisplayTemplate> IGESDraw_NetworkSubfigureDef::DesignatorTemplate() const
{
  return theDesignatorTemplate;
}

int IGESDraw_NetworkSubfigureDef::NbPointEntities() const
{
  return (thePointEntities.IsNull() ? 0 : thePointEntities->Length());
}

bool IGESDraw_NetworkSubfigureDef::HasPointEntity(const int Index) const
{
  if (thePointEntities.IsNull())
    return false;
  return (!thePointEntities->Value(Index).IsNull());
  // if Index is out of bound HArray1 will raise OutOfRange exception
}

occ::handle<IGESDraw_ConnectPoint> IGESDraw_NetworkSubfigureDef::PointEntity(const int Index) const
{
  return thePointEntities->Value(Index);
  // if Index is out of bound HArray1 will raise OutOfRange exception
}

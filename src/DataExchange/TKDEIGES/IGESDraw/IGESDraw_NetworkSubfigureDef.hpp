#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <IGESData_IGESEntity.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <IGESDraw_ConnectPoint.hpp>
class TCollection_HAsciiString;
class IGESGraph_TextDisplayTemplate;
class IGESDraw_ConnectPoint;

class IGESDraw_NetworkSubfigureDef : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESDraw_NetworkSubfigureDef();

  Standard_EXPORT void Init(
    const int                                                                   aDepth,
    const occ::handle<TCollection_HAsciiString>&                                aName,
    const occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>&   allEntities,
    const int                                                                   aTypeFlag,
    const occ::handle<TCollection_HAsciiString>&                                aDesignator,
    const occ::handle<IGESGraph_TextDisplayTemplate>&                           aTemplate,
    const occ::handle<NCollection_HArray1<occ::handle<IGESDraw_ConnectPoint>>>& allPointEntities);

  Standard_EXPORT int Depth() const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Name() const;

  Standard_EXPORT int NbEntities() const;

  Standard_EXPORT occ::handle<IGESData_IGESEntity> Entity(const int Index) const;

  Standard_EXPORT int TypeFlag() const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Designator() const;

  Standard_EXPORT bool HasDesignatorTemplate() const;

  Standard_EXPORT occ::handle<IGESGraph_TextDisplayTemplate> DesignatorTemplate() const;

  Standard_EXPORT int NbPointEntities() const;

  Standard_EXPORT bool HasPointEntity(const int Index) const;

  Standard_EXPORT occ::handle<IGESDraw_ConnectPoint> PointEntity(const int Index) const;

  DEFINE_STANDARD_RTTIEXT(IGESDraw_NetworkSubfigureDef, IGESData_IGESEntity)

private:
  int                                                                  theDepth;
  occ::handle<TCollection_HAsciiString>                                theName;
  occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>   theEntities;
  int                                                                  theTypeFlag;
  occ::handle<TCollection_HAsciiString>                                theDesignator;
  occ::handle<IGESGraph_TextDisplayTemplate>                           theDesignatorTemplate;
  occ::handle<NCollection_HArray1<occ::handle<IGESDraw_ConnectPoint>>> thePointEntities;
};

#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <IGESData_IGESEntity.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
class TCollection_HAsciiString;
class Standard_Transient;

class IGESBasic_SubfigureDef : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESBasic_SubfigureDef();

  Standard_EXPORT void Init(
    const int                                                                 aDepth,
    const occ::handle<TCollection_HAsciiString>&                              aName,
    const occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>& allAssocEntities);

  Standard_EXPORT int Depth() const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Name() const;

  Standard_EXPORT int NbEntities() const;

  Standard_EXPORT occ::handle<IGESData_IGESEntity> AssociatedEntity(const int Index) const;

  Standard_EXPORT occ::handle<Standard_Transient> Value(const int Index) const;

  DEFINE_STANDARD_RTTIEXT(IGESBasic_SubfigureDef, IGESData_IGESEntity)

private:
  int                                                                theDepth;
  occ::handle<TCollection_HAsciiString>                              theName;
  occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>> theAssocEntities;
};

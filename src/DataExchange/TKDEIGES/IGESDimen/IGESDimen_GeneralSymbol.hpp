#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IGESData_IGESEntity.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <IGESDimen_LeaderArrow.hpp>
#include <Standard_Integer.hpp>
class IGESDimen_GeneralNote;
class IGESDimen_LeaderArrow;

class IGESDimen_GeneralSymbol : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESDimen_GeneralSymbol();

  Standard_EXPORT void Init(
    const occ::handle<IGESDimen_GeneralNote>&                                   aNote,
    const occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>&   allGeoms,
    const occ::handle<NCollection_HArray1<occ::handle<IGESDimen_LeaderArrow>>>& allLeaders);

  Standard_EXPORT void SetFormNumber(const int form);

  Standard_EXPORT bool HasNote() const;

  Standard_EXPORT occ::handle<IGESDimen_GeneralNote> Note() const;

  Standard_EXPORT int NbGeomEntities() const;

  Standard_EXPORT occ::handle<IGESData_IGESEntity> GeomEntity(const int Index) const;

  Standard_EXPORT int NbLeaders() const;

  Standard_EXPORT occ::handle<IGESDimen_LeaderArrow> LeaderArrow(const int Index) const;

  DEFINE_STANDARD_RTTIEXT(IGESDimen_GeneralSymbol, IGESData_IGESEntity)

private:
  occ::handle<IGESDimen_GeneralNote>                                   theNote;
  occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>   theGeoms;
  occ::handle<NCollection_HArray1<occ::handle<IGESDimen_LeaderArrow>>> theLeaders;
};

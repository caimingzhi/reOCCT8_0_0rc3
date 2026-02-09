#pragma once

#include <Standard.hpp>

#include <IGESData_ViewKindEntity.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Integer.hpp>
#include <IGESData_LineFontEntity.hpp>
#include <IGESGraph_Color.hpp>
#include <IGESData_IGESEntity.hpp>
class IGESData_LineFontEntity;
class IGESGraph_Color;
class IGESData_IGESEntity;

class IGESDraw_ViewsVisibleWithAttr : public IGESData_ViewKindEntity
{

public:
  Standard_EXPORT IGESDraw_ViewsVisibleWithAttr();

  Standard_EXPORT void Init(
    const occ::handle<NCollection_HArray1<occ::handle<IGESData_ViewKindEntity>>>& allViewEntities,
    const occ::handle<NCollection_HArray1<int>>&                                  allLineFonts,
    const occ::handle<NCollection_HArray1<occ::handle<IGESData_LineFontEntity>>>&
                                                                              allLineDefinitions,
    const occ::handle<NCollection_HArray1<int>>&                              allColorValues,
    const occ::handle<NCollection_HArray1<occ::handle<IGESGraph_Color>>>&     allColorDefinitions,
    const occ::handle<NCollection_HArray1<int>>&                              allLineWeights,
    const occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>& allDisplayEntities);

  Standard_EXPORT void InitImplied(
    const occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>& allDisplayEntity);

  Standard_EXPORT bool IsSingle() const override;

  Standard_EXPORT int NbViews() const override;

  Standard_EXPORT int NbDisplayedEntities() const;

  Standard_EXPORT occ::handle<IGESData_ViewKindEntity> ViewItem(const int Index) const override;

  Standard_EXPORT int LineFontValue(const int Index) const;

  Standard_EXPORT bool IsFontDefinition(const int Index) const;

  Standard_EXPORT occ::handle<IGESData_LineFontEntity> FontDefinition(const int Index) const;

  Standard_EXPORT int ColorValue(const int Index) const;

  Standard_EXPORT bool IsColorDefinition(const int Index) const;

  Standard_EXPORT occ::handle<IGESGraph_Color> ColorDefinition(const int Index) const;

  Standard_EXPORT int LineWeightItem(const int Index) const;

  Standard_EXPORT occ::handle<IGESData_IGESEntity> DisplayedEntity(const int Index) const;

  DEFINE_STANDARD_RTTIEXT(IGESDraw_ViewsVisibleWithAttr, IGESData_ViewKindEntity)

private:
  occ::handle<NCollection_HArray1<occ::handle<IGESData_ViewKindEntity>>> theViewEntities;
  occ::handle<NCollection_HArray1<int>>                                  theLineFonts;
  occ::handle<NCollection_HArray1<occ::handle<IGESData_LineFontEntity>>> theLineDefinitions;
  occ::handle<NCollection_HArray1<int>>                                  theColorValues;
  occ::handle<NCollection_HArray1<occ::handle<IGESGraph_Color>>>         theColorDefinitions;
  occ::handle<NCollection_HArray1<int>>                                  theLineWeights;
  occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>     theDisplayEntities;
};

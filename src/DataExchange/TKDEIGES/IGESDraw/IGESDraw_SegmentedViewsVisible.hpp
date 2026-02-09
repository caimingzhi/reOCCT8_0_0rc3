#pragma once

#include <Standard.hpp>

#include <IGESData_ViewKindEntity.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Integer.hpp>
#include <IGESGraph_Color.hpp>
#include <IGESData_LineFontEntity.hpp>
#include <Standard_Real.hpp>
class IGESGraph_Color;
class IGESData_LineFontEntity;

class IGESDraw_SegmentedViewsVisible : public IGESData_ViewKindEntity
{

public:
  Standard_EXPORT IGESDraw_SegmentedViewsVisible();

  Standard_EXPORT void Init(
    const occ::handle<NCollection_HArray1<occ::handle<IGESData_ViewKindEntity>>>& allViews,
    const occ::handle<NCollection_HArray1<double>>&                       allBreakpointParameters,
    const occ::handle<NCollection_HArray1<int>>&                          allDisplayFlags,
    const occ::handle<NCollection_HArray1<int>>&                          allColorValues,
    const occ::handle<NCollection_HArray1<occ::handle<IGESGraph_Color>>>& allColorDefinitions,
    const occ::handle<NCollection_HArray1<int>>&                          allLineFontValues,
    const occ::handle<NCollection_HArray1<occ::handle<IGESData_LineFontEntity>>>&
                                                 allLineFontDefinitions,
    const occ::handle<NCollection_HArray1<int>>& allLineWeights);

  Standard_EXPORT bool IsSingle() const override;

  Standard_EXPORT int NbViews() const override;

  Standard_EXPORT int NbSegmentBlocks() const;

  Standard_EXPORT occ::handle<IGESData_ViewKindEntity> ViewItem(const int ViewIndex) const override;

  Standard_EXPORT double BreakpointParameter(const int BreakpointIndex) const;

  Standard_EXPORT int DisplayFlag(const int FlagIndex) const;

  Standard_EXPORT bool IsColorDefinition(const int ColorIndex) const;

  Standard_EXPORT int ColorValue(const int ColorIndex) const;

  Standard_EXPORT occ::handle<IGESGraph_Color> ColorDefinition(const int ColorIndex) const;

  Standard_EXPORT bool IsFontDefinition(const int FontIndex) const;

  Standard_EXPORT int LineFontValue(const int FontIndex) const;

  Standard_EXPORT occ::handle<IGESData_LineFontEntity> LineFontDefinition(
    const int FontIndex) const;

  Standard_EXPORT int LineWeightItem(const int WeightIndex) const;

  DEFINE_STANDARD_RTTIEXT(IGESDraw_SegmentedViewsVisible, IGESData_ViewKindEntity)

private:
  occ::handle<NCollection_HArray1<occ::handle<IGESData_ViewKindEntity>>> theViews;
  occ::handle<NCollection_HArray1<double>>                               theBreakpointParameters;
  occ::handle<NCollection_HArray1<int>>                                  theDisplayFlags;
  occ::handle<NCollection_HArray1<int>>                                  theColorValues;
  occ::handle<NCollection_HArray1<occ::handle<IGESGraph_Color>>>         theColorDefinitions;
  occ::handle<NCollection_HArray1<int>>                                  theLineFontValues;
  occ::handle<NCollection_HArray1<occ::handle<IGESData_LineFontEntity>>> theLineFontDefinitions;
  occ::handle<NCollection_HArray1<int>>                                  theLineWeights;
};

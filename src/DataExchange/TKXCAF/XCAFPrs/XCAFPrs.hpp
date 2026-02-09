#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <XCAFPrs_Style.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <Standard_Boolean.hpp>
class TDF_Label;
class TopLoc_Location;

class XCAFPrs
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void CollectStyleSettings(
    const TDF_Label&                                                                  L,
    const TopLoc_Location&                                                            loc,
    NCollection_IndexedDataMap<TopoDS_Shape, XCAFPrs_Style, TopTools_ShapeMapHasher>& settings,
    const Quantity_ColorRGBA& theLayerColor = Quantity_ColorRGBA(Quantity_NOC_WHITE));

  Standard_EXPORT static void SetViewNameMode(const bool viewNameMode);

  Standard_EXPORT static bool GetViewNameMode();
};

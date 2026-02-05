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

//! Presentation (visualiation, selection etc.) tools for
//! DECAF documents
class XCAFPrs
{
public:
  DEFINE_STANDARD_ALLOC

  //! Collect styles defined for shape on label L
  //! and its components and subshapes and fills a map of
  //! shape - style correspondence
  //! The location <loc> is for internal use, it
  //! should be Null location for external call
  Standard_EXPORT static void CollectStyleSettings(
    const TDF_Label&                                                                  L,
    const TopLoc_Location&                                                            loc,
    NCollection_IndexedDataMap<TopoDS_Shape, XCAFPrs_Style, TopTools_ShapeMapHasher>& settings,
    const Quantity_ColorRGBA& theLayerColor = Quantity_ColorRGBA(Quantity_NOC_WHITE));

  //! Set ViewNameMode for indicate display names or not.
  Standard_EXPORT static void SetViewNameMode(const bool viewNameMode);

  Standard_EXPORT static bool GetViewNameMode();
};

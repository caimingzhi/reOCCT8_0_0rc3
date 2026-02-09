#pragma once

#include <TDataStd_Name.hpp>
#include <TDF_Label.hpp>
#include <NCollection_DataMap.hpp>
#include <NCollection_Map.hpp>
#include <NCollection_Sequence.hpp>

class XCAFDoc_VisMaterial;
class XCAFDoc_ShapeTool;

class XCAFDoc_Editor
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static bool Expand(const TDF_Label& theDoc,
                                     const TDF_Label& theShape,
                                     const bool       theRecursively = true);

  Standard_EXPORT static bool Expand(const TDF_Label& theDoc, const bool theRecursively = true);

  Standard_EXPORT static bool Extract(const NCollection_Sequence<TDF_Label>& theSrcLabels,
                                      const TDF_Label&                       theDstLabel,
                                      const bool                             theIsNoVisMat = false);

  Standard_EXPORT static bool Extract(const TDF_Label& theSrcLabel,
                                      const TDF_Label& theDstLabel,
                                      const bool       theIsNoVisMat = false);

  Standard_EXPORT static TDF_Label CloneShapeLabel(
    const TDF_Label&                           theSrcLabel,
    const occ::handle<XCAFDoc_ShapeTool>&      theSrcShapeTool,
    const occ::handle<XCAFDoc_ShapeTool>&      theDstShapeTool,
    NCollection_DataMap<TDF_Label, TDF_Label>& theMap);

  Standard_EXPORT static void CloneMetaData(
    const TDF_Label& theSrcLabel,
    const TDF_Label& theDstLabel,
    NCollection_DataMap<occ::handle<XCAFDoc_VisMaterial>, occ::handle<XCAFDoc_VisMaterial>>*
               theVisMatMap,
    const bool theToCopyColor       = true,
    const bool theToCopyLayer       = true,
    const bool theToCopyMaterial    = true,
    const bool theToCopyVisMaterial = true,
    const bool theToCopyAttributes  = true);

  Standard_EXPORT static void GetParentShapeLabels(const TDF_Label&            theLabel,
                                                   NCollection_Map<TDF_Label>& theRelatedLabels);

  Standard_EXPORT static void GetChildShapeLabels(const TDF_Label&            theLabel,
                                                  NCollection_Map<TDF_Label>& theRelatedLabels);

  Standard_EXPORT static bool FilterShapeTree(const occ::handle<XCAFDoc_ShapeTool>& theShapeTool,
                                              const NCollection_Map<TDF_Label>& theLabelsToKeep);

  Standard_EXPORT static bool RescaleGeometry(const TDF_Label& theLabel,
                                              const double     theScaleFactor,
                                              const bool       theForceIfNotRoot = false);
};

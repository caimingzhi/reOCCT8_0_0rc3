#include <XCAFPrs.hpp>

#include <TDF_Label.hpp>
#include <TopLoc_Location.hpp>
#include <NCollection_IndexedMap.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Compound.hpp>
#include <XCAFDoc_ColorTool.hpp>
#include <XCAFDoc_DocumentTool.hpp>
#include <XCAFDoc_GraphNode.hpp>
#include <XCAFDoc_LayerTool.hpp>
#include <XCAFDoc_VisMaterialTool.hpp>
#include <XCAFDoc_ShapeTool.hpp>
#include <XCAFPrs_Style.hpp>

static bool viewnameMode = false;

static void fillStyleColors(XCAFPrs_Style&                        theStyle,
                            const occ::handle<XCAFDoc_ColorTool>& theTool,
                            const TDF_Label&                      theLabel)
{
  Quantity_ColorRGBA aColor;
  if (theTool->GetColor(theLabel, XCAFDoc_ColorGen, aColor))
  {
    theStyle.SetColorCurv(aColor.GetRGB());
    theStyle.SetColorSurf(aColor);
  }
  if (theTool->GetColor(theLabel, XCAFDoc_ColorSurf, aColor))
  {
    theStyle.SetColorSurf(aColor);
  }
  if (theTool->GetColor(theLabel, XCAFDoc_ColorCurv, aColor))
  {
    theStyle.SetColorCurv(aColor.GetRGB());
  }
}

static bool getShapesOfSHUO(NCollection_IndexedMap<TopLoc_Location>& theaPrevLocMap,
                            const occ::handle<XCAFDoc_ShapeTool>&    theSTool,
                            const TDF_Label&                         theSHUOlab,
                            NCollection_Sequence<TopoDS_Shape>&      theSHUOShapeSeq)
{
  occ::handle<XCAFDoc_GraphNode>  SHUO;
  NCollection_Sequence<TDF_Label> aLabSeq;
  theSTool->GetSHUONextUsage(theSHUOlab, aLabSeq);
  if (aLabSeq.Length() >= 1)
    for (int i = 1; i <= aLabSeq.Length(); i++)
    {
      TDF_Label       aSubCompL = aLabSeq.Value(i);
      TopLoc_Location compLoc   = XCAFDoc_ShapeTool::GetLocation(aSubCompL.Father());

      NCollection_IndexedMap<TopLoc_Location> aNewPrevLocMap;
      for (int m = 1; m <= theaPrevLocMap.Extent(); m++)
        aNewPrevLocMap.Add(theaPrevLocMap.FindKey(m));
      aNewPrevLocMap.Add(compLoc);

      getShapesOfSHUO(aNewPrevLocMap, theSTool, aSubCompL, theSHUOShapeSeq);
    }
  else
  {
    TopoDS_Shape aSHUO_NUSh = theSTool->GetShape(theSHUOlab.Father());
    if (aSHUO_NUSh.IsNull())
      return false;

    TopLoc_Location nullLoc;
    aSHUO_NUSh.Location(nullLoc);

    int intMapLenght = theaPrevLocMap.Extent();
    if (intMapLenght < 1)
      return false;
    TopLoc_Location SupcompLoc;
    SupcompLoc = theaPrevLocMap.FindKey(intMapLenght);
    if (intMapLenght > 1)
    {
      int l = intMapLenght - 1;
      while (l >= 1)
      {
        SupcompLoc = theaPrevLocMap.FindKey(l).Multiplied(SupcompLoc);
        l--;
      }
    }
    aSHUO_NUSh.Location(SupcompLoc, false);
    theSHUOShapeSeq.Append(aSHUO_NUSh);
  }
  return (theSHUOShapeSeq.Length() > 0);
}

void XCAFPrs::CollectStyleSettings(
  const TDF_Label&                                                                  theLabel,
  const TopLoc_Location&                                                            theLoc,
  NCollection_IndexedDataMap<TopoDS_Shape, XCAFPrs_Style, TopTools_ShapeMapHasher>& theSettings,
  const Quantity_ColorRGBA&                                                         theLayerColor)
{

  {
    TDF_Label aLabelRef;
    if (XCAFDoc_ShapeTool::GetReferredShape(theLabel, aLabelRef))
    {
      Quantity_ColorRGBA             aLayerColor = theLayerColor;
      occ::handle<XCAFDoc_LayerTool> aLayerTool  = XCAFDoc_DocumentTool::LayerTool(theLabel);
      occ::handle<NCollection_HSequence<TCollection_ExtendedString>> aLayerNames =
        new NCollection_HSequence<TCollection_ExtendedString>();
      aLayerTool->GetLayers(theLabel, aLayerNames);
      if (aLayerNames->Length() == 1)
      {
        TDF_Label                      aLayer     = aLayerTool->FindLayer(aLayerNames->First());
        occ::handle<XCAFDoc_ColorTool> aColorTool = XCAFDoc_DocumentTool::ColorTool(theLabel);
        Quantity_ColorRGBA             aColor;
        if (aColorTool->GetColor(aLayer, XCAFDoc_ColorGen, aColor))
          aLayerColor = aColor;
      }
      TopLoc_Location aLocSub = theLoc.Multiplied(XCAFDoc_ShapeTool::GetLocation(theLabel));
      CollectStyleSettings(aLabelRef, aLocSub, theSettings, aLayerColor);
    }
  }

  {
    NCollection_Sequence<TDF_Label> aComponentLabSeq;
    if (XCAFDoc_ShapeTool::GetComponents(theLabel, aComponentLabSeq) && !aComponentLabSeq.IsEmpty())
    {
      for (NCollection_Sequence<TDF_Label>::Iterator aComponentIter(aComponentLabSeq);
           aComponentIter.More();
           aComponentIter.Next())
      {
        const TDF_Label& aComponentLab = aComponentIter.Value();
        CollectStyleSettings(aComponentLab, theLoc, theSettings, theLayerColor);
      }
    }
  }

  occ::handle<XCAFDoc_ColorTool>       aColorTool = XCAFDoc_DocumentTool::ColorTool(theLabel);
  occ::handle<XCAFDoc_VisMaterialTool> aMatTool   = XCAFDoc_DocumentTool::VisMaterialTool(theLabel);

  NCollection_Sequence<TDF_Label> aLabSeq;
  XCAFDoc_ShapeTool::GetSubShapes(theLabel, aLabSeq);

  aLabSeq.Append(theLabel);
  for (NCollection_Sequence<TDF_Label>::Iterator aLabIter(aLabSeq); aLabIter.More();
       aLabIter.Next())
  {
    const TDF_Label& aLabel = aLabIter.Value();
    XCAFPrs_Style    aStyle;
    aStyle.SetVisibility(aColorTool->IsVisible(aLabel));
    aStyle.SetMaterial(aMatTool->GetShapeMaterial(aLabel));

    occ::handle<NCollection_HSequence<TCollection_ExtendedString>> aLayerNames;
    occ::handle<XCAFDoc_LayerTool> aLayerTool = XCAFDoc_DocumentTool::LayerTool(aLabel);
    if (aStyle.IsVisible())
    {
      aLayerNames = new NCollection_HSequence<TCollection_ExtendedString>();
      aLayerTool->GetLayers(aLabel, aLayerNames);
      int aNbHidden = 0;
      for (NCollection_HSequence<TCollection_ExtendedString>::Iterator aLayerIter(*aLayerNames);
           aLayerIter.More();
           aLayerIter.Next())
      {
        const TCollection_ExtendedString& aLayerName = aLayerIter.Value();
        if (!aLayerTool->IsVisible(aLayerTool->FindLayer(aLayerName)))
        {
          ++aNbHidden;
        }
      }
      aStyle.SetVisibility(aNbHidden == 0 || aNbHidden != aLayerNames->Length());
    }

    if (aColorTool->IsColorByLayer(aLabel))
    {
      Quantity_ColorRGBA aLayerColor = theLayerColor;
      if (aLayerNames.IsNull())
      {
        aLayerNames = new NCollection_HSequence<TCollection_ExtendedString>();
        aLayerTool->GetLayers(aLabel, aLayerNames);
      }
      if (aLayerNames->Length() == 1)
      {
        TDF_Label          aLayer = aLayerTool->FindLayer(aLayerNames->First());
        Quantity_ColorRGBA aColor;
        if (aColorTool->GetColor(aLayer, XCAFDoc_ColorGen, aColor))
        {
          aLayerColor = aColor;
        }
      }

      aStyle.SetColorCurv(aLayerColor.GetRGB());
      aStyle.SetColorSurf(aLayerColor);
    }
    else
    {
      fillStyleColors(aStyle, aColorTool, aLabel);
    }

    const occ::handle<XCAFDoc_ShapeTool>& aShapeTool = aColorTool->ShapeTool();
    if (aShapeTool->IsComponent(aLabel))
    {
      NCollection_Sequence<occ::handle<TDF_Attribute>> aShuoAttribSeq;
      aShapeTool->GetAllComponentSHUO(aLabel, aShuoAttribSeq);
      for (NCollection_Sequence<occ::handle<TDF_Attribute>>::Iterator aShuoAttribIter(
             aShuoAttribSeq);
           aShuoAttribIter.More();
           aShuoAttribIter.Next())
      {
        occ::handle<XCAFDoc_GraphNode> aShuoNode =
          occ::down_cast<XCAFDoc_GraphNode>(aShuoAttribIter.Value());
        if (aShuoNode.IsNull())
        {
          continue;
        }

        const TDF_Label aShuolab = aShuoNode->Label();
        {
          NCollection_Sequence<TDF_Label> aShuoLabSeq;
          aShapeTool->GetSHUONextUsage(aShuolab, aShuoLabSeq);
          if (aShuoLabSeq.IsEmpty())
          {
            continue;
          }
        }

        XCAFPrs_Style aShuoStyle;
        aShuoStyle.SetMaterial(aMatTool->GetShapeMaterial(aShuolab));
        aShuoStyle.SetVisibility(aColorTool->IsVisible(aShuolab));
        fillStyleColors(aShuoStyle, aColorTool, aShuolab);
        if (aShuoStyle.IsEmpty())
        {
          continue;
        }

#ifdef OCCT_DEBUG
        std::cout << "Set the style for SHUO next_usage-occurrence" << std::endl;
#endif

        TopLoc_Location                         compLoc = XCAFDoc_ShapeTool::GetLocation(aLabel);
        NCollection_IndexedMap<TopLoc_Location> aPrevLocMap;

        if (!theLoc.IsIdentity())
        {
          aPrevLocMap.Add(theLoc);
        }
        aPrevLocMap.Add(compLoc);

        NCollection_Sequence<TopoDS_Shape> aShuoShapeSeq;
        getShapesOfSHUO(aPrevLocMap, aShapeTool, aShuolab, aShuoShapeSeq);
        for (NCollection_Sequence<TopoDS_Shape>::Iterator aShuoShapeIter(aShuoShapeSeq);
             aShuoShapeIter.More();
             aShuoShapeIter.Next())
        {
          const TopoDS_Shape& aShuoShape = aShuoShapeIter.Value();
          XCAFPrs_Style*      aMapStyle  = theSettings.ChangeSeek(aShuoShape);
          if (aMapStyle == nullptr)
            theSettings.Add(aShuoShape, aShuoStyle);
          else
            *aMapStyle = aShuoStyle;
        }
        continue;
      }
    }

    if (aStyle.IsEmpty())
    {
      continue;
    }

    TopoDS_Shape aSubshape = XCAFDoc_ShapeTool::GetShape(aLabel);
    if (aSubshape.ShapeType() == TopAbs_COMPOUND)
    {
      if (aSubshape.NbChildren() == 0)
      {
        continue;
      }
    }
    aSubshape.Move(theLoc, false);
    XCAFPrs_Style* aMapStyle = theSettings.ChangeSeek(aSubshape);
    if (aMapStyle == nullptr)
      theSettings.Add(aSubshape, aStyle);
    else
      *aMapStyle = aStyle;
  }
}

void XCAFPrs::SetViewNameMode(const bool aNameMode)
{
  viewnameMode = aNameMode;
}

bool XCAFPrs::GetViewNameMode()
{
  return viewnameMode;
}

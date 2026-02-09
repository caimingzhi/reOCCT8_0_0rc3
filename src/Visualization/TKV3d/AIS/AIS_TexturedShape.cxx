#include <AIS_TexturedShape.hpp>

#include <AIS_GraphicTool.hpp>
#include <AIS_InteractiveContext.hpp>
#include <BRepTools.hpp>
#include <gp_Pnt2d.hpp>
#include <Graphic3d_AspectFillArea3d.hpp>
#include <Graphic3d_Group.hpp>
#include <Graphic3d_StructureManager.hpp>
#include <Graphic3d_Texture2D.hpp>
#include <Message.hpp>
#include <Message_Messenger.hpp>
#include <Prs3d_Drawer.hpp>
#include <Prs3d_Presentation.hpp>
#include <Prs3d_ShadingAspect.hpp>
#include <PrsMgr_PresentationManager.hpp>
#include <Standard_ErrorHandler.hpp>
#include <Prs3d_BndBox.hpp>
#include <StdPrs_ShadedShape.hpp>
#include <StdPrs_ToolTriangulatedShape.hpp>
#include <StdPrs_WFShape.hpp>

IMPLEMENT_STANDARD_RTTIEXT(AIS_TexturedShape, AIS_Shape)

AIS_TexturedShape::AIS_TexturedShape(const TopoDS_Shape& theShape)
    : AIS_Shape(theShape),
      myPredefTexture(Graphic3d_NameOfTexture2D(0)),
      myToMapTexture(true),
      myModulate(true),
      myIsCustomOrigin(true),
      myToRepeat(true),
      myToScale(true),
      myToShowTriangles(false)
{
}

void AIS_TexturedShape::SetTextureFileName(const TCollection_AsciiString& theTextureFileName)
{
  myTexturePixMap.Nullify();

  if (theTextureFileName.IsIntegerValue())
  {
    const int aValue = theTextureFileName.IntegerValue();
    if (aValue < Graphic3d_Texture2D::NumberOfTextures() && aValue >= 0)
    {
      myPredefTexture = Graphic3d_NameOfTexture2D(aValue);
    }
    else
    {
      Message::SendFail(TCollection_AsciiString("Error: texture with ID ") + theTextureFileName
                        + " is undefined. Texture 0 will be used instead.");
      myPredefTexture = Graphic3d_NameOfTexture2D(0);
    }
    myTextureFile = "";
  }
  else
  {
    myTextureFile   = theTextureFileName;
    myPredefTexture = Graphic3d_NOT_2D_UNKNOWN;
  }
}

void AIS_TexturedShape::SetTexturePixMap(const occ::handle<Image_PixMap>& theTexturePixMap)
{
  myTextureFile   = "";
  myPredefTexture = Graphic3d_NOT_2D_UNKNOWN;
  myTexturePixMap = theTexturePixMap;
}

void AIS_TexturedShape::SetTextureRepeat(const bool   theToRepeat,
                                         const double theURepeat,
                                         const double theVRepeat)
{
  myToRepeat = theToRepeat;
  myUVRepeat.SetCoord(theURepeat, theVRepeat);
}

void AIS_TexturedShape::SetTextureMapOn()
{
  myToMapTexture = true;
}

void AIS_TexturedShape::SetTextureMapOff()
{
  myToMapTexture = false;
}

void AIS_TexturedShape::SetTextureOrigin(const bool   theToSetTextureOrigin,
                                         const double theUOrigin,
                                         const double theVOrigin)
{
  myIsCustomOrigin = theToSetTextureOrigin;
  myUVOrigin.SetCoord(theUOrigin, theVOrigin);
}

void AIS_TexturedShape::SetTextureScale(const bool   theToSetTextureScale,
                                        const double theScaleU,
                                        const double theScaleV)
{
  myToScale = theToSetTextureScale;
  myUVScale.SetCoord(theScaleU, theScaleV);
}

void AIS_TexturedShape::ShowTriangles(const bool theToShowTriangles)
{
  myToShowTriangles = theToShowTriangles;
}

void AIS_TexturedShape::EnableTextureModulate()
{
  myModulate = true;
}

void AIS_TexturedShape::DisableTextureModulate()
{
  myModulate = false;
}

void AIS_TexturedShape::SetColor(const Quantity_Color& theColor)
{
  AIS_Shape::SetColor(theColor);

  for (NCollection_Sequence<occ::handle<PrsMgr_Presentation>>::Iterator aPrsIter(Presentations());
       aPrsIter.More();
       aPrsIter.Next())
  {
    if (aPrsIter.Value()->Mode() == 3)
    {
      updateAttributes(aPrsIter.Value());
    }
  }
}

void AIS_TexturedShape::UnsetColor()
{
  AIS_Shape::UnsetColor();
}

void AIS_TexturedShape::SetMaterial(const Graphic3d_MaterialAspect& theMat)
{
  AIS_Shape::SetMaterial(theMat);
  for (NCollection_Sequence<occ::handle<PrsMgr_Presentation>>::Iterator aPrsIter(Presentations());
       aPrsIter.More();
       aPrsIter.Next())
  {
    if (aPrsIter.Value()->Mode() == 3)
    {
      updateAttributes(aPrsIter.Value());
    }
  }
}

void AIS_TexturedShape::UnsetMaterial()
{
  AIS_Shape::UnsetMaterial();
  for (NCollection_Sequence<occ::handle<PrsMgr_Presentation>>::Iterator aPrsIter(Presentations());
       aPrsIter.More();
       aPrsIter.Next())
  {
    if (aPrsIter.Value()->Mode() == 3)
    {
      updateAttributes(aPrsIter.Value());
    }
  }
}

void AIS_TexturedShape::UpdateAttributes()
{
  updateAttributes(Presentation());
}

void AIS_TexturedShape::updateAttributes(const occ::handle<Prs3d_Presentation>& thePrs)
{
  myAspect = new Graphic3d_AspectFillArea3d(*myDrawer->ShadingAspect()->Aspect());
  if (HasPolygonOffsets())
  {
    int   aMode;
    float aFactor, aUnits;
    PolygonOffsets(aMode, aFactor, aUnits);
    myAspect->SetPolygonOffsets(aMode, aFactor, aUnits);
  }

  bool hasTexture = false;
  if (myToMapTexture)
  {
    TCollection_AsciiString aTextureDesc;
    if (!myTexturePixMap.IsNull())
    {
      myTexture    = new Graphic3d_Texture2D(myTexturePixMap);
      aTextureDesc = " (custom image)";
    }
    else if (myPredefTexture != Graphic3d_NOT_2D_UNKNOWN)
    {
      myTexture    = new Graphic3d_Texture2D(myPredefTexture);
      aTextureDesc = TCollection_AsciiString(" (predefined texture ") + myTexture->GetId() + ")";
    }
    else
    {
      myTexture    = new Graphic3d_Texture2D(myTextureFile.ToCString());
      aTextureDesc = TCollection_AsciiString(" (") + myTextureFile + ")";
    }

    if (myModulate)
    {
      myTexture->EnableModulate();
    }
    else
    {
      myTexture->DisableModulate();
    }

    if (myTexture->IsDone())
    {
      hasTexture = true;
    }
    else
    {
      Message::SendFail(TCollection_AsciiString("Error: texture can not be loaded ")
                        + aTextureDesc);
    }
  }

  myAspect->SetTextureMap(myTexture);
  if (hasTexture)
  {
    myAspect->SetTextureMapOn();
  }
  else
  {
    myAspect->SetTextureMapOff();
  }

  if (myToShowTriangles)
  {
    myAspect->SetEdgeOn();
  }
  else
  {
    myAspect->SetEdgeOff();
  }

  for (NCollection_Sequence<occ::handle<Graphic3d_Group>>::Iterator aGroupIt(thePrs->Groups());
       aGroupIt.More();
       aGroupIt.Next())
  {
    const occ::handle<Graphic3d_Group>& aGroup = aGroupIt.Value();
    aGroup->SetGroupPrimitivesAspect(myAspect);
  }
}

void AIS_TexturedShape::Compute(const occ::handle<PrsMgr_PresentationManager>&,
                                const occ::handle<Prs3d_Presentation>& thePrs,
                                const int                              theMode)
{
  if (myshape.IsNull() || (myshape.ShapeType() == TopAbs_COMPOUND && myshape.NbChildren() == 0))
  {
    return;
  }

  if (myshape.ShapeType() >= TopAbs_WIRE && myshape.ShapeType() <= TopAbs_VERTEX)
  {

    const int aPrior =
      (int)Graphic3d_DisplayPriority_Above1 + (int)myshape.ShapeType() - TopAbs_WIRE;
    thePrs->SetVisual(Graphic3d_TOS_ALL);
    thePrs->SetDisplayPriority((Graphic3d_DisplayPriority)aPrior);
  }

  if (IsInfinite())
  {
    thePrs->SetInfiniteState(true);
  }

  switch (theMode)
  {
    case AIS_WireFrame:
    {
      StdPrs_ToolTriangulatedShape::ClearOnOwnDeflectionChange(myshape, myDrawer, true);
      StdPrs_WFShape::Add(thePrs, myshape, myDrawer);
      break;
    }
    case AIS_Shaded:
    case 3:
    {
      StdPrs_ToolTriangulatedShape::ClearOnOwnDeflectionChange(myshape, myDrawer, true);
      if (myshape.ShapeType() > TopAbs_FACE)
      {
        StdPrs_WFShape::Add(thePrs, myshape, myDrawer);
        break;
      }

      if (IsInfinite())
      {
        StdPrs_WFShape::Add(thePrs, myshape, myDrawer);
        break;
      }
      try
      {
        OCC_CATCH_SIGNALS
        if (theMode == AIS_Shaded)
        {
          StdPrs_ShadedShape::Add(thePrs, myshape, myDrawer);
        }
        else
        {
          StdPrs_ShadedShape::Add(thePrs,
                                  myshape,
                                  myDrawer,
                                  true,
                                  myIsCustomOrigin ? myUVOrigin : gp_Pnt2d(0.0, 0.0),
                                  myUVRepeat,
                                  myToScale ? myUVScale : gp_Pnt2d(1.0, 1.0));
          updateAttributes(thePrs);
        }
      }
      catch (Standard_Failure const&)
      {
#ifdef OCCT_DEBUG
        std::cout << "AIS_TexturedShape::Compute() in ShadingMode failed \n";
#endif
        StdPrs_WFShape::Add(thePrs, myshape, myDrawer);
      }
      break;
    }
    case 2:
    {
      if (IsInfinite())
      {
        StdPrs_WFShape::Add(thePrs, myshape, myDrawer);
      }
      else
      {
        Prs3d_BndBox::Add(thePrs, BoundingBox(), myDrawer);
      }
      break;
    }
  }
}

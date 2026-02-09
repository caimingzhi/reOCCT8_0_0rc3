#include <AIS_ColoredShape.hpp>

#include <AIS_InteractiveContext.hpp>
#include <BRep_Builder.hpp>
#include <BRepTools.hpp>
#include <BRepMesh_IncrementalMesh.hpp>
#include <Graphic3d_AspectFillArea3d.hpp>
#include <Graphic3d_AspectLine3d.hpp>
#include <Graphic3d_ArrayOfTriangles.hpp>
#include <Graphic3d_ArrayOfSegments.hpp>
#include <Graphic3d_Group.hpp>
#include <Graphic3d_StructureManager.hpp>
#include <Precision.hpp>
#include <Prs3d_Presentation.hpp>
#include <Prs3d_ShadingAspect.hpp>
#include <PrsMgr_PresentationManager.hpp>
#include <StdSelect_BRepSelectionTool.hpp>
#include <StdPrs_ShadedShape.hpp>
#include <StdPrs_ToolTriangulatedShape.hpp>
#include <StdPrs_WFShape.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS_Compound.hpp>
#include <TopoDS_Iterator.hpp>

IMPLEMENT_STANDARD_RTTIEXT(AIS_ColoredShape, AIS_Shape)
IMPLEMENT_STANDARD_RTTIEXT(AIS_ColoredDrawer, Prs3d_Drawer)

namespace
{

  static void collectSubCompounds(NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>& theMap,
                                  const TopoDS_Shape&                                     theShape)
  {
    for (TopoDS_Iterator aChildIter(theShape); aChildIter.More(); aChildIter.Next())
    {
      const TopoDS_Shape& aShape = aChildIter.Value();
      if (aShape.ShapeType() == TopAbs_COMPOUND && theMap.Add(aShape))
      {
        collectSubCompounds(theMap, aShape);
      }
    }
  }
} // namespace

AIS_ColoredShape::AIS_ColoredShape(const TopoDS_Shape& theShape)
    : AIS_Shape(theShape)
{

  myDrawer->SetFreeBoundaryAspect(myDrawer->LineAspect());
  myDrawer->SetUnFreeBoundaryAspect(myDrawer->LineAspect());
  myDrawer->SetSeenLineAspect(myDrawer->LineAspect());
  myDrawer->SetFaceBoundaryAspect(myDrawer->LineAspect());
}

AIS_ColoredShape::AIS_ColoredShape(const occ::handle<AIS_Shape>& theShape)
    : AIS_Shape(theShape->Shape())
{

  myDrawer->SetFreeBoundaryAspect(myDrawer->LineAspect());
  myDrawer->SetUnFreeBoundaryAspect(myDrawer->LineAspect());
  myDrawer->SetSeenLineAspect(myDrawer->LineAspect());
  myDrawer->SetFaceBoundaryAspect(myDrawer->LineAspect());
  if (theShape->HasMaterial())
  {
    SetMaterial(theShape->Material());
  }
  if (theShape->HasColor())
  {
    Quantity_Color aColor;
    theShape->Color(aColor);
    SetColor(aColor);
  }
  if (theShape->HasWidth())
  {
    SetWidth(theShape->Width());
  }
  if (theShape->IsTransparent())
  {
    SetTransparency(theShape->Transparency());
  }
}

occ::handle<AIS_ColoredDrawer> AIS_ColoredShape::CustomAspects(const TopoDS_Shape& theShape)
{
  occ::handle<AIS_ColoredDrawer> aDrawer;
  myShapeColors.Find(theShape, aDrawer);
  if (aDrawer.IsNull())
  {
    aDrawer = new AIS_ColoredDrawer(myDrawer);
    myShapeColors.Bind(theShape, aDrawer);
    SetToUpdate();
  }
  return aDrawer;
}

void AIS_ColoredShape::ClearCustomAspects()
{
  if (myShapeColors.IsEmpty())
  {
    return;
  }
  myShapeColors.Clear();
  SetToUpdate();
}

void AIS_ColoredShape::UnsetCustomAspects(const TopoDS_Shape& theShape, const bool theToUnregister)
{
  if (!myShapeColors.IsBound(theShape))
  {
    return;
  }

  SetToUpdate();
  if (theToUnregister)
  {
    myShapeColors.UnBind(theShape);
    return;
  }

  myShapeColors.ChangeFind(theShape) = new AIS_ColoredDrawer(myDrawer);
}

void AIS_ColoredShape::SetCustomColor(const TopoDS_Shape& theShape, const Quantity_Color& theColor)
{
  if (theShape.IsNull())
  {
    return;
  }

  const occ::handle<AIS_ColoredDrawer>& aDrawer = CustomAspects(theShape);
  setColor(aDrawer, theColor);
  aDrawer->SetOwnColor(theColor);
}

void AIS_ColoredShape::SetCustomTransparency(const TopoDS_Shape& theShape, double theTransparency)
{
  if (theShape.IsNull())
  {
    return;
  }

  const occ::handle<AIS_ColoredDrawer>& aDrawer = CustomAspects(theShape);
  setTransparency(aDrawer, theTransparency);
  aDrawer->SetOwnTransparency(theTransparency);
}

void AIS_ColoredShape::SetCustomWidth(const TopoDS_Shape& theShape, const double theLineWidth)
{
  if (theShape.IsNull())
  {
    return;
  }

  const occ::handle<AIS_ColoredDrawer>& aDrawer = CustomAspects(theShape);
  setWidth(aDrawer, theLineWidth);
  aDrawer->SetOwnWidth(theLineWidth);
}

void AIS_ColoredShape::SetColor(const Quantity_Color& theColor)
{
  for (NCollection_DataMap<TopoDS_Shape, occ::handle<AIS_ColoredDrawer>, TopTools_ShapeMapHasher>::
         Iterator anIter(myShapeColors);
       anIter.More();
       anIter.Next())
  {
    const occ::handle<AIS_ColoredDrawer>& aDrawer = anIter.Value();
    if (aDrawer->HasOwnColor())
    {
      continue;
    }

    if (aDrawer->HasOwnShadingAspect())
    {
      aDrawer->ShadingAspect()->SetColor(theColor, myCurrentFacingModel);
    }
    if (aDrawer->HasOwnLineAspect())
    {
      aDrawer->LineAspect()->SetColor(theColor);
    }
    if (aDrawer->HasOwnWireAspect())
    {
      aDrawer->WireAspect()->SetColor(theColor);
    }
    if (aDrawer->HasOwnFaceBoundaryAspect())
    {
      aDrawer->FaceBoundaryAspect()->SetColor(theColor);
    }
  }
  AIS_Shape::SetColor(theColor);
}

void AIS_ColoredShape::SetWidth(const double theLineWidth)
{
  for (NCollection_DataMap<TopoDS_Shape, occ::handle<AIS_ColoredDrawer>, TopTools_ShapeMapHasher>::
         Iterator anIter(myShapeColors);
       anIter.More();
       anIter.Next())
  {
    const occ::handle<AIS_ColoredDrawer>& aDrawer = anIter.Value();
    if (aDrawer->HasOwnWidth())
    {
      continue;
    }

    if (aDrawer->HasOwnLineAspect())
    {
      aDrawer->LineAspect()->SetWidth(theLineWidth);
    }
    if (aDrawer->HasOwnWireAspect())
    {
      aDrawer->WireAspect()->SetWidth(theLineWidth);
    }
    if (aDrawer->HasOwnFaceBoundaryAspect())
    {
      aDrawer->FaceBoundaryAspect()->SetWidth(theLineWidth);
    }
  }
  AIS_Shape::SetWidth(theLineWidth);
}

void AIS_ColoredShape::UnsetWidth()
{
  SetWidth(1.0f);
}

void AIS_ColoredShape::SetTransparency(const double theValue)
{
  for (NCollection_DataMap<TopoDS_Shape, occ::handle<AIS_ColoredDrawer>, TopTools_ShapeMapHasher>::
         Iterator anIter(myShapeColors);
       anIter.More();
       anIter.Next())
  {
    const occ::handle<AIS_ColoredDrawer>& aDrawer = anIter.Value();
    if (aDrawer->HasOwnTransparency())
    {
      continue;
    }

    if (aDrawer->HasOwnShadingAspect())
    {
      aDrawer->ShadingAspect()->SetTransparency(theValue, myCurrentFacingModel);
    }
  }
  AIS_Shape::SetTransparency(theValue);
}

void AIS_ColoredShape::UnsetTransparency()
{
  SetTransparency(0.0f);
}

void AIS_ColoredShape::SetMaterial(const Graphic3d_MaterialAspect& theMaterial)
{
  for (NCollection_DataMap<TopoDS_Shape, occ::handle<AIS_ColoredDrawer>, TopTools_ShapeMapHasher>::
         Iterator anIter(myShapeColors);
       anIter.More();
       anIter.Next())
  {
    const occ::handle<AIS_ColoredDrawer>& aDrawer = anIter.Value();
    if (aDrawer->HasOwnMaterial())
    {
      continue;
    }

    if (aDrawer->HasOwnShadingAspect())
    {
      setMaterial(aDrawer, theMaterial, aDrawer->HasOwnColor(), aDrawer->HasOwnTransparency());
    }
  }
  AIS_Shape::SetMaterial(theMaterial);
}

void AIS_ColoredShape::Compute(const occ::handle<PrsMgr_PresentationManager>& thePrsMgr,
                               const occ::handle<Prs3d_Presentation>&         thePrs,
                               const int                                      theMode)
{
  if (myshape.IsNull())
  {
    return;
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

      StdPrs_ToolTriangulatedShape::GetDeflection(myshape, myDrawer);
      break;
    }
    case AIS_Shaded:
    {
      if (myDrawer->IsAutoTriangulation())
      {

        StdPrs_ToolTriangulatedShape::ClearOnOwnDeflectionChange(myshape, myDrawer, true);

        bool wasRecomputed = StdPrs_ToolTriangulatedShape::Tessellate(myshape, myDrawer);

        if (myDrawer->IsoOnTriangulation() && wasRecomputed)
        {
          SetToUpdate(AIS_WireFrame);
        }
      }
      break;
    }
    case 2:
    {
      AIS_Shape::Compute(thePrsMgr, thePrs, theMode);
      return;
    }
    default:
    {
      return;
    }
  }

  NCollection_DataMap<TopoDS_Shape, occ::handle<AIS_ColoredDrawer>, TopTools_ShapeMapHasher>
    aSubshapeDrawerMap;
  fillSubshapeDrawerMap(aSubshapeDrawerMap);

  occ::handle<AIS_ColoredDrawer> aBaseDrawer;
  myShapeColors.Find(myshape, aBaseDrawer);

  DataMapOfDrawerCompd aDispatchedOpened[(size_t)TopAbs_SHAPE];
  DataMapOfDrawerCompd aDispatchedClosed;
  dispatchColors(aBaseDrawer,
                 myshape,
                 aSubshapeDrawerMap,
                 TopAbs_COMPOUND,
                 false,
                 aDispatchedOpened,
                 theMode == AIS_Shaded ? aDispatchedClosed : aDispatchedOpened[TopAbs_FACE]);
  addShapesWithCustomProps(thePrs, aDispatchedOpened, aDispatchedClosed, theMode);
}

void AIS_ColoredShape::fillSubshapeDrawerMap(
  NCollection_DataMap<TopoDS_Shape, occ::handle<AIS_ColoredDrawer>, TopTools_ShapeMapHasher>&
    theSubshapeDrawerMap) const
{

  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> aMapOfOwnCompounds;
  if (myshape.ShapeType() == TopAbs_COMPOUND)
  {
    aMapOfOwnCompounds.Add(myshape);
    collectSubCompounds(aMapOfOwnCompounds, myshape);
  }
  for (NCollection_DataMap<TopoDS_Shape, occ::handle<AIS_ColoredDrawer>, TopTools_ShapeMapHasher>::
         Iterator aKeyShapeIter(myShapeColors);
       aKeyShapeIter.More();
       aKeyShapeIter.Next())
  {
    const TopoDS_Shape& aKeyShape = aKeyShapeIter.Key();
    if (aKeyShape.ShapeType() != TopAbs_COMPOUND || aMapOfOwnCompounds.Contains(aKeyShape))
    {
      continue;
    }

    for (TopoDS_Iterator aChildIter(aKeyShape); aChildIter.More(); aChildIter.Next())
    {
      const TopoDS_Shape& aShape = aChildIter.Value();
      if (!myShapeColors.IsBound(aShape))
      {
        bindSubShapes(theSubshapeDrawerMap, aShape, aKeyShapeIter.Value());
      }
    }
  }

  for (NCollection_DataMap<TopoDS_Shape, occ::handle<AIS_ColoredDrawer>, TopTools_ShapeMapHasher>::
         Iterator aKeyShapeIter(myShapeColors);
       aKeyShapeIter.More();
       aKeyShapeIter.Next())
  {
    const TopoDS_Shape& aKeyShape = aKeyShapeIter.Key();
    if (myshape == aKeyShape
        || (aKeyShape.ShapeType() == TopAbs_COMPOUND && !aMapOfOwnCompounds.Contains(aKeyShape)))
    {
      continue;
    }

    bindSubShapes(theSubshapeDrawerMap, aKeyShape, aKeyShapeIter.Value());
  }
}

void AIS_ColoredShape::ComputeSelection(const occ::handle<SelectMgr_Selection>& theSelection,
                                        const int                               theMode)
{
  if (myshape.IsNull())
  {
    return;
  }
  else if (isShapeEntirelyVisible())
  {
    base_type::ComputeSelection(theSelection, theMode);
    return;
  }

  const TopAbs_ShapeEnum aTypOfSel = AIS_Shape::SelectionType(theMode);
  const double aDeflection         = StdPrs_ToolTriangulatedShape::GetDeflection(myshape, myDrawer);
  const double aDeviationAngle     = myDrawer->DeviationAngle();
  const int    aPriority = StdSelect_BRepSelectionTool::GetStandardPriority(myshape, aTypOfSel);
  if (myDrawer->IsAutoTriangulation() && !BRepTools::Triangulation(myshape, Precision::Infinite()))
  {
    BRepMesh_IncrementalMesh aMesher(myshape, aDeflection, false, aDeviationAngle);
  }

  NCollection_DataMap<TopoDS_Shape, occ::handle<AIS_ColoredDrawer>, TopTools_ShapeMapHasher>
    aSubshapeDrawerMap;
  fillSubshapeDrawerMap(aSubshapeDrawerMap);

  occ::handle<StdSelect_BRepOwner> aBrepOwner = new StdSelect_BRepOwner(myshape, aPriority);
  if (aTypOfSel == TopAbs_SHAPE)
  {
    aBrepOwner = new StdSelect_BRepOwner(myshape, aPriority);
  }

  occ::handle<AIS_ColoredDrawer> aBaseDrawer;
  myShapeColors.Find(myshape, aBaseDrawer);
  computeSubshapeSelection(aBaseDrawer,
                           aSubshapeDrawerMap,
                           myshape,
                           aBrepOwner,
                           theSelection,
                           aTypOfSel,
                           aPriority,
                           aDeflection,
                           aDeviationAngle);

  occ::handle<SelectMgr_SelectableObject> aThis(this);
  for (NCollection_Vector<occ::handle<SelectMgr_SensitiveEntity>>::Iterator aSelEntIter(
         theSelection->Entities());
       aSelEntIter.More();
       aSelEntIter.Next())
  {
    const occ::handle<SelectMgr_EntityOwner>& anOwner =
      aSelEntIter.Value()->BaseSensitive()->OwnerId();
    anOwner->SetSelectable(aThis);
  }
}

void AIS_ColoredShape::computeSubshapeSelection(
  const occ::handle<AIS_ColoredDrawer>& theParentDrawer,
  const NCollection_DataMap<TopoDS_Shape, occ::handle<AIS_ColoredDrawer>, TopTools_ShapeMapHasher>&
                                          theShapeDrawerMap,
  const TopoDS_Shape&                     theShape,
  const occ::handle<StdSelect_BRepOwner>& theOwner,
  const occ::handle<SelectMgr_Selection>& theSelection,
  const TopAbs_ShapeEnum                  theTypOfSel,
  const int                               thePriority,
  const double                            theDeflection,
  const double                            theDeflAngle)
{
  occ::handle<AIS_ColoredDrawer> aDrawer = theParentDrawer;
  theShapeDrawerMap.Find(theShape, aDrawer);
  if (!aDrawer.IsNull() && aDrawer->IsHidden())
  {
    return;
  }

  const int    aNbPOnEdge        = 9;
  const double aMaximalParameter = 500.0;
  if (theTypOfSel == TopAbs_SHAPE && theShape.ShapeType() >= TopAbs_FACE)
  {
    StdSelect_BRepSelectionTool::ComputeSensitive(theShape,
                                                  theOwner,
                                                  theSelection,
                                                  theDeflection,
                                                  theDeflAngle,
                                                  aNbPOnEdge,
                                                  aMaximalParameter,
                                                  myDrawer->IsAutoTriangulation());
    return;
  }
  else if (theShape.ShapeType() == theTypOfSel)
  {
    const bool                       isComesFromDecomposition = !theShape.IsEqual(myshape);
    occ::handle<StdSelect_BRepOwner> aBrepOwner =
      new StdSelect_BRepOwner(theShape, thePriority, isComesFromDecomposition);
    StdSelect_BRepSelectionTool::ComputeSensitive(theShape,
                                                  aBrepOwner,
                                                  theSelection,
                                                  theDeflection,
                                                  theDeflAngle,
                                                  aNbPOnEdge,
                                                  aMaximalParameter,
                                                  myDrawer->IsAutoTriangulation());
    return;
  }

  for (TopoDS_Iterator aSubShapeIter(theShape); aSubShapeIter.More(); aSubShapeIter.Next())
  {
    const TopoDS_Shape& aSubShape = aSubShapeIter.Value();
    computeSubshapeSelection(aDrawer,
                             theShapeDrawerMap,
                             aSubShape,
                             theOwner,
                             theSelection,
                             theTypOfSel,
                             thePriority,
                             theDeflection,
                             theDeflAngle);
  }
}

void AIS_ColoredShape::addShapesWithCustomProps(
  const occ::handle<Prs3d_Presentation>& thePrs,
  const DataMapOfDrawerCompd*            theDrawerOpenedShapePerType,
  const DataMapOfDrawerCompd&            theDrawerClosedFaces,
  const int                              theMode)
{
  occ::handle<Graphic3d_Group> anOpenGroup, aClosedGroup, anEdgesGroup;
  for (size_t aShType = 0; aShType <= (size_t)TopAbs_SHAPE; ++aShType)
  {
    const bool                    isClosed     = aShType == TopAbs_SHAPE;
    occ::handle<Graphic3d_Group>& aShadedGroup = isClosed ? aClosedGroup : anOpenGroup;
    const DataMapOfDrawerCompd&   aDrawerShapeMap =
      isClosed ? theDrawerClosedFaces : theDrawerOpenedShapePerType[aShType];
    for (DataMapOfDrawerCompd::Iterator aMapIter(aDrawerShapeMap); aMapIter.More(); aMapIter.Next())
    {
      const occ::handle<AIS_ColoredDrawer>& aCustomDrawer = aMapIter.Key();

      const TopoDS_Compound& aShapeDraw = aMapIter.Value();

      occ::handle<Prs3d_Drawer> aDrawer;
      if (!aCustomDrawer.IsNull())
      {
        aDrawer = aCustomDrawer;
        if (aCustomDrawer->IsHidden())
        {
          continue;
        }
      }
      else
      {
        aDrawer = myDrawer;
      }

      Aspect_TypeOfDeflection aPrevType = aDrawer->TypeOfDeflection();
      aDrawer->SetTypeOfDeflection(Aspect_TOD_ABSOLUTE);

      if (theMode == AIS_Shaded && aShapeDraw.ShapeType() <= TopAbs_FACE && !IsInfinite())
      {

        StdPrs_ShadedShape::AddWireframeForFreeElements(thePrs, aShapeDraw, aDrawer);

        StdPrs_ShadedShape::AddWireframeForFacesWithoutTriangles(thePrs, aShapeDraw, aDrawer);

        occ::handle<Graphic3d_ArrayOfTriangles> aTriangles = StdPrs_ShadedShape::FillTriangles(
          aShapeDraw,
          aDrawer->ShadingAspect()->Aspect()->ToMapTexture()
            && !aDrawer->ShadingAspect()->Aspect()->TextureMap().IsNull(),
          myUVOrigin,
          myUVRepeat,
          myUVScale);
        if (!aTriangles.IsNull())
        {
          if (aShadedGroup.IsNull())
          {
            aShadedGroup = thePrs->NewGroup();
            aShadedGroup->SetClosed(isClosed);
          }
          aShadedGroup->SetPrimitivesAspect(aDrawer->ShadingAspect()->Aspect());
          aShadedGroup->AddPrimitiveArray(aTriangles);
        }

        if (aDrawer->FaceBoundaryDraw())
        {
          if (occ::handle<Graphic3d_ArrayOfSegments> aBndSegments =
                StdPrs_ShadedShape::FillFaceBoundaries(aShapeDraw,
                                                       aDrawer->FaceBoundaryUpperContinuity()))
          {
            if (anEdgesGroup.IsNull())
            {
              anEdgesGroup = thePrs->NewGroup();
            }

            anEdgesGroup->SetPrimitivesAspect(aDrawer->FaceBoundaryAspect()->Aspect());
            anEdgesGroup->AddPrimitiveArray(aBndSegments);
          }
        }
      }
      else
      {
        StdPrs_WFShape::Add(thePrs, aShapeDraw, aDrawer);
      }
      aDrawer->SetTypeOfDeflection(aPrevType);
    }
  }
}

bool AIS_ColoredShape::dispatchColors(
  const occ::handle<AIS_ColoredDrawer>& theParentDrawer,
  const TopoDS_Shape&                   theShapeToParse,
  const NCollection_DataMap<TopoDS_Shape, occ::handle<AIS_ColoredDrawer>, TopTools_ShapeMapHasher>&
                         theShapeDrawerMap,
  const TopAbs_ShapeEnum theParentType,
  const bool             theIsParentClosed,
  DataMapOfDrawerCompd*  theDrawerOpenedShapePerType,
  DataMapOfDrawerCompd&  theDrawerClosedFaces)
{
  const TopAbs_ShapeEnum aShapeType = theShapeToParse.ShapeType();
  if (aShapeType == TopAbs_SHAPE)
  {
    return false;
  }

  occ::handle<AIS_ColoredDrawer> aDrawer     = theParentDrawer;
  const bool                     isOverriden = theShapeDrawerMap.Find(theShapeToParse, aDrawer);
  if (isOverriden && aDrawer->IsHidden())
  {
    return true;
  }

  bool isSubOverride = false;
  if (aShapeType <= TopAbs_SHELL)
  {

    bool isClosedShell = theParentType == TopAbs_SOLID && aShapeType == TopAbs_SHELL
                         && BRep_Tool::IsClosed(theShapeToParse)
                         && StdPrs_ToolTriangulatedShape::IsTriangulated(theShapeToParse);
    if (isClosedShell)
    {
      for (TopoDS_Iterator aFaceIter(theShapeToParse); aFaceIter.More(); aFaceIter.Next())
      {
        const TopoDS_Shape&            aFace = aFaceIter.Value();
        occ::handle<AIS_ColoredDrawer> aFaceDrawer;
        if (aFace.ShapeType() != TopAbs_FACE || !theShapeDrawerMap.Find(aFace, aFaceDrawer))
        {
          continue;
        }

        if (aFaceDrawer->IsHidden())
        {
          isClosedShell = false;
          break;
        }
        else if (aFaceDrawer->HasOwnShadingAspect()
                 && aFaceDrawer->ShadingAspect()->Aspect()->AlphaMode()
                      != Graphic3d_AlphaMode_Opaque)
        {
          if (aFaceDrawer->ShadingAspect()->Aspect()->AlphaMode() != Graphic3d_AlphaMode_BlendAuto
              || aFaceDrawer->ShadingAspect()->Aspect()->FrontMaterial().Alpha() < 1.0f
              || (aFaceDrawer->ShadingAspect()->Aspect()->Distinguish()
                  && aFaceDrawer->ShadingAspect()->Aspect()->BackMaterial().Alpha() < 1.0f))
          {
            isClosedShell = false;
            break;
          }
        }
      }
    }

    for (TopoDS_Iterator aSubShapeIter(theShapeToParse); aSubShapeIter.More(); aSubShapeIter.Next())
    {
      const TopoDS_Shape& aSubShape = aSubShapeIter.Value();
      if (dispatchColors(aDrawer,
                         aSubShape,
                         theShapeDrawerMap,
                         aShapeType,
                         isClosedShell,
                         theDrawerOpenedShapePerType,
                         theDrawerClosedFaces))
      {
        isSubOverride = true;
      }
    }
    return isOverriden || isSubOverride;
  }

  BRep_Builder aBBuilder;
  TopoDS_Shape aShapeCopy = theShapeToParse.EmptyCopied();
  aShapeCopy.Closed(theShapeToParse.Closed());
  int nbDef = 0;
  for (TopoDS_Iterator aSubShapeIter(theShapeToParse); aSubShapeIter.More(); aSubShapeIter.Next())
  {
    const TopoDS_Shape& aSubShape = aSubShapeIter.Value();
    if (dispatchColors(aDrawer,
                       aSubShape,
                       theShapeDrawerMap,
                       aShapeType,
                       theIsParentClosed,
                       theDrawerOpenedShapePerType,
                       theDrawerClosedFaces))
    {
      isSubOverride = true;
    }
    else
    {
      aBBuilder.Add(aShapeCopy, aSubShape);
      ++nbDef;
    }
  }
  if (aShapeType == TopAbs_FACE || !isSubOverride)
  {
    aShapeCopy = theShapeToParse;
  }
  else if (nbDef == 0)
  {
    return isOverriden || isSubOverride;
  }

  if (isOverriden || (isSubOverride && theParentType != TopAbs_WIRE && theParentType != TopAbs_FACE)
      || (theParentType <= TopAbs_SHELL && !(isOverriden || isSubOverride)))
  {
    TopoDS_Compound       aCompound;
    DataMapOfDrawerCompd& aDrawerShapeMap = theIsParentClosed && aShapeType == TopAbs_FACE
                                              ? theDrawerClosedFaces
                                              : theDrawerOpenedShapePerType[(size_t)aShapeType];
    if (!aDrawerShapeMap.FindFromKey(aDrawer, aCompound))
    {
      aBBuilder.MakeCompound(aCompound);
      aDrawerShapeMap.Add(aDrawer, aCompound);
    }
    aBBuilder.Add(aCompound, aShapeCopy);
  }
  return isOverriden || isSubOverride;
}

bool AIS_ColoredShape::isShapeEntirelyVisible() const
{
  for (NCollection_DataMap<TopoDS_Shape, occ::handle<AIS_ColoredDrawer>, TopTools_ShapeMapHasher>::
         Iterator aMapIter(myShapeColors);
       aMapIter.More();
       aMapIter.Next())
  {
    if (aMapIter.Value()->IsHidden())
    {
      return false;
    }
  }
  return true;
}

void AIS_ColoredShape::bindSubShapes(
  NCollection_DataMap<TopoDS_Shape, occ::handle<AIS_ColoredDrawer>, TopTools_ShapeMapHasher>&
                                        theShapeDrawerMap,
  const TopoDS_Shape&                   theKeyShape,
  const occ::handle<AIS_ColoredDrawer>& theDrawer) const
{
  TopAbs_ShapeEnum aShapeWithColorType = theKeyShape.ShapeType();
  if (aShapeWithColorType == TopAbs_COMPOUND)
  {
    theShapeDrawerMap.Bind(theKeyShape, theDrawer);
  }
  else if (aShapeWithColorType == TopAbs_SOLID || aShapeWithColorType == TopAbs_SHELL)
  {
    for (TopExp_Explorer anExp(theKeyShape, TopAbs_FACE); anExp.More(); anExp.Next())
    {
      if (!theShapeDrawerMap.IsBound(anExp.Current()))
      {
        theShapeDrawerMap.Bind(anExp.Current(), theDrawer);
      }
    }
  }
  else if (aShapeWithColorType == TopAbs_WIRE)
  {
    for (TopExp_Explorer anExp(theKeyShape, TopAbs_EDGE); anExp.More(); anExp.Next())
    {
      if (!theShapeDrawerMap.IsBound(anExp.Current()))
      {
        theShapeDrawerMap.Bind(anExp.Current(), theDrawer);
      }
    }
  }
  else
  {

    theShapeDrawerMap.Bind(theKeyShape, theDrawer);
  }
}

#pragma once

#include <Prs3d_Drawer.hpp>
#include <Quantity_Color.hpp>

class AIS_ColoredDrawer : public Prs3d_Drawer
{
  DEFINE_STANDARD_RTTIEXT(AIS_ColoredDrawer, Prs3d_Drawer)
public:
  AIS_ColoredDrawer(const occ::handle<Prs3d_Drawer>& theLink)
      : myIsHidden(false),
        myHasOwnMaterial(false),
        myHasOwnColor(false),
        myHasOwnTransp(false),
        myHasOwnWidth(false)
  {
    Link(theLink);
  }

  bool IsHidden() const { return myIsHidden; }

  void SetHidden(const bool theToHide) { myIsHidden = theToHide; }

  bool HasOwnMaterial() const { return myHasOwnMaterial; }

  void UnsetOwnMaterial() { myHasOwnMaterial = false; }

  void SetOwnMaterial() { myHasOwnMaterial = true; }

  bool HasOwnColor() const { return myHasOwnColor; }

  void UnsetOwnColor() { myHasOwnColor = false; }

  void SetOwnColor(const Quantity_Color&) { myHasOwnColor = true; }

  bool HasOwnTransparency() const { return myHasOwnTransp; }

  void UnsetOwnTransparency() { myHasOwnTransp = false; }

  void SetOwnTransparency(double) { myHasOwnTransp = true; }

  bool HasOwnWidth() const { return myHasOwnWidth; }

  void UnsetOwnWidth() { myHasOwnWidth = false; }

  void SetOwnWidth(const double) { myHasOwnWidth = true; }

public:
  bool myIsHidden;
  bool myHasOwnMaterial;
  bool myHasOwnColor;
  bool myHasOwnTransp;
  bool myHasOwnWidth;
};

#include <NCollection_DataMap.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <AIS_Shape.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <TopoDS_Compound.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_Map.hpp>

class StdSelect_BRepOwner;

class AIS_ColoredShape : public AIS_Shape
{
public:
  Standard_EXPORT AIS_ColoredShape(const TopoDS_Shape& theShape);

  Standard_EXPORT AIS_ColoredShape(const occ::handle<AIS_Shape>& theShape);

public:
  Standard_EXPORT virtual occ::handle<AIS_ColoredDrawer> CustomAspects(
    const TopoDS_Shape& theShape);

  Standard_EXPORT virtual void ClearCustomAspects();

  Standard_EXPORT void UnsetCustomAspects(const TopoDS_Shape& theShape,
                                          const bool          theToUnregister = false);

  Standard_EXPORT void SetCustomColor(const TopoDS_Shape& theShape, const Quantity_Color& theColor);

  Standard_EXPORT void SetCustomTransparency(const TopoDS_Shape& theShape, double theTransparency);

  Standard_EXPORT void SetCustomWidth(const TopoDS_Shape& theShape, const double theLineWidth);

  const NCollection_DataMap<TopoDS_Shape, occ::handle<AIS_ColoredDrawer>, TopTools_ShapeMapHasher>&
    CustomAspectsMap() const
  {
    return myShapeColors;
  }

  NCollection_DataMap<TopoDS_Shape, occ::handle<AIS_ColoredDrawer>, TopTools_ShapeMapHasher>&
    ChangeCustomAspectsMap()
  {
    return myShapeColors;
  }

public:
  Standard_EXPORT void SetColor(const Quantity_Color& theColor) override;

  Standard_EXPORT void SetWidth(const double theLineWidth) override;

  Standard_EXPORT void SetTransparency(const double theValue) override;

  Standard_EXPORT void SetMaterial(const Graphic3d_MaterialAspect& theAspect) override;

public:
  Standard_EXPORT void UnsetTransparency() override;

  Standard_EXPORT void UnsetWidth() override;

protected:
  Standard_EXPORT void Compute(const occ::handle<PrsMgr_PresentationManager>& thePrsMgr,
                               const occ::handle<Prs3d_Presentation>&         thePrs,
                               const int                                      theMode) override;

  Standard_EXPORT void ComputeSelection(const occ::handle<SelectMgr_Selection>& theSelection,
                                        const int                               theMode) override;

protected:
  typedef NCollection_IndexedDataMap<occ::handle<AIS_ColoredDrawer>, TopoDS_Compound>
    DataMapOfDrawerCompd;

protected:
  Standard_EXPORT static bool dispatchColors(
    const occ::handle<AIS_ColoredDrawer>&               theParentDrawer,
    const TopoDS_Shape&                                 theShapeToParse,
    const NCollection_DataMap<TopoDS_Shape,
                              occ::handle<AIS_ColoredDrawer>,
                              TopTools_ShapeMapHasher>& theShapeDrawerMap,
    const TopAbs_ShapeEnum                              theParentType,
    const bool                                          theIsParentClosed,
    DataMapOfDrawerCompd*                               theDrawerOpenedShapePerType,
    DataMapOfDrawerCompd&                               theDrawerClosedFaces);

protected:
  Standard_EXPORT void fillSubshapeDrawerMap(
    NCollection_DataMap<TopoDS_Shape, occ::handle<AIS_ColoredDrawer>, TopTools_ShapeMapHasher>&
      theSubshapeDrawerMap) const;

  Standard_EXPORT void addShapesWithCustomProps(
    const occ::handle<Prs3d_Presentation>& thePrs,
    const DataMapOfDrawerCompd*            theDrawerOpenedShapePerType,
    const DataMapOfDrawerCompd&            theDrawerClosedFaces,
    const int                              theMode);

  Standard_EXPORT bool isShapeEntirelyVisible() const;

  Standard_EXPORT void bindSubShapes(
    NCollection_DataMap<TopoDS_Shape, occ::handle<AIS_ColoredDrawer>, TopTools_ShapeMapHasher>&
                                          theShapeDrawerMap,
    const TopoDS_Shape&                   theKeyShape,
    const occ::handle<AIS_ColoredDrawer>& theDrawer) const;

  Standard_EXPORT void computeSubshapeSelection(
    const occ::handle<AIS_ColoredDrawer>&               theParentDrawer,
    const NCollection_DataMap<TopoDS_Shape,
                              occ::handle<AIS_ColoredDrawer>,
                              TopTools_ShapeMapHasher>& theShapeDrawerMap,
    const TopoDS_Shape&                                 theShape,
    const occ::handle<StdSelect_BRepOwner>&             theOwner,
    const occ::handle<SelectMgr_Selection>&             theSelection,
    const TopAbs_ShapeEnum                              theTypOfSel,
    const int                                           thePriority,
    const double                                        theDeflection,
    const double                                        theDeflAngle);

protected:
  NCollection_DataMap<TopoDS_Shape, occ::handle<AIS_ColoredDrawer>, TopTools_ShapeMapHasher>
    myShapeColors;

public:
  DEFINE_STANDARD_RTTIEXT(AIS_ColoredShape, AIS_Shape)
};

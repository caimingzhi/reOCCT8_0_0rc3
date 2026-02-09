#pragma once

#include <AIS_DisplayMode.hpp>
#include <AIS_InteractiveObject.hpp>
#include <Bnd_Box.hpp>
#include <TopoDS_Shape.hpp>
#include <Prs3d_Drawer.hpp>
#include <Prs3d_TypeOfHLR.hpp>

class AIS_Shape : public AIS_InteractiveObject
{
  DEFINE_STANDARD_RTTIEXT(AIS_Shape, AIS_InteractiveObject)
public:
  Standard_EXPORT AIS_Shape(const TopoDS_Shape& shap);

  int Signature() const override { return 0; }

  AIS_KindOfInteractive Type() const override { return AIS_KindOfInteractive_Shape; }

  bool AcceptShapeDecomposition() const override { return true; }

  bool AcceptDisplayMode(const int theMode) const override { return theMode >= 0 && theMode <= 2; }

  const TopoDS_Shape& Shape() const { return myshape; }

  void SetShape(const TopoDS_Shape& theShape)
  {
    myshape  = theShape;
    myCompBB = true;
  }

  void Set(const TopoDS_Shape& theShape) { SetShape(theShape); }

  Standard_EXPORT bool SetOwnDeviationCoefficient();

  Standard_EXPORT bool SetOwnDeviationAngle();

  Standard_EXPORT void SetOwnDeviationCoefficient(const double aCoefficient);

  Standard_EXPORT void SetAngleAndDeviation(const double anAngle);

  Standard_EXPORT double UserAngle() const;

  Standard_EXPORT void SetOwnDeviationAngle(const double anAngle);

  Standard_EXPORT bool OwnDeviationCoefficient(double& aCoefficient,
                                               double& aPreviousCoefficient) const;

  Standard_EXPORT bool OwnDeviationAngle(double& anAngle, double& aPreviousAngle) const;

  void SetTypeOfHLR(const Prs3d_TypeOfHLR theTypeOfHLR) { myDrawer->SetTypeOfHLR(theTypeOfHLR); }

  Prs3d_TypeOfHLR TypeOfHLR() const { return myDrawer->TypeOfHLR(); }

  Standard_EXPORT void SetColor(const Quantity_Color& theColor) override;

  Standard_EXPORT void UnsetColor() override;

  Standard_EXPORT void SetWidth(const double aValue) override;

  Standard_EXPORT void UnsetWidth() override;

  Standard_EXPORT void SetMaterial(const Graphic3d_MaterialAspect& aName) override;

  Standard_EXPORT void UnsetMaterial() override;

  Standard_EXPORT void SetTransparency(const double aValue = 0.6) override;

  Standard_EXPORT void UnsetTransparency() override;

  Standard_EXPORT virtual const Bnd_Box& BoundingBox();

  using AIS_InteractiveObject::BoundingBox;

  Standard_EXPORT void Color(Quantity_Color& aColor) const override;

  Standard_EXPORT Graphic3d_NameOfMaterial Material() const override;

  Standard_EXPORT double Transparency() const override;

  static TopAbs_ShapeEnum SelectionType(const int theSelMode)
  {
    switch (theSelMode)
    {
      case 1:
        return TopAbs_VERTEX;
      case 2:
        return TopAbs_EDGE;
      case 3:
        return TopAbs_WIRE;
      case 4:
        return TopAbs_FACE;
      case 5:
        return TopAbs_SHELL;
      case 6:
        return TopAbs_SOLID;
      case 7:
        return TopAbs_COMPSOLID;
      case 8:
        return TopAbs_COMPOUND;
      case 0:
        return TopAbs_SHAPE;
    }
    return TopAbs_SHAPE;
  }

  static int SelectionMode(const TopAbs_ShapeEnum theShapeType)
  {
    switch (theShapeType)
    {
      case TopAbs_VERTEX:
        return 1;
      case TopAbs_EDGE:
        return 2;
      case TopAbs_WIRE:
        return 3;
      case TopAbs_FACE:
        return 4;
      case TopAbs_SHELL:
        return 5;
      case TopAbs_SOLID:
        return 6;
      case TopAbs_COMPSOLID:
        return 7;
      case TopAbs_COMPOUND:
        return 8;
      case TopAbs_SHAPE:
        return 0;
    }
    return 0;
  }

public:
  const gp_Pnt2d& TextureRepeatUV() const { return myUVRepeat; }

  void SetTextureRepeatUV(const gp_Pnt2d& theRepeatUV) { myUVRepeat = theRepeatUV; }

  const gp_Pnt2d& TextureOriginUV() const { return myUVOrigin; }

  void SetTextureOriginUV(const gp_Pnt2d& theOriginUV) { myUVOrigin = theOriginUV; }

  const gp_Pnt2d& TextureScaleUV() const { return myUVScale; }

  void SetTextureScaleUV(const gp_Pnt2d& theScaleUV) { myUVScale = theScaleUV; }

protected:
  Standard_EXPORT void Compute(const occ::handle<PrsMgr_PresentationManager>& thePrsMgr,
                               const occ::handle<Prs3d_Presentation>&         thePrs,
                               const int                                      theMode) override;

  void computeHLR(const occ::handle<Graphic3d_Camera>&   theProjector,
                  const occ::handle<TopLoc_Datum3D>&     theTrsf,
                  const occ::handle<Prs3d_Presentation>& thePrs) override
  {
    if (!theTrsf.IsNull() && theTrsf->Form() != gp_Identity)
    {
      const TopLoc_Location& aLoc   = myshape.Location();
      const TopoDS_Shape     aShape = myshape.Located(TopLoc_Location(theTrsf->Trsf()) * aLoc);
      computeHlrPresentation(theProjector, thePrs, aShape, myDrawer);
    }
    else
    {
      computeHlrPresentation(theProjector, thePrs, myshape, myDrawer);
    }
  }

  Standard_EXPORT void ComputeSelection(const occ::handle<SelectMgr_Selection>& theSelection,
                                        const int                               theMode) override;

  Standard_EXPORT bool setColor(const occ::handle<Prs3d_Drawer>& theDrawer,
                                const Quantity_Color&            theColor) const;

  Standard_EXPORT bool setWidth(const occ::handle<Prs3d_Drawer>& theDrawer,
                                const double                     theWidth) const;

  Standard_EXPORT void setTransparency(const occ::handle<Prs3d_Drawer>& theDrawer,
                                       const double                     theValue) const;

  Standard_EXPORT void setMaterial(const occ::handle<Prs3d_Drawer>& theDrawer,
                                   const Graphic3d_MaterialAspect&  theMaterial,
                                   const bool                       theToKeepColor,
                                   const bool                       theToKeepTransp) const;

  Standard_EXPORT void replaceWithNewOwnAspects();

public:
  Standard_EXPORT static void computeHlrPresentation(
    const occ::handle<Graphic3d_Camera>&   theProjector,
    const occ::handle<Prs3d_Presentation>& thePrs,
    const TopoDS_Shape&                    theShape,
    const occ::handle<Prs3d_Drawer>&       theDrawer);

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

protected:
  TopoDS_Shape myshape;
  Bnd_Box      myBB;
  gp_Pnt2d     myUVOrigin;
  gp_Pnt2d     myUVRepeat;
  gp_Pnt2d     myUVScale;
  double       myInitAng;
  bool         myCompBB;
};

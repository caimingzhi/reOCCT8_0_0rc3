#pragma once

#include <AIS_InteractiveObject.hpp>
#include <Aspect_TypeOfLine.hpp>
#include <Aspect_TypeOfMarker.hpp>
#include <Bnd_Box.hpp>
#include <DsgPrs_ArrowSide.hpp>
#include <gp_Pln.hpp>
#include <gp_Pnt.hpp>
#include <PrsDim_KindOfDimension.hpp>
#include <PrsDim_KindOfSurface.hpp>
#include <TCollection_ExtendedString.hpp>
#include <TopoDS_Shape.hpp>

class Geom_Curve;
class Geom_Plane;
class Geom_Surface;
class TopoDS_Edge;
class TopoDS_Vertex;

class PrsDim_Relation : public AIS_InteractiveObject
{
  DEFINE_STANDARD_RTTIEXT(PrsDim_Relation, AIS_InteractiveObject)
public:
  Standard_EXPORT void SetColor(const Quantity_Color& theColor) override;

  Standard_EXPORT void UnsetColor() override;

  AIS_KindOfInteractive Type() const override { return AIS_KindOfInteractive_Relation; }

  virtual PrsDim_KindOfDimension KindOfDimension() const { return PrsDim_KOD_NONE; }

  virtual bool IsMovable() const { return false; }

  const TopoDS_Shape& FirstShape() const { return myFShape; }

  virtual void SetFirstShape(const TopoDS_Shape& aFShape) { myFShape = aFShape; }

  const TopoDS_Shape& SecondShape() const { return mySShape; }

  virtual void SetSecondShape(const TopoDS_Shape& aSShape) { mySShape = aSShape; }

  void SetBndBox(const double theXmin,
                 const double theYmin,
                 const double theZmin,
                 const double theXmax,
                 const double theYmax,
                 const double theZmax)
  {
    myBndBox.Update(theXmin, theYmin, theZmin, theXmax, theYmax, theZmax);
    myIsSetBndBox = true;
  }

  void UnsetBndBox() { myIsSetBndBox = false; }

  const occ::handle<Geom_Plane>& Plane() const { return myPlane; }

  void SetPlane(const occ::handle<Geom_Plane>& thePlane) { myPlane = thePlane; }

  double Value() const { return myVal; }

  void SetValue(const double theVal) { myVal = theVal; }

  const gp_Pnt& Position() const { return myPosition; }

  void SetPosition(const gp_Pnt& thePosition)
  {
    myPosition          = thePosition;
    myAutomaticPosition = false;
  }

  const TCollection_ExtendedString& Text() const { return myText; }

  void SetText(const TCollection_ExtendedString& theText) { myText = theText; }

  double ArrowSize() const { return myArrowSize; }

  void SetArrowSize(const double theArrowSize)
  {
    myArrowSize          = theArrowSize;
    myArrowSizeIsDefined = true;
  }

  DsgPrs_ArrowSide SymbolPrs() const { return mySymbolPrs; }

  void SetSymbolPrs(const DsgPrs_ArrowSide theSymbolPrs) { mySymbolPrs = theSymbolPrs; }

  void SetExtShape(const int theIndex) { myExtShape = theIndex; }

  int ExtShape() const { return myExtShape; }

  bool AcceptDisplayMode(const int theMode) const override { return theMode == 0; }

  void SetAutomaticPosition(const bool theStatus) { myAutomaticPosition = theStatus; }

  bool AutomaticPosition() const { return myAutomaticPosition; }

protected:
  Standard_EXPORT PrsDim_Relation(
    const PrsMgr_TypeOfPresentation3d aTypeOfPresentation3d = PrsMgr_TOP_AllView);

  Standard_EXPORT void ComputeProjEdgePresentation(
    const occ::handle<Prs3d_Presentation>& aPres,
    const TopoDS_Edge&                     anEdge,
    const occ::handle<Geom_Curve>&         ProjCurve,
    const gp_Pnt&                          FirstP,
    const gp_Pnt&                          LastP,
    const Quantity_NameOfColor             aColor   = Quantity_NOC_PURPLE,
    const double                           aWidth   = 2,
    const Aspect_TypeOfLine                aProjTOL = Aspect_TOL_DASH,
    const Aspect_TypeOfLine                aCallTOL = Aspect_TOL_DOT) const;

  Standard_EXPORT void ComputeProjVertexPresentation(
    const occ::handle<Prs3d_Presentation>& aPres,
    const TopoDS_Vertex&                   aVertex,
    const gp_Pnt&                          ProjPoint,
    const Quantity_NameOfColor             aColor   = Quantity_NOC_PURPLE,
    const double                           aWidth   = 2,
    const Aspect_TypeOfMarker              aProjTOM = Aspect_TOM_PLUS,
    const Aspect_TypeOfLine                aCallTOL = Aspect_TOL_DOT) const;

protected:
  TopoDS_Shape               myFShape;
  TopoDS_Shape               mySShape;
  occ::handle<Geom_Plane>    myPlane;
  double                     myVal;
  gp_Pnt                     myPosition;
  TCollection_ExtendedString myText;
  double                     myArrowSize;
  bool                       myAutomaticPosition;
  DsgPrs_ArrowSide           mySymbolPrs;
  int                        myExtShape;
  gp_Pln                     myFirstPlane;
  gp_Pln                     mySecondPlane;
  occ::handle<Geom_Surface>  myFirstBasisSurf;
  occ::handle<Geom_Surface>  mySecondBasisSurf;
  PrsDim_KindOfSurface       myFirstSurfType;
  PrsDim_KindOfSurface       mySecondSurfType;
  double                     myFirstOffset;
  double                     mySecondOffset;
  Bnd_Box                    myBndBox;
  bool                       myIsSetBndBox;
  bool                       myArrowSizeIsDefined;
};

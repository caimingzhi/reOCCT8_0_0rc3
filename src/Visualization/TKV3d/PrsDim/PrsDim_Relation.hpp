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

//! One of the four types of interactive object in
//! AIS,comprising dimensions and constraints. Serves
//! as the abstract class for the seven relation classes as
//! well as the seven dimension classes.
//! The statuses available for relations between shapes are as follows:
//! -   0 - there is no connection to a shape;
//! -   1 - there is a connection to the first shape;
//! -   2 - there is a connection to the second shape.
//! The connection takes the form of an edge between the two shapes.
class PrsDim_Relation : public AIS_InteractiveObject
{
  DEFINE_STANDARD_RTTIEXT(PrsDim_Relation, AIS_InteractiveObject)
public:
  //! Allows you to provide settings for the color theColor
  //! of the lines representing the relation between the two shapes.
  Standard_EXPORT void SetColor(const Quantity_Color& theColor) override;

  //! Allows you to remove settings for the color of the
  //! lines representing the relation between the two shapes.
  Standard_EXPORT void UnsetColor() override;

  AIS_KindOfInteractive Type() const override { return AIS_KindOfInteractive_Relation; }

  //! Indicates that the type of dimension is unknown.
  virtual PrsDim_KindOfDimension KindOfDimension() const { return PrsDim_KOD_NONE; }

  //! Returns true if the interactive object is movable.
  virtual bool IsMovable() const { return false; }

  const TopoDS_Shape& FirstShape() const { return myFShape; }

  virtual void SetFirstShape(const TopoDS_Shape& aFShape) { myFShape = aFShape; }

  //! Returns the second shape.
  const TopoDS_Shape& SecondShape() const { return mySShape; }

  //! Allows you to identify the second shape aSShape
  //! relative to the first.
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

  //! Returns the plane.
  const occ::handle<Geom_Plane>& Plane() const { return myPlane; }

  //! Allows you to set the plane thePlane. This is used to
  //! define relations and dimensions in several daughter classes.
  void SetPlane(const occ::handle<Geom_Plane>& thePlane) { myPlane = thePlane; }

  //! Returns the value of each object in the relation.
  double Value() const { return myVal; }

  //! Allows you to provide settings for the value theVal for each object in the relation.
  void SetValue(const double theVal) { myVal = theVal; }

  //! Returns the position set using SetPosition.
  const gp_Pnt& Position() const { return myPosition; }

  //! Allows you to provide the objects in the relation with
  //! settings for a non-default position.
  void SetPosition(const gp_Pnt& thePosition)
  {
    myPosition          = thePosition;
    myAutomaticPosition = false;
  }

  //! Returns settings for text aspect.
  const TCollection_ExtendedString& Text() const { return myText; }

  //! Allows you to provide the settings theText for text aspect.
  void SetText(const TCollection_ExtendedString& theText) { myText = theText; }

  //! Returns the value for the size of the arrow identifying
  //! the relation between the two shapes.
  double ArrowSize() const { return myArrowSize; }

  //! Allows you to provide settings for the size of the
  //! arrow theArrowSize identifying the relation between the two shapes.
  void SetArrowSize(const double theArrowSize)
  {
    myArrowSize          = theArrowSize;
    myArrowSizeIsDefined = true;
  }

  //! Returns the value of the symbol presentation. This will be one of:
  //! -   AS_NONE - none
  //! -   AS_FIRSTAR - first arrow
  //! -   AS_LASTAR - last arrow
  //! -   AS_BOTHAR - both arrows
  //! -   AS_FIRSTPT - first point
  //! -   AS_LASTPT - last point
  //! -   AS_BOTHPT - both points
  //! -   AS_FIRSTAR_LASTPT - first arrow, last point
  //! -   AS_FIRSTPT_LASTAR - first point, last arrow
  DsgPrs_ArrowSide SymbolPrs() const { return mySymbolPrs; }

  //! Allows you to provide settings for the symbol presentation.
  void SetSymbolPrs(const DsgPrs_ArrowSide theSymbolPrs) { mySymbolPrs = theSymbolPrs; }

  //! Allows you to set the status of the extension shape by
  //! the index aIndex.
  //! The status will be one of the following:
  //! -   0 - there is no connection to a shape;
  //! -   1 - there is a connection to the first shape;
  //! -   2 - there is a connection to the second shape.
  void SetExtShape(const int theIndex) { myExtShape = theIndex; }

  //! Returns the status index of the extension shape.
  int ExtShape() const { return myExtShape; }

  //! Returns true if the display mode aMode is accepted
  //! for the Interactive Objects in the relation.
  //! ComputeProjPresentation(me;
  //! aPres    : Presentation from Prs3d;
  //! Curve1   : Curve                from Geom;
  //! Curve2   : Curve                from Geom;
  //! FirstP1  : Pnt                  from gp;
  //! LastP1   : Pnt                  from gp;
  //! FirstP2  : Pnt                  from gp;
  //! LastP2   : Pnt                  from gp;
  //! aColor   : NameOfColor          from Quantity = Quantity_NOC_PURPLE;
  //! aWidth   : Real                 from Standard = 2;
  //! aProjTOL : TypeOfLine           from Aspect   = Aspect_TOL_DASH;
  //! aCallTOL : TypeOfLine           from Aspect   = Aspect_TOL_DOT)
  bool AcceptDisplayMode(const int theMode) const override { return theMode == 0; }

  void SetAutomaticPosition(const bool theStatus) { myAutomaticPosition = theStatus; }

  bool AutomaticPosition() const { return myAutomaticPosition; }

protected:
  Standard_EXPORT PrsDim_Relation(
    const PrsMgr_TypeOfPresentation3d aTypeOfPresentation3d = PrsMgr_TOP_AllView);

  //! Calculates the presentation aPres of the edge
  //! anEdge and the curve it defines, ProjCurve. The later
  //! is also specified by the first point FirstP and the last point LastP.
  //! The presentation includes settings for color aColor,
  //! type - aProjTOL and aCallTOL -   and width of line, aWidth.
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

  //! Calculates the presentation aPres of the vertex
  //! aVertex and the point it defines, ProjPoint.
  //! The presentation includes settings for color aColor,
  //! type - aProjTOM and aCallTOL -   and width of line, aWidth.
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

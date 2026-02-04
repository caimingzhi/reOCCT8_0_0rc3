#pragma once


#include <AIS_InteractiveObject.hpp>
#include <TCollection_AsciiString.hpp>

class AIS_Line;
class AIS_Point;
class Geom_Plane;

//! To construct a selectable 2d axis system in a 3d
//! drawing. This can be placed anywhere in the 3d
//! system, and provides a coordinate system for
//! drawing curves and shapes in a plane.
//! There are 3 selection modes:
//! -   mode 0   selection of the whole plane "trihedron"
//! -   mode 1   selection of the origin of the plane "trihedron"
//! -   mode 2   selection of the axes.
//! Warning
//! For the presentation of planes and trihedra, the
//! millimetre is default unit of length, and 100 the default
//! value for the representation of the axes. If you modify
//! these dimensions, you must temporarily recover the
//! Drawer object. From inside it, take the Aspects in
//! which the values for length are stocked, for example,
//! PlaneAspect for planes and LineAspect for
//! trihedra. Change these values and recalculate the presentation.
class AIS_PlaneTrihedron : public AIS_InteractiveObject
{
  DEFINE_STANDARD_RTTIEXT(AIS_PlaneTrihedron, AIS_InteractiveObject)
public:
  //! Initializes the plane aPlane. The plane trihedron is
  //! constructed from this and an axis.
  Standard_EXPORT AIS_PlaneTrihedron(const occ::handle<Geom_Plane>& aPlane);

  //! Returns the component specified in SetComponent.
  Standard_EXPORT occ::handle<Geom_Plane> Component();

  //! Creates an instance of the component object aPlane.
  Standard_EXPORT void SetComponent(const occ::handle<Geom_Plane>& aPlane);

  //! Returns the "XAxis".
  Standard_EXPORT occ::handle<AIS_Line> XAxis() const;

  //! Returns the "YAxis".
  Standard_EXPORT occ::handle<AIS_Line> YAxis() const;

  //! Returns the point of origin of the plane trihedron.
  Standard_EXPORT occ::handle<AIS_Point> Position() const;

  //! Sets the length of the X and Y axes.
  Standard_EXPORT void SetLength(const double theLength);

  //! Returns the length of X and Y axes.
  Standard_EXPORT double GetLength() const;

  //! Returns true if the display mode selected, aMode, is valid.
  Standard_EXPORT bool AcceptDisplayMode(const int aMode) const override;

  int Signature() const override { return 4; }

  //! Returns datum as the type of Interactive Object.
  AIS_KindOfInteractive Type() const override { return AIS_KindOfInteractive_Datum; }

  //! Allows you to provide settings for the color aColor.
  Standard_EXPORT void SetColor(const Quantity_Color& theColor) override;

  void SetXLabel(const TCollection_AsciiString& theLabel) { myXLabel = theLabel; }

  void SetYLabel(const TCollection_AsciiString& theLabel) { myYLabel = theLabel; }

protected:
  Standard_EXPORT void Compute(const occ::handle<PrsMgr_PresentationManager>& theprsMgr,
                               const occ::handle<Prs3d_Presentation>&         thePrs,
                               const int                                      theMode) override;

private:
  Standard_EXPORT void ComputeSelection(const occ::handle<SelectMgr_Selection>& theSel,
                                        const int                               theMode) override;

private:
  occ::handle<Geom_Plane>            myPlane;
  occ::handle<AIS_InteractiveObject> myShapes[3];
  TCollection_AsciiString            myXLabel;
  TCollection_AsciiString            myYLabel;
};


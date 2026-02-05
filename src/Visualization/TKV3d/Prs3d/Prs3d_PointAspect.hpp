#pragma once

#include <Prs3d_BasicAspect.hpp>
#include <Graphic3d_AspectMarker3d.hpp>
#include <Graphic3d_MarkerImage.hpp>

//! This class defines attributes for the points
//! The points are drawn using markers, whose size does not depend on
//! the zoom value of the views.
class Prs3d_PointAspect : public Prs3d_BasicAspect
{
  DEFINE_STANDARD_RTTIEXT(Prs3d_PointAspect, Prs3d_BasicAspect)
public:
  Standard_EXPORT Prs3d_PointAspect(const Aspect_TypeOfMarker theType,
                                    const Quantity_Color&     theColor,
                                    const double              theScale);

  //! Defines the user defined marker point.
  Standard_EXPORT Prs3d_PointAspect(const Quantity_Color&                            theColor,
                                    const int                                        theWidth,
                                    const int                                        theHeight,
                                    const occ::handle<NCollection_HArray1<uint8_t>>& theTexture);

  Prs3d_PointAspect(const occ::handle<Graphic3d_AspectMarker3d>& theAspect)
      : myAspect(theAspect)
  {
  }

  //! defines the color to be used when drawing a point.
  //! Default value: Quantity_NOC_YELLOW
  void SetColor(const Quantity_Color& theColor) { myAspect->SetColor(theColor); }

  //! defines the type of representation to be used when drawing a point.
  //! Default value: Aspect_TOM_PLUS
  void SetTypeOfMarker(const Aspect_TypeOfMarker theType) { myAspect->SetType(theType); }

  //! defines the size of the marker used when drawing a point.
  //! Default value: 1.
  void SetScale(const double theScale) { myAspect->SetScale(theScale); }

  const occ::handle<Graphic3d_AspectMarker3d>& Aspect() const { return myAspect; }

  void SetAspect(const occ::handle<Graphic3d_AspectMarker3d>& theAspect) { myAspect = theAspect; }

  //! Returns marker's texture size.
  void GetTextureSize(int& theWidth, int& theHeight) const
  {
    myAspect->GetTextureSize(theWidth, theHeight);
  }

  //! Returns marker's texture.
  const occ::handle<Graphic3d_MarkerImage>& GetTexture() const
  {
    return myAspect->GetMarkerImage();
  }

  //! Dumps the content of me into the stream
  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

protected:
  occ::handle<Graphic3d_AspectMarker3d> myAspect;
};

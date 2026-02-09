#pragma once

#include <Prs3d_BasicAspect.hpp>
#include <Graphic3d_AspectMarker3d.hpp>
#include <Graphic3d_MarkerImage.hpp>

class Prs3d_PointAspect : public Prs3d_BasicAspect
{
  DEFINE_STANDARD_RTTIEXT(Prs3d_PointAspect, Prs3d_BasicAspect)
public:
  Standard_EXPORT Prs3d_PointAspect(const Aspect_TypeOfMarker theType,
                                    const Quantity_Color&     theColor,
                                    const double              theScale);

  Standard_EXPORT Prs3d_PointAspect(const Quantity_Color&                            theColor,
                                    const int                                        theWidth,
                                    const int                                        theHeight,
                                    const occ::handle<NCollection_HArray1<uint8_t>>& theTexture);

  Prs3d_PointAspect(const occ::handle<Graphic3d_AspectMarker3d>& theAspect)
      : myAspect(theAspect)
  {
  }

  void SetColor(const Quantity_Color& theColor) { myAspect->SetColor(theColor); }

  void SetTypeOfMarker(const Aspect_TypeOfMarker theType) { myAspect->SetType(theType); }

  void SetScale(const double theScale) { myAspect->SetScale(theScale); }

  const occ::handle<Graphic3d_AspectMarker3d>& Aspect() const { return myAspect; }

  void SetAspect(const occ::handle<Graphic3d_AspectMarker3d>& theAspect) { myAspect = theAspect; }

  void GetTextureSize(int& theWidth, int& theHeight) const
  {
    myAspect->GetTextureSize(theWidth, theHeight);
  }

  const occ::handle<Graphic3d_MarkerImage>& GetTexture() const
  {
    return myAspect->GetMarkerImage();
  }

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

protected:
  occ::handle<Graphic3d_AspectMarker3d> myAspect;
};

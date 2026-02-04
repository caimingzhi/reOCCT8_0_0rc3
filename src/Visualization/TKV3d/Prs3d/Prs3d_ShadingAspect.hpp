#pragma once


#include <Aspect_TypeOfFacingModel.hpp>
#include <Graphic3d_AspectFillArea3d.hpp>
#include <Graphic3d_MaterialAspect.hpp>
#include <Prs3d_BasicAspect.hpp>

//! A framework to define the display of shading.
//! The attributes which make up this definition include:
//! -   fill aspect
//! -   color, and
//! -   material
class Prs3d_ShadingAspect : public Prs3d_BasicAspect
{
  DEFINE_STANDARD_RTTIEXT(Prs3d_ShadingAspect, Prs3d_BasicAspect)
public:
  //! Constructs an empty framework to display shading.
  Standard_EXPORT Prs3d_ShadingAspect();

  //! Constructor with initialization.
  Prs3d_ShadingAspect(const occ::handle<Graphic3d_AspectFillArea3d>& theAspect)
      : myAspect(theAspect)
  {
  }

  //! Change the polygons interior color and material ambient color.
  Standard_EXPORT void SetColor(const Quantity_Color&          aColor,
                                const Aspect_TypeOfFacingModel aModel = Aspect_TOFM_BOTH_SIDE);

  //! Change the polygons material aspect.
  Standard_EXPORT void SetMaterial(const Graphic3d_MaterialAspect& aMaterial,
                                   const Aspect_TypeOfFacingModel  aModel = Aspect_TOFM_BOTH_SIDE);

  //! Change the polygons transparency value.
  //! Warning : aValue must be in the range 0,1. 0 is the default (NO transparent)
  Standard_EXPORT void SetTransparency(
    const double                   aValue,
    const Aspect_TypeOfFacingModel aModel = Aspect_TOFM_BOTH_SIDE);

  //! Returns the polygons color.
  Standard_EXPORT const Quantity_Color& Color(
    const Aspect_TypeOfFacingModel aModel = Aspect_TOFM_FRONT_SIDE) const;

  //! Returns the polygons material aspect.
  Standard_EXPORT const Graphic3d_MaterialAspect& Material(
    const Aspect_TypeOfFacingModel aModel = Aspect_TOFM_FRONT_SIDE) const;

  //! Returns the polygons transparency value.
  Standard_EXPORT double Transparency(
    const Aspect_TypeOfFacingModel aModel = Aspect_TOFM_FRONT_SIDE) const;

  //! Returns the polygons aspect properties.
  const occ::handle<Graphic3d_AspectFillArea3d>& Aspect() const { return myAspect; }

  void SetAspect(const occ::handle<Graphic3d_AspectFillArea3d>& theAspect) { myAspect = theAspect; }

  //! Dumps the content of me into the stream
  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

protected:
  occ::handle<Graphic3d_AspectFillArea3d> myAspect;
};


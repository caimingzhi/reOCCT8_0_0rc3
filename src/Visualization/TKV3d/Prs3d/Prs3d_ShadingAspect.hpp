#pragma once

#include <Aspect_TypeOfFacingModel.hpp>
#include <Graphic3d_AspectFillArea3d.hpp>
#include <Graphic3d_MaterialAspect.hpp>
#include <Prs3d_BasicAspect.hpp>

class Prs3d_ShadingAspect : public Prs3d_BasicAspect
{
  DEFINE_STANDARD_RTTIEXT(Prs3d_ShadingAspect, Prs3d_BasicAspect)
public:
  Standard_EXPORT Prs3d_ShadingAspect();

  Prs3d_ShadingAspect(const occ::handle<Graphic3d_AspectFillArea3d>& theAspect)
      : myAspect(theAspect)
  {
  }

  Standard_EXPORT void SetColor(const Quantity_Color&          aColor,
                                const Aspect_TypeOfFacingModel aModel = Aspect_TOFM_BOTH_SIDE);

  Standard_EXPORT void SetMaterial(const Graphic3d_MaterialAspect& aMaterial,
                                   const Aspect_TypeOfFacingModel  aModel = Aspect_TOFM_BOTH_SIDE);

  Standard_EXPORT void SetTransparency(
    const double                   aValue,
    const Aspect_TypeOfFacingModel aModel = Aspect_TOFM_BOTH_SIDE);

  Standard_EXPORT const Quantity_Color& Color(
    const Aspect_TypeOfFacingModel aModel = Aspect_TOFM_FRONT_SIDE) const;

  Standard_EXPORT const Graphic3d_MaterialAspect& Material(
    const Aspect_TypeOfFacingModel aModel = Aspect_TOFM_FRONT_SIDE) const;

  Standard_EXPORT double Transparency(
    const Aspect_TypeOfFacingModel aModel = Aspect_TOFM_FRONT_SIDE) const;

  const occ::handle<Graphic3d_AspectFillArea3d>& Aspect() const { return myAspect; }

  void SetAspect(const occ::handle<Graphic3d_AspectFillArea3d>& theAspect) { myAspect = theAspect; }

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

protected:
  occ::handle<Graphic3d_AspectFillArea3d> myAspect;
};

#pragma once

#include <Aspect_GradientFillMethod.hpp>
#include <Aspect_FillMethod.hpp>
#include <Graphic3d_Camera.hpp>
#include <Graphic3d_TypeOfBackground.hpp>
#include <OpenGl_Aspects.hpp>
#include <OpenGl_PrimitiveArray.hpp>
#include <OpenGl_Vec.hpp>

class OpenGl_BackgroundArray : public OpenGl_PrimitiveArray
{
public:
  Standard_EXPORT OpenGl_BackgroundArray(const Graphic3d_TypeOfBackground theType);

  Standard_EXPORT void Render(const occ::handle<OpenGl_Workspace>& theWorkspace,
                              Graphic3d_Camera::Projection         theProjection) const;

  Standard_EXPORT bool IsDefined() const;

  Standard_EXPORT void SetTextureParameters(const Aspect_FillMethod theFillMethod);

  Standard_EXPORT void SetTextureFillMethod(const Aspect_FillMethod theFillMethod);

  Aspect_FillMethod TextureFillMethod() const { return myFillMethod; }

  Aspect_GradientFillMethod GradientFillMethod() const { return myGradientParams.type; }

  const NCollection_Vec4<float>& GradientColor(const int theIndex) const
  {
    return (&myGradientParams.color1)[theIndex];
  }

  Standard_EXPORT void SetGradientFillMethod(const Aspect_GradientFillMethod theType);

  Standard_EXPORT void SetGradientParameters(const Quantity_Color&           theColor1,
                                             const Quantity_Color&           theColor2,
                                             const Aspect_GradientFillMethod theType);

protected:
  struct OpenGl_GradientParameters
  {
    NCollection_Vec4<float>   color1;
    NCollection_Vec4<float>   color2;
    Aspect_GradientFillMethod type;
  };

protected:
  Standard_EXPORT bool init(const occ::handle<OpenGl_Workspace>& theWorkspace) const;

  Standard_EXPORT bool createGradientArray(const occ::handle<OpenGl_Context>& theCtx) const;

  Standard_EXPORT bool createTextureArray(const occ::handle<OpenGl_Workspace>& theWorkspace) const;

  Standard_EXPORT bool createCubeMapArray() const;

  Standard_EXPORT void invalidateData();

  using OpenGl_PrimitiveArray::Render;

protected:
  Graphic3d_TypeOfBackground        myType;
  Aspect_FillMethod                 myFillMethod;
  mutable OpenGl_GradientParameters myGradientParams;
  mutable int                       myViewWidth;
  mutable int                       myViewHeight;
  mutable bool                      myToUpdate;
};

#pragma once


#include <Aspect_GradientFillMethod.hpp>
#include <Aspect_FillMethod.hpp>
#include <Graphic3d_Camera.hpp>
#include <Graphic3d_TypeOfBackground.hpp>
#include <OpenGl_Aspects.hpp>
#include <OpenGl_PrimitiveArray.hpp>
#include <OpenGl_Vec.hpp>

//! Tool class for generating reusable data for
//! gradient or texture background rendering.
class OpenGl_BackgroundArray : public OpenGl_PrimitiveArray
{
public:
  //! Main constructor.
  Standard_EXPORT OpenGl_BackgroundArray(const Graphic3d_TypeOfBackground theType);

  //! Render primitives to the window
  Standard_EXPORT void Render(const occ::handle<OpenGl_Workspace>& theWorkspace,
                              Graphic3d_Camera::Projection         theProjection) const;

  //! Check if background parameters are set properly
  Standard_EXPORT bool IsDefined() const;

  //! Sets background texture parameters
  Standard_EXPORT void SetTextureParameters(const Aspect_FillMethod theFillMethod);

  //! Sets texture fill method
  Standard_EXPORT void SetTextureFillMethod(const Aspect_FillMethod theFillMethod);

  //! Gets background texture fill method
  Aspect_FillMethod TextureFillMethod() const { return myFillMethod; }

  //! Gets background gradient fill method
  Aspect_GradientFillMethod GradientFillMethod() const { return myGradientParams.type; }

  //! Returns color of gradient background for the given index.
  const NCollection_Vec4<float>& GradientColor(const int theIndex) const
  {
    return (&myGradientParams.color1)[theIndex];
  }

  //! Sets type of gradient fill method
  Standard_EXPORT void SetGradientFillMethod(const Aspect_GradientFillMethod theType);

  //! Sets background gradient parameters
  Standard_EXPORT void SetGradientParameters(const Quantity_Color&           theColor1,
                                             const Quantity_Color&           theColor2,
                                             const Aspect_GradientFillMethod theType);

protected: //! @name Internal structure for storing gradient parameters
  struct OpenGl_GradientParameters
  {
    NCollection_Vec4<float>   color1;
    NCollection_Vec4<float>   color2;
    Aspect_GradientFillMethod type;
  };

protected:
  //! Fill attributes arrays for background array according to its type:
  //! - for gradient background its attributes consist of colors and gradient coordinates
  //! - for texture one its attributes consist of position and texture coordinates.
  Standard_EXPORT bool init(const occ::handle<OpenGl_Workspace>& theWorkspace) const;

  //! Initializes gradient arrays.
  Standard_EXPORT bool createGradientArray(const occ::handle<OpenGl_Context>& theCtx) const;

  //! Initializes texture arrays.
  //! @param theWorkspace OpenGl workspace that stores texture in the current enabled face aspect.
  Standard_EXPORT bool createTextureArray(const occ::handle<OpenGl_Workspace>& theWorkspace) const;

  //! Initializes cubemap arrays.
  Standard_EXPORT bool createCubeMapArray() const;

  //! Marks array parameters as changed,
  //! on next rendering stage array data is to be updated.
  Standard_EXPORT void invalidateData();

  using OpenGl_PrimitiveArray::Render;

protected:
  // clang-format off
  Graphic3d_TypeOfBackground        myType;           //!< Type of background: texture or gradient.
  Aspect_FillMethod                 myFillMethod;     //!< Texture parameters
  mutable OpenGl_GradientParameters myGradientParams; //!< Gradient parameters
  mutable int          myViewWidth;      //!< view width  used for array initialization
  mutable int          myViewHeight;     //!< view height used for array initialization
  mutable bool          myToUpdate;       //!< Shows if array parameters were changed and data (myAttribs storage) is to be updated
  // clang-format on
};


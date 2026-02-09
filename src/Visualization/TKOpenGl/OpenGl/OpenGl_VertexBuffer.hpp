#pragma once

#include <OpenGl_Buffer.hpp>
#include <Graphic3d_Buffer.hpp>

class OpenGl_VertexBuffer : public OpenGl_Buffer
{
public:
  Standard_EXPORT OpenGl_VertexBuffer();

  Standard_EXPORT ~OpenGl_VertexBuffer() override;

  Standard_EXPORT unsigned int GetTarget() const override;

  Standard_EXPORT void BindVertexAttrib(const occ::handle<OpenGl_Context>& theGlCtx,
                                        const unsigned int                 theAttribLoc) const;

  Standard_EXPORT void UnbindVertexAttrib(const occ::handle<OpenGl_Context>& theGlCtx,
                                          const unsigned int                 theAttribLoc) const;

  void BindAttribute(const occ::handle<OpenGl_Context>& theCtx,
                     const Graphic3d_TypeOfAttribute    theMode) const
  {
    if (IsValid())
    {
      Bind(theCtx);
      bindAttribute(theCtx, theMode, static_cast<int>(myComponentsNb), myDataType, 0, myOffset);
    }
  }

  void UnbindAttribute(const occ::handle<OpenGl_Context>& theCtx,
                       const Graphic3d_TypeOfAttribute    theMode) const
  {
    if (IsValid())
    {
      Unbind(theCtx);
      unbindAttribute(theCtx, theMode);
    }
  }

public:
  Standard_EXPORT static void bindAttribute(const occ::handle<OpenGl_Context>& theGlCtx,
                                            const Graphic3d_TypeOfAttribute    theMode,
                                            const int                          theNbComp,
                                            const unsigned int                 theDataType,
                                            const int                          theStride,
                                            const void*                        theOffset);

  Standard_EXPORT static void unbindAttribute(const occ::handle<OpenGl_Context>& theGlCtx,
                                              const Graphic3d_TypeOfAttribute    theMode);

private:
  Standard_EXPORT static void bindFixed(const occ::handle<OpenGl_Context>& theGlCtx,
                                        const Graphic3d_TypeOfAttribute    theMode,
                                        const int                          theNbComp,
                                        const unsigned int                 theDataType,
                                        const int                          theStride,
                                        const void*                        theOffset);

  Standard_EXPORT static void unbindFixed(const occ::handle<OpenGl_Context>& theGlCtx,
                                          const Graphic3d_TypeOfAttribute    theMode);

  Standard_EXPORT static void unbindFixedColor(const occ::handle<OpenGl_Context>& theCtx);

public:
  Standard_EXPORT virtual bool HasColorAttribute() const;

  Standard_EXPORT virtual bool HasNormalAttribute() const;

  Standard_EXPORT virtual void BindAllAttributes(const occ::handle<OpenGl_Context>& theGlCtx) const;

  Standard_EXPORT virtual void BindPositionAttribute(
    const occ::handle<OpenGl_Context>& theGlCtx) const;

  Standard_EXPORT virtual void UnbindAllAttributes(
    const occ::handle<OpenGl_Context>& theGlCtx) const;

public:
  DEFINE_STANDARD_RTTIEXT(OpenGl_VertexBuffer, OpenGl_Buffer)
};

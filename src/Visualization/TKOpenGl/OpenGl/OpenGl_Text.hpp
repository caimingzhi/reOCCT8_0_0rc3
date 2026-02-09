#pragma once

#include <OpenGl_Element.hpp>

#include <OpenGl_TextBuilder.hpp>

#include <Graphic3d_RenderingParams.hpp>
#include <Graphic3d_Text.hpp>

class OpenGl_Text : public OpenGl_Element
{

public:
  Standard_EXPORT OpenGl_Text(const occ::handle<Graphic3d_Text>& theTextParams);

  Standard_EXPORT ~OpenGl_Text() override;

  Standard_EXPORT void Reset(const occ::handle<OpenGl_Context>& theCtx);

  const occ::handle<Graphic3d_Text>& Text() const { return myText; }

  void SetText(const occ::handle<Graphic3d_Text>& theText) { myText = theText; }

  bool Is2D() const { return myIs2d; }

  void Set2D(const bool theEnable) { myIs2d = theEnable; }

  Standard_EXPORT void SetFontSize(const occ::handle<OpenGl_Context>& theContext,
                                   const int                          theFontSize);

  Standard_EXPORT void Render(const occ::handle<OpenGl_Workspace>& theWorkspace) const override;
  Standard_EXPORT void Release(OpenGl_Context* theContext) override;

  Standard_EXPORT size_t EstimatedDataSize() const override;

  Standard_EXPORT void UpdateDrawStats(Graphic3d_FrameStatsDataTmp& theStats,
                                       bool                         theIsDetailed) const override;

public:
  Standard_EXPORT OpenGl_Text();

  Standard_EXPORT static TCollection_AsciiString FontKey(const OpenGl_Aspects& theAspect,
                                                         int                   theHeight,
                                                         unsigned int          theResolution,
                                                         Font_Hinting          theFontHinting);

  Standard_EXPORT static occ::handle<OpenGl_Font> FindFont(
    const occ::handle<OpenGl_Context>& theCtx,
    const OpenGl_Aspects&              theAspect,
    int                                theHeight,
    unsigned int                       theResolution,
    Font_Hinting                       theFontHinting,
    const TCollection_AsciiString&     theKey);

  Standard_EXPORT static void StringSize(const occ::handle<OpenGl_Context>& theCtx,
                                         const NCollection_String&          theText,
                                         const OpenGl_Aspects&              theTextAspect,
                                         const float                        theHeight,
                                         const unsigned int                 theResolution,
                                         const Font_Hinting                 theFontHinting,
                                         float&                             theWidth,
                                         float&                             theAscent,
                                         float&                             theDescent);

  Standard_EXPORT void Render(
    const occ::handle<OpenGl_Context>& theCtx,
    const OpenGl_Aspects&              theTextAspect,
    unsigned int theResolution  = Graphic3d_RenderingParams::THE_DEFAULT_RESOLUTION,
    Font_Hinting theFontHinting = Font_Hinting_Off) const;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

public:
  Standard_DEPRECATED(
    "Deprecated method Init() with obsolete arguments, use Init() and Text() instead of it")
  Standard_EXPORT void Init(const occ::handle<OpenGl_Context>& theCtx,
                            const char*                        theText,
                            const NCollection_Vec3<float>&     thePoint);

  Standard_DEPRECATED("Deprecated method SetPosition(), use Graphic3d_Text for it")
  Standard_EXPORT void SetPosition(const NCollection_Vec3<float>& thePoint);

protected:
  friend class OpenGl_Trihedron;
  friend class OpenGl_GraduatedTrihedron;

  Standard_EXPORT void releaseVbos(OpenGl_Context* theCtx);

private:
  void setupMatrix(const occ::handle<OpenGl_Context>& theCtx,
                   const OpenGl_Aspects&              theTextAspect,
                   const NCollection_Vec3<float>&     theDVec) const;

  void drawText(const occ::handle<OpenGl_Context>& theCtx,
                const OpenGl_Aspects&              theTextAspect) const;

  void drawRect(const occ::handle<OpenGl_Context>& theCtx,
                const OpenGl_Aspects&              theTextAspect,
                const NCollection_Vec4<float>&     theColorSubs) const;

  void render(const occ::handle<OpenGl_Context>& theCtx,
              const OpenGl_Aspects&              theTextAspect,
              const NCollection_Vec4<float>&     theColorText,
              const NCollection_Vec4<float>&     theColorSubs,
              unsigned int                       theResolution,
              Font_Hinting                       theFontHinting) const;

protected:
  occ::handle<Graphic3d_Text>                                  myText;
  mutable occ::handle<OpenGl_Font>                             myFont;
  mutable NCollection_Vector<GLuint>                           myTextures;
  mutable NCollection_Vector<occ::handle<OpenGl_VertexBuffer>> myVertsVbo;

  mutable NCollection_Vector<occ::handle<OpenGl_VertexBuffer>> myTCrdsVbo;
  mutable occ::handle<OpenGl_VertexBuffer>                     myBndVertsVbo;

  mutable Font_Rect myBndBox;

protected:
  mutable NCollection_Mat4<double> myProjMatrix;
  mutable NCollection_Mat4<double> myModelMatrix;
  mutable NCollection_Mat4<double> myOrientationMatrix;
  mutable NCollection_Vec3<double> myWinXYZ;
  mutable GLdouble                 myScaleHeight;

protected:
  bool myIs2d;

public:
  DEFINE_STANDARD_ALLOC
};

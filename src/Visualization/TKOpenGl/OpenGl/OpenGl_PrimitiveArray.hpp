#pragma once

#include <Graphic3d_TypeOfPrimitiveArray.hpp>
#include <Graphic3d_IndexBuffer.hpp>
#include <Graphic3d_BoundBuffer.hpp>

#include <OpenGl_Element.hpp>

class OpenGl_IndexBuffer;
class OpenGl_VertexBuffer;
class OpenGl_GraphicDriver;

class OpenGl_PrimitiveArray : public OpenGl_Element
{
public:
  enum
  {
    DRAW_MODE_NONE = -1
  };

  Standard_EXPORT OpenGl_PrimitiveArray(const OpenGl_GraphicDriver* theDriver);

  Standard_EXPORT OpenGl_PrimitiveArray(const OpenGl_GraphicDriver*               theDriver,
                                        const Graphic3d_TypeOfPrimitiveArray      theType,
                                        const occ::handle<Graphic3d_IndexBuffer>& theIndices,
                                        const occ::handle<Graphic3d_Buffer>&      theAttribs,
                                        const occ::handle<Graphic3d_BoundBuffer>& theBounds);

  Standard_EXPORT ~OpenGl_PrimitiveArray() override;

  Standard_EXPORT void Render(const occ::handle<OpenGl_Workspace>& theWorkspace) const override;

  Standard_EXPORT void Release(OpenGl_Context* theContext) override;

  Standard_EXPORT size_t EstimatedDataSize() const override;

  Standard_EXPORT void UpdateDrawStats(Graphic3d_FrameStatsDataTmp& theStats,
                                       bool                         theIsDetailed) const override;

  bool IsInitialized() const { return myIsVboInit; }

  void Invalidate() const { myIsVboInit = false; }

  int DrawMode() const { return myDrawMode; }

  bool IsFillDrawMode() const override { return myIsFillType; }

  const occ::handle<Graphic3d_IndexBuffer>& Indices() const { return myIndices; }

  const occ::handle<Graphic3d_Buffer>& Attributes() const { return myAttribs; }

  const occ::handle<Graphic3d_BoundBuffer>& Bounds() const { return myBounds; }

  size_t GetUID() const { return myUID; }

  Standard_EXPORT void InitBuffers(const occ::handle<OpenGl_Context>&        theContext,
                                   const Graphic3d_TypeOfPrimitiveArray      theType,
                                   const occ::handle<Graphic3d_IndexBuffer>& theIndices,
                                   const occ::handle<Graphic3d_Buffer>&      theAttribs,
                                   const occ::handle<Graphic3d_BoundBuffer>& theBounds);

public:
  const occ::handle<OpenGl_IndexBuffer>& IndexVbo() const { return myVboIndices; }

  const occ::handle<OpenGl_VertexBuffer>& AttributesVbo() const { return myVboAttribs; }

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

protected:
  Standard_EXPORT bool buildVBO(const occ::handle<OpenGl_Context>& theCtx,
                                const bool                         theToKeepData) const;

  Standard_EXPORT void updateVBO(const occ::handle<OpenGl_Context>& theCtx) const;

  Standard_EXPORT void clearMemoryGL(const occ::handle<OpenGl_Context>& theGlCtx) const;

private:
  bool initNormalVbo(const occ::handle<OpenGl_Context>& theCtx) const;

  void drawArray(const occ::handle<OpenGl_Workspace>& theWorkspace,
                 const NCollection_Vec4<float>*       theFaceColors,
                 const bool                           theHasVertColor) const;

  void drawEdges(const occ::handle<OpenGl_Workspace>& theWorkspace) const;

  void drawMarkers(const occ::handle<OpenGl_Workspace>& theWorkspace) const;

  void setDrawMode(const Graphic3d_TypeOfPrimitiveArray theType);

  bool processIndices(const occ::handle<OpenGl_Context>& theContext) const;

protected:
  mutable occ::handle<OpenGl_IndexBuffer>  myVboIndices;
  mutable occ::handle<OpenGl_VertexBuffer> myVboAttribs;

  mutable occ::handle<Graphic3d_IndexBuffer> myIndices;
  mutable occ::handle<Graphic3d_Buffer>      myAttribs;
  mutable occ::handle<Graphic3d_BoundBuffer> myBounds;
  short                                      myDrawMode;
  mutable bool                               myIsFillType;
  mutable bool                               myIsVboInit;

  size_t myUID;

public:
  DEFINE_STANDARD_ALLOC
};

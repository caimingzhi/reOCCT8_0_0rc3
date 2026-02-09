#pragma once

#include <OpenGl_Font.hpp>
#include <OpenGl_VertexBuffer.hpp>

#include <OpenGl_Buffer.hpp>
#include <OpenGl_Context.hpp>

#include <NCollection_Array1.hpp>

template <typename theVec_t>
class OpenGl_VertexBufferEditor
{

public:
  explicit OpenGl_VertexBufferEditor(const int theTmpBufferLength = 0)
      : myElemFrom(0),
        myElemsNb(0),
        myTmpBuffer(0, theTmpBufferLength > 0 ? (theTmpBufferLength - 1) : 2047)
  {
  }

  OpenGl_VertexBufferEditor(theVec_t* theTmpBuffer, const int theTmpBufferLength)
      : myElemFrom(0),
        myElemsNb(0),
        myTmpBuffer(theTmpBuffer[0], 0, theTmpBufferLength - 1)
  {
  }

  bool Init(const occ::handle<OpenGl_Context>& theGlCtx, const occ::handle<OpenGl_Buffer>& theVbo)
  {
    myGlCtx = theGlCtx;
    myVbo   = theVbo;
    if (myGlCtx.IsNull() || myVbo.IsNull() || !myVbo->IsValid()
        || myVbo->GetComponentsNb() != GLuint(theVec_t::Length()))
    {
      return false;
    }

    myElemFrom = myElemsNb = 0;
    return true;
  }

  theVec_t& Value() { return myTmpBuffer.ChangeValue(myElemsNb); }

  bool Next()
  {
    if (++myElemsNb > myTmpBuffer.Upper())
    {
      return Flush();
    }
    return true;
  }

  bool Flush()
  {
    if (myElemsNb <= 0)
    {
      return true;
    }

    if (myVbo.IsNull() || !myVbo->SubData(myGlCtx, myElemFrom, myElemsNb, &myTmpBuffer.Value(0)[0]))
    {

      return false;
    }
    myElemFrom += myElemsNb;
    myElemsNb = 0;

    return true;
  }

  const occ::handle<OpenGl_Buffer>& GetVBO() const { return myVbo; }

private:
  occ::handle<OpenGl_Context>  myGlCtx;
  occ::handle<OpenGl_Buffer>   myVbo;
  int                          myElemFrom;
  int                          myElemsNb;
  NCollection_Array1<theVec_t> myTmpBuffer;
};

#include <OpenGl_Vec.hpp>

#include <NCollection_Vector.hpp>
#include <NCollection_Handle.hpp>

class Font_TextFormatter;

class OpenGl_TextBuilder
{
public:
  Standard_EXPORT OpenGl_TextBuilder();

  Standard_EXPORT void Perform(
    const occ::handle<Font_TextFormatter>&                theFormatter,
    const occ::handle<OpenGl_Context>&                    theContext,
    OpenGl_Font&                                          theFont,
    NCollection_Vector<GLuint>&                           theTextures,
    NCollection_Vector<occ::handle<OpenGl_VertexBuffer>>& theVertsPerTexture,
    NCollection_Vector<occ::handle<OpenGl_VertexBuffer>>& theTCrdsPerTexture);

protected:
  Standard_EXPORT void createGlyphs(
    const occ::handle<Font_TextFormatter>& theFormatter,
    const occ::handle<OpenGl_Context>&     theCtx,
    OpenGl_Font&                           theFont,
    NCollection_Vector<GLuint>&            theTextures,
    NCollection_Vector<NCollection_Handle<NCollection_Vector<NCollection_Vec2<float>>>>&
      theVertsPerTexture,
    NCollection_Vector<NCollection_Handle<NCollection_Vector<NCollection_Vec2<float>>>>&
      theTCrdsPerTexture);

protected:
  NCollection_Vector<OpenGl_Font::Tile>              myTileRects;
  OpenGl_VertexBufferEditor<NCollection_Vec2<float>> myVboEditor;
};

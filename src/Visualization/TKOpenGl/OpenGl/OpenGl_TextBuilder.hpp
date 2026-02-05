#pragma once

#include <OpenGl_Font.hpp>
#include <OpenGl_VertexBuffer.hpp>

#include <OpenGl_Buffer.hpp>
#include <OpenGl_Context.hpp>

#include <NCollection_Array1.hpp>

//! Auxiliary class to iteratively modify data of existing VBO.
//! It provides iteration interface with delayed CPU->GPU memory transfer to avoid slow per-element
//! data transfer. User should explicitly call Flush() method to ensure that all data is transferred
//! to VBO. Temporary buffer on CPU side can be initialized with lesser capacity than VBO to allow
//! re-usage of shared buffer with fixed size between VBOs.
//!
//! You should use NCollection_Vec2/NCollection_Vec3/NCollection_Vec4 with appropriate length
//! to instantiate this template and access elements in VBO.
//!
//! Notice that this technique designed for VBO streaming scenarios (when VBO is modified from time
//! to time). Also this class doesn't retrieve existing data from VBO - data transferred only in one
//! direction! In case of static data this is preferred to upload it within one call during VBO
//! initialization.
template <typename theVec_t>
class OpenGl_VertexBufferEditor
{

public:
  //! Creates empty editor
  //! theTmpBufferLength[in]  temporary buffer length
  explicit OpenGl_VertexBufferEditor(const int theTmpBufferLength = 0)
      : myElemFrom(0),
        myElemsNb(0),
        myTmpBuffer(0, theTmpBufferLength > 0 ? (theTmpBufferLength - 1) : 2047)
  {
  }

  //! Creates empty editor
  //! theTmpBuffer[in]        pointer to temporary buffer
  //! theTmpBufferLength[in]  temporary buffer length
  OpenGl_VertexBufferEditor(theVec_t* theTmpBuffer, const int theTmpBufferLength)
      : myElemFrom(0),
        myElemsNb(0),
        myTmpBuffer(theTmpBuffer[0], 0, theTmpBufferLength - 1)
  {
  }

  //! Initialize editor for specified buffer object.
  //! theGlCtx[in]  bound OpenGL context to edit buffer object
  //! theVbo[in]    buffer to edit
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

  //! Modify current element in VBO.
  theVec_t& Value() { return myTmpBuffer.ChangeValue(myElemsNb); }

  //! Move to the next position in VBO.
  bool Next()
  {
    if (++myElemsNb > myTmpBuffer.Upper())
    {
      return Flush();
    }
    return true;
  }

  //! Push current data from local buffer to VBO.
  bool Flush()
  {
    if (myElemsNb <= 0)
    {
      return true;
    }

    if (myVbo.IsNull() || !myVbo->SubData(myGlCtx, myElemFrom, myElemsNb, &myTmpBuffer.Value(0)[0]))
    {
      // should never happens
      return false;
    }
    myElemFrom += myElemsNb;
    myElemsNb = 0;

    return true;
  }

  //! @return assigned VBO
  const occ::handle<OpenGl_Buffer>& GetVBO() const { return myVbo; }

private:
  occ::handle<OpenGl_Context>  myGlCtx;     //!< handle to current OpenGL context
  occ::handle<OpenGl_Buffer>   myVbo;       //!< edited VBO
  int                          myElemFrom;  //!< element in VBO to upload from
  int                          myElemsNb;   //!< current element in temporary buffer
  NCollection_Array1<theVec_t> myTmpBuffer; //!< temporary array
};

#include <OpenGl_Vec.hpp>

#include <NCollection_Vector.hpp>
#include <NCollection_Handle.hpp>

class Font_TextFormatter;

//! This class generates primitive array required for rendering textured text using OpenGl_Font
//! instance.
class OpenGl_TextBuilder
{
public:
  //! Creates empty object.
  Standard_EXPORT OpenGl_TextBuilder();

  //! Creates texture quads for the given text.
  Standard_EXPORT void Perform(
    const occ::handle<Font_TextFormatter>&                theFormatter,
    const occ::handle<OpenGl_Context>&                    theContext,
    OpenGl_Font&                                          theFont,
    NCollection_Vector<GLuint>&                           theTextures,
    NCollection_Vector<occ::handle<OpenGl_VertexBuffer>>& theVertsPerTexture,
    NCollection_Vector<occ::handle<OpenGl_VertexBuffer>>& theTCrdsPerTexture);

protected: //! @name class auxiliary methods
  Standard_EXPORT void createGlyphs(
    const occ::handle<Font_TextFormatter>& theFormatter,
    const occ::handle<OpenGl_Context>&     theCtx,
    OpenGl_Font&                           theFont,
    NCollection_Vector<GLuint>&            theTextures,
    NCollection_Vector<NCollection_Handle<NCollection_Vector<NCollection_Vec2<float>>>>&
      theVertsPerTexture,
    NCollection_Vector<NCollection_Handle<NCollection_Vector<NCollection_Vec2<float>>>>&
      theTCrdsPerTexture);

protected: //! @name class auxiliary fields
  NCollection_Vector<OpenGl_Font::Tile>              myTileRects;
  OpenGl_VertexBufferEditor<NCollection_Vec2<float>> myVboEditor;
};

#pragma once


#include <Standard_Type.hpp>

class Graphic3d_FrameStatsDataTmp;
class OpenGl_Workspace;
class OpenGl_Context;

//! Base interface for drawable elements.
class OpenGl_Element
{
public:
  Standard_EXPORT OpenGl_Element();

  virtual void Render(const occ::handle<OpenGl_Workspace>& theWorkspace) const = 0;

  //! Release GPU resources.
  //! Pointer to the context is used because this method might be called
  //! when the context is already being destroyed and usage of a handle
  //! would be unsafe
  virtual void Release(OpenGl_Context* theContext) = 0;

  //! Pointer to the context is used because this method might be called
  //! when the context is already being destroyed and usage of a handle
  //! would be unsafe
  template <typename theResource_t>
  static void Destroy(OpenGl_Context* theContext, theResource_t*& theElement)
  {
    if (theElement == nullptr)
    {
      return;
    }

    theElement->Release(theContext);
    OpenGl_Element* anElement = theElement;
    delete anElement;
    theElement = nullptr;
  }

public:
  //! Return TRUE if primitive type generates shaded triangulation (to be used in filters).
  virtual bool IsFillDrawMode() const { return false; }

  //! Returns estimated GPU memory usage for holding data without considering overheads and
  //! allocation alignment rules.
  virtual size_t EstimatedDataSize() const { return 0; }

  //! Increment memory usage statistics.
  //! Default implementation puts EstimatedDataSize() into
  //! Graphic3d_FrameStatsCounter_EstimatedBytesGeom.
  Standard_EXPORT virtual void UpdateMemStats(Graphic3d_FrameStatsDataTmp& theStats) const;

  //! Increment draw calls statistics.
  //! @param[in][out] theStats   frame counters to increment
  //! @param[in] theIsDetailed   indicate detailed dump (more counters - number of triangles,
  //! points, etc.)
  Standard_EXPORT virtual void UpdateDrawStats(Graphic3d_FrameStatsDataTmp& theStats,
                                               bool                         theIsDetailed) const;

  //! Update parameters of the drawable elements.
  virtual void SynchronizeAspects() {}

  //! Dumps the content of me into the stream
  Standard_EXPORT virtual void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

protected:
  Standard_EXPORT virtual ~OpenGl_Element();

public:
  DEFINE_STANDARD_ALLOC
};


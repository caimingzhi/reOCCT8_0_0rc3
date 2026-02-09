#pragma once

#include <Standard_Type.hpp>

class Graphic3d_FrameStatsDataTmp;
class OpenGl_Workspace;
class OpenGl_Context;

class OpenGl_Element
{
public:
  Standard_EXPORT OpenGl_Element();

  virtual void Render(const occ::handle<OpenGl_Workspace>& theWorkspace) const = 0;

  virtual void Release(OpenGl_Context* theContext) = 0;

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
  virtual bool IsFillDrawMode() const { return false; }

  virtual size_t EstimatedDataSize() const { return 0; }

  Standard_EXPORT virtual void UpdateMemStats(Graphic3d_FrameStatsDataTmp& theStats) const;

  Standard_EXPORT virtual void UpdateDrawStats(Graphic3d_FrameStatsDataTmp& theStats,
                                               bool                         theIsDetailed) const;

  virtual void SynchronizeAspects() {}

  Standard_EXPORT virtual void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

protected:
  Standard_EXPORT virtual ~OpenGl_Element();

public:
  DEFINE_STANDARD_ALLOC
};

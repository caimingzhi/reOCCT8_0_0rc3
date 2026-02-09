#pragma once

#include <OpenGl_Element.hpp>
#include <OpenGl_Vec.hpp>

class gp_Ax2;

class OpenGl_Flipper : public OpenGl_Element
{
public:
  Standard_EXPORT OpenGl_Flipper(const gp_Ax2& theReferenceSystem);

  void SetOptions(const bool theIsEnabled) { myIsEnabled = theIsEnabled; }

  Standard_EXPORT void Render(const occ::handle<OpenGl_Workspace>& theWorkspace) const override;
  Standard_EXPORT void Release(OpenGl_Context* theCtx) override;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

public:
  DEFINE_STANDARD_ALLOC

protected:
  NCollection_Vec4<float> myReferenceOrigin;
  NCollection_Vec4<float> myReferenceX;
  NCollection_Vec4<float> myReferenceY;
  NCollection_Vec4<float> myReferenceZ;
  bool                    myIsEnabled;
};

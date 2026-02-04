#pragma once


#include <OpenGl_Element.hpp>
#include <OpenGl_Vec.hpp>

class gp_Ax2;

//! Being rendered, the elements modifies current model-view matrix such that the axes of
//! the specified reference system (in model space) become oriented in the following way:
//! - X    - heads to the right side of view.
//! - Y    - heads to the up side of view.
//! - N(Z) - heads towards the screen.
//! Originally, this element serves for need of flipping the 3D text of dimension presentations.
class OpenGl_Flipper : public OpenGl_Element
{
public:
  //! Construct rendering element to flip model-view matrix
  //! along the reference system to ensure up-Y, right-X orientation.
  //! @param[in] theReferenceSystem  the reference coordinate system.
  Standard_EXPORT OpenGl_Flipper(const gp_Ax2& theReferenceSystem);

  //! Set options for the element.
  //! @param[in] theIsEnabled  flag indicates whether the flipper
  //! matrix modification should be set up or restored back.
  void SetOptions(const bool theIsEnabled) { myIsEnabled = theIsEnabled; }

  Standard_EXPORT void Render(const occ::handle<OpenGl_Workspace>& theWorkspace) const override;
  Standard_EXPORT void Release(OpenGl_Context* theCtx) override;

  //! Dumps the content of me into the stream
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


#pragma once

#include <OpenGl_Resource.hpp>

#include <Graphic3d_HatchStyle.hpp>
#include <NCollection_DataMap.hpp>

class OpenGl_Context;

//! Utility class to manage OpenGL resources of polygon hatching styles.
//! @note the implementation is not supported by Core Profile and by ES version.
class OpenGl_LineAttributes : public OpenGl_Resource
{
  DEFINE_STANDARD_RTTIEXT(OpenGl_LineAttributes, OpenGl_Resource)
public:
  //! Default constructor.
  Standard_EXPORT OpenGl_LineAttributes();

  //! Default destructor.
  Standard_EXPORT ~OpenGl_LineAttributes() override;

  //! Release GL resources.
  Standard_EXPORT void Release(OpenGl_Context* theGlCtx) override;

  //! Returns estimated GPU memory usage - not implemented.
  size_t EstimatedDataSize() const override { return 0; }

  //! Sets type of the hatch.
  Standard_EXPORT bool SetTypeOfHatch(const OpenGl_Context*                    theGlCtx,
                                      const occ::handle<Graphic3d_HatchStyle>& theStyle);

private:
  unsigned int init(const OpenGl_Context*                    theGlCtx,
                    const occ::handle<Graphic3d_HatchStyle>& theStyle);

protected:
  NCollection_DataMap<occ::handle<Graphic3d_HatchStyle>, unsigned int> myStyles; //!< Hatch patterns
};

#pragma once

#include <OpenGl_Resource.hpp>

#include <Graphic3d_HatchStyle.hpp>
#include <NCollection_DataMap.hpp>

class OpenGl_Context;

class OpenGl_LineAttributes : public OpenGl_Resource
{
  DEFINE_STANDARD_RTTIEXT(OpenGl_LineAttributes, OpenGl_Resource)
public:
  Standard_EXPORT OpenGl_LineAttributes();

  Standard_EXPORT ~OpenGl_LineAttributes() override;

  Standard_EXPORT void Release(OpenGl_Context* theGlCtx) override;

  size_t EstimatedDataSize() const override { return 0; }

  Standard_EXPORT bool SetTypeOfHatch(const OpenGl_Context*                    theGlCtx,
                                      const occ::handle<Graphic3d_HatchStyle>& theStyle);

private:
  unsigned int init(const OpenGl_Context*                    theGlCtx,
                    const occ::handle<Graphic3d_HatchStyle>& theStyle);

protected:
  NCollection_DataMap<occ::handle<Graphic3d_HatchStyle>, unsigned int> myStyles;
};

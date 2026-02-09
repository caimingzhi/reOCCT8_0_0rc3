#pragma once

#include <OpenGl_GraphicDriverFactory.hpp>

class D3DHost_GraphicDriverFactory : public OpenGl_GraphicDriverFactory
{
  DEFINE_STANDARD_RTTIEXT(D3DHost_GraphicDriverFactory, OpenGl_GraphicDriverFactory)
public:
  Standard_EXPORT D3DHost_GraphicDriverFactory();

  Standard_EXPORT virtual occ::handle<Graphic3d_GraphicDriver> CreateDriver(
    const occ::handle<Aspect_DisplayConnection>& theDisp) override;
};

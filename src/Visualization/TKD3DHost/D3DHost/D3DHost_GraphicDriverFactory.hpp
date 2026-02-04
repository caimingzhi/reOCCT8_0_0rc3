#pragma once


#include <OpenGl_GraphicDriverFactory.hpp>

//! This class for creation of D3DHost_GraphicDriver.
class D3DHost_GraphicDriverFactory : public OpenGl_GraphicDriverFactory
{
  DEFINE_STANDARD_RTTIEXT(D3DHost_GraphicDriverFactory, OpenGl_GraphicDriverFactory)
public:
  //! Empty constructor.
  Standard_EXPORT D3DHost_GraphicDriverFactory();

  //! Creates new empty graphic driver.
  Standard_EXPORT virtual occ::handle<Graphic3d_GraphicDriver> CreateDriver(
    const occ::handle<Aspect_DisplayConnection>& theDisp) override;
};


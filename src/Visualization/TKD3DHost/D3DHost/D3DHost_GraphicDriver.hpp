#pragma once

#include <OpenGl_GraphicDriver.hpp>

class D3DHost_GraphicDriver : public OpenGl_GraphicDriver
{
public:
  Standard_EXPORT D3DHost_GraphicDriver();

  Standard_EXPORT virtual ~D3DHost_GraphicDriver();

  Standard_EXPORT virtual occ::handle<Graphic3d_CView> CreateView(
    const occ::handle<Graphic3d_StructureManager>& theMgr) override;

public:
  DEFINE_STANDARD_RTTIEXT(D3DHost_GraphicDriver, OpenGl_GraphicDriver)
};

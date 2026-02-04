#pragma once


#include <OpenGl_GraphicDriver.hpp>

//! This class defines D3D host for an OpenGl graphic driver
class D3DHost_GraphicDriver : public OpenGl_GraphicDriver
{
public:
  //! Constructor.
  Standard_EXPORT D3DHost_GraphicDriver();

  //! Destructor.
  Standard_EXPORT virtual ~D3DHost_GraphicDriver();

  //! Create instance of D3D host view.
  Standard_EXPORT virtual occ::handle<Graphic3d_CView> CreateView(
    const occ::handle<Graphic3d_StructureManager>& theMgr) override;

public:
  DEFINE_STANDARD_RTTIEXT(D3DHost_GraphicDriver, OpenGl_GraphicDriver)
};


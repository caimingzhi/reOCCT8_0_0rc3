#pragma once

#include <Standard_Type.hpp>
#include <Standard_Transient.hpp>

//! @class IVtk_Interface
//! @brief Base interface for visualisation component.
//!
//! It is a handle class ("smart" pointer). IVtk_Interface is a base class for OCC interfaces
//! for VTK classes, such as interface for shape objects (IVtk_IShape) and view(IVtk_IView),
//! shape triangulation (IVtk_IShapeData, IVtk_IShapeMesher) and picking (IVtk_IShapePickerAlgo).
class IVtk_Interface : public Standard_Transient
{

public:
  typedef occ::handle<IVtk_Interface> Handle;
  DEFINE_STANDARD_RTTIEXT(IVtk_Interface, Standard_Transient)

  ~IVtk_Interface() override = default;
};

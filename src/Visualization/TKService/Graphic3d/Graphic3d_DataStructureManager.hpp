#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>

class Graphic3d_Camera;

//! This class allows the definition of a manager to
//! which the graphic objects are associated.
//! It allows them to be globally manipulated.
//! It defines the global attributes.
class Graphic3d_DataStructureManager : public Standard_Transient
{

  DEFINE_STANDARD_RTTIEXT(Graphic3d_DataStructureManager, Standard_Transient)
protected:
  //! Initializes the manager <me>.
  Standard_EXPORT Graphic3d_DataStructureManager();

  //! Returns camera object of the view.
  virtual const occ::handle<Graphic3d_Camera>& Camera() const = 0;

  //! Dumps the content of me into the stream
  Standard_EXPORT virtual void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;
};

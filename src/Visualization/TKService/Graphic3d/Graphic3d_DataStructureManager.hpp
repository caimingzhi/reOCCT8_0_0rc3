#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>

class Graphic3d_Camera;

class Graphic3d_DataStructureManager : public Standard_Transient
{

  DEFINE_STANDARD_RTTIEXT(Graphic3d_DataStructureManager, Standard_Transient)
protected:
  Standard_EXPORT Graphic3d_DataStructureManager();

  virtual const occ::handle<Graphic3d_Camera>& Camera() const = 0;

  Standard_EXPORT virtual void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;
};

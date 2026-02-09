#pragma once

#include <Standard.hpp>
#include <Standard_OStream.hpp>
#include <Standard_Type.hpp>
#include <Standard_Transient.hpp>

class Prs3d_BasicAspect : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(Prs3d_BasicAspect, Standard_Transient)

  virtual void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const = 0;
};

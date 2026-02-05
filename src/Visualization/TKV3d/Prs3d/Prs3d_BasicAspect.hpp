#pragma once

#include <Standard.hpp>
#include <Standard_OStream.hpp>
#include <Standard_Type.hpp>
#include <Standard_Transient.hpp>

//! All basic Prs3d_xxxAspect must inherits from this class
//! The aspect classes qualifies how to represent a given kind of object.
class Prs3d_BasicAspect : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(Prs3d_BasicAspect, Standard_Transient)

  //! Dumps the content of me into the stream
  virtual void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const = 0;
};

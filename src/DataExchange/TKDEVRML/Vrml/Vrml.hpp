#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_OStream.hpp>
#include <Standard_CString.hpp>

//! Vrml package implements the specification of the
//! VRML (Virtual Reality Modeling Language ). VRML
//! is a standard language for describing interactive
//! 3-D objects and worlds delivered across Internet.
//! Actual version of Vrml package have made for objects
//! of VRML version 1.0.
//! This package is used by VrmlConverter package.
//! The developer should already be familiar with VRML
//! specification before using this package.
class Vrml
{
public:
  DEFINE_STANDARD_ALLOC

  //! Writes a header in anOStream (VRML file).
  //! Writes one line of commentary in anOStream (VRML file).
  Standard_EXPORT static Standard_OStream& VrmlHeaderWriter(Standard_OStream& anOStream);

  Standard_EXPORT static Standard_OStream& CommentWriter(const char*       aComment,
                                                         Standard_OStream& anOStream);
};

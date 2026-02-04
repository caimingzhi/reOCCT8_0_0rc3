#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TCollection_AsciiString.hpp>
#include <Standard_OStream.hpp>

//! defines "instancing" - using the same instance of a node
//! multiple times.
//! It is accomplished by using the "DEF" and "USE" keywords.
//! The DEF keyword both defines a named node, and creates a single
//! instance of it.
//! The USE keyword indicates that the most recently defined instance
//! should be used again.
//! If several nades were given the same name, then the last DEF
//! encountered during parsing "wins".
//! DEF/USE is limited to a single file.
class Vrml_Instancing
{
public:
  DEFINE_STANDARD_ALLOC

  //! Adds "DEF <myName>" in anOStream (VRML file).
  Standard_EXPORT Vrml_Instancing(const TCollection_AsciiString& aString);

  //! Adds "USE <myName>" in anOStream (VRML file).
  Standard_EXPORT Standard_OStream& DEF(Standard_OStream& anOStream) const;

  Standard_EXPORT Standard_OStream& USE(Standard_OStream& anOStream) const;

private:
  TCollection_AsciiString myName;
};


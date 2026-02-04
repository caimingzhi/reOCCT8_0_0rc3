#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
class IGESData_IGESEntity;
class Interface_Graph;

//! This package defines the library of the most used tools for
//! IGES Files : Selections & Modifiers specific to the IGES norm,
//! and the most needed converters
class IGESSelect
{
public:
  DEFINE_STANDARD_ALLOC

  //! Simply gives a prompt for a conversational action on standard
  //! input/output. Returns the status of a
  Standard_EXPORT static void Run();

  //! Gives a quick analysis of an IGES Entity in the context of a
  //! model (i.e. a File) described by a Graph.
  //! Returned values are :
  //! <sup> : the most meaningful super entity, if any (else Null)
  //! <index> : meaningful index relating to super entity, if any
  //! <returned> : a status which helps exploitation of <sup>, by
  //! giving a case
  //! (normally, types of <ent> and <sup> should suffice to
  //! known the case)
  Standard_EXPORT static int WhatIges(const occ::handle<IGESData_IGESEntity>& ent,
                                      const Interface_Graph&                  G,
                                      occ::handle<IGESData_IGESEntity>&       sup,
                                      int&                                    index);
};


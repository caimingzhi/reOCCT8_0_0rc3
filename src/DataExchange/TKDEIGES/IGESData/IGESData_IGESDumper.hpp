#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <IGESData_SpecificLib.hpp>
#include <Standard_Integer.hpp>
#include <Standard_OStream.hpp>

class IGESData_IGESModel;
class IGESData_Protocol;
class IGESData_IGESEntity;

//! Provides a way to obtain a clear Dump of an IGESEntity
//! (distinct from normalized output). It works with tools
//! attached to Entities, as for normalized Reade and Write
//!
//! For each Entity, displaying data is split in own data
//! (specific to each type) and other attached data, which are
//! defined for all IGES Types (either from "Directory Entry" or
//! from Lists of Associativities and Properties)
class IGESData_IGESDumper
{
public:
  DEFINE_STANDARD_ALLOC

  //! Returns an IGESDumper ready to work.
  //! The IGESModel provides the numbering of Entities:
  //! as for any InterfaceModel, it gives each Entity a number;
  //! but for IGESEntities, the "Number of Directory Entry"
  //! according to the definition of IGES Files, is also useful.
  Standard_EXPORT IGESData_IGESDumper(const occ::handle<IGESData_IGESModel>& model,
                                      const occ::handle<IGESData_Protocol>&  protocol);

  //! Prints onto an output, the "Number of Directory Entry" which
  //! corresponds to an IGESEntity in the IGESModel, under the form
  //! "D#nnn" (a Null Handle gives D#0)
  Standard_EXPORT void PrintDNum(const occ::handle<IGESData_IGESEntity>& ent,
                                 Standard_OStream&                       S) const;

  //! Prints onto an output, the "Number of Directory Entry" (see
  //! PrintDNum) plus IGES Type and Form Numbers, which gives
  //! "D#nnn  Type nnn  Form nnn"
  Standard_EXPORT void PrintShort(const occ::handle<IGESData_IGESEntity>& ent,
                                  Standard_OStream&                       S) const;

  Standard_EXPORT void Dump(const occ::handle<IGESData_IGESEntity>& ent,
                            Standard_OStream&                       S,
                            const int                               own,
                            const int                               attached = -1) const;

  //! Specific Dump for each IGES Entity, call by Dump (just above)
  //! <own> is the parameter <own> from Dump
  Standard_EXPORT void OwnDump(const occ::handle<IGESData_IGESEntity>& ent,
                               Standard_OStream&                       S,
                               const int                               own) const;

private:
  occ::handle<IGESData_IGESModel> themodel;
  IGESData_SpecificLib            thelib;
};

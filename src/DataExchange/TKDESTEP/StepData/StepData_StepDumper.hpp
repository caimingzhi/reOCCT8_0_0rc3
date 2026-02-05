#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Interface_GeneralLib.hpp>
#include <StepData_WriterLib.hpp>
#include <StepData_StepWriter.hpp>
#include <Standard_Integer.hpp>
class StepData_StepModel;
class StepData_Protocol;

//! Provides a way to dump entities processed through STEP, with
//! these features :
//! - same form as for writing a STEP File (because it is clear
//! and compact enough, even if the names of the fields do not
//! appear) : thus, no additional resource is required
//! - possibility to look for an entity itself (only its Type or
//! with its content), an entity and it shared items (one level)
//! or all the entities its refers to, directly or recursively.
class StepData_StepDumper
{
public:
  DEFINE_STANDARD_ALLOC

  //! Creates a StepDumper, able to work on a given StepModel
  //! (which defines the total scope for dumping entities) and
  //! a given Protocol from Step (which defines the authorized
  //! types to be dumped)
  //! <mode> commands what is to be displayed (number or label)
  //! 0 for number (and corresponding labels  are displayed apart)
  //! 1 for label  (and corresponding numbers are displayed apart)
  //! 2 for label without anymore
  Standard_EXPORT StepData_StepDumper(const occ::handle<StepData_StepModel>& amodel,
                                      const occ::handle<StepData_Protocol>&  protocol,
                                      const int                              mode = 0);

  //! Gives an access to the tool which is used to work : this allow
  //! to acts on some parameters : Floating Format, Scopes ...
  Standard_EXPORT StepData_StepWriter& StepWriter();

  //! Dumps a Entity on an Messenger. Returns True if
  //! success, False, if the entity to dump has not been recognized
  //! by the Protocol. <level> can have one of these values :
  //! - 0 : prints the TYPE only, as known in STEP Files (StepType)
  //! If <ent> has not been regognized by the Protocol, or if its
  //! type is Complex, the StepType is replaced by the display of
  //! the cdl type. Complex Type are well processed by level 1.
  //! - 1 : dumps the entity, completely (whatever it has simple or
  //! complex type) but alone.
  //! - 2 : dumps the entity completely, plus the item its refers to
  //! at first level (a header message designates the starting
  //! entity of the dump) <Lists Shared and Implied>
  //! - 3 : dumps the entity and its referred items at any levels
  //!
  //! For levels 1,2,3, the numbers displayed (form #nnn) are the
  //! numbers of the corresponding entities in the Model
  Standard_EXPORT bool Dump(Standard_OStream&                      S,
                            const occ::handle<Standard_Transient>& ent,
                            const int                              level);

  //! Works as Dump with a Transient, but directly takes the
  //! entity designated by its number in the Model
  //! Returns False, also if <num> is out of range
  Standard_EXPORT bool Dump(Standard_OStream& S, const int num, const int level);

private:
  occ::handle<StepData_StepModel> themodel;
  Interface_GeneralLib            theslib;
  StepData_WriterLib              thewlib;
  StepData_StepWriter             thewriter;
};

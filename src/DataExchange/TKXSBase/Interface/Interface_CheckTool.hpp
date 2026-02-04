#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Interface_ShareTool.hpp>
#include <Standard_Integer.hpp>
class Interface_GTool;
class Interface_InterfaceModel;
class Interface_Protocol;
class Interface_Graph;
class Interface_HGraph;
class Standard_Transient;
class Interface_Check;
class Interface_CheckIterator;
class Interface_EntityIterator;

//! Performs Checks on Entities, using General Service Library and
//! Modules to work. Works on one Entity or on a complete Model
class Interface_CheckTool
{
public:
  DEFINE_STANDARD_ALLOC

  //! Creates a CheckTool, by calling the General Service Library
  //! and Modules, selected through a Protocol, to work on a Model
  //! Moreover, Protocol recognizes Unknown Entities
  Standard_EXPORT Interface_CheckTool(const occ::handle<Interface_InterfaceModel>& model,
                                      const occ::handle<Interface_Protocol>&       protocol);

  //! Creates a CheckTool, by calling the General Service Library
  //! and Modules, selected through a Protocol, to work on a Model
  //! Protocol and so on are taken from the Model (its GTool)
  Standard_EXPORT Interface_CheckTool(const occ::handle<Interface_InterfaceModel>& model);

  //! Creates a CheckTool from a Graph. The Graph contains a Model
  //! which designates a Protocol: they are used to create ShareTool
  Standard_EXPORT Interface_CheckTool(const Interface_Graph& graph);

  Standard_EXPORT Interface_CheckTool(const occ::handle<Interface_HGraph>& hgraph);

  //! Fills as required a Check with the Error and Warning messages
  //! produced by Checking a given Entity.
  //! For an Erroneous or Corrected Entity : Check build at Analyse
  //! time; else, Check computed for Entity (Verify integrity), can
  //! use a Graph as required to control context
  Standard_EXPORT void FillCheck(const occ::handle<Standard_Transient>& ent,
                                 const Interface_ShareTool&             sh,
                                 occ::handle<Interface_Check>&          ach);

  //! Utility method which Prints the content of a Check
  Standard_EXPORT void Print(const occ::handle<Interface_Check>& ach, Standard_OStream& S) const;

  //! Simply Lists all the Checks and the Content (messages) and the
  //! Entity, if there is, of each Check
  //! (if all Checks are OK, nothing is Printed)
  Standard_EXPORT void Print(const Interface_CheckIterator& list, Standard_OStream& S) const;

  //! Returns the Check associated to an Entity identified by
  //! its Number in a Model.
  Standard_EXPORT occ::handle<Interface_Check> Check(const int num);

  //! Checks if any Error has been detected (CheckList not empty)
  //! Returns normally if none, raises exception if some exists.
  //! It reuses the last computations from other checking methods,
  //! unless the argument <reset> is given True
  Standard_EXPORT void CheckSuccess(const bool reset = false);

  //! Returns list of all "remarkable" information, which include :
  //! - GlobalCheck, if not empty
  //! - Error Checks, for all Errors (Verify + Analyse)
  //! - also Corrected Entities
  //! - and Unknown Entities : for those, each Unknown Entity is
  //! associated to an empty Check (it is neither an Error nor a
  //! Correction, but a remarkable information)
  Standard_EXPORT Interface_CheckIterator CompleteCheckList();

  //! Returns list of all Errors detected
  //! Note that presence of Unknown Entities is not an error
  //! Cumulates : GlobalCheck if error +
  //! AnalyseCheckList + VerifyCheckList
  Standard_EXPORT Interface_CheckIterator CheckList();

  //! Returns list of errors detected at Analyse time (syntactic)
  //! (note that GlobalCheck is not in this list)
  Standard_EXPORT Interface_CheckIterator AnalyseCheckList();

  //! Returns list of integrity constraints errors (semantic)
  //! (note that GlobalCheck is not in this list)
  Standard_EXPORT Interface_CheckIterator VerifyCheckList();

  //! Returns list of Corrections (includes GlobalCheck if corrected)
  Standard_EXPORT Interface_CheckIterator WarningCheckList();

  //! Returns list of Unknown Entities
  //! Note that Error and Erroneous Entities are not considered
  //! as Unknown
  Standard_EXPORT Interface_EntityIterator UnknownEntities();

private:
  occ::handle<Interface_GTool> thegtool;
  Interface_ShareTool          theshare;
  int                          thestat;
};


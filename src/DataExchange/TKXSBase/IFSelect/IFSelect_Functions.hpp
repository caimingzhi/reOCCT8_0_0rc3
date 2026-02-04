#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_CString.hpp>
#include <Standard_Integer.hpp>
#include <Standard_Transient.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
class Standard_Transient;
class IFSelect_WorkSession;
class IFSelect_Dispatch;

//! Functions gives access to all the actions which can be
//! commanded with the resources provided by IFSelect : especially
//! WorkSession and various types of Selections and Dispatches
//!
//! It works by adding functions by method Init
class IFSelect_Functions
{
public:
  DEFINE_STANDARD_ALLOC

  //! Takes the name of an entity, either as argument,
  //! or (if <name> is empty) on keyboard, and returns the entity
  //! name can be a label or a number (in alphanumeric),
  //! it is searched by NumberFromLabel from WorkSession.
  //! If <name> doesn't match en entity, a Null Handle is returned
  Standard_EXPORT static occ::handle<Standard_Transient> GiveEntity(
    const occ::handle<IFSelect_WorkSession>& WS,
    const char*                              name = "");

  //! Same as GetEntity, but returns the number in the model of the
  //! entity. Returns 0 for null handle
  Standard_EXPORT static int GiveEntityNumber(const occ::handle<IFSelect_WorkSession>& WS,
                                              const char*                              name = "");

  //! Computes a List of entities from a WorkSession and two idents,
  //! first and second, as follows :
  //! if <first> is a Number or Label of an entity : this entity
  //! if <first> is the name of a Selection in <WS>, and <second>
  //! not defined, the standard result of this Selection
  //! if <first> is for a Selection and <second> is defined, the
  //! standard result of this selection from the list computed
  //! with <second> (an entity or a selection)
  //! If <second> is erroneous, it is ignored
  Standard_EXPORT static occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>>
    GiveList(const occ::handle<IFSelect_WorkSession>& WS,
             const char*                              first  = "",
             const char*                              second = "");

  //! Evaluates and returns a Dispatch, from data of a WorkSession
  //! if <mode> is False, searches for exact name of Dispatch in WS
  //! Else (D), allows a parameter between brackets :
  //! ex.: dispatch_name(parameter)
  //! The parameter can be: an integer for DispPerCount or DispPerFiles
  //! or the name of a Signature for DispPerSignature
  //! Returns Null Handle if not found not well evaluated
  Standard_EXPORT static occ::handle<IFSelect_Dispatch> GiveDispatch(
    const occ::handle<IFSelect_WorkSession>& WS,
    const char*                              name,
    const bool                               mode = true);

  //! Defines and loads all basic functions (as ActFunc)
  Standard_EXPORT static void Init();
};


#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <Standard_CString.hpp>
class XSControl_WorkSession;
class TCollection_AsciiString;

//! Defines additional commands for XSControl to :
//! - control of initialisation (xinit, xnorm, newmodel)
//! - analyse of the result of a transfer (recorded in a
//! TransientProcess for Read, FinderProcess for Write) :
//! statistics, various lists (roots,complete,abnormal), what
//! about one specific entity, producing a model with the
//! abnormal result
//!
//! This appendix of XSControl is compiled separately to distinguish
//! basic features from user callable forms
class XSControl_FuncShape
{
public:
  DEFINE_STANDARD_ALLOC

  //! Defines and loads all functions which work on shapes for XSControl (as ActFunc)
  Standard_EXPORT static void Init();

  //! Analyses a name as designating Shapes from a Vars or from
  //! XSTEP transfer (last Transfer on Reading). <name> can be :
  //! "*" : all the root shapes produced by last Transfer (Read)
  //! i.e. considers roots of the TransientProcess
  //! a name : a name of a variable DRAW
  //!
  //! Returns the count of designated Shapes. Their list is put in
  //! <list>. If <list> is null, it is firstly created. Then it is
  //! completed (Append without Clear) by the Shapes found
  //! Returns 0 if no Shape could be found
  Standard_EXPORT static int MoreShapes(const occ::handle<XSControl_WorkSession>&         session,
                                        occ::handle<NCollection_HSequence<TopoDS_Shape>>& list,
                                        const char*                                       name);

  //! Analyses given file name and variable name, with a default
  //! name for variables. Returns resulting file name and variable
  //! name plus status "file to read"(True) or "already read"(False)
  //! In the latter case, empty resfile means no file available
  //!
  //! If <file> is null or empty or equates ".", considers Session
  //! and returned status is False
  //! Else, returns resfile = file and status is True
  //! If <var> is neither null nor empty, resvar = var
  //! Else, the root part of <resfile> is considered, if defined
  //! Else, <def> is taken
  Standard_EXPORT static bool FileAndVar(const occ::handle<XSControl_WorkSession>& session,
                                         const char*                               file,
                                         const char*                               var,
                                         const char*                               def,
                                         TCollection_AsciiString&                  resfile,
                                         TCollection_AsciiString&                  resvar);
};


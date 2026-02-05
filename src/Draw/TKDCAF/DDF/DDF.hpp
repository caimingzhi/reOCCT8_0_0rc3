#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>
#include <Draw_Interpretor.hpp>
class TDF_Data;
class TDF_Label;
class Standard_GUID;
class TDF_Attribute;

//! Provides facilities to manipulate data framework
//! in a Draw-Commands environment.
class DDF
{
public:
  DEFINE_STANDARD_ALLOC

  //! Search in draw directory the framewok identified
  //! by its name <Name>. returns True if found. In that
  //! case <DF> is set.
  Standard_EXPORT static bool GetDF(const char*&           Name,
                                    occ::handle<TDF_Data>& DF,
                                    const bool             Complain = true);

  //! Search in <DF> the label identified by its entry
  //! <Entry>. returns <True> if found. In that case
  //! <Label> is set.
  Standard_EXPORT static bool FindLabel(const occ::handle<TDF_Data>& DF,
                                        const char*                  Entry,
                                        TDF_Label&                   Label,
                                        const bool                   Complain = true);

  //! Search in <DF> the label identified by its entry
  //! <Entry>. if label doesn't exist, create and add
  //! the Label in <DF>. In that case return True.
  Standard_EXPORT static bool AddLabel(const occ::handle<TDF_Data>& DF,
                                       const char*                  Entry,
                                       TDF_Label&                   Label);

  //! Search in <DF> the attribute identified by its
  //! <ID> and its <entry>. returns <True> if found. In
  //! that case A is set.
  Standard_EXPORT static bool Find(const occ::handle<TDF_Data>& DF,
                                   const char*                  Entry,
                                   const Standard_GUID&         ID,
                                   occ::handle<TDF_Attribute>&  A,
                                   const bool                   Complain = true);

  //! Safe variant for arbitrary type of argument
  template <class T>
  static bool Find(const occ::handle<TDF_Data>& DF,
                   const char*                  Entry,
                   const Standard_GUID&         ID,
                   occ::handle<T>&              A,
                   const bool                   Complain = true)
  {
    occ::handle<TDF_Attribute> anAttr = A;
    return Find(DF, Entry, ID, anAttr, Complain) && !(A = occ::down_cast<T>(anAttr)).IsNull();
  }

  Standard_EXPORT static Draw_Interpretor& ReturnLabel(Draw_Interpretor& theCommands,
                                                       const TDF_Label&  L);

  Standard_EXPORT static void AllCommands(Draw_Interpretor& theCommands);

  //! Basic commands.
  Standard_EXPORT static void BasicCommands(Draw_Interpretor& theCommands);

  //! Data framework commands
  //! create, clear & copy.
  Standard_EXPORT static void DataCommands(Draw_Interpretor& theCommands);

  //! open commit abort a transaction
  //! undo facilities.
  Standard_EXPORT static void TransactionCommands(Draw_Interpretor& theCommands);

  //! Browser commands .
  Standard_EXPORT static void BrowserCommands(Draw_Interpretor& theCommands);
};

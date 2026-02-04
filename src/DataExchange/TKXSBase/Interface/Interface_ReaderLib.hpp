#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
class Interface_NodeOfReaderLib;
class Standard_NoSuchObject;
class Standard_Transient;
class Interface_ReaderModule;
class Interface_Protocol;
class Interface_GlobalNodeOfReaderLib;

class Interface_ReaderLib
{
public:
  DEFINE_STANDARD_ALLOC

  //! Adds a couple (Module-Protocol) into the global definition set
  //! for this class of Library.
  Standard_EXPORT static void SetGlobal(const occ::handle<Interface_ReaderModule>& amodule,
                                        const occ::handle<Interface_Protocol>&     aprotocol);

  //! Creates a Library which complies with a Protocol, that is :
  //! Same class (criterium IsInstance)
  //! This creation gets the Modules from the global set, those
  //! which are bound to the given Protocol and its Resources
  Standard_EXPORT Interface_ReaderLib(const occ::handle<Interface_Protocol>& aprotocol);

  //! Creates an empty Library : it will later by filled by method
  //! AddProtocol
  Standard_EXPORT Interface_ReaderLib();

  //! Adds a couple (Module-Protocol) to the Library, given the
  //! class of a Protocol. Takes Resources into account.
  //! (if <aprotocol> is not of type TheProtocol, it is not added)
  Standard_EXPORT void AddProtocol(const occ::handle<Standard_Transient>& aprotocol);

  //! Clears the list of Modules of a library (can be used to
  //! redefine the order of Modules before action : Clear then
  //! refill the Library by calls to AddProtocol)
  Standard_EXPORT void Clear();

  //! Sets a library to be defined with the complete Global list
  //! (all the couples Protocol/Modules recorded in it)
  Standard_EXPORT void SetComplete();

  //! Selects a Module from the Library, given an Object.
  //! Returns True if Select has succeeded, False else.
  //! Also Returns (as arguments) the selected Module and the Case
  //! Number determined by the associated Protocol.
  //! If Select has failed, <module> is Null Handle and CN is zero.
  //! (Select can work on any criterium, such as Object DynamicType)
  Standard_EXPORT bool Select(const occ::handle<Standard_Transient>& obj,
                              occ::handle<Interface_ReaderModule>&   module,
                              int&                                   CN) const;

  //! Starts Iteration on the Modules (sets it on the first one)
  Standard_EXPORT void Start();

  //! Returns True if there are more Modules to iterate on
  Standard_EXPORT bool More() const;

  //! Iterates by getting the next Module in the list
  //! If there is none, the exception will be raised by Value
  Standard_EXPORT void Next();

  //! Returns the current Module in the Iteration
  Standard_EXPORT const occ::handle<Interface_ReaderModule>& Module() const;

  //! Returns the current Protocol in the Iteration
  Standard_EXPORT const occ::handle<Interface_Protocol>& Protocol() const;

private:
  occ::handle<Interface_NodeOfReaderLib> thelist;
  occ::handle<Interface_NodeOfReaderLib> thecurr;
};


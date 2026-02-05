#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Transfer_Finder.hpp>
#include <Standard_Handle.hpp>

//! FindHasher defines HashCode for Finder, which is : ask a
//! Finder its HashCode! Because this is the Finder itself which
//! brings the HashCode for its Key
//!
//! This class complies to the template given in TCollection by
//! MapHasher itself
class Transfer_FindHasher
{
public:
  size_t operator()(const occ::handle<Transfer_Finder>& theFinder) const
  {
    return theFinder->GetHashCode();
  }

  //! Returns True if two keys are the same.
  //! The test does not work on the Finders themselves but by
  //! calling their methods Equates
  bool operator()(const occ::handle<Transfer_Finder>& theK1,
                  const occ::handle<Transfer_Finder>& theK2) const
  {
    if (theK1.IsNull())
      return false;
    return theK1->Equates(theK2);
  }
};

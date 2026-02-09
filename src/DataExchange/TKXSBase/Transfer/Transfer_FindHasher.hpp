#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Transfer_Finder.hpp>
#include <Standard_Handle.hpp>

class Transfer_FindHasher
{
public:
  size_t operator()(const occ::handle<Transfer_Finder>& theFinder) const
  {
    return theFinder->GetHashCode();
  }

  bool operator()(const occ::handle<Transfer_Finder>& theK1,
                  const occ::handle<Transfer_Finder>& theK2) const
  {
    if (theK1.IsNull())
      return false;
    return theK1->Equates(theK2);
  }
};

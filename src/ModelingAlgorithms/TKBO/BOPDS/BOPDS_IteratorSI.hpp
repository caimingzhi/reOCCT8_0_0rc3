#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <BOPDS_Iterator.hpp>
#include <NCollection_BaseAllocator.hpp>
#include <Standard_Integer.hpp>

class BOPDS_IteratorSI : public BOPDS_Iterator
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BOPDS_IteratorSI();

  Standard_EXPORT ~BOPDS_IteratorSI() override;

  Standard_EXPORT BOPDS_IteratorSI(const occ::handle<NCollection_BaseAllocator>& theAllocator);

  Standard_EXPORT void UpdateByLevelOfCheck(const int theLevel);

protected:
  Standard_EXPORT void Intersect(
    const occ::handle<IntTools_Context>& theCtx        = occ::handle<IntTools_Context>(),
    const bool                           theCheckOBB   = false,
    const double                         theFuzzyValue = Precision::Confusion()) override;
};

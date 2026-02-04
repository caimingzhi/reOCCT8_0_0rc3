#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <BOPDS_Iterator.hpp>
#include <NCollection_BaseAllocator.hpp>
#include <Standard_Integer.hpp>

//! The class BOPDS_IteratorSI is
//! 1.to compute self-intersections between BRep sub-shapes
//! of each argument of an operation (see the class BOPDS_DS)
//! in terms of theirs bounding boxes
//! 2.provides interface to iterare the pairs of
//! intersected sub-shapes of given type
class BOPDS_IteratorSI : public BOPDS_Iterator
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  Standard_EXPORT BOPDS_IteratorSI();

  Standard_EXPORT ~BOPDS_IteratorSI() override;

  //! Constructor
  //! @param theAllocator the allocator to manage the memory
  Standard_EXPORT BOPDS_IteratorSI(const occ::handle<NCollection_BaseAllocator>& theAllocator);

  //! Updates the lists of possible intersections
  //! according to the value of <theLevel>.
  //! It defines which interferferences will be checked:
  //! 0 - only V/V;
  //! 1 - V/V and V/E;
  //! 2 - V/V, V/E and E/E;
  //! 3 - V/V, V/E, E/E and V/F;
  //! 4 - V/V, V/E, E/E, V/F and E/F;
  //! other - all interferences.
  Standard_EXPORT void UpdateByLevelOfCheck(const int theLevel);

protected:
  Standard_EXPORT void Intersect(
    const occ::handle<IntTools_Context>& theCtx        = occ::handle<IntTools_Context>(),
    const bool                           theCheckOBB   = false,
    const double                         theFuzzyValue = Precision::Confusion()) override;
};


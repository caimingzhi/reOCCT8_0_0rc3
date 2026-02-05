#include <Poly_CoherentTriPtr.hpp>

//=================================================================================================

void Poly_CoherentTriPtr::Iterator::Next()
{
  if (myCurrent)
  {
    myCurrent = myCurrent->myNext;
    if (myCurrent == myFirst)
      myCurrent = nullptr;
  }
}

//=================================================================================================

void Poly_CoherentTriPtr::Append(const Poly_CoherentTriangle*                  pTri,
                                 const occ::handle<NCollection_BaseAllocator>& theAlloc)
{
  occ::handle<NCollection_BaseAllocator> anAlloc = theAlloc;
  if (theAlloc.IsNull())
    anAlloc = NCollection_BaseAllocator::CommonBaseAllocator();
  Poly_CoherentTriPtr* aNewPtr = new (anAlloc) Poly_CoherentTriPtr(*pTri);
  aNewPtr->myNext              = myNext;
  myNext->myPrevious           = aNewPtr;
  aNewPtr->myPrevious          = this;
  myNext                       = aNewPtr;
}

//=================================================================================================

void Poly_CoherentTriPtr::Prepend(const Poly_CoherentTriangle*                  pTri,
                                  const occ::handle<NCollection_BaseAllocator>& theAlloc)
{
  occ::handle<NCollection_BaseAllocator> anAlloc = theAlloc;
  if (theAlloc.IsNull())
    anAlloc = NCollection_BaseAllocator::CommonBaseAllocator();
  Poly_CoherentTriPtr* aNewPtr = new (anAlloc) Poly_CoherentTriPtr(*pTri);
  aNewPtr->myPrevious          = myPrevious;
  myPrevious->myNext           = aNewPtr;
  aNewPtr->myNext              = this;
  myPrevious                   = aNewPtr;
}

//=================================================================================================

void Poly_CoherentTriPtr::Remove(Poly_CoherentTriPtr*                          thePtr,
                                 const occ::handle<NCollection_BaseAllocator>& theAlloc)
{
  occ::handle<NCollection_BaseAllocator> anAlloc = theAlloc;
  if (theAlloc.IsNull())
    anAlloc = NCollection_BaseAllocator::CommonBaseAllocator();
  if (thePtr->myNext && thePtr->myPrevious)
  {
    thePtr->myPrevious->myNext = thePtr->myNext;
    thePtr->myNext->myPrevious = thePtr->myPrevious;
    thePtr->myNext             = thePtr;
    thePtr->myPrevious         = thePtr;
  }
  anAlloc->Free(thePtr);
}

//=================================================================================================

void Poly_CoherentTriPtr::RemoveList(Poly_CoherentTriPtr*                          thePtr,
                                     const occ::handle<NCollection_BaseAllocator>& theAlloc)
{
  occ::handle<NCollection_BaseAllocator> anAlloc = theAlloc;
  if (theAlloc.IsNull())
    anAlloc = NCollection_BaseAllocator::CommonBaseAllocator();
  Poly_CoherentTriPtr* aPtr = thePtr;
  do
  {
    if (aPtr == nullptr)
      break;
    Poly_CoherentTriPtr* aLostPtr = aPtr;
    aPtr                          = aPtr->myNext;
    anAlloc->Free(aLostPtr);
  } while (aPtr != thePtr);
}

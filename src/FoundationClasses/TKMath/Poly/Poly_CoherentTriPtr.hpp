#pragma once

#include <NCollection_BaseAllocator.hpp>
#include <NCollection_DefineAlloc.hpp>

class Poly_CoherentTriangle;

#ifdef _MSC_VER
  #pragma warning(push)
  #pragma warning(disable : 4355)
#endif

class Poly_CoherentTriPtr
{
public:
  class Iterator
  {
  public:
    inline Iterator()
        : myFirst(nullptr),
          myCurrent(nullptr)
    {
    }

    inline Iterator(const Poly_CoherentTriPtr& thePtr)
        : myFirst(&thePtr),
          myCurrent(&thePtr)
    {
    }

    inline const Poly_CoherentTriangle* First() const
    {
      return myFirst ? &myFirst->GetTriangle() : nullptr;
    }

    inline bool More() const { return myCurrent != nullptr; }

    Standard_EXPORT void Next();

    inline const Poly_CoherentTriangle& Value() const { return myCurrent->GetTriangle(); }

    inline Poly_CoherentTriangle& ChangeValue() const
    {
      return const_cast<Poly_CoherentTriangle&>(myCurrent->GetTriangle());
    }

    inline const Poly_CoherentTriPtr& PtrValue() const { return *myCurrent; }

  private:
    const Poly_CoherentTriPtr* myFirst;
    const Poly_CoherentTriPtr* myCurrent;
  };

  inline Poly_CoherentTriPtr(const Poly_CoherentTriangle& theTri)
      : mypTriangle(&theTri),
        myNext(this),
        myPrevious(this)
  {
  }

  DEFINE_NCOLLECTION_ALLOC

  inline const Poly_CoherentTriangle& GetTriangle() const { return *mypTriangle; }

  inline void SetTriangle(const Poly_CoherentTriangle* pTri) { mypTriangle = pTri; }

  inline Poly_CoherentTriPtr& Next() const { return *myNext; }

  inline Poly_CoherentTriPtr& Previous() const { return *myPrevious; }

  Standard_EXPORT void Append(const Poly_CoherentTriangle*                  pTri,
                              const occ::handle<NCollection_BaseAllocator>& theA);

  Standard_EXPORT void Prepend(const Poly_CoherentTriangle*                  pTri,
                               const occ::handle<NCollection_BaseAllocator>& theA);

  Standard_EXPORT static void Remove(Poly_CoherentTriPtr*                          thePtr,
                                     const occ::handle<NCollection_BaseAllocator>& theA);

  Standard_EXPORT static void RemoveList(Poly_CoherentTriPtr* thePtr,
                                         const occ::handle<NCollection_BaseAllocator>&);

protected:
  inline Poly_CoherentTriPtr(const Poly_CoherentTriangle* pTri)
      : mypTriangle(pTri),
        myNext(this),
        myPrevious(this)
  {
  }

private:
  const Poly_CoherentTriangle* mypTriangle;
  Poly_CoherentTriPtr*         myNext;
  Poly_CoherentTriPtr*         myPrevious;

  friend class Iterator;
};

#ifdef _MSC_VER
  #pragma warning(pop)
#endif

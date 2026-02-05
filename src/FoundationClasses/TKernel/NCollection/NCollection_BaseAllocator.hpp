#pragma once

#include <Standard_DefineHandle.hpp>
#include <Standard_Transient.hpp>

/**
 * Purpose:     Basic class for memory allocation wizards.
 *              Defines  the  interface  for devising  different  allocators
 *              firstly to be used  by collections of NCollection, though it
 *              it is not  deferred. It allocates/frees  the memory  through
 *              Standard procedures, thus it is  unnecessary (and  sometimes
 *              injurious) to have  more than one such  allocator.  To avoid
 *              creation  of multiple  objects the  constructors  were  maid
 *              inaccessible.  To  create the  BaseAllocator use  the method
 *              CommonBaseAllocator.
 *              Note that this object is managed by Handle.
 */
class NCollection_BaseAllocator : public Standard_Transient
{
public:
  // ---------- PUBLIC METHODS ------------
  Standard_EXPORT virtual void* Allocate(const size_t theSize);
  Standard_EXPORT virtual void* AllocateOptimal(const size_t theSize);
  Standard_EXPORT virtual void  Free(void* theAddress);

  //! CommonBaseAllocator
  //! This method is designed to have the only one BaseAllocator (to avoid
  //! useless copying of collections). However one can use operator new to
  //! create more BaseAllocators, but it is injurious.
  Standard_EXPORT static const occ::handle<NCollection_BaseAllocator>& CommonBaseAllocator();

protected:
  //! Constructor - prohibited
  NCollection_BaseAllocator() noexcept {}

private:
  //! Copy constructor - prohibited
  NCollection_BaseAllocator(const NCollection_BaseAllocator&) = delete;

public:
  // ---------- CasCade RunTime Type Information
  DEFINE_STANDARD_RTTIEXT(NCollection_BaseAllocator, Standard_Transient)
};

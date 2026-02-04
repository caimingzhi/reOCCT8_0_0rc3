#pragma once


#include <Standard_Transient.hpp>
#include <Standard_Handle.hpp>

//! Purpose: This template class is used to define Handle adaptor
//! for allocated dynamically objects of arbitrary type.
//!
//! The advantage is that this handle will automatically destroy
//! the object when last referred Handle is destroyed (i.e. it is a
//! typical smart pointer), and that it can be handled as
//! occ::handle<Standard_Transient> in OCCT components.

template <class T>
class NCollection_Handle : public opencascade::handle<Standard_Transient>
{
private:
  //! Internal adaptor class wrapping actual type
  //! and enhancing it by reference counter inherited from
  //! Standard_Transient
  class Ptr : public Standard_Transient
  {
  public:
    //! Constructor: stores pointer to the object
    Ptr(T* theObj)
        : myPtr(theObj)
    {
    }

    //! Destructor deletes the object
    ~Ptr() override
    {
      if (myPtr)
        delete myPtr;
      myPtr = nullptr;
    }

  protected:
    //! Copy constructor
    Ptr(const Ptr&);

    //! Assignment operator
    Ptr& operator=(const Ptr&);

  public:
    T* myPtr; //!< Pointer to the object
  };

  //! Constructor of handle from pointer on newly allocated object.
  //! Note that additional argument is used to avoid ambiguity with
  //! public constructor from pointer when Handle is intilialized by 0.
  NCollection_Handle(Ptr* thePtr, int)
      : opencascade::handle<Standard_Transient>(thePtr)
  {
  }

public:
  typedef T element_type;

  //! Default constructor; creates null handle
  NCollection_Handle() = default;

  //! Constructor of handle from pointer on newly allocated object
  NCollection_Handle(T* theObject)
      : opencascade::handle<Standard_Transient>(theObject ? new Ptr(theObject) : nullptr)
  {
  }

  //! Cast handle to contained type
  T* get() noexcept { return ((Ptr*)opencascade::handle<Standard_Transient>::get())->myPtr; }

  //! Cast handle to contained type
  const T* get() const noexcept
  {
    return ((Ptr*)opencascade::handle<Standard_Transient>::get())->myPtr;
  }

  //! Cast handle to contained type
  T* operator->() noexcept { return get(); }

  //! Cast handle to contained type
  const T* operator->() const noexcept { return get(); }

  //! Cast handle to contained type
  T& operator*() noexcept { return *get(); }

  //! Cast handle to contained type
  const T& operator*() const noexcept { return *get(); }

  //! Downcast arbitrary Handle to the argument type if contained
  //! object is Handle for this type; returns null otherwise
  static NCollection_Handle<T> DownCast(
    const opencascade::handle<Standard_Transient>& theOther) noexcept
  {
    return NCollection_Handle<T>(dynamic_cast<Ptr*>(theOther.get()), 0);
  }
};


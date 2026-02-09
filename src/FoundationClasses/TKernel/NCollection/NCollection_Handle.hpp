#pragma once

#include <Standard_Transient.hpp>
#include <Standard_Handle.hpp>

template <class T>
class NCollection_Handle : public opencascade::handle<Standard_Transient>
{
private:
  class Ptr : public Standard_Transient
  {
  public:
    Ptr(T* theObj)
        : myPtr(theObj)
    {
    }

    ~Ptr() override
    {
      if (myPtr)
        delete myPtr;
      myPtr = nullptr;
    }

  protected:
    Ptr(const Ptr&);

    Ptr& operator=(const Ptr&);

  public:
    T* myPtr;
  };

  NCollection_Handle(Ptr* thePtr, int)
      : opencascade::handle<Standard_Transient>(thePtr)
  {
  }

public:
  typedef T element_type;

  NCollection_Handle() = default;

  NCollection_Handle(T* theObject)
      : opencascade::handle<Standard_Transient>(theObject ? new Ptr(theObject) : nullptr)
  {
  }

  T* get() noexcept { return ((Ptr*)opencascade::handle<Standard_Transient>::get())->myPtr; }

  const T* get() const noexcept
  {
    return ((Ptr*)opencascade::handle<Standard_Transient>::get())->myPtr;
  }

  T* operator->() noexcept { return get(); }

  const T* operator->() const noexcept { return get(); }

  T& operator*() noexcept { return *get(); }

  const T& operator*() const noexcept { return *get(); }

  static NCollection_Handle<T> DownCast(
    const opencascade::handle<Standard_Transient>& theOther) noexcept
  {
    return NCollection_Handle<T>(dynamic_cast<Ptr*>(theOther.get()), 0);
  }
};

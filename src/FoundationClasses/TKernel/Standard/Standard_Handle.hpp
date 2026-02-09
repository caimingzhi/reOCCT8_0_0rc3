#pragma once

#include <Standard_Std.hpp>
#include <Standard_Macro.hpp>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <Standard_Transient.hpp>

class Standard_Transient;

namespace opencascade
{

  template <class T>
  class handle
  {
  public:
    typedef T element_type;

  public:
    handle()
        : entity(nullptr)
    {
    }

    handle(const T* thePtr)
        : entity(const_cast<T*>(thePtr))
    {
      BeginScope();
    }

    handle(const handle& theHandle)
        : entity(theHandle.entity)
    {
      BeginScope();
    }

    handle(handle&& theHandle) noexcept
        : entity(theHandle.entity)
    {
      theHandle.entity = nullptr;
    }

    ~handle() { EndScope(); }

    void Nullify() { EndScope(); }

    bool IsNull() const { return entity == nullptr; }

    void reset(T* thePtr) { Assign(thePtr); }

    handle& operator=(const handle& theHandle)
    {
      Assign(theHandle.entity);
      return *this;
    }

    handle& operator=(const T* thePtr)
    {
      Assign(const_cast<T*>(thePtr));
      return *this;
    }

    handle& operator=(handle&& theHandle) noexcept
    {
      std::swap(this->entity, theHandle.entity);
      return *this;
    }

    T* get() const { return static_cast<T*>(this->entity); }

    T* operator->() const { return static_cast<T*>(this->entity); }

    T& operator*() const { return *get(); }

    template <class T2>
    bool operator==(const handle<T2>& theHandle) const
    {
      return get() == theHandle.get();
    }

    template <class T2>
    bool operator==(const T2* thePtr) const
    {
      return get() == thePtr;
    }

    template <class T2>
    friend bool operator==(const T2* left, const handle& right)
    {
      return left == right.get();
    }

    template <class T2>
    bool operator!=(const handle<T2>& theHandle) const
    {
      return get() != theHandle.get();
    }

    template <class T2>
    bool operator!=(const T2* thePtr) const
    {
      return get() != thePtr;
    }

    template <class T2>
    friend bool operator!=(const T2* left, const handle& right)
    {
      return left != right.get();
    }

    template <class T2>
    bool operator<(const handle<T2>& theHandle) const
    {
      return get() < theHandle.get();
    }

    template <class T2>
    static typename opencascade::std::enable_if<is_base_but_not_same<T2, T>::value, handle>::type
      DownCast(const handle<T2>& theObject)
    {
      return handle(dynamic_cast<T*>(const_cast<T2*>(theObject.get())));
    }

    template <class T2>
    static typename opencascade::std::enable_if<is_base_but_not_same<T2, T>::value, handle>::type
      DownCast(const T2* thePtr)
    {
      return handle(dynamic_cast<T*>(const_cast<T2*>(thePtr)));
    }

    template <class T2>
    Standard_DEPRECATED("down-casting from object of the same or unrelated type is meaningless")

    static handle DownCast(
      const handle<T2>& theObject,
      typename opencascade::std::enable_if<!is_base_but_not_same<T2, T>::value, void*>::type = 0)
    {
      return handle(dynamic_cast<T*>(const_cast<T2*>(theObject.get())));
    }

    template <class T2>
    Standard_DEPRECATED("down-casting from object of the same or unrelated type is meaningless")

    static handle DownCast(
      const T2* thePtr,
      typename opencascade::std::enable_if<!is_base_but_not_same<T2, T>::value, void*>::type = 0)
    {
      return handle(dynamic_cast<T*>(const_cast<T2*>(thePtr)));
    }

#if (defined(__clang__)) || (defined(__INTEL_COMPILER) && __INTEL_COMPILER >= 1300)                \
  || (defined(_MSC_VER) && _MSC_VER >= 1800)                                                       \
  || (defined(__GNUC__) && (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6)))

    explicit operator bool() const { return entity != nullptr; }

#else

    operator Standard_Transient* handle::*() const { return entity ? &handle::entity : 0; }

#endif

#if (defined(__clang__)) || (defined(__INTEL_COMPILER) && __INTEL_COMPILER >= 1206)                \
  || (defined(_MSC_VER) && _MSC_VER >= 1800)                                                       \
  || (defined(__GNUC__) && (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 3)))

  #ifdef OCCT_HANDLE_NOCAST

    template <class T2,
              typename = typename std::enable_if<is_base_but_not_same<T, T2>::value>::type>
    handle(const handle<T2>& theHandle)
        : entity(theHandle.entity)
    {
      BeginScope();
    }

    template <class T2,
              typename = typename std::enable_if<is_base_but_not_same<T, T2>::value>::type>
    handle(handle<T2>&& theHandle)
        : entity(theHandle.entity)
    {
      theHandle.entity = 0;
    }

    template <class T2,
              typename = typename std::enable_if<is_base_but_not_same<T, T2>::value>::type>
    handle operator=(const handle<T2>& theHandle)
    {
      Assign(theHandle.entity);
      return *this;
    }

    template <class T2,
              typename = typename std::enable_if<is_base_but_not_same<T, T2>::value>::type>
    handle& operator=(handle<T2>&& theHandle)
    {
      std::swap(this->entity, theHandle.entity);
      return *this;
    }

  #else

    template <class T2,
              typename = typename std::enable_if<is_base_but_not_same<T2, T>::value>::type>
    operator const handle<T2>&() const
    {
      return reinterpret_cast<const handle<T2>&>(*this);
    }

    template <class T2,
              typename = typename std::enable_if<is_base_but_not_same<T2, T>::value>::type>
    operator handle<T2>&()
    {
      return reinterpret_cast<handle<T2>&>(*this);
    }

  #endif

#else

  #ifdef OCCT_HANDLE_NOCAST

    template <class T2>
    handle(const handle<T2>& theHandle,
           typename std::enable_if<is_base_but_not_same<T, T2>::value>::type* = nullptr)
        : entity(theHandle.entity)
    {
      BeginScope();
    }

    template <class T2>
    handle(handle<T2>&& theHandle,
           typename std::enable_if<is_base_but_not_same<T, T2>::value>::type* = nullptr)
        : entity(theHandle.entity)
    {
      theHandle.entity = 0;
    }

    template <class T2>
    handle operator=(const handle<T2>& theHandle)
    {
      std::enable_if<is_base_but_not_same<T, T2>::value, void*>::type aTypeCheckHelperVar;
      (void)aTypeCheckHelperVar;
      Assign(theHandle.entity);
      return *this;
    }

    template <class T2>
    handle& operator=(handle<T2>&& theHandle)
    {
      std::enable_if<is_base_but_not_same<T, T2>::value, void*>::type aTypeCheckHelperVar;
      (void)aTypeCheckHelperVar;
      std::swap(this->entity, theHandle.entity);
      return *this;
    }

  #else

    template <class T2>
    operator const handle<T2>&() const
    {

      return reinterpret_cast<
        typename opencascade::std::enable_if<is_base_but_not_same<T2, T>::value,
                                             const handle<T2>&>::type>(*this);
    }

    template <class T2>
    Standard_DEPRECATED("Passing non-const reference to handle of base type in function is unsafe; "
                        "use variable of exact type")

    operator handle<T2>&()
    {

      return reinterpret_cast<typename opencascade::std::
                                enable_if<is_base_but_not_same<T2, T>::value, handle<T2>&>::type>(
        *this);
    }

  #endif

#endif

  private:
    void Assign(Standard_Transient* thePtr)
    {
      if (thePtr == entity)
        return;
      EndScope();
      entity = thePtr;
      BeginScope();
    }

    void BeginScope()
    {
      if (entity != nullptr)
        entity->IncrementRefCounter();
    }

    void EndScope()
    {
      if (entity != nullptr && entity->DecrementRefCounter() == 0)
        entity->Delete();
      entity = nullptr;
    }

    template <class T2>
    friend class handle;

  private:
    Standard_Transient* entity;
  };

} // namespace opencascade

namespace occ
{

  template <class T>
  using handle = opencascade::handle<T>;

  template <class TDerived, class TBase>
  inline handle<TDerived> down_cast(const handle<TBase>& theObject)
  {
    return handle<TDerived>::DownCast(theObject);
  }

  template <class TDerived, class TBase>
  inline handle<TDerived> down_cast(const TBase* thePtr)
  {
    return handle<TDerived>::DownCast(thePtr);
  }

} // namespace occ

#define Handle(Class) opencascade::handle<Class>

#include <Standard_HashUtils.hpp>

namespace std
{
  template <class TheTransientType>
  struct hash<Handle(TheTransientType)>
  {
    size_t operator()(const Handle(TheTransientType)& theHandle) const noexcept
    {
      return static_cast<size_t>(reinterpret_cast<std::uintptr_t>(theHandle.get()));
    }
  };
} // namespace std

#if (defined(_MSC_VER) && _MSC_VER >= 1800)

  #define DEFINE_STANDARD_HANDLECLASS(C1, C2, BC)                                                  \
    class C1;                                                                                      \
    class Standard_DEPRECATED(                                                                     \
      "This class will be removed right after 7.9 release. Use Handle(T) directly instead.")       \
      Handle_##C1 : public Handle(C1){                                                             \
        public : Handle_##C1(){} Handle_##C1(Handle(C1)&& theHandle) : Handle(C1)(                 \
          theHandle){} template <class T2,                                                         \
                                 typename =                                                        \
                                   typename std::enable_if<std::is_base_of<C1, T2>::value>::type>  \
        inline Handle_##C1(const opencascade::handle<T2>& theOther) : Handle(C1)(                  \
          theOther){} template <class T2,                                                          \
                                typename =                                                         \
                                  typename std::enable_if<std::is_base_of<C1, T2>::value>::type>   \
        inline Handle_##C1(const T2* theOther) : Handle(C1)(theOther){} template <typename T>      \
        inline Handle_##C1                                                                         \
        & operator=(T theOther){Handle(C1)::operator=(theOther);                                   \
    return *this;                                                                                  \
    }                                                                                              \
    }                                                                                              \
    ;
#else

  #define DEFINE_STANDARD_HANDLECLASS(C1, C2, BC)                                                  \
    class C1;                                                                                      \
    Standard_DEPRECATED("This typedef will be removed right after 7.9 release. Use Handle(T) "     \
                        "directly instead.")                                                       \
    typedef Handle(C1) Handle_##C1;
#endif

#define DEFINE_STANDARD_HANDLE(C1, C2) DEFINE_STANDARD_HANDLECLASS(C1, C2, Standard_Transient)
#define DEFINE_STANDARD_PHANDLE(C1, C2) DEFINE_STANDARD_HANDLECLASS(C1, C2, Standard_Persistent)

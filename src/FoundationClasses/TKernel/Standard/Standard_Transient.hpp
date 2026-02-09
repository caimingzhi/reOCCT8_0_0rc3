#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <stddef.h>
#include <stdlib.h>
#include <Standard_Macro.hpp>
#include <Standard_Boolean.hpp>
#include <Standard_Integer.hpp>
#include <Standard_Real.hpp>
#include <Standard_Character.hpp>
#include <Standard_ExtCharacter.hpp>
#include <Standard_CString.hpp>

#include <atomic>

class Standard_Type;

namespace opencascade
{
  template <class T>
  class handle;
}

class Standard_Transient
{
public:
  DEFINE_STANDARD_ALLOC

public:
  Standard_Transient()
      : myRefCount_(0)
  {
  }

  Standard_Transient(const Standard_Transient&)
      : myRefCount_(0)
  {
  }

  Standard_Transient& operator=(const Standard_Transient&) { return *this; }

  virtual ~Standard_Transient() = default;

public:
  typedef void base_type;

  static constexpr const char* get_type_name() { return "Standard_Transient"; }

  Standard_EXPORT static const opencascade::handle<Standard_Type>& get_type_descriptor();

  Standard_EXPORT virtual const opencascade::handle<Standard_Type>& DynamicType() const;

  Standard_EXPORT bool IsInstance(const opencascade::handle<Standard_Type>& theType) const;

  Standard_EXPORT bool IsInstance(const char* theTypeName) const;

  Standard_EXPORT bool IsKind(const opencascade::handle<Standard_Type>& theType) const;

  Standard_EXPORT bool IsKind(const char* theTypeName) const;

  Standard_EXPORT Standard_Transient* This() const;

public:
  inline int GetRefCount() const noexcept { return myRefCount_; }

  inline void IncrementRefCounter() noexcept { myRefCount_.operator++(); }

  inline int DecrementRefCounter() noexcept { return myRefCount_.operator--(); }

  virtual void Delete() const { delete this; }

private:
  std::atomic_int myRefCount_;
};

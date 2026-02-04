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

//! Abstract class which forms the root of the entire
//! Transient class hierarchy.

class Standard_Transient
{
public:
  // Standard OCCT memory allocation stuff
  DEFINE_STANDARD_ALLOC

public:
  //! Empty constructor
  Standard_Transient()
      : myRefCount_(0)
  {
  }

  //! Copy constructor -- does nothing
  Standard_Transient(const Standard_Transient&)
      : myRefCount_(0)
  {
  }

  //! Assignment operator, needed to avoid copying reference counter
  Standard_Transient& operator=(const Standard_Transient&) { return *this; }

  //! Destructor must be virtual
  virtual ~Standard_Transient() = default;

public:
  //!@name Support of run-time type information (RTTI)

  typedef void base_type;

  static constexpr const char* get_type_name() { return "Standard_Transient"; }

  //! Returns type descriptor of Standard_Transient class
  Standard_EXPORT static const opencascade::handle<Standard_Type>& get_type_descriptor();

  //! Returns a type descriptor about this object.
  Standard_EXPORT virtual const opencascade::handle<Standard_Type>& DynamicType() const;

  //! Returns a true value if this is an instance of Type.
  Standard_EXPORT bool IsInstance(const opencascade::handle<Standard_Type>& theType) const;

  //! Returns a true value if this is an instance of TypeName.
  Standard_EXPORT bool IsInstance(const char* theTypeName) const;

  //! Returns true if this is an instance of Type or an
  //! instance of any class that inherits from Type.
  //! Note that multiple inheritance is not supported by OCCT RTTI mechanism.
  Standard_EXPORT bool IsKind(const opencascade::handle<Standard_Type>& theType) const;

  //! Returns true if this is an instance of TypeName or an
  //! instance of any class that inherits from TypeName.
  //! Note that multiple inheritance is not supported by OCCT RTTI mechanism.
  Standard_EXPORT bool IsKind(const char* theTypeName) const;

  //! Returns non-const pointer to this object (like const_cast).
  //! For protection against creating handle to objects allocated in stack
  //! or call from constructor, it will raise exception Standard_ProgramError
  //! if reference counter is zero.
  Standard_EXPORT Standard_Transient* This() const;

public:
  //!@name Reference counting, for use by handle<>

  //! Get the reference counter of this object
  inline int GetRefCount() const noexcept { return myRefCount_; }

  //! Increments the reference counter of this object
  inline void IncrementRefCounter() noexcept { myRefCount_.operator++(); }

  //! Decrements the reference counter of this object;
  //! returns the decremented value
  inline int DecrementRefCounter() noexcept { return myRefCount_.operator--(); }

  //! Memory deallocator for transient classes
  virtual void Delete() const { delete this; }

private:
  //! Reference counter.
  //! Note use of underscore, aimed to reduce probability
  //! of conflict with names of members of derived classes.
  std::atomic_int myRefCount_;
};

//! Definition of opencascade::handle<Standard_Transient> as typedef for compatibility


#pragma once

#include <Standard_Handle.hpp>
#include <Standard_DefineHandle.hpp>

class TObj_Object;

class TObj_ObjectIterator : public Standard_Transient
{
public:
  virtual Standard_EXPORT bool More() const;

  virtual Standard_EXPORT void Next();

  virtual Standard_EXPORT occ::handle<TObj_Object> Value() const;

public:
  DEFINE_STANDARD_RTTIEXT(TObj_ObjectIterator, Standard_Transient)
};

#ifdef _MSC_VER
  #pragma once
#endif

#pragma once

#include <TObj_Object.hpp>
#include <NCollection_Sequence.hpp>
#include <TObj_ObjectIterator.hpp>

class TObj_ModelIterator : public TObj_ObjectIterator
{
public:
  Standard_EXPORT TObj_ModelIterator(const occ::handle<TObj_Model>& theModel);

public:
  Standard_EXPORT bool More() const override;

  Standard_EXPORT void Next() override;

  Standard_EXPORT occ::handle<TObj_Object> Value() const override;

protected:
  virtual Standard_EXPORT void addIterator(const occ::handle<TObj_Object>& theObj);

protected:
  occ::handle<TObj_Object>                               myObject;
  NCollection_Sequence<occ::handle<TObj_ObjectIterator>> myIterSeq;

public:
  DEFINE_STANDARD_RTTIEXT(TObj_ModelIterator, TObj_ObjectIterator)
};

#ifdef _MSC_VER
  #pragma once
#endif

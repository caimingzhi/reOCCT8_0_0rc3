#pragma once

#include <TObj_Object.hpp>

#include <TDF_Label.hpp>
#include <TDF_ChildIterator.hpp>
#include <TObj_ObjectIterator.hpp>

class TObj_LabelIterator : public TObj_ObjectIterator
{

protected:
  Standard_EXPORT TObj_LabelIterator();

public:
  Standard_EXPORT TObj_LabelIterator(const TDF_Label& theLabel, const bool isRecursive = false);

public:
  bool More() const override { return !myNode.IsNull(); }

  Standard_EXPORT void Next() override;

  occ::handle<TObj_Object> Value() const override { return myObject; }

  inline const TDF_Label& LabelValue() const { return myNode; }

protected:
  virtual void MakeStep() = 0;

protected:
  void Init(const TDF_Label& theLabel, const bool isRecursive = false)
  {
    myIterator.Initialize(theLabel, isRecursive);
  }

protected:
  TDF_Label                myNode;
  TDF_ChildIterator        myIterator;
  occ::handle<TObj_Object> myObject;

public:
  DEFINE_STANDARD_RTTIEXT(TObj_LabelIterator, TObj_ObjectIterator)
};

#ifdef _MSC_VER
  #pragma once
#endif

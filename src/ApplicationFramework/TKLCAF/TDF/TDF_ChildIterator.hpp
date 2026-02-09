#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>
#include <TDF_Label.hpp>
class TDF_Label;

class TDF_ChildIterator
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TDF_ChildIterator();

  Standard_EXPORT TDF_ChildIterator(const TDF_Label& aLabel, const bool allLevels = false);

  Standard_EXPORT void Initialize(const TDF_Label& aLabel, const bool allLevels = false);

  bool More() const;

  Standard_EXPORT void Next();

  Standard_EXPORT void NextBrother();

  const TDF_Label Value() const;

private:
  TDF_LabelNodePtr myNode;
  int              myFirstLevel;
};

inline bool TDF_ChildIterator::More() const
{
  return (myNode != nullptr);
}

inline const TDF_Label TDF_ChildIterator::Value() const
{
  return TDF_Label(myNode);
}

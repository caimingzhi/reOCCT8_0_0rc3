#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_GUID.hpp>
#include <TDF_ChildIterator.hpp>
class TDF_Attribute;
class TDF_Label;

class TDF_ChildIDIterator
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TDF_ChildIDIterator();

  Standard_EXPORT TDF_ChildIDIterator(const TDF_Label&     aLabel,
                                      const Standard_GUID& anID,
                                      const bool           allLevels = false);

  Standard_EXPORT void Initialize(const TDF_Label&     aLabel,
                                  const Standard_GUID& anID,
                                  const bool           allLevels = false);

  bool More() const;

  Standard_EXPORT void Next();

  Standard_EXPORT void NextBrother();

  occ::handle<TDF_Attribute> Value() const;

private:
  Standard_GUID              myID;
  TDF_ChildIterator          myItr;
  occ::handle<TDF_Attribute> myAtt;
};

inline bool TDF_ChildIDIterator::More() const
{
  return !myAtt.IsNull();
}

inline occ::handle<TDF_Attribute> TDF_ChildIDIterator::Value() const
{
  return myAtt;
}

#pragma once

#include <TDF_Label.hpp>
#include <TDF_LabelNodePtr.hpp>

class TDF_AttributeIterator
{

public:
  Standard_EXPORT      TDF_AttributeIterator();
  Standard_EXPORT      TDF_AttributeIterator(const TDF_Label& aLabel,
                                             const bool       withoutForgotten = true);
  Standard_EXPORT      TDF_AttributeIterator(const TDF_LabelNodePtr aLabelNode,
                                             const bool             withoutForgotten = true);
  Standard_EXPORT void Initialize(const TDF_Label& aLabel, const bool withoutForgotten = true);
  inline bool          More() const;
  Standard_EXPORT void Next();
  inline occ::handle<TDF_Attribute> Value() const;

  inline const TDF_Attribute* PtrValue() const { return myValue; }

private:
  void goToNext(const occ::handle<TDF_Attribute>& anAttr);

  TDF_Attribute* myValue;
  bool           myWithoutForgotten;
};

inline bool TDF_AttributeIterator::More() const
{
  return (myValue != nullptr);
}

inline occ::handle<TDF_Attribute> TDF_AttributeIterator::Value() const
{
  return myValue;
}

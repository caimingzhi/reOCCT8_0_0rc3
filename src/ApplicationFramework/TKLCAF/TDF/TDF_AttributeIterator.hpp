#pragma once


#include <TDF_Label.hpp>
#include <TDF_LabelNodePtr.hpp>

// This class provides a way to iterates on the
// up-to-date (current) valid attributes of a label.
//
// This class should not be used for standard attributes workflow.
// Application always knows what to search at particular label.
// So, use IsAttribute and FindAttribute methods of
// TDF_Label to check and get attributes in usual way.
// This class may be used for processing of content of labels
// in generic way, like copy-tool, specific save/restore algorithms,
// etc.
//
// Even a forgotten attribute may be found if this
// option is set. To use this possibility, look at
// the constructor.

class TDF_AttributeIterator
{

public:
  // Methods PUBLIC
  //
  Standard_EXPORT      TDF_AttributeIterator();
  Standard_EXPORT      TDF_AttributeIterator(const TDF_Label& aLabel,
                                             const bool       withoutForgotten = true);
  Standard_EXPORT      TDF_AttributeIterator(const TDF_LabelNodePtr aLabelNode,
                                             const bool             withoutForgotten = true);
  Standard_EXPORT void Initialize(const TDF_Label& aLabel, const bool withoutForgotten = true);
  inline bool          More() const;
  Standard_EXPORT void Next();
  inline occ::handle<TDF_Attribute> Value() const;

  //! Provides an access to the internal pointer of the current attribute.
  //! The method has better performance as not-creating handle.
  inline const TDF_Attribute* PtrValue() const { return myValue; }

private:
  // Methods PRIVATE
  //
  void goToNext(const occ::handle<TDF_Attribute>& anAttr);

  // Fields PRIVATE
  //
  TDF_Attribute* myValue;
  bool           myWithoutForgotten;
};

// other inline functions and methods (like "C++: function call" methods)
//

inline bool TDF_AttributeIterator::More() const
{
  return (myValue != nullptr);
}

inline occ::handle<TDF_Attribute> TDF_AttributeIterator::Value() const
{
  return myValue;
}


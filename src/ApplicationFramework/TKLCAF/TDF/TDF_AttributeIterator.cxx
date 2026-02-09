#include <TDF_AttributeIterator.hpp>

TDF_AttributeIterator::TDF_AttributeIterator()
    : myValue(nullptr),
      myWithoutForgotten(true)
{
}

TDF_AttributeIterator::TDF_AttributeIterator(const TDF_Label& aLabel, const bool withoutForgotten)
    : myValue(nullptr),
      myWithoutForgotten(withoutForgotten)
{
  const occ::handle<TDF_Attribute>& aFirstAttribute = aLabel.myLabelNode->FirstAttribute();
  if (!aFirstAttribute.IsNull())
    goToNext(aFirstAttribute);
}

TDF_AttributeIterator::TDF_AttributeIterator(const TDF_LabelNodePtr aLabelNode,
                                             const bool             withoutForgotten)
    : myValue(nullptr),
      myWithoutForgotten(withoutForgotten)
{
  const occ::handle<TDF_Attribute>& aFirstAttribute = aLabelNode->FirstAttribute();
  if (!aFirstAttribute.IsNull())
    goToNext(aFirstAttribute);
}

void TDF_AttributeIterator::Initialize(const TDF_Label& aLabel, const bool withoutForgotten)
{
  myWithoutForgotten                                = withoutForgotten;
  const occ::handle<TDF_Attribute>& aFirstAttribute = aLabel.myLabelNode->FirstAttribute();
  if (aFirstAttribute.IsNull())
    myValue = nullptr;
  else
    goToNext(aFirstAttribute);
}

void TDF_AttributeIterator::Next()
{

  if (myValue)
  {
    const occ::handle<TDF_Attribute>& anAttribute = myValue->myNext;
    if (anAttribute.IsNull())
      myValue = nullptr;
    else
      goToNext(anAttribute);
  }
}

void TDF_AttributeIterator::goToNext(const occ::handle<TDF_Attribute>& anAttr)
{
  myValue = anAttr.operator->();
  if (myWithoutForgotten)
  {
    while (myValue->IsForgotten())
    {
      const occ::handle<TDF_Attribute>& anAttribute = myValue->myNext;
      if (anAttribute.IsNull())
      {
        myValue = nullptr;
        break;
      }
      myValue = anAttribute.operator->();
    }
  }
}

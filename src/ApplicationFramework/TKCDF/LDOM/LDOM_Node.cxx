#include <LDOM_BasicAttribute.hpp>
#include <LDOM_BasicElement.hpp>
#include <LDOM_BasicText.hpp>

const LDOM_BasicNode& LDOM_Node::Origin() const
{
  if (myOrigin == nullptr)
  {
    static LDOM_BasicNode aNullNode;
    return aNullNode;
  }
  return *myOrigin;
}

const LDOM_MemManager& LDOM_Node::getOwnerDocument() const
{
  return myDocument->Self();
}

LDOM_Node& LDOM_Node::operator=(const LDOM_Node& theOther) = default;

LDOM_Node& LDOM_Node::operator=(const LDOM_NullPtr*)
{
  myDocument.Nullify();
  myOrigin    = nullptr;
  myLastChild = nullptr;
  return *this;
}

bool LDOM_Node::isNull() const
{
  return myOrigin == nullptr || myOrigin->isNull();
}

bool LDOM_Node::operator==(const LDOM_Node& anOther) const
{
  if (isNull())
    return anOther.isNull();
  return myOrigin == anOther.myOrigin;
}

bool LDOM_Node::operator!=(const LDOM_Node& anOther) const
{
  if (isNull())
    return !anOther.isNull();
  return myOrigin != anOther.myOrigin;
}

LDOM_Node::NodeType LDOM_Node::getNodeType() const
{
  return myOrigin == nullptr ? UNKNOWN : myOrigin->getNodeType();
}

LDOMString LDOM_Node::getNodeName() const
{
  switch (getNodeType())
  {
    case ELEMENT_NODE:
    {
      const LDOM_BasicElement& anElement = *(const LDOM_BasicElement*)myOrigin;
      return LDOMString::CreateDirectString(anElement.GetTagName(), myDocument->Self());
    }
    case ATTRIBUTE_NODE:
    {
      const LDOM_BasicAttribute& anAttr = *(const LDOM_BasicAttribute*)myOrigin;
      return LDOMString::CreateDirectString(anAttr.GetName(), myDocument->Self());
    }
    default:;
  }
  return LDOMString();
}

LDOMString LDOM_Node::getNodeValue() const
{
  switch (getNodeType())
  {
    case ATTRIBUTE_NODE:
    {
      const LDOM_BasicAttribute& anAttr = *(const LDOM_BasicAttribute*)myOrigin;
      return LDOMString(anAttr.GetValue(), myDocument->Self());
    }
    case TEXT_NODE:
    case CDATA_SECTION_NODE:
    case COMMENT_NODE:
    {
      const LDOM_BasicText& aText = *(const LDOM_BasicText*)myOrigin;
      return LDOMString(aText.GetData(), myDocument->Self());
    }
    default:;
  }
  return LDOMString();
}

LDOM_Node LDOM_Node::getFirstChild() const
{
  const NodeType aType = getNodeType();
  if (aType == ELEMENT_NODE)
  {
    const LDOM_BasicElement& anElement = *(const LDOM_BasicElement*)myOrigin;
    const LDOM_BasicNode*    aChild    = anElement.GetFirstChild();
    if (aChild)
      if (aChild->getNodeType() != LDOM_Node::ATTRIBUTE_NODE)
        return LDOM_Node(*aChild, myDocument);
  }
  return LDOM_Node();
}

LDOM_Node LDOM_Node::getLastChild() const
{
  const NodeType aType = getNodeType();
  if (aType == ELEMENT_NODE)
  {
    if (myLastChild == nullptr)
    {
      const LDOM_BasicElement& anElement  = *(const LDOM_BasicElement*)myOrigin;
      (const LDOM_BasicNode*&)myLastChild = anElement.GetLastChild();
    }
    return LDOM_Node(*myLastChild, myDocument);
  }
  return LDOM_Node();
}

LDOM_Node LDOM_Node::getNextSibling() const
{
  const LDOM_BasicNode* aSibling = myOrigin->mySibling;
  if (aSibling)
    if (aSibling->getNodeType() != ATTRIBUTE_NODE)
      return LDOM_Node(*aSibling, myDocument);
  return LDOM_Node();
}

void LDOM_Node::removeChild(const LDOM_Node& aChild)
{
  const NodeType aType = getNodeType();
  if (aType == ELEMENT_NODE)
  {
    const LDOM_BasicElement& anElement = *(LDOM_BasicElement*)myOrigin;
    if (aChild != nullptr)
      anElement.RemoveChild(aChild.myOrigin);
    if (aChild.myOrigin == myLastChild)

      myLastChild = nullptr;
  }
}

void LDOM_Node::appendChild(const LDOM_Node& aChild)
{
  const NodeType aType = getNodeType();
  if (aType == ELEMENT_NODE && aChild != nullptr)
  {
    if (myLastChild)
    {
      aChild.myOrigin->SetSibling(myLastChild->mySibling);
      (const LDOM_BasicNode*&)myLastChild->mySibling = aChild.myOrigin;
    }
    else
    {
      const LDOM_BasicElement& anElement = *(LDOM_BasicElement*)myOrigin;
      anElement.AppendChild(aChild.myOrigin, myLastChild);
    }
    myLastChild = aChild.myOrigin;
  }
}

bool LDOM_Node::hasChildNodes() const
{
  const NodeType aType = getNodeType();
  if (aType == ELEMENT_NODE)
  {
    const LDOM_BasicElement& anElement = *(const LDOM_BasicElement*)myOrigin;
    const LDOM_BasicNode*    aChild    = anElement.GetFirstChild();
    if (aChild)
      return !aChild->isNull();
  }
  return false;
}

void LDOM_Node::SetValueClear() const
{
  LDOMBasicString* aValue = nullptr;
  switch (getNodeType())
  {
    case ATTRIBUTE_NODE:
    {
      const LDOM_BasicAttribute& anAttr = *(const LDOM_BasicAttribute*)myOrigin;
      aValue                            = (LDOMBasicString*)&anAttr.GetValue();
      break;
    }
    case TEXT_NODE:
    case CDATA_SECTION_NODE:
    case COMMENT_NODE:
    {
      const LDOM_BasicText& aText = *(const LDOM_BasicText*)myOrigin;
      aValue                      = (LDOMBasicString*)&aText.GetData();
      break;
    }
    default:
      return;
  }
  if (aValue->Type() == LDOMBasicString::LDOM_AsciiDoc)
    aValue->myType = LDOMBasicString::LDOM_AsciiDocClear;
}

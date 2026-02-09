#pragma once

#include <LDOM_BasicNode.hpp>
#include <LDOMBasicString.hpp>
#include <LDOM_Node.hpp>

class LDOM_NodeList;
class LDOM_BasicAttribute;

class LDOM_BasicElement : public LDOM_BasicNode
{
public:
  LDOM_BasicElement()
      : LDOM_BasicNode(LDOM_Node::UNKNOWN),
        myTagName(nullptr),
        myAttributeMask(0),
        myFirstChild(nullptr)
  {
  }

  static LDOM_BasicElement& Create(const char*                         aName,
                                   const int                           aLength,
                                   const occ::handle<LDOM_MemManager>& aDoc);

  Standard_EXPORT LDOM_BasicElement& operator=(const LDOM_NullPtr* aNull);

  Standard_EXPORT ~LDOM_BasicElement();

  const char* GetTagName() const { return myTagName; }

  const LDOM_BasicNode* GetFirstChild() const { return myFirstChild; }

  Standard_EXPORT const LDOM_BasicNode* GetLastChild() const;

  Standard_EXPORT const LDOM_BasicAttribute& GetAttribute(const LDOMBasicString& aName,
                                                          const LDOM_BasicNode*  aLastCh) const;

protected:
  Standard_EXPORT const LDOM_BasicNode* AddAttribute(const LDOMBasicString& anAttrName,
                                                     const LDOMBasicString& anAttrValue,
                                                     const occ::handle<LDOM_MemManager>& aDoc,
                                                     const LDOM_BasicNode*               aLastCh);

  Standard_EXPORT const LDOM_BasicNode* RemoveAttribute(const LDOMBasicString& aName,
                                                        const LDOM_BasicNode*  aLastCh) const;

  Standard_EXPORT void RemoveChild(const LDOM_BasicNode* aChild) const;

  Standard_EXPORT void AppendChild(const LDOM_BasicNode*  aChild,
                                   const LDOM_BasicNode*& aLastCh) const;

private:
  friend class LDOMParser;
  friend class LDOM_XmlReader;
  friend class LDOM_Document;
  friend class LDOM_Element;
  friend class LDOM_Node;

  const LDOM_BasicAttribute* GetFirstAttribute(const LDOM_BasicNode*&  aLastCh,
                                               const LDOM_BasicNode**& thePrN) const;

  void RemoveNodes();

  void ReplaceElement(const LDOM_BasicElement& anOther, const occ::handle<LDOM_MemManager>& aDoc);

  void AddElementsByTagName(LDOM_NodeList& aList, const LDOMBasicString& aTagName) const;

  void AddAttributes(LDOM_NodeList& aList, const LDOM_BasicNode* aLastCh) const;

private:
  const char*     myTagName;
  unsigned long   myAttributeMask;
  LDOM_BasicNode* myFirstChild;
};

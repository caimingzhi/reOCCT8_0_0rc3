#pragma once

#include <LDOM_Node.hpp>

class LDOM_NullPtr;

//  Block of comments describing class LDOM_BasicNode
//

class LDOM_BasicNode
{
public:
  DEFINE_STANDARD_ALLOC

public:
  bool isNull() const { return myNodeType == LDOM_Node::UNKNOWN; }

  LDOM_Node::NodeType getNodeType() const { return myNodeType; }

  Standard_EXPORT const LDOM_BasicNode* GetSibling() const;

protected:
  // ---------- PROTECTED METHODS ----------

  LDOM_BasicNode()
      : myNodeType(LDOM_Node::UNKNOWN),
        mySibling(nullptr)
  {
  }

  //    Empty constructor

  LDOM_BasicNode(LDOM_Node::NodeType aType)
      : myNodeType(aType),
        mySibling(nullptr)
  {
  }

  //    Constructor

  LDOM_BasicNode(const LDOM_BasicNode& anOther)
      : myNodeType(anOther.getNodeType()),
        mySibling(anOther.GetSibling())
  {
  }

  //    Copy constructor

  LDOM_BasicNode& operator=(const LDOM_NullPtr*)
  {
    myNodeType = LDOM_Node::UNKNOWN;
    return *this;
  }

  Standard_EXPORT LDOM_BasicNode& operator=(const LDOM_BasicNode& anOther);

  void SetSibling(const LDOM_BasicNode* anOther) { mySibling = anOther; }

protected:
  friend class LDOM_BasicElement;
  friend class LDOM_Node;
  friend class LDOMParser;
  // ---------- PROTECTED FIELDSS ----------

  LDOM_Node::NodeType   myNodeType;
  const LDOM_BasicNode* mySibling;
};

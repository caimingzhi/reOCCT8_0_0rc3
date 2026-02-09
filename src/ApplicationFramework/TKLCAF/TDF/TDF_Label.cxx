#include <Standard_DomainError.hpp>
#include <Standard_ImmutableObject.hpp>
#include <Standard_NullObject.hpp>
#include <TDF_AttributeIterator.hpp>
#include <TDF_ChildIterator.hpp>
#include <TDF_Data.hpp>
#include <TDF_IDFilter.hpp>
#include <TDF_Label.hpp>
#include <TDF_LabelNode.hpp>
#include <TDF_LabelNodePtr.hpp>
#include <TDF_Tool.hpp>

void TDF_Label::Imported(const bool aStatus) const
{
  if (IsNull())
    throw Standard_NullObject("A null Label has no status.");
  if (myLabelNode->IsImported() != aStatus)
  {
    myLabelNode->Imported(aStatus);
    for (TDF_ChildIterator itr(*this, true); itr.More(); itr.Next())
      itr.Value().myLabelNode->Imported(aStatus);
  }
}

bool TDF_Label::FindAttribute(const Standard_GUID&        anID,
                              occ::handle<TDF_Attribute>& anAttribute) const
{
  if (IsNull())
    throw Standard_NullObject("A null Label has no attribute.");
  TDF_AttributeIterator itr(myLabelNode);
  for (; itr.More(); itr.Next())
  {
    if (itr.PtrValue()->ID() == anID)
    {
      anAttribute = itr.PtrValue();
      return true;
    }
  }
  return false;
}

bool TDF_Label::FindAttribute(const Standard_GUID&        anID,
                              const int                   aTransaction,
                              occ::handle<TDF_Attribute>& anAttribute) const
{
  occ::handle<TDF_Attribute> locAtt;
  if (FindAttribute(anID, locAtt))
  {
    while ((!locAtt.IsNull()) && (locAtt->myTransaction > aTransaction))
      locAtt = locAtt->myBackup;
    if (!locAtt.IsNull())
    {
      anAttribute = locAtt;
      return true;
    }
  }
  return false;
}

int TDF_Label::Depth() const
{
  if (IsNull())
    throw Standard_NullObject("A null Label has no depth.");
  return myLabelNode->Depth();
}

bool TDF_Label::IsDescendant(const TDF_Label& aLabel) const
{

  const TDF_LabelNode* lp1 = aLabel.myLabelNode;
  TDF_LabelNode*       lp2 = myLabelNode;
#ifdef OCCT_DEBUG
  if ((lp1 == NULL) || (lp2 == NULL))
    throw Standard_NullObject("A null label has no ancestor nor descendant.");
#endif
  if ((lp1 != nullptr) && (lp2 != nullptr))
  {
    const int d1 = lp1->Depth();
    int       d2 = lp2->Depth();

    while ((d2 > d1) && (lp2 != lp1))
    {
      lp2 = lp2->Father();
      d2  = lp2->Depth();
    }
    return (lp1 == lp2);
  }
  return false;
}

const TDF_Label TDF_Label::Root() const
{
  if (IsNull())
    throw Standard_NullObject("A null Label has no root.");
  return myLabelNode->RootNode();
}

int TDF_Label::NbChildren() const
{
  if (IsNull())
    throw Standard_NullObject("A null Label has no children.");
  int n = 0;
  if (myLabelNode->FirstChild() != nullptr)
    for (TDF_ChildIterator itr(*this); itr.More(); itr.Next())
      ++n;
  return n;
}

TDF_Label TDF_Label::FindChild(const int aTag, const bool create) const
{
  if (IsNull())
    throw Standard_NullObject("A null Label has no child.");
  if (create && ((Depth() + 1) & TDF_LabelNodeFlagsMsk))
    throw Standard_OutOfRange("Depth value out of range");

  return FindOrAddChild(aTag, create);
}

bool TDF_Label::IsAttribute(const Standard_GUID& anID) const
{
  occ::handle<TDF_Attribute> att;
  return FindAttribute(anID, att);
}

bool TDF_Label::HasAttribute() const
{
  if (IsNull())
    throw Standard_NullObject("A null Label has no attribute.");

  if (!myLabelNode->FirstAttribute().IsNull())
  {
    TDF_AttributeIterator itr(myLabelNode);
    return itr.More();
  }
  return false;
}

int TDF_Label::NbAttributes() const
{
  if (IsNull())
    throw Standard_NullObject("A null Label has no attribute.");
  int n = 0;
  if (!myLabelNode->FirstAttribute().IsNull())
    for (TDF_AttributeIterator itr(myLabelNode); itr.More(); itr.Next())
      ++n;
  return n;
}

int TDF_Label::Transaction() const
{
  if (IsNull())
    throw Standard_NullObject("A null Label has no transaction.");
  return myLabelNode->Data()->Transaction();
}

Standard_OStream& TDF_Label::Dump(Standard_OStream& anOS) const
{
  TDF_IDFilter                                       f;
  NCollection_IndexedMap<occ::handle<TDF_Attribute>> m;
  TDF_Label::InternalDump(anOS, f, m, false);
  return anOS;
}

void TDF_Label::ExtendedDump(Standard_OStream&                                   anOS,
                             const TDF_IDFilter&                                 aFilter,
                             NCollection_IndexedMap<occ::handle<TDF_Attribute>>& aMap) const
{
  TDF_Label::InternalDump(anOS, aFilter, aMap, true);
}

void TDF_Label::EntryDump(Standard_OStream& anOS) const
{
  if (IsNull())
  {
    anOS << "This label is null.";
  }
  else
  {
    TCollection_AsciiString entry;
    TDF_Tool::Entry(*this, entry);
    anOS << entry;
  }
}

TDF_LabelNode* TDF_Label::FindOrAddChild(const int aTag, const bool create) const
{
  TDF_LabelNode* currentLnp     = myLabelNode->FirstChild();
  TDF_LabelNode* lastLnp        = nullptr;
  TDF_LabelNode* lastFoundLnp   = myLabelNode->myLastFoundChild;
  TDF_LabelNode* childLabelNode = nullptr;

  if (lastFoundLnp != nullptr)
  {
    if (lastFoundLnp->Tag() == aTag)
    {
      return lastFoundLnp;
    }
    else if (lastFoundLnp->Tag() < aTag)
    {
      lastLnp    = lastFoundLnp;
      currentLnp = lastFoundLnp->Brother();
    }
  }

  while ((currentLnp != nullptr) && (currentLnp->Tag() < aTag))
  {
    lastLnp    = currentLnp;
    currentLnp = currentLnp->Brother();
  }

  if ((currentLnp != nullptr) && (currentLnp->Tag() == aTag))
  {

    childLabelNode = currentLnp;
  }
  else if (create)
  {

    const TDF_HAllocator& anAllocator = myLabelNode->Data()->LabelNodeAllocator();
    childLabelNode                    = new (anAllocator) TDF_LabelNode(aTag, myLabelNode);
    childLabelNode->myBrother         = currentLnp;
    childLabelNode->Imported(IsImported());

    if (lastLnp == nullptr)
      myLabelNode->myFirstChild = childLabelNode;
    else
      lastLnp->myBrother = childLabelNode;

    if (myLabelNode->Data()->IsAccessByEntries())
      myLabelNode->Data()->RegisterLabel(childLabelNode);
  }

  if (lastLnp)
    myLabelNode->myLastFoundChild = lastLnp;

  return childLabelNode;
}

void TDF_Label::InternalDump(Standard_OStream&                                   anOS,
                             const TDF_IDFilter&                                 aFilter,
                             NCollection_IndexedMap<occ::handle<TDF_Attribute>>& aMap,
                             const bool                                          extended) const
{
  if (IsNull())
  {
    anOS << "This label is null.";
  }
  else
  {
    TCollection_AsciiString entry;
    TDF_Tool::Entry(*this, entry);
    anOS << entry << "\t";
    if (IsImported())
      anOS << "IS ";
    else
      anOS << "NOT";
    anOS << " imported; ";
    if (MayBeModified())
      anOS << "MAYBE";
    else
      anOS << "NOT";
    anOS << " modified; ";
    if (AttributesModified())
      anOS << "HAS attributes";
    else
      anOS << "NO attribute";
    anOS << " modified; ";
    if (HasAttribute())
    {
      int nba = NbAttributes();
      anOS << "has " << nba << " attribute";
      if (nba > 1)
        anOS << "s";
      anOS << "." << std::endl;
      for (TDF_AttributeIterator itr(myLabelNode); itr.More(); itr.Next())
      {

        occ::handle<TDF_Attribute> att = itr.Value();

        if (extended && aFilter.IsKept(att))
          anOS << "\t# " << aMap.Add(att);
        att->TDF_Attribute::Dump(anOS);
      }
    }
    else
    {
      anOS << " has no attribute" << std::endl;
    }
  }
}

bool TDF_Label::HasLowerNode(const TDF_Label& aLabel) const
{
  return (myLabelNode < aLabel.myLabelNode);
}

bool TDF_Label::HasGreaterNode(const TDF_Label& aLabel) const
{
  return (myLabelNode > aLabel.myLabelNode);
}

void TDF_Label::AddAttribute(const occ::handle<TDF_Attribute>& anAttribute, const bool append) const
{
  AddToNode(myLabelNode, anAttribute, append);
}

void TDF_Label::ForgetAttribute(const occ::handle<TDF_Attribute>& anAttribute) const
{
  ForgetFromNode(myLabelNode, anAttribute);
}

bool TDF_Label::ForgetAttribute(const Standard_GUID& anID) const
{
  occ::handle<TDF_Attribute> anAttribute;

  if (FindAttribute(anID, anAttribute))
  {
    ForgetAttribute(anAttribute);
    return true;
  }
  return false;
}

void TDF_Label::ForgetAllAttributes(const bool clearChildren) const
{
  TDF_AttributeIterator itr1(myLabelNode);

  while (itr1.More())
  {
    const occ::handle<TDF_Attribute> anAttr = itr1.Value();
    itr1.Next();
    ForgetFromNode(myLabelNode, anAttr);
  }

  if (clearChildren)
    for (TDF_ChildIterator itr2(myLabelNode); itr2.More(); itr2.Next())
    {
      itr2.Value().ForgetAllAttributes(clearChildren);
    }
}

void TDF_Label::ResumeAttribute(const occ::handle<TDF_Attribute>& anAttribute) const
{
  ResumeToNode(myLabelNode, anAttribute);
}

void TDF_Label::AddToNode(const TDF_LabelNodePtr&           toNode,
                          const occ::handle<TDF_Attribute>& anAttribute,
                          const bool                        append) const
{

  if (!toNode->Data()->IsModificationAllowed())
  {
    TCollection_AsciiString aMess;
    aMess = "Attribute \"";
    aMess += anAttribute->DynamicType()->Name();
    aMess += "\" is added to label outside transaction";
    throw Standard_ImmutableObject(aMess.ToCString());
  }

  if (!anAttribute->Label().IsNull())
    throw Standard_DomainError("Attribute to add is already attached to a label.");
  occ::handle<TDF_Attribute> dummyAtt;

  if (FindAttribute(anAttribute->ID(), dummyAtt))
    throw Standard_DomainError("This label has already such an attribute.");

  anAttribute->myTransaction      = toNode->Data()->Transaction();
  anAttribute->mySavedTransaction = 0;

  dummyAtt.Nullify();
  if (append)
  {
    for (TDF_AttributeIterator itr(toNode); itr.More(); itr.Next())
      dummyAtt = itr.Value();
  }

  toNode->AddAttribute(dummyAtt, anAttribute);
  toNode->AttributesModified(anAttribute->myTransaction != 0);

  if (toNode->Data()->NotUndoMode())
    anAttribute->AfterAddition();
}

void TDF_Label::ForgetFromNode(const TDF_LabelNodePtr&           fromNode,
                               const occ::handle<TDF_Attribute>& anAttribute) const
{

  if (!fromNode->Data()->IsModificationAllowed())
  {
    TCollection_AsciiString aMess;
    aMess = "Attribute \"";
    aMess += anAttribute->DynamicType()->Name();
    aMess += "\" is removed from label outside transaction";
    throw Standard_ImmutableObject(aMess.ToCString());
  }

  if (fromNode != anAttribute->Label().myLabelNode)
    throw Standard_DomainError("Attribute to forget not attached to my label.");

  int curTrans = fromNode->Data()->Transaction();
  if (!anAttribute->IsForgotten())
  {
    if ((curTrans == 0)
        || ((anAttribute->myTransaction == curTrans) && anAttribute->myBackup.IsNull()))
    {

      occ::handle<TDF_Attribute> lastAtt;
      for (TDF_AttributeIterator itr(fromNode, false); itr.More(); itr.Next())
      {
        if (itr.Value() == anAttribute)
        {

          if (fromNode->Data()->NotUndoMode())
          {
            anAttribute->BeforeForget();
            anAttribute->BeforeRemoval();
          }
          fromNode->RemoveAttribute(lastAtt, anAttribute);
          anAttribute->Forget(fromNode->Data()->Transaction());
          break;
        }
        lastAtt = itr.Value();
      }
    }
    else
    {

      if (fromNode->Data()->NotUndoMode())
        anAttribute->BeforeForget();
      anAttribute->Forget(fromNode->Data()->Transaction());
    }
  }
}

void TDF_Label::ResumeToNode(const TDF_LabelNodePtr&           toNode,
                             const occ::handle<TDF_Attribute>& anAttribute) const
{
  if (anAttribute.IsNull())
    throw Standard_NullObject("The attribute is a null handle.");
  if (!anAttribute->Label().IsNull())
    throw Standard_NullObject("Cannot resume an attribute already attached to a label.");
  if (!anAttribute->IsForgotten())
    throw Standard_DomainError("Cannot resume an unforgotten attribute.");

  AddToNode(toNode, anAttribute, false);
  anAttribute->Resume();
  if (toNode->Data()->NotUndoMode())
    anAttribute->AfterResume();
}

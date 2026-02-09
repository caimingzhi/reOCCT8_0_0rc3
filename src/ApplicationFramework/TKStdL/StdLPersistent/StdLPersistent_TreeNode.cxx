

#include <StdLPersistent_TreeNode.hpp>

void StdLPersistent_TreeNode::Read(StdObjMgt_ReadData& theReadData)
{
  myDynamicData = new dynamic;
  theReadData >> myDynamicData->First >> myNext >> myDynamicData->TreeID;
}

void StdLPersistent_TreeNode::Write(StdObjMgt_WriteData& theWriteData) const
{
  theWriteData << myDynamicData->First << myNext << myDynamicData->TreeID;
}

void StdLPersistent_TreeNode::PChildren(
  StdObjMgt_Persistent::SequenceOfPersistent& theChildren) const
{
  theChildren.Append(myNext);
  if (!myDynamicData.IsNull())
    theChildren.Append(myDynamicData->First);
}

occ::handle<TDF_Attribute> StdLPersistent_TreeNode::CreateAttribute()
{
  Static::CreateAttribute();
  myTransient->SetTreeID(myDynamicData->TreeID);
  return myTransient;
}

void StdLPersistent_TreeNode::ImportAttribute()
{
  if (myDynamicData)
  {
    occ::handle<StdLPersistent_TreeNode> aChild = myDynamicData->First;
    while (aChild)
    {
      if (aChild->myTransient)
        myTransient->Append(aChild->myTransient);
      StdLPersistent_TreeNode* aCurr = aChild.get();
      aChild                         = aChild->myNext;
      aCurr->myNext.Nullify();
    }

    myDynamicData.Nullify();
  }
}

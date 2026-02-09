

#include <gtest/gtest.h>

#include <TDataStd_TreeNode.hpp>
#include <TDF_Data.hpp>
#include <TDF_Label.hpp>

TEST(TDataStd_TreeNode_Test, BUC60817_DescendantRelationship)
{

  occ::handle<TDF_Data> aDF = new TDF_Data();

  TDF_Label aLabel1 = aDF->Root().FindChild(2, true);
  TDF_Label aLabel2 = aDF->Root().FindChild(3, true);

  occ::handle<TDataStd_TreeNode> aTN1 = TDataStd_TreeNode::Set(aLabel1);
  occ::handle<TDataStd_TreeNode> aTN2 = TDataStd_TreeNode::Set(aLabel2);

  aTN1->Append(aTN2);

  EXPECT_TRUE(aTN2->IsDescendant(aTN1)) << "TN2 should be a descendant of TN1 after Append";

  EXPECT_FALSE(aTN1->IsDescendant(aTN2)) << "TN1 should not be a descendant of TN2";
}

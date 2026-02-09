

#include <TNaming_Tool.hpp>

#include <BRepPrimAPI_MakeBox.hpp>
#include <BRepPrimAPI_MakeSphere.hpp>
#include <TDF_Data.hpp>
#include <TDF_Label.hpp>
#include <TNaming_Builder.hpp>
#include <TNaming_NamedShape.hpp>
#include <TNaming_UsedShapes.hpp>
#include <TopoDS_Shape.hpp>

#include <gtest/gtest.h>

class TNaming_ToolTest : public ::testing::Test
{
protected:
  void SetUp() override
  {

    myData = new TDF_Data();
    myRoot = myData->Root();
  }

  void TearDown() override { myData.Nullify(); }

  TopoDS_Shape MakeBox(double dx, double dy, double dz)
  {
    return BRepPrimAPI_MakeBox(dx, dy, dz).Shape();
  }

  TopoDS_Shape MakeSphere(double radius) { return BRepPrimAPI_MakeSphere(radius).Shape(); }

  occ::handle<TDF_Data> myData;
  TDF_Label             myRoot;
};

TEST_F(TNaming_ToolTest, GetShape_Primitive)
{

  TopoDS_Shape aBox = MakeBox(10.0, 20.0, 30.0);

  TDF_Label       aLabel = myRoot.FindChild(1);
  TNaming_Builder aBuilder(aLabel);
  aBuilder.Generated(aBox);

  occ::handle<TNaming_NamedShape> aNS;
  ASSERT_TRUE(aLabel.FindAttribute(TNaming_NamedShape::GetID(), aNS));

  TopoDS_Shape aRetrievedShape = TNaming_Tool::GetShape(aNS);
  EXPECT_FALSE(aRetrievedShape.IsNull());
  EXPECT_TRUE(aRetrievedShape.IsSame(aBox));
}

TEST_F(TNaming_ToolTest, GetShape_NullNamedShape)
{
  occ::handle<TNaming_NamedShape> aNS;

  EXPECT_NO_THROW({
    if (!aNS.IsNull())
    {
      TNaming_Tool::GetShape(aNS);
    }
  });
}

TEST_F(TNaming_ToolTest, OriginalShape_Modification)
{

  TopoDS_Shape aBox1 = MakeBox(10.0, 10.0, 10.0);
  TopoDS_Shape aBox2 = MakeBox(20.0, 20.0, 20.0);

  TDF_Label       aLabel = myRoot.FindChild(1);
  TNaming_Builder aBuilder(aLabel);
  aBuilder.Modify(aBox1, aBox2);

  occ::handle<TNaming_NamedShape> aNS;
  ASSERT_TRUE(aLabel.FindAttribute(TNaming_NamedShape::GetID(), aNS));

  TopoDS_Shape aOriginal = TNaming_Tool::OriginalShape(aNS);
  EXPECT_FALSE(aOriginal.IsNull());
  EXPECT_TRUE(aOriginal.IsSame(aBox1));
}

TEST_F(TNaming_ToolTest, CurrentShape_NoModification)
{

  TopoDS_Shape aBox = MakeBox(10.0, 20.0, 30.0);

  TDF_Label       aLabel = myRoot.FindChild(1);
  TNaming_Builder aBuilder(aLabel);
  aBuilder.Generated(aBox);

  occ::handle<TNaming_NamedShape> aNS;
  ASSERT_TRUE(aLabel.FindAttribute(TNaming_NamedShape::GetID(), aNS));

  TopoDS_Shape aCurrentShape = TNaming_Tool::CurrentShape(aNS);
  EXPECT_FALSE(aCurrentShape.IsNull());
  EXPECT_TRUE(aCurrentShape.IsSame(aBox));
}

TEST_F(TNaming_ToolTest, CurrentShape_WithModification)
{

  TopoDS_Shape aBox1 = MakeBox(10.0, 10.0, 10.0);
  TopoDS_Shape aBox2 = MakeBox(20.0, 20.0, 20.0);

  TDF_Label       aLabel1 = myRoot.FindChild(1);
  TNaming_Builder aBuilder1(aLabel1);
  aBuilder1.Generated(aBox1);

  occ::handle<TNaming_NamedShape> aNS1;
  ASSERT_TRUE(aLabel1.FindAttribute(TNaming_NamedShape::GetID(), aNS1));

  TDF_Label       aLabel2 = myRoot.FindChild(2);
  TNaming_Builder aBuilder2(aLabel2);
  aBuilder2.Modify(aBox1, aBox2);

  TopoDS_Shape aCurrentShape = TNaming_Tool::CurrentShape(aNS1);
  EXPECT_FALSE(aCurrentShape.IsNull());
}

TEST_F(TNaming_ToolTest, HasLabel_ExistingShape)
{

  TopoDS_Shape aBox = MakeBox(10.0, 20.0, 30.0);

  TDF_Label       aLabel = myRoot.FindChild(1);
  TNaming_Builder aBuilder(aLabel);
  aBuilder.Generated(aBox);

  EXPECT_TRUE(TNaming_Tool::HasLabel(aLabel, aBox));
}

TEST_F(TNaming_ToolTest, HasLabel_NonExistingShape)
{

  TopoDS_Shape aBox    = MakeBox(10.0, 20.0, 30.0);
  TopoDS_Shape aSphere = MakeSphere(15.0);

  TDF_Label       aLabel = myRoot.FindChild(1);
  TNaming_Builder aBuilder(aLabel);
  aBuilder.Generated(aBox);

  EXPECT_FALSE(TNaming_Tool::HasLabel(aLabel, aSphere));
}

TEST_F(TNaming_ToolTest, NamedShape_RetrieveByShape)
{

  TopoDS_Shape aBox = MakeBox(10.0, 20.0, 30.0);

  TDF_Label       aLabel = myRoot.FindChild(1);
  TNaming_Builder aBuilder(aLabel);
  aBuilder.Generated(aBox);

  occ::handle<TNaming_NamedShape> aNS = TNaming_Tool::NamedShape(aBox, aLabel);
  EXPECT_FALSE(aNS.IsNull());

  TopoDS_Shape aRetrieved = TNaming_Tool::GetShape(aNS);
  EXPECT_TRUE(aRetrieved.IsSame(aBox));
}

TEST_F(TNaming_ToolTest, NamedShape_NonExistingShape)
{

  TopoDS_Shape aBox    = MakeBox(10.0, 20.0, 30.0);
  TopoDS_Shape aSphere = MakeSphere(15.0);

  TDF_Label       aLabel = myRoot.FindChild(1);
  TNaming_Builder aBuilder(aLabel);
  aBuilder.Generated(aBox);

  occ::handle<TNaming_NamedShape> aNS = TNaming_Tool::NamedShape(aSphere, aLabel);
  EXPECT_TRUE(aNS.IsNull());
}

TEST_F(TNaming_ToolTest, CurrentNamedShape_Simple)
{

  TopoDS_Shape aBox = MakeBox(10.0, 20.0, 30.0);

  TDF_Label       aLabel = myRoot.FindChild(1);
  TNaming_Builder aBuilder(aLabel);
  aBuilder.Generated(aBox);

  occ::handle<TNaming_NamedShape> aNS;
  ASSERT_TRUE(aLabel.FindAttribute(TNaming_NamedShape::GetID(), aNS));

  occ::handle<TNaming_NamedShape> aCurrentNS = TNaming_Tool::CurrentNamedShape(aNS);
  EXPECT_FALSE(aCurrentNS.IsNull());
}

TEST_F(TNaming_ToolTest, Label_RetrieveLabel)
{

  TopoDS_Shape aBox = MakeBox(10.0, 20.0, 30.0);

  TDF_Label       aLabel = myRoot.FindChild(1);
  TNaming_Builder aBuilder(aLabel);
  aBuilder.Generated(aBox);

  int       aTransDef       = 0;
  TDF_Label aRetrievedLabel = TNaming_Tool::Label(aLabel, aBox, aTransDef);

  EXPECT_FALSE(aRetrievedLabel.IsNull());
  EXPECT_TRUE(aRetrievedLabel.IsEqual(aLabel));
}

TEST_F(TNaming_ToolTest, GeneratedShape_Simple)
{

  TopoDS_Shape anOldBox = MakeBox(10.0, 10.0, 10.0);
  TopoDS_Shape aNewBox  = MakeBox(20.0, 20.0, 20.0);

  TDF_Label       aLabel = myRoot.FindChild(1);
  TNaming_Builder aBuilder(aLabel);
  aBuilder.Generated(anOldBox, aNewBox);

  occ::handle<TNaming_NamedShape> aNS;
  ASSERT_TRUE(aLabel.FindAttribute(TNaming_NamedShape::GetID(), aNS));

  TopoDS_Shape aGenerated = TNaming_Tool::GeneratedShape(anOldBox, aNS);

  EXPECT_FALSE(aGenerated.IsNull());
  EXPECT_TRUE(aGenerated.IsSame(aNewBox));
}

TEST_F(TNaming_ToolTest, MultipleShapes_GetShape)
{

  TopoDS_Shape aBox1 = MakeBox(10.0, 10.0, 10.0);
  TopoDS_Shape aBox2 = MakeBox(20.0, 20.0, 20.0);
  TopoDS_Shape aBox3 = MakeBox(30.0, 30.0, 30.0);

  TDF_Label       aLabel1 = myRoot.FindChild(1);
  TNaming_Builder aBuilder1(aLabel1);
  aBuilder1.Generated(aBox1);

  TDF_Label       aLabel2 = myRoot.FindChild(2);
  TNaming_Builder aBuilder2(aLabel2);
  aBuilder2.Generated(aBox2);

  TDF_Label       aLabel3 = myRoot.FindChild(3);
  TNaming_Builder aBuilder3(aLabel3);
  aBuilder3.Generated(aBox3);

  occ::handle<TNaming_NamedShape> aNS1, aNS2, aNS3;
  ASSERT_TRUE(aLabel1.FindAttribute(TNaming_NamedShape::GetID(), aNS1));
  ASSERT_TRUE(aLabel2.FindAttribute(TNaming_NamedShape::GetID(), aNS2));
  ASSERT_TRUE(aLabel3.FindAttribute(TNaming_NamedShape::GetID(), aNS3));

  TopoDS_Shape aRetrieved1 = TNaming_Tool::GetShape(aNS1);
  TopoDS_Shape aRetrieved2 = TNaming_Tool::GetShape(aNS2);
  TopoDS_Shape aRetrieved3 = TNaming_Tool::GetShape(aNS3);

  EXPECT_TRUE(aRetrieved1.IsSame(aBox1));
  EXPECT_TRUE(aRetrieved2.IsSame(aBox2));
  EXPECT_TRUE(aRetrieved3.IsSame(aBox3));
}

TEST_F(TNaming_ToolTest, ValidUntil_SimpleCase)
{

  TopoDS_Shape aBox = MakeBox(10.0, 20.0, 30.0);

  TDF_Label       aLabel = myRoot.FindChild(1);
  TNaming_Builder aBuilder(aLabel);
  aBuilder.Generated(aBox);

  int aValidUntil = TNaming_Tool::ValidUntil(aLabel, aBox);

  EXPECT_GE(aValidUntil, 0);
}

TEST_F(TNaming_ToolTest, DeletedShape_CurrentShape)
{

  TopoDS_Shape aBox = MakeBox(10.0, 20.0, 30.0);

  TDF_Label       aLabel1 = myRoot.FindChild(1);
  TNaming_Builder aBuilder1(aLabel1);
  aBuilder1.Generated(aBox);

  TDF_Label       aLabel2 = myRoot.FindChild(2);
  TNaming_Builder aBuilder2(aLabel2);
  aBuilder2.Delete(aBox);

  occ::handle<TNaming_NamedShape> aNS1;
  ASSERT_TRUE(aLabel1.FindAttribute(TNaming_NamedShape::GetID(), aNS1));

  TopoDS_Shape aCurrentShape = TNaming_Tool::CurrentShape(aNS1);

  EXPECT_NO_THROW({ TNaming_Tool::CurrentShape(aNS1); });
}

TEST_F(TNaming_ToolTest, EmptyLabel_HasLabel)
{

  TopoDS_Shape aBox = MakeBox(10.0, 20.0, 30.0);

  TDF_Label aEmptyLabel = myRoot.FindChild(99);

  EXPECT_FALSE(TNaming_Tool::HasLabel(aEmptyLabel, aBox));
}

TEST_F(TNaming_ToolTest, Collect_SimpleCase)
{

  TopoDS_Shape aBox = MakeBox(10.0, 20.0, 30.0);

  TDF_Label       aLabel = myRoot.FindChild(1);
  TNaming_Builder aBuilder(aLabel);
  aBuilder.Generated(aBox);

  occ::handle<TNaming_NamedShape> aNS;
  ASSERT_TRUE(aLabel.FindAttribute(TNaming_NamedShape::GetID(), aNS));

  NCollection_Map<occ::handle<TNaming_NamedShape>> aLabels;
  EXPECT_NO_THROW({ TNaming_Tool::Collect(aNS, aLabels); });
}

TEST_F(TNaming_ToolTest, NamedShape_MissingUsedShapes)
{

  occ::handle<TDF_Data> aDataWithoutUS = new TDF_Data();
  TDF_Label             aRootWithoutUS = aDataWithoutUS->Root();

  TopoDS_Shape aBox = MakeBox(10.0, 20.0, 30.0);

  occ::handle<TNaming_NamedShape> aNS = TNaming_Tool::NamedShape(aBox, aRootWithoutUS);

  EXPECT_TRUE(aNS.IsNull());
}

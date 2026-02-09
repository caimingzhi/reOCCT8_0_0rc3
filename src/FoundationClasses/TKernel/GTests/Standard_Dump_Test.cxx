

#include <gtest/gtest.h>

#include <Standard_Dump.hpp>
#include <gp_Pnt.hpp>
#include <gp_Ax3.hpp>
#include <Bnd_Box.hpp>
#include <TCollection_AsciiString.hpp>

TEST(Standard_DumpTest, AddValuesSeparator_EmptyStream)
{

  std::ostringstream anOStream;

  Standard_Dump::AddValuesSeparator(anOStream);

  std::string aResult = anOStream.str();
  EXPECT_TRUE(aResult.empty()) << "Separator should not be added to empty stream. Got: '" << aResult
                               << "'";
}

TEST(Standard_DumpTest, AddValuesSeparator_AfterContent)
{

  std::ostringstream anOStream;
  anOStream << "\"Field1\": 42";

  Standard_Dump::AddValuesSeparator(anOStream);

  std::string aResult = anOStream.str();
  EXPECT_EQ("\"Field1\": 42, ", aResult)
    << "Separator should be added after content. Got: '" << aResult << "'";
}

TEST(Standard_DumpTest, AddValuesSeparator_AfterOpeningBrace)
{

  std::ostringstream anOStream;
  anOStream << "{";

  Standard_Dump::AddValuesSeparator(anOStream);

  std::string aResult = anOStream.str();
  EXPECT_EQ("{", aResult) << "Separator should not be added after opening brace. Got: '" << aResult
                          << "'";
}

TEST(Standard_DumpTest, AddValuesSeparator_AfterExistingSeparator)
{

  std::ostringstream anOStream;
  anOStream << "\"Field1\": 42, ";

  Standard_Dump::AddValuesSeparator(anOStream);

  std::string aResult = anOStream.str();
  EXPECT_EQ("\"Field1\": 42, ", aResult)
    << "Separator should not be duplicated. Got: '" << aResult << "'";
}

TEST(Standard_DumpTest, AddValuesSeparator_MultipleFields)
{

  std::ostringstream anOStream;

  anOStream << "\"Field1\": 42";
  Standard_Dump::AddValuesSeparator(anOStream);

  anOStream << "\"Field2\": \"value\"";
  Standard_Dump::AddValuesSeparator(anOStream);

  anOStream << "\"Field3\": [1, 2, 3]";

  std::string aResult = anOStream.str();
  EXPECT_EQ("\"Field1\": 42, \"Field2\": \"value\", \"Field3\": [1, 2, 3]", aResult)
    << "Separators should be added between fields. Got: '" << aResult << "'";
}

TEST(Standard_DumpTest, gp_Pnt_DumpAndInit)
{

  gp_Pnt aPoint(1.5, 2.5, 3.5);

  std::ostringstream anOStream;
  aPoint.DumpJson(anOStream);
  std::string aJsonStr = anOStream.str();

  EXPECT_NE(aJsonStr.find("\"gp_Pnt\""), std::string::npos)
    << "JSON should contain class name. Got: " << aJsonStr;
  EXPECT_NE(aJsonStr.find("[1.5, 2.5, 3.5]"), std::string::npos)
    << "JSON should contain coordinates. Got: " << aJsonStr;

  std::stringstream anIStream(aJsonStr);
  gp_Pnt            aDeserializedPnt;
  int               aStreamPos = 1;

  EXPECT_TRUE(aDeserializedPnt.InitFromJson(anIStream, aStreamPos))
    << "Deserialization should succeed. JSON: " << aJsonStr;

  EXPECT_DOUBLE_EQ(aPoint.X(), aDeserializedPnt.X());
  EXPECT_DOUBLE_EQ(aPoint.Y(), aDeserializedPnt.Y());
  EXPECT_DOUBLE_EQ(aPoint.Z(), aDeserializedPnt.Z());
}

TEST(Standard_DumpTest, gp_Ax3_DumpAndInit_MultipleSeparators)
{

  gp_Ax3 anAxis(gp_Pnt(1, 2, 3), gp_Dir(gp_Dir::D::Z), gp_Dir(gp_Dir::D::X));

  std::ostringstream anOStream;
  anAxis.DumpJson(anOStream);
  std::string aJsonStr = anOStream.str();

  EXPECT_NE(aJsonStr.find(", \"Direction\""), std::string::npos)
    << "Separator should be before Direction. Got: " << aJsonStr;
  EXPECT_NE(aJsonStr.find(", \"XDirection\""), std::string::npos)
    << "Separator should be before XDirection. Got: " << aJsonStr;
  EXPECT_NE(aJsonStr.find(", \"YDirection\""), std::string::npos)
    << "Separator should be before YDirection. Got: " << aJsonStr;

  EXPECT_EQ(aJsonStr.find("]\"Direction\""), std::string::npos)
    << "Should not have missing separator. Got: " << aJsonStr;
  EXPECT_EQ(aJsonStr.find("]\"XDirection\""), std::string::npos)
    << "Should not have missing separator. Got: " << aJsonStr;
  EXPECT_EQ(aJsonStr.find("]\"YDirection\""), std::string::npos)
    << "Should not have missing separator. Got: " << aJsonStr;

  std::stringstream anIStream(aJsonStr);
  gp_Ax3            aDeserializedAxis;
  int               aStreamPos = 1;

  EXPECT_TRUE(aDeserializedAxis.InitFromJson(anIStream, aStreamPos))
    << "Deserialization should succeed. JSON: " << aJsonStr;

  EXPECT_TRUE(anAxis.Location().IsEqual(aDeserializedAxis.Location(), 1e-10))
    << "Locations should match";
  EXPECT_TRUE(anAxis.Direction().IsEqual(aDeserializedAxis.Direction(), 1e-10))
    << "Directions should match";
}

TEST(Standard_DumpTest, Bnd_Box_ComplexDump)
{

  Bnd_Box aBox(gp_Pnt(-5, -10, -15), gp_Pnt(20, 30, 40));
  aBox.SetGap(1.5);

  std::ostringstream anOStream;
  aBox.DumpJson(anOStream);
  std::string aJsonStr = anOStream.str();

  EXPECT_NE(aJsonStr.find(", \"CornerMax\""), std::string::npos)
    << "Separator before CornerMax. Got: " << aJsonStr;
  EXPECT_NE(aJsonStr.find(", \"Gap\""), std::string::npos)
    << "Separator before Gap. Got: " << aJsonStr;
  EXPECT_NE(aJsonStr.find(", \"Flags\""), std::string::npos)
    << "Separator before Flags. Got: " << aJsonStr;

  std::stringstream anIStream(aJsonStr);
  Bnd_Box           aDeserializedBox;
  int               aStreamPos = 1;

  EXPECT_TRUE(aDeserializedBox.InitFromJson(anIStream, aStreamPos))
    << "Deserialization should succeed. JSON: " << aJsonStr;

  double aXmin1, aYmin1, aZmin1, aXmax1, aYmax1, aZmax1;
  double aXmin2, aYmin2, aZmin2, aXmax2, aYmax2, aZmax2;

  aBox.Get(aXmin1, aYmin1, aZmin1, aXmax1, aYmax1, aZmax1);
  aDeserializedBox.Get(aXmin2, aYmin2, aZmin2, aXmax2, aYmax2, aZmax2);

  EXPECT_DOUBLE_EQ(aXmin1, aXmin2);
  EXPECT_DOUBLE_EQ(aYmin1, aYmin2);
  EXPECT_DOUBLE_EQ(aZmin1, aZmin2);
  EXPECT_DOUBLE_EQ(aXmax1, aXmax2);
  EXPECT_DOUBLE_EQ(aYmax1, aYmax2);
  EXPECT_DOUBLE_EQ(aZmax1, aZmax2);
  EXPECT_DOUBLE_EQ(aBox.GetGap(), aDeserializedBox.GetGap());
}

TEST(Standard_DumpTest, TellP_BehaviorValidation)
{

  std::ostringstream anOStream;

  std::streampos aPos1 = anOStream.tellp();
  EXPECT_TRUE(aPos1 == std::streampos(0) || aPos1 == std::streampos(-1))
    << "Empty stream position should be 0 or -1, got: " << aPos1;

  anOStream << "test";
  std::streampos aPos2 = anOStream.tellp();
  EXPECT_GT(aPos2, std::streampos(0))
    << "Stream with content should have positive position, got: " << aPos2;

  std::ostringstream anEmptyStream;
  Standard_Dump::AddValuesSeparator(anEmptyStream);
  EXPECT_TRUE(anEmptyStream.str().empty())
    << "Separator should not be added to empty stream based on tellp()";

  std::ostringstream aNonEmptyStream;
  aNonEmptyStream << "content";
  std::string aBefore = aNonEmptyStream.str();
  Standard_Dump::AddValuesSeparator(aNonEmptyStream);
  std::string aAfter = aNonEmptyStream.str();
  EXPECT_NE(aBefore, aAfter) << "Separator should be added to non-empty stream based on tellp()";
}

TEST(Standard_DumpTest, ConsecutiveDumps)
{

  std::ostringstream anOStream;

  gp_Pnt aPoint1(1, 2, 3);
  aPoint1.DumpJson(anOStream);

  Standard_Dump::AddValuesSeparator(anOStream);

  gp_Pnt aPoint2(4, 5, 6);
  aPoint2.DumpJson(anOStream);

  std::string aResult = anOStream.str();

  EXPECT_NE(aResult.find(", \"gp_Pnt\""), std::string::npos)
    << "Should have separator between dumps. Got: " << aResult;
}

TEST(Standard_DumpTest, StreamWithOnlyOpenBrace)
{

  std::ostringstream anOStream;
  anOStream << "{";

  std::string aBefore = anOStream.str();
  Standard_Dump::AddValuesSeparator(anOStream);
  std::string aAfter = anOStream.str();

  EXPECT_EQ(aBefore, aAfter) << "Separator should not be added after lone opening brace. Before: '"
                             << aBefore << "', After: '" << aAfter << "'";
}

TEST(Standard_DumpTest, VoidBoxSerialization)
{

  Bnd_Box aVoidBox;

  std::ostringstream anOStream;
  aVoidBox.DumpJson(anOStream);
  std::string aJsonStr = anOStream.str();

  EXPECT_FALSE(aJsonStr.empty()) << "Void box should still produce JSON output";

  std::stringstream anIStream(aJsonStr);
  Bnd_Box           aDeserializedBox;
  int               aStreamPos = 1;

  EXPECT_TRUE(aDeserializedBox.InitFromJson(anIStream, aStreamPos))
    << "Should be able to deserialize void box. JSON: " << aJsonStr;

  EXPECT_TRUE(aDeserializedBox.IsVoid()) << "Deserialized box should also be void";
}

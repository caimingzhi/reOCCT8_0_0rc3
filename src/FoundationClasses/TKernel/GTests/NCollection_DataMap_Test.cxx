

#include <NCollection_DataMap.hpp>
#include <Standard_Integer.hpp>
#include <TCollection_AsciiString.hpp>

#include <gtest/gtest.h>
#include <algorithm>
#include <vector>
#include <set>

class NCollection_DataMapTest : public testing::Test
{
protected:
  void SetUp() override {}

  void TearDown() override {}
};

TEST_F(NCollection_DataMapTest, IntegerKeys)
{

  NCollection_DataMap<int, TCollection_AsciiString> aMap;

  EXPECT_TRUE(aMap.IsEmpty());
  EXPECT_EQ(0, aMap.Size());
  EXPECT_EQ(0, aMap.Extent());
}

TEST_F(NCollection_DataMapTest, BindingAndAccess)
{
  NCollection_DataMap<int, TCollection_AsciiString> aMap;

  aMap.Bind(1, "One");
  aMap.Bind(2, "Two");
  aMap.Bind(3, "Three");

  EXPECT_FALSE(aMap.IsEmpty());
  EXPECT_EQ(3, aMap.Size());

  EXPECT_STREQ("One", aMap.Find(1).ToCString());
  EXPECT_STREQ("Two", aMap.Find(2).ToCString());
  EXPECT_STREQ("Three", aMap.Find(3).ToCString());

  EXPECT_TRUE(aMap.IsBound(1));
  EXPECT_TRUE(aMap.IsBound(2));
  EXPECT_TRUE(aMap.IsBound(3));
  EXPECT_FALSE(aMap.IsBound(4));
}

TEST_F(NCollection_DataMapTest, ChangeFind)
{
  NCollection_DataMap<int, TCollection_AsciiString> aMap;

  aMap.Bind(1, "One");

  EXPECT_STREQ("One", aMap.Find(1).ToCString());
  aMap.ChangeFind(1) = "Modified One";
  EXPECT_STREQ("Modified One", aMap.Find(1).ToCString());
}

TEST_F(NCollection_DataMapTest, Rebind)
{
  NCollection_DataMap<int, TCollection_AsciiString> aMap;

  aMap.Bind(1, "One");
  EXPECT_STREQ("One", aMap.Find(1).ToCString());

  aMap.Bind(1, "New One");
  EXPECT_STREQ("New One", aMap.Find(1).ToCString());

  EXPECT_EQ(1, aMap.Size());
}

TEST_F(NCollection_DataMapTest, UnBind)
{
  NCollection_DataMap<int, TCollection_AsciiString> aMap;

  aMap.Bind(1, "One");
  aMap.Bind(2, "Two");
  aMap.Bind(3, "Three");

  EXPECT_TRUE(aMap.UnBind(2));
  EXPECT_EQ(2, aMap.Size());

  EXPECT_FALSE(aMap.IsBound(2));

  EXPECT_FALSE(aMap.UnBind(4));
  EXPECT_EQ(2, aMap.Size());
}

TEST_F(NCollection_DataMapTest, Clear)
{
  NCollection_DataMap<int, TCollection_AsciiString> aMap;

  aMap.Bind(1, "One");
  aMap.Bind(2, "Two");

  aMap.Clear();
  EXPECT_TRUE(aMap.IsEmpty());
  EXPECT_EQ(0, aMap.Size());
  EXPECT_FALSE(aMap.IsBound(1));
  EXPECT_FALSE(aMap.IsBound(2));
}

TEST_F(NCollection_DataMapTest, Assignment)
{
  NCollection_DataMap<int, TCollection_AsciiString> aMap1;
  aMap1.Bind(1, "One");
  aMap1.Bind(2, "Two");

  NCollection_DataMap<int, TCollection_AsciiString> aMap2;
  aMap2 = aMap1;

  EXPECT_EQ(aMap1.Size(), aMap2.Size());
  EXPECT_STREQ(aMap1.Find(1).ToCString(), aMap2.Find(1).ToCString());
  EXPECT_STREQ(aMap1.Find(2).ToCString(), aMap2.Find(2).ToCString());

  aMap1.ChangeFind(1) = "Modified One";
  EXPECT_STREQ("Modified One", aMap1.Find(1).ToCString());
  EXPECT_STREQ("One", aMap2.Find(1).ToCString());
}

TEST_F(NCollection_DataMapTest, Find_NonExisting)
{
  NCollection_DataMap<int, TCollection_AsciiString> aMap;
  aMap.Bind(1, "One");

  EXPECT_THROW(aMap.Find(2), Standard_NoSuchObject);

  EXPECT_THROW(aMap.ChangeFind(2), Standard_NoSuchObject);
}

TEST_F(NCollection_DataMapTest, IteratorAccess)
{
  NCollection_DataMap<int, TCollection_AsciiString> aMap;
  aMap.Bind(1, "One");
  aMap.Bind(2, "Two");
  aMap.Bind(3, "Three");

  NCollection_DataMap<int, TCollection_AsciiString>::Iterator it(aMap);

  std::set<int>         foundKeys;
  std::set<std::string> foundValues;

  for (; it.More(); it.Next())
  {
    foundKeys.insert(it.Key());
    foundValues.insert(it.Value().ToCString());
  }

  EXPECT_EQ(3, foundKeys.size());
  EXPECT_TRUE(foundKeys.find(1) != foundKeys.end());
  EXPECT_TRUE(foundKeys.find(2) != foundKeys.end());
  EXPECT_TRUE(foundKeys.find(3) != foundKeys.end());

  EXPECT_EQ(3, foundValues.size());
  EXPECT_TRUE(foundValues.find("One") != foundValues.end());
  EXPECT_TRUE(foundValues.find("Two") != foundValues.end());
  EXPECT_TRUE(foundValues.find("Three") != foundValues.end());
}

TEST_F(NCollection_DataMapTest, ChangeValue)
{
  NCollection_DataMap<int, TCollection_AsciiString> aMap;
  aMap.Bind(1, "One");

  NCollection_DataMap<int, TCollection_AsciiString>::Iterator it(aMap);
  EXPECT_STREQ("One", it.Value().ToCString());

  it.ChangeValue() = "Modified via Iterator";
  EXPECT_STREQ("Modified via Iterator", it.Value().ToCString());

  EXPECT_STREQ("Modified via Iterator", aMap.Find(1).ToCString());
}

TEST_F(NCollection_DataMapTest, ExhaustiveIterator)
{
  const int NUM_ELEMENTS = 1000;

  NCollection_DataMap<int, int> aMap;

  for (int i = 0; i < NUM_ELEMENTS; ++i)
  {
    aMap.Bind(i, i * 2);
  }

  EXPECT_EQ(NUM_ELEMENTS, aMap.Size());

  int                                     count = 0;
  NCollection_DataMap<int, int>::Iterator it(aMap);
  for (; it.More(); it.Next())
  {
    EXPECT_EQ(it.Key() * 2, it.Value());
    count++;
  }

  EXPECT_EQ(NUM_ELEMENTS, count);
}

TEST_F(NCollection_DataMapTest, STLAlgorithmCompatibility_MinMax)
{
  NCollection_DataMap<int, int> aMap;

  for (int anIdx = 10; anIdx <= 50; anIdx += 5)
  {
    aMap.Bind(anIdx, anIdx * 2);
  }

  EXPECT_FALSE(aMap.IsEmpty());

  auto aMinElement = std::min_element(aMap.cbegin(), aMap.cend());
  auto aMaxElement = std::max_element(aMap.cbegin(), aMap.cend());

  EXPECT_TRUE(aMinElement != aMap.cend());
  EXPECT_TRUE(aMaxElement != aMap.cend());
  EXPECT_LE(*aMinElement, *aMaxElement);
}

TEST_F(NCollection_DataMapTest, STLAlgorithmCompatibility_Find)
{
  NCollection_DataMap<int, int> aMap;

  aMap.Bind(100, 200);
  aMap.Bind(200, 400);
  aMap.Bind(300, 600);

  auto aFound = std::find(aMap.cbegin(), aMap.cend(), 200);
  EXPECT_TRUE(aFound != aMap.cend());
  EXPECT_EQ(*aFound, 200);

  auto aNotFound = std::find(aMap.cbegin(), aMap.cend(), 999);
  EXPECT_TRUE(aNotFound == aMap.cend());
}

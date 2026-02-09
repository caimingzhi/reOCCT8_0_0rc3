

#include <NCollection_IndexedMap.hpp>
#include <TCollection_AsciiString.hpp>

#include <gtest/gtest.h>
#include <algorithm>
#include <random>
#include <vector>

typedef int KeyType;

class TestKey
{
public:
  TestKey(int id = 0, const char* name = "")
      : myId(id),
        myName(name)
  {
  }

  bool operator==(const TestKey& other) const
  {
    return myId == other.myId && myName == other.myName;
  }

  int GetId() const { return myId; }

  const std::string& GetName() const { return myName; }

private:
  int         myId;
  std::string myName;
};

struct TestKeyHasher
{
  size_t operator()(const TestKey& theKey) const
  {

    size_t aCombination[2] = {std::hash<int>()(theKey.GetId()),
                              std::hash<std::string>()(theKey.GetName())};

    return opencascade::hashBytes(aCombination, sizeof(aCombination));
  }

  bool operator()(const TestKey& theKey1, const TestKey& theKey2) const
  {
    return theKey1 == theKey2;
  }
};

TEST(NCollection_IndexedMapTest, DefaultConstructor)
{

  NCollection_IndexedMap<KeyType> aMap;
  EXPECT_TRUE(aMap.IsEmpty());
  EXPECT_EQ(aMap.Extent(), 0);
  EXPECT_EQ(aMap.Size(), 0);
}

TEST(NCollection_IndexedMapTest, BasicAddFind)
{
  NCollection_IndexedMap<KeyType> aMap;

  int index1 = aMap.Add(10);
  int index2 = aMap.Add(20);
  int index3 = aMap.Add(30);

  EXPECT_EQ(index1, 1);
  EXPECT_EQ(index2, 2);
  EXPECT_EQ(index3, 3);
  EXPECT_EQ(aMap.Extent(), 3);

  EXPECT_EQ(aMap.FindIndex(10), 1);
  EXPECT_EQ(aMap.FindIndex(20), 2);
  EXPECT_EQ(aMap.FindIndex(30), 3);

  EXPECT_EQ(aMap.FindKey(1), 10);
  EXPECT_EQ(aMap.FindKey(2), 20);
  EXPECT_EQ(aMap.FindKey(3), 30);

  EXPECT_EQ(aMap(1), 10);
  EXPECT_EQ(aMap(2), 20);
  EXPECT_EQ(aMap(3), 30);

  EXPECT_TRUE(aMap.Contains(10));
  EXPECT_TRUE(aMap.Contains(20));
  EXPECT_TRUE(aMap.Contains(30));
  EXPECT_FALSE(aMap.Contains(40));
}

TEST(NCollection_IndexedMapTest, DuplicateKey)
{
  NCollection_IndexedMap<KeyType> aMap;

  int index1 = aMap.Add(10);
  int index2 = aMap.Add(20);

  EXPECT_EQ(index1, 1);
  EXPECT_EQ(index2, 2);

  int indexDup = aMap.Add(10);
  EXPECT_EQ(indexDup, 1);
  EXPECT_EQ(aMap.Extent(), 2);
}

TEST(NCollection_IndexedMapTest, RemoveLast)
{
  NCollection_IndexedMap<KeyType> aMap;

  aMap.Add(10);
  aMap.Add(20);
  aMap.Add(30);

  aMap.RemoveLast();

  EXPECT_EQ(aMap.Extent(), 2);
  EXPECT_TRUE(aMap.Contains(10));
  EXPECT_TRUE(aMap.Contains(20));
  EXPECT_FALSE(aMap.Contains(30));

  EXPECT_EQ(aMap.FindIndex(10), 1);
  EXPECT_EQ(aMap.FindIndex(20), 2);
}

TEST(NCollection_IndexedMapTest, RemoveFromIndex)
{
  NCollection_IndexedMap<KeyType> aMap;

  aMap.Add(10);
  aMap.Add(20);
  aMap.Add(30);
  aMap.Add(40);

  aMap.RemoveFromIndex(2);

  EXPECT_EQ(aMap.Extent(), 3);
  EXPECT_TRUE(aMap.Contains(10));
  EXPECT_FALSE(aMap.Contains(20));
  EXPECT_TRUE(aMap.Contains(30));
  EXPECT_TRUE(aMap.Contains(40));

  EXPECT_EQ(aMap.FindKey(2), 40);
  EXPECT_EQ(aMap.FindKey(1), 10);
  EXPECT_EQ(aMap.FindKey(3), 30);
}

TEST(NCollection_IndexedMapTest, RemoveKey)
{
  NCollection_IndexedMap<KeyType> aMap;

  aMap.Add(10);
  aMap.Add(20);
  aMap.Add(30);

  bool removed = aMap.RemoveKey(20);

  EXPECT_TRUE(removed);
  EXPECT_EQ(aMap.Extent(), 2);
  EXPECT_TRUE(aMap.Contains(10));
  EXPECT_FALSE(aMap.Contains(20));
  EXPECT_TRUE(aMap.Contains(30));

  removed = aMap.RemoveKey(50);
  EXPECT_FALSE(removed);
  EXPECT_EQ(aMap.Extent(), 2);
}

TEST(NCollection_IndexedMapTest, Substitute)
{
  NCollection_IndexedMap<KeyType> aMap;

  aMap.Add(10);
  aMap.Add(20);
  aMap.Add(30);

  aMap.Substitute(2, 25);

  EXPECT_EQ(aMap.Extent(), 3);
  EXPECT_TRUE(aMap.Contains(10));
  EXPECT_FALSE(aMap.Contains(20));
  EXPECT_TRUE(aMap.Contains(25));
  EXPECT_TRUE(aMap.Contains(30));

  EXPECT_EQ(aMap.FindIndex(10), 1);
  EXPECT_EQ(aMap.FindIndex(25), 2);
  EXPECT_EQ(aMap.FindIndex(30), 3);

  EXPECT_EQ(aMap.FindKey(1), 10);
  EXPECT_EQ(aMap.FindKey(2), 25);
  EXPECT_EQ(aMap.FindKey(3), 30);
}

TEST(NCollection_IndexedMapTest, Swap)
{
  NCollection_IndexedMap<KeyType> aMap;

  aMap.Add(10);
  aMap.Add(20);
  aMap.Add(30);

  aMap.Swap(1, 3);

  EXPECT_EQ(aMap.Extent(), 3);

  EXPECT_TRUE(aMap.Contains(10));
  EXPECT_TRUE(aMap.Contains(20));
  EXPECT_TRUE(aMap.Contains(30));

  EXPECT_EQ(aMap.FindKey(1), 30);
  EXPECT_EQ(aMap.FindKey(2), 20);
  EXPECT_EQ(aMap.FindKey(3), 10);

  EXPECT_EQ(aMap.FindIndex(10), 3);
  EXPECT_EQ(aMap.FindIndex(20), 2);
  EXPECT_EQ(aMap.FindIndex(30), 1);
}

TEST(NCollection_IndexedMapTest, Clear)
{
  NCollection_IndexedMap<KeyType> aMap;

  aMap.Add(10);
  aMap.Add(20);
  aMap.Add(30);

  EXPECT_EQ(aMap.Extent(), 3);

  aMap.Clear();

  EXPECT_TRUE(aMap.IsEmpty());
  EXPECT_EQ(aMap.Extent(), 0);

  int index1 = aMap.Add(40);
  EXPECT_EQ(index1, 1);
  EXPECT_EQ(aMap.Extent(), 1);
}

TEST(NCollection_IndexedMapTest, CopyConstructor)
{
  NCollection_IndexedMap<KeyType> aMap1;

  aMap1.Add(10);
  aMap1.Add(20);
  aMap1.Add(30);

  NCollection_IndexedMap<KeyType> aMap2(aMap1);

  EXPECT_EQ(aMap2.Extent(), 3);
  EXPECT_TRUE(aMap2.Contains(10));
  EXPECT_TRUE(aMap2.Contains(20));
  EXPECT_TRUE(aMap2.Contains(30));

  EXPECT_EQ(aMap2.FindIndex(10), 1);
  EXPECT_EQ(aMap2.FindIndex(20), 2);
  EXPECT_EQ(aMap2.FindIndex(30), 3);

  aMap1.Add(40);
  EXPECT_EQ(aMap1.Extent(), 4);
  EXPECT_EQ(aMap2.Extent(), 3);
  EXPECT_FALSE(aMap2.Contains(40));
}

TEST(NCollection_IndexedMapTest, AssignmentOperator)
{
  NCollection_IndexedMap<KeyType> aMap1;
  NCollection_IndexedMap<KeyType> aMap2;

  aMap1.Add(10);
  aMap1.Add(20);

  aMap2.Add(30);
  aMap2.Add(40);
  aMap2.Add(50);

  aMap2 = aMap1;

  EXPECT_EQ(aMap2.Extent(), 2);
  EXPECT_TRUE(aMap2.Contains(10));
  EXPECT_TRUE(aMap2.Contains(20));
  EXPECT_FALSE(aMap2.Contains(30));
  EXPECT_FALSE(aMap2.Contains(40));
  EXPECT_FALSE(aMap2.Contains(50));
}

TEST(NCollection_IndexedMapTest, Iterator)
{
  NCollection_IndexedMap<KeyType> aMap;

  aMap.Add(10);
  aMap.Add(20);
  aMap.Add(30);

  bool   found10 = false;
  bool   found20 = false;
  bool   found30 = false;
  size_t count   = 0;

  for (NCollection_IndexedMap<KeyType>::Iterator it(aMap); it.More(); it.Next(), ++count)
  {
    const KeyType& key = it.Value();
    if (key == 10)
      found10 = true;
    else if (key == 20)
      found20 = true;
    else if (key == 30)
      found30 = true;
  }

  EXPECT_EQ(count, 3);
  EXPECT_TRUE(found10);
  EXPECT_TRUE(found20);
  EXPECT_TRUE(found30);
}

TEST(NCollection_IndexedMapTest, StlIterator)
{
  NCollection_IndexedMap<KeyType> aMap;

  aMap.Add(10);
  aMap.Add(20);
  aMap.Add(30);

  bool   found10 = false;
  bool   found20 = false;
  bool   found30 = false;
  size_t count   = 0;

  for (auto it = aMap.cbegin(); it != aMap.cend(); ++it, ++count)
  {
    if (*it == 10)
      found10 = true;
    else if (*it == 20)
      found20 = true;
    else if (*it == 30)
      found30 = true;
  }

  EXPECT_EQ(count, 3);
  EXPECT_TRUE(found10);
  EXPECT_TRUE(found20);
  EXPECT_TRUE(found30);
}

TEST(NCollection_IndexedMapTest, StringKeys)
{

  NCollection_IndexedMap<TCollection_AsciiString> aStringMap;

  int index1 = aStringMap.Add(TCollection_AsciiString("First"));
  int index2 = aStringMap.Add(TCollection_AsciiString("Second"));
  int index3 = aStringMap.Add(TCollection_AsciiString("Third"));

  EXPECT_EQ(index1, 1);
  EXPECT_EQ(index2, 2);
  EXPECT_EQ(index3, 3);

  EXPECT_EQ(aStringMap.FindIndex(TCollection_AsciiString("First")), 1);
  EXPECT_EQ(aStringMap.FindIndex(TCollection_AsciiString("Second")), 2);
  EXPECT_EQ(aStringMap.FindIndex(TCollection_AsciiString("Third")), 3);

  EXPECT_TRUE(aStringMap.FindKey(1).IsEqual("First"));
  EXPECT_TRUE(aStringMap.FindKey(2).IsEqual("Second"));
  EXPECT_TRUE(aStringMap.FindKey(3).IsEqual("Third"));
}

TEST(NCollection_IndexedMapTest, ComplexKeys)
{

  NCollection_IndexedMap<TestKey, TestKeyHasher> aComplexMap;

  TestKey key1(1, "One");
  TestKey key2(2, "Two");
  TestKey key3(3, "Three");

  int index1 = aComplexMap.Add(key1);
  int index2 = aComplexMap.Add(key2);
  int index3 = aComplexMap.Add(key3);

  EXPECT_EQ(index1, 1);
  EXPECT_EQ(index2, 2);
  EXPECT_EQ(index3, 3);

  EXPECT_EQ(aComplexMap.FindIndex(key1), 1);
  EXPECT_EQ(aComplexMap.FindIndex(key2), 2);
  EXPECT_EQ(aComplexMap.FindIndex(key3), 3);

  EXPECT_EQ(aComplexMap.FindKey(1).GetId(), 1);
  EXPECT_EQ(aComplexMap.FindKey(2).GetId(), 2);
  EXPECT_EQ(aComplexMap.FindKey(3).GetId(), 3);

  EXPECT_TRUE(aComplexMap.Contains(TestKey(1, "One")));
  EXPECT_FALSE(aComplexMap.Contains(TestKey(4, "Four")));
}

TEST(NCollection_IndexedMapTest, Exchange)
{
  NCollection_IndexedMap<KeyType> aMap1;
  NCollection_IndexedMap<KeyType> aMap2;

  aMap1.Add(10);
  aMap1.Add(20);

  aMap2.Add(30);
  aMap2.Add(40);
  aMap2.Add(50);

  aMap1.Exchange(aMap2);

  EXPECT_EQ(aMap1.Extent(), 3);
  EXPECT_TRUE(aMap1.Contains(30));
  EXPECT_TRUE(aMap1.Contains(40));
  EXPECT_TRUE(aMap1.Contains(50));

  EXPECT_EQ(aMap2.Extent(), 2);
  EXPECT_TRUE(aMap2.Contains(10));
  EXPECT_TRUE(aMap2.Contains(20));
}

TEST(NCollection_IndexedMapTest, ReSize)
{
  NCollection_IndexedMap<KeyType> aMap(3);

  for (int i = 1; i <= 100; ++i)
  {
    aMap.Add(i);
  }

  EXPECT_EQ(aMap.Extent(), 100);
  for (int i = 1; i <= 100; ++i)
  {
    EXPECT_TRUE(aMap.Contains(i));
    EXPECT_EQ(aMap.FindIndex(i), i);
    EXPECT_EQ(aMap.FindKey(i), i);
  }

  aMap.ReSize(200);

  EXPECT_EQ(aMap.Extent(), 100);
  for (int i = 1; i <= 100; ++i)
  {
    EXPECT_TRUE(aMap.Contains(i));
    EXPECT_EQ(aMap.FindIndex(i), i);
    EXPECT_EQ(aMap.FindKey(i), i);
  }
}

TEST(NCollection_IndexedMapTest, STLAlgorithmCompatibility_MinMax)
{
  NCollection_IndexedMap<int> aMap;
  std::vector<int>            aVector;

  std::mt19937                       aGenerator(1);
  std::uniform_int_distribution<int> aDistribution(0, RAND_MAX);
  for (int anIdx = 0; anIdx < 100; ++anIdx)
  {
    int aVal = aDistribution(aGenerator);
    aMap.Add(aVal);
    aVector.push_back(aVal);
  }

  auto aMinOCCT = std::min_element(aMap.cbegin(), aMap.cend());
  auto aMinStd  = std::min_element(aVector.begin(), aVector.end());

  auto aMaxOCCT = std::max_element(aMap.cbegin(), aMap.cend());
  auto aMaxStd  = std::max_element(aVector.begin(), aVector.end());

  EXPECT_EQ(*aMinOCCT, *aMinStd);
  EXPECT_EQ(*aMaxOCCT, *aMaxStd);
}

TEST(NCollection_IndexedMapTest, STLAlgorithmCompatibility_Find)
{
  NCollection_IndexedMap<int> aMap;
  std::vector<int>            aVector;

  std::mt19937                       aGenerator(1);
  std::uniform_int_distribution<int> aDistribution(0, RAND_MAX);
  for (int anIdx = 0; anIdx < 100; ++anIdx)
  {
    int aVal = aDistribution(aGenerator);
    aMap.Add(aVal);
    aVector.push_back(aVal);
  }

  int  aSearchValue = aVector[10];
  auto aFoundOCCT   = std::find(aMap.cbegin(), aMap.cend(), aSearchValue);
  auto aFoundStd    = std::find(aVector.begin(), aVector.end(), aSearchValue);

  EXPECT_TRUE(aFoundOCCT != aMap.cend());
  EXPECT_TRUE(aFoundStd != aVector.end());
  EXPECT_EQ(*aFoundOCCT, *aFoundStd);
}

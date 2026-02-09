

#include <NCollection_IndexedDataMap.hpp>
#include <TCollection_AsciiString.hpp>

#include <gtest/gtest.h>
#include <algorithm>
#include <vector>

typedef int    KeyType;
typedef double ItemType;

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

namespace std
{
  template <>
  struct hash<TestKey>
  {
    size_t operator()(const TestKey& key) const
    {

      size_t aCombintation[2] = {std::hash<int>()(key.GetId()),
                                 std::hash<std::string>()(key.GetName())};
      return opencascade::hashBytes(aCombintation, sizeof(aCombintation));
    }
  };
} // namespace std

class TestItem
{
public:
  TestItem(double value = 0.0, const char* description = "")
      : myValue(value),
        myDescription(description)
  {
  }

  bool operator==(const TestItem& other) const
  {
    return fabs(myValue - other.myValue) < 1e-10 && myDescription == other.myDescription;
  }

  double GetValue() const { return myValue; }

  const std::string& GetDescription() const { return myDescription; }

  void SetValue(double value) { myValue = value; }

private:
  double      myValue;
  std::string myDescription;
};

TEST(NCollection_IndexedDataMapTest, DefaultConstructor)
{

  NCollection_IndexedDataMap<KeyType, ItemType> aMap;
  EXPECT_TRUE(aMap.IsEmpty());
  EXPECT_EQ(aMap.Extent(), 0);
  EXPECT_EQ(aMap.Size(), 0);
}

TEST(NCollection_IndexedDataMapTest, BasicAddFind)
{
  NCollection_IndexedDataMap<KeyType, ItemType> aMap;

  int index1 = aMap.Add(10, 1.0);
  int index2 = aMap.Add(20, 2.0);
  int index3 = aMap.Add(30, 3.0);

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

  EXPECT_DOUBLE_EQ(aMap.FindFromIndex(1), 1.0);
  EXPECT_DOUBLE_EQ(aMap.FindFromIndex(2), 2.0);
  EXPECT_DOUBLE_EQ(aMap.FindFromIndex(3), 3.0);

  EXPECT_DOUBLE_EQ(aMap(1), 1.0);
  EXPECT_DOUBLE_EQ(aMap(2), 2.0);
  EXPECT_DOUBLE_EQ(aMap(3), 3.0);

  EXPECT_DOUBLE_EQ(aMap.FindFromKey(10), 1.0);
  EXPECT_DOUBLE_EQ(aMap.FindFromKey(20), 2.0);
  EXPECT_DOUBLE_EQ(aMap.FindFromKey(30), 3.0);

  EXPECT_TRUE(aMap.Contains(10));
  EXPECT_TRUE(aMap.Contains(20));
  EXPECT_TRUE(aMap.Contains(30));
  EXPECT_FALSE(aMap.Contains(40));
}

TEST(NCollection_IndexedDataMapTest, DuplicateKey)
{
  NCollection_IndexedDataMap<KeyType, ItemType> aMap;

  int index1 = aMap.Add(10, 1.0);
  int index2 = aMap.Add(20, 2.0);

  EXPECT_EQ(index1, 1);
  EXPECT_EQ(index2, 2);

  int indexDup = aMap.Add(10, 3.0);
  EXPECT_EQ(indexDup, 1);
  EXPECT_EQ(aMap.Extent(), 2);
  EXPECT_DOUBLE_EQ(aMap.FindFromKey(10), 1.0);
}

TEST(NCollection_IndexedDataMapTest, ChangeValues)
{
  NCollection_IndexedDataMap<KeyType, ItemType> aMap;

  aMap.Add(10, 1.0);
  aMap.Add(20, 2.0);

  aMap.ChangeFromIndex(1) = 1.5;
  aMap.ChangeFromIndex(2) = 2.5;

  EXPECT_DOUBLE_EQ(aMap.FindFromIndex(1), 1.5);
  EXPECT_DOUBLE_EQ(aMap.FindFromIndex(2), 2.5);
  EXPECT_DOUBLE_EQ(aMap.FindFromKey(10), 1.5);
  EXPECT_DOUBLE_EQ(aMap.FindFromKey(20), 2.5);

  aMap.ChangeFromKey(10) = 1.75;
  aMap.ChangeFromKey(20) = 2.75;

  EXPECT_DOUBLE_EQ(aMap.FindFromIndex(1), 1.75);
  EXPECT_DOUBLE_EQ(aMap.FindFromIndex(2), 2.75);
  EXPECT_DOUBLE_EQ(aMap.FindFromKey(10), 1.75);
  EXPECT_DOUBLE_EQ(aMap.FindFromKey(20), 2.75);

  aMap(1) = 1.9;
  aMap(2) = 2.9;

  EXPECT_DOUBLE_EQ(aMap.FindFromIndex(1), 1.9);
  EXPECT_DOUBLE_EQ(aMap.FindFromIndex(2), 2.9);
  EXPECT_DOUBLE_EQ(aMap.FindFromKey(10), 1.9);
  EXPECT_DOUBLE_EQ(aMap.FindFromKey(20), 2.9);
}

TEST(NCollection_IndexedDataMapTest, SeekTests)
{
  NCollection_IndexedDataMap<KeyType, ItemType> aMap;

  aMap.Add(10, 1.0);
  aMap.Add(20, 2.0);

  const ItemType* item1 = aMap.Seek(10);
  const ItemType* item2 = aMap.Seek(20);
  const ItemType* item3 = aMap.Seek(30);

  EXPECT_TRUE(item1 != nullptr);
  EXPECT_TRUE(item2 != nullptr);
  EXPECT_TRUE(item3 == nullptr);

  EXPECT_DOUBLE_EQ(*item1, 1.0);
  EXPECT_DOUBLE_EQ(*item2, 2.0);

  ItemType* changeItem1 = aMap.ChangeSeek(10);
  ItemType* changeItem2 = aMap.ChangeSeek(20);
  ItemType* changeItem3 = aMap.ChangeSeek(30);

  EXPECT_TRUE(changeItem1 != nullptr);
  EXPECT_TRUE(changeItem2 != nullptr);
  EXPECT_TRUE(changeItem3 == nullptr);

  *changeItem1 = 1.5;
  *changeItem2 = 2.5;

  EXPECT_DOUBLE_EQ(aMap.FindFromKey(10), 1.5);
  EXPECT_DOUBLE_EQ(aMap.FindFromKey(20), 2.5);

  ItemType value;
  bool     found = aMap.FindFromKey(10, value);
  EXPECT_TRUE(found);
  EXPECT_DOUBLE_EQ(value, 1.5);

  found = aMap.FindFromKey(30, value);
  EXPECT_FALSE(found);
}

TEST(NCollection_IndexedDataMapTest, RemoveLast)
{
  NCollection_IndexedDataMap<KeyType, ItemType> aMap;

  aMap.Add(10, 1.0);
  aMap.Add(20, 2.0);
  aMap.Add(30, 3.0);

  aMap.RemoveLast();

  EXPECT_EQ(aMap.Extent(), 2);
  EXPECT_TRUE(aMap.Contains(10));
  EXPECT_TRUE(aMap.Contains(20));
  EXPECT_FALSE(aMap.Contains(30));

  EXPECT_EQ(aMap.FindIndex(10), 1);
  EXPECT_EQ(aMap.FindIndex(20), 2);
}

TEST(NCollection_IndexedDataMapTest, RemoveFromIndex)
{
  NCollection_IndexedDataMap<KeyType, ItemType> aMap;

  aMap.Add(10, 1.0);
  aMap.Add(20, 2.0);
  aMap.Add(30, 3.0);
  aMap.Add(40, 4.0);

  aMap.RemoveFromIndex(2);

  EXPECT_EQ(aMap.Extent(), 3);
  EXPECT_TRUE(aMap.Contains(10));
  EXPECT_FALSE(aMap.Contains(20));
  EXPECT_TRUE(aMap.Contains(30));
  EXPECT_TRUE(aMap.Contains(40));

  EXPECT_EQ(aMap.FindKey(2), 40);
  EXPECT_DOUBLE_EQ(aMap.FindFromIndex(2), 4.0);

  EXPECT_EQ(aMap.FindKey(1), 10);
  EXPECT_EQ(aMap.FindKey(3), 30);
}

TEST(NCollection_IndexedDataMapTest, RemoveKey)
{
  NCollection_IndexedDataMap<KeyType, ItemType> aMap;

  aMap.Add(10, 1.0);
  aMap.Add(20, 2.0);
  aMap.Add(30, 3.0);

  aMap.RemoveKey(20);

  EXPECT_EQ(aMap.Extent(), 2);
  EXPECT_TRUE(aMap.Contains(10));
  EXPECT_FALSE(aMap.Contains(20));
  EXPECT_TRUE(aMap.Contains(30));

  aMap.RemoveKey(50);
  EXPECT_EQ(aMap.Extent(), 2);
}

TEST(NCollection_IndexedDataMapTest, Substitute)
{
  NCollection_IndexedDataMap<KeyType, ItemType> aMap;

  aMap.Add(10, 1.0);
  aMap.Add(20, 2.0);
  aMap.Add(30, 3.0);

  aMap.Substitute(2, 25, 2.5);

  EXPECT_EQ(aMap.Extent(), 3);
  EXPECT_TRUE(aMap.Contains(10));
  EXPECT_FALSE(aMap.Contains(20));
  EXPECT_TRUE(aMap.Contains(25));
  EXPECT_TRUE(aMap.Contains(30));

  EXPECT_EQ(aMap.FindIndex(10), 1);
  EXPECT_EQ(aMap.FindIndex(25), 2);
  EXPECT_EQ(aMap.FindIndex(30), 3);

  EXPECT_DOUBLE_EQ(aMap.FindFromKey(10), 1.0);
  EXPECT_DOUBLE_EQ(aMap.FindFromKey(25), 2.5);
  EXPECT_DOUBLE_EQ(aMap.FindFromKey(30), 3.0);
}

TEST(NCollection_IndexedDataMapTest, Swap)
{
  NCollection_IndexedDataMap<KeyType, ItemType> aMap;

  aMap.Add(10, 1.0);
  aMap.Add(20, 2.0);
  aMap.Add(30, 3.0);

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

  EXPECT_DOUBLE_EQ(aMap.FindFromIndex(1), 3.0);
  EXPECT_DOUBLE_EQ(aMap.FindFromIndex(2), 2.0);
  EXPECT_DOUBLE_EQ(aMap.FindFromIndex(3), 1.0);

  EXPECT_DOUBLE_EQ(aMap.FindFromKey(10), 1.0);
  EXPECT_DOUBLE_EQ(aMap.FindFromKey(20), 2.0);
  EXPECT_DOUBLE_EQ(aMap.FindFromKey(30), 3.0);
}

TEST(NCollection_IndexedDataMapTest, Clear)
{
  NCollection_IndexedDataMap<KeyType, ItemType> aMap;

  aMap.Add(10, 1.0);
  aMap.Add(20, 2.0);
  aMap.Add(30, 3.0);

  EXPECT_EQ(aMap.Extent(), 3);

  aMap.Clear();

  EXPECT_TRUE(aMap.IsEmpty());
  EXPECT_EQ(aMap.Extent(), 0);

  int index1 = aMap.Add(40, 4.0);
  EXPECT_EQ(index1, 1);
  EXPECT_EQ(aMap.Extent(), 1);
}

TEST(NCollection_IndexedDataMapTest, CopyConstructor)
{
  NCollection_IndexedDataMap<KeyType, ItemType> aMap1;

  aMap1.Add(10, 1.0);
  aMap1.Add(20, 2.0);
  aMap1.Add(30, 3.0);

  NCollection_IndexedDataMap<KeyType, ItemType> aMap2(aMap1);

  EXPECT_EQ(aMap2.Extent(), 3);
  EXPECT_TRUE(aMap2.Contains(10));
  EXPECT_TRUE(aMap2.Contains(20));
  EXPECT_TRUE(aMap2.Contains(30));

  EXPECT_EQ(aMap2.FindIndex(10), 1);
  EXPECT_EQ(aMap2.FindIndex(20), 2);
  EXPECT_EQ(aMap2.FindIndex(30), 3);

  EXPECT_DOUBLE_EQ(aMap2.FindFromKey(10), 1.0);
  EXPECT_DOUBLE_EQ(aMap2.FindFromKey(20), 2.0);
  EXPECT_DOUBLE_EQ(aMap2.FindFromKey(30), 3.0);

  aMap1.Add(40, 4.0);
  EXPECT_EQ(aMap1.Extent(), 4);
  EXPECT_EQ(aMap2.Extent(), 3);
  EXPECT_FALSE(aMap2.Contains(40));
}

TEST(NCollection_IndexedDataMapTest, AssignmentOperator)
{
  NCollection_IndexedDataMap<KeyType, ItemType> aMap1;
  NCollection_IndexedDataMap<KeyType, ItemType> aMap2;

  aMap1.Add(10, 1.0);
  aMap1.Add(20, 2.0);

  aMap2.Add(30, 3.0);
  aMap2.Add(40, 4.0);
  aMap2.Add(50, 5.0);

  aMap2 = aMap1;

  EXPECT_EQ(aMap2.Extent(), 2);
  EXPECT_TRUE(aMap2.Contains(10));
  EXPECT_TRUE(aMap2.Contains(20));
  EXPECT_FALSE(aMap2.Contains(30));
  EXPECT_FALSE(aMap2.Contains(40));
  EXPECT_FALSE(aMap2.Contains(50));

  EXPECT_DOUBLE_EQ(aMap2.FindFromKey(10), 1.0);
  EXPECT_DOUBLE_EQ(aMap2.FindFromKey(20), 2.0);
}

TEST(NCollection_IndexedDataMapTest, Iterator)
{
  NCollection_IndexedDataMap<KeyType, ItemType> aMap;

  aMap.Add(10, 1.0);
  aMap.Add(20, 2.0);
  aMap.Add(30, 3.0);

  bool   found10 = false;
  bool   found20 = false;
  bool   found30 = false;
  size_t count   = 0;

  for (NCollection_IndexedDataMap<KeyType, ItemType>::Iterator it(aMap); it.More();
       it.Next(), ++count)
  {
    const KeyType&  key   = it.Key();
    const ItemType& value = it.Value();

    if (key == 10 && value == 1.0)
      found10 = true;
    else if (key == 20 && value == 2.0)
      found20 = true;
    else if (key == 30 && value == 3.0)
      found30 = true;
  }

  EXPECT_EQ(count, 3);
  EXPECT_TRUE(found10);
  EXPECT_TRUE(found20);
  EXPECT_TRUE(found30);

  for (NCollection_IndexedDataMap<KeyType, ItemType>::Iterator it(aMap); it.More(); it.Next())
  {
    it.ChangeValue() *= 2;
  }

  EXPECT_DOUBLE_EQ(aMap.FindFromKey(10), 2.0);
  EXPECT_DOUBLE_EQ(aMap.FindFromKey(20), 4.0);
  EXPECT_DOUBLE_EQ(aMap.FindFromKey(30), 6.0);
}

TEST(NCollection_IndexedDataMapTest, StlIterator)
{
  NCollection_IndexedDataMap<KeyType, ItemType> aMap;

  aMap.Add(10, 1.0);
  aMap.Add(20, 2.0);
  aMap.Add(30, 3.0);

  bool   found1 = false;
  bool   found2 = false;
  bool   found3 = false;
  size_t count  = 0;

  for (auto it = aMap.begin(); it != aMap.end(); ++it, ++count)
  {
    if (*it == 1.0)
      found1 = true;
    else if (*it == 2.0)
      found2 = true;
    else if (*it == 3.0)
      found3 = true;
  }

  EXPECT_EQ(count, 3);
  EXPECT_TRUE(found1);
  EXPECT_TRUE(found2);
  EXPECT_TRUE(found3);

  count  = 0;
  found1 = false;
  found2 = false;
  found3 = false;

  for (auto it = aMap.cbegin(); it != aMap.cend(); ++it, ++count)
  {
    if (*it == 1.0)
      found1 = true;
    else if (*it == 2.0)
      found2 = true;
    else if (*it == 3.0)
      found3 = true;
  }

  EXPECT_EQ(count, 3);
  EXPECT_TRUE(found1);
  EXPECT_TRUE(found2);
  EXPECT_TRUE(found3);
}

TEST(NCollection_IndexedDataMapTest, StringKeys)
{

  NCollection_IndexedDataMap<TCollection_AsciiString, ItemType> aStringMap;

  int index1 = aStringMap.Add(TCollection_AsciiString("First"), 1.0);
  int index2 = aStringMap.Add(TCollection_AsciiString("Second"), 2.0);
  int index3 = aStringMap.Add(TCollection_AsciiString("Third"), 3.0);

  EXPECT_EQ(index1, 1);
  EXPECT_EQ(index2, 2);
  EXPECT_EQ(index3, 3);

  EXPECT_EQ(aStringMap.FindIndex(TCollection_AsciiString("First")), 1);
  EXPECT_EQ(aStringMap.FindIndex(TCollection_AsciiString("Second")), 2);
  EXPECT_EQ(aStringMap.FindIndex(TCollection_AsciiString("Third")), 3);

  EXPECT_TRUE(aStringMap.FindKey(1).IsEqual("First"));
  EXPECT_TRUE(aStringMap.FindKey(2).IsEqual("Second"));
  EXPECT_TRUE(aStringMap.FindKey(3).IsEqual("Third"));

  EXPECT_DOUBLE_EQ(aStringMap.FindFromKey(TCollection_AsciiString("First")), 1.0);
  EXPECT_DOUBLE_EQ(aStringMap.FindFromKey(TCollection_AsciiString("Second")), 2.0);
  EXPECT_DOUBLE_EQ(aStringMap.FindFromKey(TCollection_AsciiString("Third")), 3.0);
}

TEST(NCollection_IndexedDataMapTest, ComplexKeyAndValue)
{

  NCollection_IndexedDataMap<TestKey, TestItem> aComplexMap;

  TestKey key1(1, "One");
  TestKey key2(2, "Two");
  TestKey key3(3, "Three");

  TestItem item1(1.1, "Item One");
  TestItem item2(2.2, "Item Two");
  TestItem item3(3.3, "Item Three");

  int index1 = aComplexMap.Add(key1, item1);
  int index2 = aComplexMap.Add(key2, item2);
  int index3 = aComplexMap.Add(key3, item3);

  EXPECT_EQ(index1, 1);
  EXPECT_EQ(index2, 2);
  EXPECT_EQ(index3, 3);

  EXPECT_EQ(aComplexMap.FindIndex(key1), 1);
  EXPECT_EQ(aComplexMap.FindIndex(key2), 2);
  EXPECT_EQ(aComplexMap.FindIndex(key3), 3);

  EXPECT_EQ(aComplexMap.FindKey(1).GetId(), 1);
  EXPECT_EQ(aComplexMap.FindKey(2).GetId(), 2);
  EXPECT_EQ(aComplexMap.FindKey(3).GetId(), 3);

  EXPECT_DOUBLE_EQ(aComplexMap.FindFromKey(key1).GetValue(), 1.1);
  EXPECT_DOUBLE_EQ(aComplexMap.FindFromKey(key2).GetValue(), 2.2);
  EXPECT_DOUBLE_EQ(aComplexMap.FindFromKey(key3).GetValue(), 3.3);

  EXPECT_TRUE(aComplexMap.Contains(TestKey(1, "One")));
  EXPECT_FALSE(aComplexMap.Contains(TestKey(4, "Four")));

  aComplexMap.ChangeFromKey(key1).SetValue(1.5);
  EXPECT_DOUBLE_EQ(aComplexMap.FindFromKey(key1).GetValue(), 1.5);
}

TEST(NCollection_IndexedDataMapTest, Exchange)
{
  NCollection_IndexedDataMap<KeyType, ItemType> aMap1;
  NCollection_IndexedDataMap<KeyType, ItemType> aMap2;

  aMap1.Add(10, 1.0);
  aMap1.Add(20, 2.0);

  aMap2.Add(30, 3.0);
  aMap2.Add(40, 4.0);
  aMap2.Add(50, 5.0);

  aMap1.Exchange(aMap2);

  EXPECT_EQ(aMap1.Extent(), 3);
  EXPECT_TRUE(aMap1.Contains(30));
  EXPECT_TRUE(aMap1.Contains(40));
  EXPECT_TRUE(aMap1.Contains(50));
  EXPECT_DOUBLE_EQ(aMap1.FindFromKey(30), 3.0);
  EXPECT_DOUBLE_EQ(aMap1.FindFromKey(40), 4.0);
  EXPECT_DOUBLE_EQ(aMap1.FindFromKey(50), 5.0);

  EXPECT_EQ(aMap2.Extent(), 2);
  EXPECT_TRUE(aMap2.Contains(10));
  EXPECT_TRUE(aMap2.Contains(20));
  EXPECT_DOUBLE_EQ(aMap2.FindFromKey(10), 1.0);
  EXPECT_DOUBLE_EQ(aMap2.FindFromKey(20), 2.0);
}

TEST(NCollection_IndexedDataMapTest, ReSize)
{
  NCollection_IndexedDataMap<KeyType, ItemType> aMap(3);

  for (int i = 1; i <= 100; ++i)
  {
    aMap.Add(i, static_cast<double>(i) / 10.0);
  }

  EXPECT_EQ(aMap.Extent(), 100);
  for (int i = 1; i <= 100; ++i)
  {
    EXPECT_TRUE(aMap.Contains(i));
    EXPECT_EQ(aMap.FindIndex(i), i);
    EXPECT_DOUBLE_EQ(aMap.FindFromKey(i), static_cast<double>(i) / 10.0);
  }

  aMap.ReSize(200);

  EXPECT_EQ(aMap.Extent(), 100);
  for (int i = 1; i <= 100; ++i)
  {
    EXPECT_TRUE(aMap.Contains(i));
    EXPECT_EQ(aMap.FindIndex(i), i);
    EXPECT_DOUBLE_EQ(aMap.FindFromKey(i), static_cast<double>(i) / 10.0);
  }
}

TEST(NCollection_IndexedDataMapTest, STLAlgorithmCompatibility_MinMax)
{
  NCollection_IndexedDataMap<int, int> aMap;

  for (int anIdx = 10; anIdx <= 50; anIdx += 5)
  {
    aMap.Add(anIdx, anIdx * 2);
  }

  EXPECT_FALSE(aMap.IsEmpty());

  auto aMinElement = std::min_element(aMap.cbegin(), aMap.cend());
  auto aMaxElement = std::max_element(aMap.cbegin(), aMap.cend());

  EXPECT_TRUE(aMinElement != aMap.cend());
  EXPECT_TRUE(aMaxElement != aMap.cend());
  EXPECT_LE(*aMinElement, *aMaxElement);
}

TEST(NCollection_IndexedDataMapTest, STLAlgorithmCompatibility_Find)
{
  NCollection_IndexedDataMap<int, int> aMap;

  aMap.Add(100, 200);
  aMap.Add(200, 400);
  aMap.Add(300, 600);

  auto aFound = std::find(aMap.cbegin(), aMap.cend(), 200);
  EXPECT_TRUE(aFound != aMap.cend());
  EXPECT_EQ(*aFound, 200);

  auto aNotFound = std::find(aMap.cbegin(), aMap.cend(), 999);
  EXPECT_TRUE(aNotFound == aMap.cend());
}

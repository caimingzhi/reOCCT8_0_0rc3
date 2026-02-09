

#include <NCollection_DoubleMap.hpp>
#include <TCollection_AsciiString.hpp>

#include <gtest/gtest.h>

typedef int    Key1Type;
typedef double Key2Type;

class TestKey1
{
public:
  TestKey1(int id = 0, const char* name = "")
      : myId(id),
        myName(name)
  {
  }

  bool operator==(const TestKey1& other) const
  {
    return myId == other.myId && myName == other.myName;
  }

  int GetId() const { return myId; }

  const std::string& GetName() const { return myName; }

private:
  int         myId;
  std::string myName;
};

class TestKey2
{
public:
  TestKey2(double value = 0.0, const char* code = "")
      : myValue(value),
        myCode(code)
  {
  }

  bool operator==(const TestKey2& other) const
  {
    return fabs(myValue - other.myValue) < 1e-10 && myCode == other.myCode;
  }

  double GetValue() const { return myValue; }

  const std::string& GetCode() const { return myCode; }

private:
  double      myValue;
  std::string myCode;
};

namespace std
{
  template <>
  struct hash<TestKey1>
  {
    size_t operator()(const TestKey1& key) const
    {
      return static_cast<size_t>(key.GetId() + std::hash<std::string>()(key.GetName()));
    }
  };

  template <>
  struct hash<TestKey2>
  {
    size_t operator()(const TestKey2& key) const
    {
      return static_cast<size_t>(key.GetValue() * 100 + std::hash<std::string>()(key.GetCode()));
    }
  };
} // namespace std

TEST(NCollection_DoubleMapTest, DefaultConstructor)
{

  NCollection_DoubleMap<Key1Type, Key2Type> aMap;
  EXPECT_TRUE(aMap.IsEmpty());
  EXPECT_EQ(aMap.Extent(), 0);
  EXPECT_EQ(aMap.Size(), 0);
}

TEST(NCollection_DoubleMapTest, CustomBuckets)
{

  NCollection_DoubleMap<Key1Type, Key2Type> aMap(100);
  EXPECT_TRUE(aMap.IsEmpty());
  EXPECT_EQ(aMap.Extent(), 0);
  EXPECT_EQ(aMap.Size(), 0);
}

TEST(NCollection_DoubleMapTest, BasicBindFind)
{
  NCollection_DoubleMap<Key1Type, Key2Type> aMap;

  aMap.Bind(10, 1.0);
  aMap.Bind(20, 2.0);
  aMap.Bind(30, 3.0);

  EXPECT_EQ(aMap.Extent(), 3);

  EXPECT_TRUE(aMap.IsBound1(10));
  EXPECT_TRUE(aMap.IsBound1(20));
  EXPECT_TRUE(aMap.IsBound1(30));
  EXPECT_FALSE(aMap.IsBound1(40));

  EXPECT_TRUE(aMap.IsBound2(1.0));
  EXPECT_TRUE(aMap.IsBound2(2.0));
  EXPECT_TRUE(aMap.IsBound2(3.0));
  EXPECT_FALSE(aMap.IsBound2(4.0));

  EXPECT_DOUBLE_EQ(aMap.Find1(10), 1.0);
  EXPECT_DOUBLE_EQ(aMap.Find1(20), 2.0);
  EXPECT_DOUBLE_EQ(aMap.Find1(30), 3.0);

  EXPECT_EQ(aMap.Find2(1.0), 10);
  EXPECT_EQ(aMap.Find2(2.0), 20);
  EXPECT_EQ(aMap.Find2(3.0), 30);
}

TEST(NCollection_DoubleMapTest, BindWithDuplicateKeys)
{
  NCollection_DoubleMap<Key1Type, Key2Type> aMap;

  aMap.Bind(10, 1.0);
  EXPECT_EQ(aMap.Extent(), 1);
  EXPECT_DOUBLE_EQ(aMap.Find1(10), 1.0);

  EXPECT_ANY_THROW(aMap.Bind(10, 2.0));
  EXPECT_EQ(aMap.Extent(), 1);
  EXPECT_DOUBLE_EQ(aMap.Find1(10), 1.0);
  EXPECT_FALSE(aMap.IsBound2(2.0));

  EXPECT_ANY_THROW(aMap.Bind(20, 1.0));
  EXPECT_EQ(aMap.Extent(), 1);
  EXPECT_FALSE(aMap.IsBound1(20));
}

TEST(NCollection_DoubleMapTest, UnbindTest)
{
  NCollection_DoubleMap<Key1Type, Key2Type> aMap;

  aMap.Bind(10, 1.0);
  aMap.Bind(20, 2.0);
  aMap.Bind(30, 3.0);

  EXPECT_EQ(aMap.Extent(), 3);

  aMap.UnBind1(20);
  EXPECT_EQ(aMap.Extent(), 2);
  EXPECT_FALSE(aMap.IsBound1(20));
  EXPECT_FALSE(aMap.IsBound2(2.0));

  aMap.UnBind2(3.0);
  EXPECT_EQ(aMap.Extent(), 1);
  EXPECT_FALSE(aMap.IsBound1(30));
  EXPECT_FALSE(aMap.IsBound2(3.0));

  aMap.UnBind1(40);
  EXPECT_EQ(aMap.Extent(), 1);

  aMap.UnBind2(4.0);
  EXPECT_EQ(aMap.Extent(), 1);
}

TEST(NCollection_DoubleMapTest, Clear)
{
  NCollection_DoubleMap<Key1Type, Key2Type> aMap;

  aMap.Bind(10, 1.0);
  aMap.Bind(20, 2.0);
  aMap.Bind(30, 3.0);

  EXPECT_EQ(aMap.Extent(), 3);

  aMap.Clear();

  EXPECT_TRUE(aMap.IsEmpty());
  EXPECT_EQ(aMap.Extent(), 0);

  aMap.Bind(40, 4.0);
  EXPECT_EQ(aMap.Extent(), 1);
}

TEST(NCollection_DoubleMapTest, SeekTests)
{
  NCollection_DoubleMap<Key1Type, Key2Type> aMap;

  aMap.Bind(10, 1.0);
  aMap.Bind(20, 2.0);

  const Key2Type* key2Ptr = aMap.Seek1(10);
  EXPECT_TRUE(key2Ptr != nullptr);
  EXPECT_DOUBLE_EQ(*key2Ptr, 1.0);

  const Key1Type* key1Ptr = aMap.Seek2(2.0);
  EXPECT_TRUE(key1Ptr != nullptr);
  EXPECT_EQ(*key1Ptr, 20);

  EXPECT_TRUE(aMap.Seek1(30) == nullptr);
  EXPECT_TRUE(aMap.Seek2(3.0) == nullptr);
}

TEST(NCollection_DoubleMapTest, CopyConstructor)
{
  NCollection_DoubleMap<Key1Type, Key2Type> aMap1;

  aMap1.Bind(10, 1.0);
  aMap1.Bind(20, 2.0);
  aMap1.Bind(30, 3.0);

  NCollection_DoubleMap<Key1Type, Key2Type> aMap2(aMap1);

  EXPECT_EQ(aMap2.Extent(), 3);
  EXPECT_TRUE(aMap2.IsBound1(10));
  EXPECT_TRUE(aMap2.IsBound1(20));
  EXPECT_TRUE(aMap2.IsBound1(30));
  EXPECT_TRUE(aMap2.IsBound2(1.0));
  EXPECT_TRUE(aMap2.IsBound2(2.0));
  EXPECT_TRUE(aMap2.IsBound2(3.0));

  aMap1.Bind(40, 4.0);
  EXPECT_EQ(aMap1.Extent(), 4);
  EXPECT_EQ(aMap2.Extent(), 3);
  EXPECT_FALSE(aMap2.IsBound1(40));
  EXPECT_FALSE(aMap2.IsBound2(4.0));
}

TEST(NCollection_DoubleMapTest, AssignmentOperator)
{
  NCollection_DoubleMap<Key1Type, Key2Type> aMap1;
  NCollection_DoubleMap<Key1Type, Key2Type> aMap2;

  aMap1.Bind(10, 1.0);
  aMap1.Bind(20, 2.0);

  aMap2.Bind(30, 3.0);
  aMap2.Bind(40, 4.0);
  aMap2.Bind(50, 5.0);

  aMap2 = aMap1;

  EXPECT_EQ(aMap2.Extent(), 2);
  EXPECT_TRUE(aMap2.IsBound1(10));
  EXPECT_TRUE(aMap2.IsBound1(20));
  EXPECT_FALSE(aMap2.IsBound1(30));
  EXPECT_FALSE(aMap2.IsBound1(40));
  EXPECT_FALSE(aMap2.IsBound1(50));

  EXPECT_TRUE(aMap2.IsBound2(1.0));
  EXPECT_TRUE(aMap2.IsBound2(2.0));
  EXPECT_FALSE(aMap2.IsBound2(3.0));
  EXPECT_FALSE(aMap2.IsBound2(4.0));
  EXPECT_FALSE(aMap2.IsBound2(5.0));
}

TEST(NCollection_DoubleMapTest, ReSize)
{
  NCollection_DoubleMap<Key1Type, Key2Type> aMap(3);

  for (int i = 1; i <= 100; ++i)
  {
    aMap.Bind(i, static_cast<double>(i) / 10.0);
  }

  EXPECT_EQ(aMap.Extent(), 100);
  for (int i = 1; i <= 100; ++i)
  {
    EXPECT_TRUE(aMap.IsBound1(i));
    EXPECT_TRUE(aMap.IsBound2(static_cast<double>(i) / 10.0));
    EXPECT_DOUBLE_EQ(aMap.Find1(i), static_cast<double>(i) / 10.0);
    EXPECT_EQ(aMap.Find2(static_cast<double>(i) / 10.0), i);
  }
}

TEST(NCollection_DoubleMapTest, Exchange)
{
  NCollection_DoubleMap<Key1Type, Key2Type> aMap1;
  NCollection_DoubleMap<Key1Type, Key2Type> aMap2;

  aMap1.Bind(10, 1.0);
  aMap1.Bind(20, 2.0);

  aMap2.Bind(30, 3.0);
  aMap2.Bind(40, 4.0);
  aMap2.Bind(50, 5.0);

  aMap1.Exchange(aMap2);

  EXPECT_EQ(aMap1.Extent(), 3);
  EXPECT_TRUE(aMap1.IsBound1(30));
  EXPECT_TRUE(aMap1.IsBound1(40));
  EXPECT_TRUE(aMap1.IsBound1(50));
  EXPECT_TRUE(aMap1.IsBound2(3.0));
  EXPECT_TRUE(aMap1.IsBound2(4.0));
  EXPECT_TRUE(aMap1.IsBound2(5.0));

  EXPECT_EQ(aMap2.Extent(), 2);
  EXPECT_TRUE(aMap2.IsBound1(10));
  EXPECT_TRUE(aMap2.IsBound1(20));
  EXPECT_TRUE(aMap2.IsBound2(1.0));
  EXPECT_TRUE(aMap2.IsBound2(2.0));
}

TEST(NCollection_DoubleMapTest, Iterator)
{
  NCollection_DoubleMap<Key1Type, Key2Type> aMap;

  aMap.Bind(10, 1.0);
  aMap.Bind(20, 2.0);
  aMap.Bind(30, 3.0);

  bool   found10 = false;
  bool   found20 = false;
  bool   found30 = false;
  size_t count   = 0;

  for (NCollection_DoubleMap<Key1Type, Key2Type>::Iterator it(aMap); it.More(); it.Next(), ++count)
  {
    const Key1Type& key1 = it.Key1();
    const Key2Type& key2 = it.Key2();

    if (key1 == 10 && key2 == 1.0)
      found10 = true;
    else if (key1 == 20 && key2 == 2.0)
      found20 = true;
    else if (key1 == 30 && key2 == 3.0)
      found30 = true;
  }

  EXPECT_EQ(count, 3);
  EXPECT_TRUE(found10);
  EXPECT_TRUE(found20);
  EXPECT_TRUE(found30);
}

TEST(NCollection_DoubleMapTest, StringKeys)
{

  NCollection_DoubleMap<TCollection_AsciiString, TCollection_AsciiString> aStringMap;

  aStringMap.Bind(TCollection_AsciiString("Key1"), TCollection_AsciiString("Value1"));
  aStringMap.Bind(TCollection_AsciiString("Key2"), TCollection_AsciiString("Value2"));
  aStringMap.Bind(TCollection_AsciiString("Key3"), TCollection_AsciiString("Value3"));

  EXPECT_EQ(aStringMap.Extent(), 3);

  EXPECT_TRUE(aStringMap.IsBound1(TCollection_AsciiString("Key1")));
  EXPECT_TRUE(aStringMap.IsBound1(TCollection_AsciiString("Key2")));
  EXPECT_TRUE(aStringMap.IsBound1(TCollection_AsciiString("Key3")));

  EXPECT_TRUE(aStringMap.IsBound2(TCollection_AsciiString("Value1")));
  EXPECT_TRUE(aStringMap.IsBound2(TCollection_AsciiString("Value2")));
  EXPECT_TRUE(aStringMap.IsBound2(TCollection_AsciiString("Value3")));

  EXPECT_TRUE(aStringMap.Find1(TCollection_AsciiString("Key1")).IsEqual("Value1"));
  EXPECT_TRUE(aStringMap.Find1(TCollection_AsciiString("Key2")).IsEqual("Value2"));
  EXPECT_TRUE(aStringMap.Find1(TCollection_AsciiString("Key3")).IsEqual("Value3"));

  EXPECT_TRUE(aStringMap.Find2(TCollection_AsciiString("Value1")).IsEqual("Key1"));
  EXPECT_TRUE(aStringMap.Find2(TCollection_AsciiString("Value2")).IsEqual("Key2"));
  EXPECT_TRUE(aStringMap.Find2(TCollection_AsciiString("Value3")).IsEqual("Key3"));
}

TEST(NCollection_DoubleMapTest, ComplexKeys)
{

  NCollection_DoubleMap<TestKey1, TestKey2> aComplexMap;

  TestKey1 key1_1(1, "One");
  TestKey1 key1_2(2, "Two");
  TestKey1 key1_3(3, "Three");

  TestKey2 key2_1(1.1, "A");
  TestKey2 key2_2(2.2, "B");
  TestKey2 key2_3(3.3, "C");

  aComplexMap.Bind(key1_1, key2_1);
  aComplexMap.Bind(key1_2, key2_2);
  aComplexMap.Bind(key1_3, key2_3);

  EXPECT_EQ(aComplexMap.Extent(), 3);

  EXPECT_TRUE(aComplexMap.IsBound1(TestKey1(1, "One")));
  EXPECT_TRUE(aComplexMap.IsBound1(TestKey1(2, "Two")));
  EXPECT_TRUE(aComplexMap.IsBound1(TestKey1(3, "Three")));

  EXPECT_TRUE(aComplexMap.IsBound2(TestKey2(1.1, "A")));
  EXPECT_TRUE(aComplexMap.IsBound2(TestKey2(2.2, "B")));
  EXPECT_TRUE(aComplexMap.IsBound2(TestKey2(3.3, "C")));

  const TestKey2& foundKey2 = aComplexMap.Find1(key1_2);
  EXPECT_DOUBLE_EQ(foundKey2.GetValue(), 2.2);
  EXPECT_EQ(foundKey2.GetCode(), "B");

  const TestKey1& foundKey1 = aComplexMap.Find2(key2_3);
  EXPECT_EQ(foundKey1.GetId(), 3);
  EXPECT_EQ(foundKey1.GetName(), "Three");
}

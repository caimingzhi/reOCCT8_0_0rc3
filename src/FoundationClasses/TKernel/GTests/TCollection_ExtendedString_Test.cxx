

#include <TCollection_ExtendedString.hpp>
#include <TCollection_AsciiString.hpp>

#include <gtest/gtest.h>

TEST(TCollection_ExtendedStringTest, DefaultConstructor)
{
  TCollection_ExtendedString aString;
  EXPECT_EQ(0, aString.Length());
  EXPECT_TRUE(aString.IsEmpty());
}

TEST(TCollection_ExtendedStringTest, ConstructorWithCString)
{
  TCollection_ExtendedString aString("Test String");
  EXPECT_EQ(11, aString.Length());
  EXPECT_FALSE(aString.IsEmpty());
}

TEST(TCollection_ExtendedStringTest, ConstructorWithChar)
{
  TCollection_ExtendedString aString('A');
  EXPECT_EQ(1, aString.Length());
  EXPECT_FALSE(aString.IsEmpty());
}

TEST(TCollection_ExtendedStringTest, ConstructorWithAsciiString)
{
  TCollection_AsciiString    asciiString("ASCII Test");
  TCollection_ExtendedString extendedString(asciiString);
  EXPECT_EQ(asciiString.Length(), extendedString.Length());
}

TEST(TCollection_ExtendedStringTest, CopyConstructor)
{
  TCollection_ExtendedString aString1("Original");
  TCollection_ExtendedString aString2(aString1);
  EXPECT_EQ(aString1.Length(), aString2.Length());
  EXPECT_TRUE(aString1.IsEqual(aString2));
}

TEST(TCollection_ExtendedStringTest, AssignmentOperator)
{
  TCollection_ExtendedString aString1("First");
  TCollection_ExtendedString aString2;
  aString2 = aString1;
  EXPECT_TRUE(aString1.IsEqual(aString2));

  aString1 = TCollection_ExtendedString("Changed");
  EXPECT_FALSE(aString1.IsEqual(aString2));
}

TEST(TCollection_ExtendedStringTest, Concatenation)
{
  TCollection_ExtendedString aString1("Hello");
  TCollection_ExtendedString aString2(" World");
  TCollection_ExtendedString aString3 = aString1 + aString2;
  EXPECT_EQ(11, aString3.Length());

  TCollection_AsciiString asciiResult(aString3);
  EXPECT_STREQ("Hello World", asciiResult.ToCString());

  aString1 += aString2;
  EXPECT_TRUE(aString1.IsEqual(aString3));
}

TEST(TCollection_ExtendedStringTest, ConversionToFromAscii)
{

  TCollection_AsciiString    asciiString("Test String");
  TCollection_ExtendedString extendedString(asciiString);

  TCollection_AsciiString convertedBack(extendedString);

  EXPECT_STREQ(asciiString.ToCString(), convertedBack.ToCString());
}

TEST(TCollection_ExtendedStringTest, Comparison)
{
  TCollection_ExtendedString aString1("Test");
  TCollection_ExtendedString aString2("Test");
  TCollection_ExtendedString aString3("Different");

  EXPECT_TRUE(aString1.IsEqual(aString2));
  EXPECT_TRUE(aString1 == aString2);
  EXPECT_FALSE(aString1.IsDifferent(aString2));
  EXPECT_FALSE(aString1 != aString2);

  EXPECT_FALSE(aString1.IsEqual(aString3));
  EXPECT_FALSE(aString1 == aString3);
  EXPECT_TRUE(aString1.IsDifferent(aString3));
  EXPECT_TRUE(aString1 != aString3);

  TCollection_ExtendedString aStringA("A");
  TCollection_ExtendedString aStringZ("Z");

  EXPECT_TRUE(aStringA.IsLess(aStringZ));
  EXPECT_TRUE(aStringA < aStringZ);
  EXPECT_FALSE(aStringA.IsGreater(aStringZ));
  EXPECT_FALSE(aStringA > aStringZ);

  EXPECT_TRUE(aStringZ.IsGreater(aStringA));
  EXPECT_TRUE(aStringZ > aStringA);
  EXPECT_FALSE(aStringZ.IsLess(aStringA));
  EXPECT_FALSE(aStringZ < aStringA);
}

TEST(TCollection_ExtendedStringTest, UnicodeSupport)
{

  const char16_t             unicodeChars[] = {0x0041, 0x00A9, 0x2122, 0x20AC, 0};
  TCollection_ExtendedString unicodeString(unicodeChars);

  EXPECT_EQ(4, unicodeString.Length());
  EXPECT_EQ(0x0041, unicodeString.Value(1));
  EXPECT_EQ(0x00A9, unicodeString.Value(2));
  EXPECT_EQ(0x2122, unicodeString.Value(3));
  EXPECT_EQ(0x20AC, unicodeString.Value(4));
}

TEST(TCollection_ExtendedStringTest, HashCode)
{
  TCollection_ExtendedString aString1("Test");
  TCollection_ExtendedString aString2("Test");
  TCollection_ExtendedString aString3("Different");

  EXPECT_EQ(aString1.HashCode(), aString2.HashCode());
  EXPECT_NE(aString1.HashCode(), aString3.HashCode());
}

TEST(TCollection_ExtendedStringTest, Remove)
{
  TCollection_ExtendedString aString("Hello World");
  aString.Remove(6, 6);

  TCollection_AsciiString asciiResult(aString);
  EXPECT_STREQ("Hello", asciiResult.ToCString());
}

TEST(TCollection_ExtendedStringTest, ToExtString)
{
  TCollection_ExtendedString aString("Test String");
  const char16_t*            extString = aString.ToExtString();

  EXPECT_EQ('T', extString[0]);
  EXPECT_EQ('e', extString[1]);
  EXPECT_EQ('s', extString[2]);
  EXPECT_EQ('t', extString[3]);
}

TEST(TCollection_ExtendedStringTest, IsAscii)
{
  TCollection_ExtendedString asciiString("Simple ASCII");
  EXPECT_TRUE(asciiString.IsAscii());

  char16_t                   unicodeChars[] = {'A', 0x20AC, 0};
  TCollection_ExtendedString unicodeString(unicodeChars);
  EXPECT_FALSE(unicodeString.IsAscii());
}

TEST(TCollection_ExtendedStringTest, Cat)
{
  TCollection_ExtendedString aString("Hello");

  TCollection_ExtendedString result1 = aString.Cat(TCollection_ExtendedString(" World"));
  TCollection_AsciiString    asciiResult1(result1);
  EXPECT_STREQ("Hello World", asciiResult1.ToCString());

  TCollection_ExtendedString result2 = aString.Cat('!');
  TCollection_AsciiString    asciiResult2(result2);
  EXPECT_STREQ("Hello!", asciiResult2.ToCString());
}

TEST(TCollection_ExtendedStringTest, ChangeAll)
{
  TCollection_ExtendedString aString("Helloo Woorld");
  aString.ChangeAll('o', 'X');

  TCollection_AsciiString asciiResult(aString);
  EXPECT_STREQ("HellXX WXXrld", asciiResult.ToCString());
}

TEST(TCollection_ExtendedStringTest, UTF8Conversion)
{

  TCollection_ExtendedString aString("Hello World");

  int aBufferSize = aString.LengthOfCString();
  EXPECT_GT(aBufferSize, 0);

  Standard_PCharacter aBuffer        = new char[aBufferSize + 1];
  int                 anActualLength = aString.ToUTF8CString(aBuffer);

  EXPECT_EQ(aBufferSize, anActualLength);
  EXPECT_EQ('\0', aBuffer[anActualLength]);
  EXPECT_STREQ("Hello World", aBuffer);

  delete[] aBuffer;
}

TEST(TCollection_ExtendedStringTest, UTF8ConversionUnicode)
{

  const char16_t             aUnicodeStr[] = {0x0048, 0x00E9, 0x006C, 0x006C, 0x006F, 0};
  TCollection_ExtendedString aString(aUnicodeStr);

  int aBufferSize = aString.LengthOfCString();
  EXPECT_GT(aBufferSize, 5);

  Standard_PCharacter aBuffer        = new char[aBufferSize + 1];
  int                 anActualLength = aString.ToUTF8CString(aBuffer);

  EXPECT_EQ(aBufferSize, anActualLength);
  EXPECT_EQ('\0', aBuffer[anActualLength]);

  delete[] aBuffer;
}

TEST(TCollection_ExtendedStringTest, WideCharConstructor)
{

  const wchar_t*             aWideStr = L"Wide string test";
  TCollection_ExtendedString aString(aWideStr);

  EXPECT_GT(aString.Length(), 0);
  EXPECT_FALSE(aString.IsEmpty());
}

TEST(TCollection_ExtendedStringTest, NumericalConstructors)
{

  TCollection_ExtendedString anIntString(42);
  TCollection_AsciiString    anAsciiFromInt(anIntString);
  EXPECT_STREQ("42", anAsciiFromInt.ToCString());

  TCollection_ExtendedString aRealString(3.14);
  TCollection_AsciiString    anAsciiFromReal(aRealString);
  const char*                aRealCStr = anAsciiFromReal.ToCString();
  EXPECT_TRUE(strstr(aRealCStr, "3.14") != nullptr);
}

TEST(TCollection_ExtendedStringTest, FillerConstructor)
{

  TCollection_ExtendedString aFilledString(5, 'X');
  EXPECT_EQ(5, aFilledString.Length());

  TCollection_AsciiString anAsciiFromFilled(aFilledString);
  EXPECT_STREQ("XXXXX", anAsciiFromFilled.ToCString());
}

TEST(TCollection_ExtendedStringTest, ExtendedCharConstructor)
{

  const char16_t             aEuroChar = 0x20AC;
  TCollection_ExtendedString aString(aEuroChar);

  EXPECT_EQ(1, aString.Length());
  EXPECT_FALSE(aString.IsAscii());
  EXPECT_EQ(aEuroChar, aString.Value(1));
}

TEST(TCollection_ExtendedStringTest, UnicodeCharacters)
{

  const char16_t aLatinA = 0x0041;
  const char16_t aLatinE = 0x00E9;
  const char16_t aEuro   = 0x20AC;
  const char16_t aCJK    = 0x4E2D;

  const char16_t             aUnicodeStr[] = {aLatinA, aLatinE, aEuro, aCJK, 0};
  TCollection_ExtendedString aString(aUnicodeStr);

  EXPECT_EQ(4, aString.Length());
  EXPECT_EQ(aLatinA, aString.Value(1));
  EXPECT_EQ(aLatinE, aString.Value(2));
  EXPECT_EQ(aEuro, aString.Value(3));
  EXPECT_EQ(aCJK, aString.Value(4));
  EXPECT_FALSE(aString.IsAscii());
}

TEST(TCollection_ExtendedStringTest, AsciiDetection)
{

  TCollection_ExtendedString anAsciiString("Simple ASCII");
  EXPECT_TRUE(anAsciiString.IsAscii());

  const char16_t             aNonAsciiStr[] = {0x0041, 0x20AC, 0};
  TCollection_ExtendedString aNonAsciiString(aNonAsciiStr);
  EXPECT_FALSE(aNonAsciiString.IsAscii());
}

TEST(TCollection_ExtendedStringTest, EmptyStringHandling)
{

  TCollection_ExtendedString anEmptyString;
  EXPECT_EQ(0, anEmptyString.Length());
  EXPECT_TRUE(anEmptyString.IsEmpty());
  EXPECT_EQ(0, anEmptyString.LengthOfCString());

  Standard_PCharacter aBuffer = new char[1];
  int                 aLength = anEmptyString.ToUTF8CString(aBuffer);
  EXPECT_EQ(0, aLength);
  EXPECT_EQ('\0', aBuffer[0]);

  delete[] aBuffer;
}

TEST(TCollection_ExtendedStringTest, ConversionRoundTrip)
{

  const char* anOriginalStr = "Test conversion with special chars: !@#$%";

  TCollection_AsciiString    anAsciiOriginal(anOriginalStr);
  TCollection_ExtendedString anExtendedConverted(anAsciiOriginal);
  TCollection_AsciiString    anAsciiRoundTrip(anExtendedConverted);

  EXPECT_STREQ(anOriginalStr, anAsciiRoundTrip.ToCString());
  EXPECT_EQ(anAsciiOriginal.Length(), anExtendedConverted.Length());
  EXPECT_EQ(anAsciiOriginal.Length(), anAsciiRoundTrip.Length());
}

TEST(TCollection_ExtendedStringTest, LargeStrings)
{

  const int                  aLargeSize = 1000;
  TCollection_ExtendedString aLargeString(aLargeSize, 'A');

  EXPECT_EQ(aLargeSize, aLargeString.Length());
  EXPECT_EQ('A', aLargeString.Value(1));
  EXPECT_EQ('A', aLargeString.Value(aLargeSize));
  EXPECT_TRUE(aLargeString.IsAscii());
}

TEST(TCollection_ExtendedStringTest, MemoryAllocation)
{

  for (int anIdx = 1; anIdx <= 16; ++anIdx)
  {
    TCollection_ExtendedString aTestString(anIdx, 'X');
    EXPECT_EQ(anIdx, aTestString.Length());
    EXPECT_EQ('X', aTestString.Value(1));

    if (anIdx > 1)
    {
      EXPECT_EQ('X', aTestString.Value(anIdx));
    }
  }
}

TEST(TCollection_ExtendedStringTest, MultiByteCString)
{

  const char*                aMultiByteStr = "Multi-byte test";
  TCollection_ExtendedString aString(aMultiByteStr, true);

  EXPECT_GT(aString.Length(), 0);
  EXPECT_FALSE(aString.IsEmpty());
}

TEST(TCollection_ExtendedStringTest, BoundaryValues)
{

  const char16_t aLastStandardAscii = 0x007F;
  const char16_t aLastOCCTAscii     = 0x00FF;
  const char16_t aFirstExtended     = 0x0100;
  const char16_t aMaxBMP            = 0xFFFF;

  TCollection_ExtendedString aStringLastStandardAscii(aLastStandardAscii);
  EXPECT_EQ(1, aStringLastStandardAscii.Length());
  EXPECT_TRUE(aStringLastStandardAscii.IsAscii());

  TCollection_ExtendedString aStringLastOCCTAscii(aLastOCCTAscii);
  EXPECT_EQ(1, aStringLastOCCTAscii.Length());
  EXPECT_TRUE(aStringLastOCCTAscii.IsAscii());

  TCollection_ExtendedString aStringFirstExtended(aFirstExtended);
  EXPECT_EQ(1, aStringFirstExtended.Length());
  EXPECT_FALSE(aStringFirstExtended.IsAscii());

  TCollection_ExtendedString aStringMaxBMP(aMaxBMP);
  EXPECT_EQ(1, aStringMaxBMP.Length());
  EXPECT_FALSE(aStringMaxBMP.IsAscii());
}

TEST(TCollection_ExtendedStringTest, TestMem_LargeStringAllocation)
{

  const int                  aLargeSize = 1024 * 1024;
  TCollection_ExtendedString aString(aLargeSize, 'A');

  EXPECT_EQ(aLargeSize, aString.Length());
  EXPECT_FALSE(aString.IsEmpty());
}

TEST(TCollection_ExtendedStringTest, OCC3277_CatOperation)
{

  TCollection_ExtendedString anExtendedString;
  TCollection_ExtendedString anInputString("TestString");

  TCollection_ExtendedString aResult = anExtendedString.Cat(anInputString);

  EXPECT_EQ(anInputString.Length(), aResult.Length())
    << "Concatenated string should have same length as input";
  EXPECT_FALSE(aResult.IsEmpty()) << "Concatenated string should not be empty";

  EXPECT_EQ(anInputString, aResult) << "Concatenated string should match input string";
}

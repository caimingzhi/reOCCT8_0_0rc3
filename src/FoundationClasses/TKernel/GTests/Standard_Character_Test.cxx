

#include <Standard_Character.hpp>

#include <gtest/gtest.h>

TEST(Standard_Character_Test, OCC29925_CharacterClassificationFunctions)
{

  for (int i = 0; i < 256; i++)
  {
    char c = (char)(unsigned char)i;

    EXPECT_NO_THROW(IsAlphabetic(c));
    EXPECT_NO_THROW(IsDigit(c));
    EXPECT_NO_THROW(IsXDigit(c));
    EXPECT_NO_THROW(IsAlphanumeric(c));
    EXPECT_NO_THROW(IsControl(c));
    EXPECT_NO_THROW(IsGraphic(c));
    EXPECT_NO_THROW(IsLowerCase(c));
    EXPECT_NO_THROW(IsPrintable(c));
    EXPECT_NO_THROW(IsPunctuation(c));
    EXPECT_NO_THROW(IsSpace(c));
    EXPECT_NO_THROW(IsUpperCase(c));
    EXPECT_NO_THROW(LowerCase(c));
    EXPECT_NO_THROW(UpperCase(c));
  }

  EXPECT_TRUE(IsAlphabetic('A'));
  EXPECT_TRUE(IsAlphabetic('z'));
  EXPECT_FALSE(IsAlphabetic('5'));

  EXPECT_TRUE(IsDigit('0'));
  EXPECT_TRUE(IsDigit('9'));
  EXPECT_FALSE(IsDigit('A'));

  EXPECT_TRUE(IsSpace(' '));
  EXPECT_TRUE(IsSpace('\t'));
  EXPECT_FALSE(IsSpace('A'));

  EXPECT_TRUE(IsLowerCase('a'));
  EXPECT_FALSE(IsLowerCase('A'));

  EXPECT_TRUE(IsUpperCase('A'));
  EXPECT_FALSE(IsUpperCase('a'));

  EXPECT_EQ('a', LowerCase('A'));
  EXPECT_EQ('A', UpperCase('a'));
}

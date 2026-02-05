#pragma once

//! Enumeration defining Unicode subsets.
enum Font_UnicodeSubset
{
  Font_UnicodeSubset_Western, //!< western letters
  Font_UnicodeSubset_Korean,  //!< modern Korean letters
  Font_UnicodeSubset_CJK,     //!< Chinese characters (Chinese, Japanese, Korean and Vietnam)
  Font_UnicodeSubset_Arabic,  //!< Arabic  characters
};

enum
{
  Font_UnicodeSubset_NB = Font_UnicodeSubset_Arabic
};

#pragma once

enum BinTools_FormatVersion
{
  BinTools_FormatVersion_VERSION_1 = 1,

  BinTools_FormatVersion_VERSION_2 = 2,

  BinTools_FormatVersion_VERSION_3 = 3,

  BinTools_FormatVersion_VERSION_4 = 4,

  BinTools_FormatVersion_CURRENT = BinTools_FormatVersion_VERSION_4
};

enum
{
  BinTools_FormatVersion_LOWER = BinTools_FormatVersion_VERSION_1,
  BinTools_FormatVersion_UPPER = BinTools_FormatVersion_VERSION_4
};

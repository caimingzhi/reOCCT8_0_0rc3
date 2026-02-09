#pragma once

enum TopTools_FormatVersion
{
  TopTools_FormatVersion_VERSION_1 = 1,

  TopTools_FormatVersion_VERSION_2 = 2,

  TopTools_FormatVersion_VERSION_3 = 3,

  TopTools_FormatVersion_CURRENT = TopTools_FormatVersion_VERSION_3
};

enum
{
  TopTools_FormatVersion_LOWER = TopTools_FormatVersion_VERSION_1,
  TopTools_FormatVersion_UPPER = TopTools_FormatVersion_VERSION_3
};

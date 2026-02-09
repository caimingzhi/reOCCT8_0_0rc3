#pragma once

enum TDocStd_FormatVersion
{
  TDocStd_FormatVersion_VERSION_2 = 2,

  TDocStd_FormatVersion_VERSION_3,

  TDocStd_FormatVersion_VERSION_4,

  TDocStd_FormatVersion_VERSION_5,

  TDocStd_FormatVersion_VERSION_6,

  TDocStd_FormatVersion_VERSION_7,

  TDocStd_FormatVersion_VERSION_8,

  TDocStd_FormatVersion_VERSION_9,

  TDocStd_FormatVersion_VERSION_10,

  TDocStd_FormatVersion_VERSION_11,

  TDocStd_FormatVersion_VERSION_12,

  TDocStd_FormatVersion_CURRENT = TDocStd_FormatVersion_VERSION_12
};

enum
{
  TDocStd_FormatVersion_LOWER = TDocStd_FormatVersion_VERSION_2,
  TDocStd_FormatVersion_UPPER = TDocStd_FormatVersion_VERSION_12
};

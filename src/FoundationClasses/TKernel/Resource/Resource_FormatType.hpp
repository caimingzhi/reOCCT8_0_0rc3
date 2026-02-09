#pragma once

enum Resource_FormatType
{
  Resource_FormatType_SJIS,
  Resource_FormatType_EUC,

  Resource_FormatType_NoConversion,
  Resource_FormatType_GB,
  Resource_FormatType_UTF8,
  Resource_FormatType_SystemLocale,

  Resource_FormatType_CP1250,
  Resource_FormatType_CP1251,
  Resource_FormatType_CP1252,
  Resource_FormatType_CP1253,
  Resource_FormatType_CP1254,
  Resource_FormatType_CP1255,
  Resource_FormatType_CP1256,
  Resource_FormatType_CP1257,
  Resource_FormatType_CP1258,

  Resource_FormatType_iso8859_1,
  Resource_FormatType_iso8859_2,
  Resource_FormatType_iso8859_3,
  Resource_FormatType_iso8859_4,
  Resource_FormatType_iso8859_5,
  Resource_FormatType_iso8859_6,
  Resource_FormatType_iso8859_7,
  Resource_FormatType_iso8859_8,
  Resource_FormatType_iso8859_9,

  Resource_FormatType_CP850,
  Resource_FormatType_GBK,
  Resource_FormatType_Big5,

  Resource_FormatType_ANSI = Resource_FormatType_NoConversion,
  Resource_SJIS            = Resource_FormatType_SJIS,
  Resource_EUC             = Resource_FormatType_EUC,
  Resource_ANSI            = Resource_FormatType_ANSI,
  Resource_GB              = Resource_FormatType_GB,
};

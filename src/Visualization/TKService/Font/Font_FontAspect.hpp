#pragma once

//! Specifies aspect of system font.
enum Font_FontAspect
{
  Font_FontAspect_UNDEFINED = -1, //!< special value reserved for undefined aspect
  Font_FontAspect_Regular   = 0,  //!< normal (regular) aspect
  Font_FontAspect_Bold,           //!< bold aspect
  Font_FontAspect_Italic,         //!< italic aspect
  Font_FontAspect_BoldItalic,     //!< bold+italic aspect

  // old aliases
  Font_FA_Undefined  = Font_FontAspect_UNDEFINED,
  Font_FA_Regular    = Font_FontAspect_Regular,
  Font_FA_Bold       = Font_FontAspect_Bold,
  Font_FA_Italic     = Font_FontAspect_Italic,
  Font_FA_BoldItalic = Font_FontAspect_BoldItalic
};

enum
{
  Font_FontAspect_NB = Font_FontAspect_BoldItalic + 1
};

#pragma once


//! Enumeration defining font hinting options.
enum Font_Hinting
{
  // hinting style
  Font_Hinting_Off    = 0x00, //!< no      hinting (FT_LOAD_NO_HINTING)
  Font_Hinting_Normal = 0x01, //!< default hinting (FT_LOAD_TARGET_NORMAL)
  Font_Hinting_Light  = 0x02, //!< light   hinting (FT_LOAD_TARGET_LIGHT)
  // native/autohinting flags
  Font_Hinting_ForceAutohint =
    0x10, //!< prefer autohinting over native hinting (FT_LOAD_FORCE_AUTOHINT)
  Font_Hinting_NoAutohint = 0x20, //!< disallow autohinting (FT_LOAD_NO_AUTOHINT)
};


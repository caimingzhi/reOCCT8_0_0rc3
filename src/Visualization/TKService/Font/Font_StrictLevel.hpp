#pragma once

//! Enumeration defining font search restrictions.
enum Font_StrictLevel
{
  Font_StrictLevel_Strict,  //!< search only for exact font
  Font_StrictLevel_Aliases, //!< search for exact font match and for aliases (ignore global
                            //!< fallback)
  Font_StrictLevel_Any,     //!< search for any font, including global fallback
};

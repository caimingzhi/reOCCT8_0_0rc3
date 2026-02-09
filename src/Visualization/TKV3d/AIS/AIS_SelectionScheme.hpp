#pragma once

enum AIS_SelectionScheme
{
  AIS_SelectionScheme_UNKNOWN = -1,
  AIS_SelectionScheme_Replace = 0,
  AIS_SelectionScheme_Add,
  AIS_SelectionScheme_Remove,
  AIS_SelectionScheme_XOR,
  AIS_SelectionScheme_Clear,
  AIS_SelectionScheme_ReplaceExtra,
};

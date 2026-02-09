#pragma once

enum PrsMgr_DisplayStatus
{
  PrsMgr_DisplayStatus_Displayed,
  PrsMgr_DisplayStatus_Erased,
  PrsMgr_DisplayStatus_None,

  AIS_DS_Displayed = PrsMgr_DisplayStatus_Displayed,
  AIS_DS_Erased    = PrsMgr_DisplayStatus_Erased,
  AIS_DS_None      = PrsMgr_DisplayStatus_None
};

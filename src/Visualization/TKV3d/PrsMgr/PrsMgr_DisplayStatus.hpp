#pragma once

//! To give the display status of an Interactive Object.
enum PrsMgr_DisplayStatus
{
  PrsMgr_DisplayStatus_Displayed, //!< the Interactive Object is displayed in the main viewer
  PrsMgr_DisplayStatus_Erased,    //!< the Interactive Object is hidden in main viewer
  PrsMgr_DisplayStatus_None,      //!< the Interactive Object is nowhere displayed
  // old aliases
  AIS_DS_Displayed = PrsMgr_DisplayStatus_Displayed,
  AIS_DS_Erased    = PrsMgr_DisplayStatus_Erased,
  AIS_DS_None      = PrsMgr_DisplayStatus_None
};

#pragma once


//! Classifies checks
//! OK     : check is empty
//! Warning: Warning, no Fail
//! Fail   : Fail
//! Others to query:
//! Any    : any status
//! Message: Warning/Fail
//! NoFail : Warning/OK
enum Interface_CheckStatus
{
  Interface_CheckOK,
  Interface_CheckWarning,
  Interface_CheckFail,
  Interface_CheckAny,
  Interface_CheckMessage,
  Interface_CheckNoFail
};


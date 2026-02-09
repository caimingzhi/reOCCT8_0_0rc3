#pragma once

enum PCDM_StoreStatus
{
  PCDM_SS_OK,
  PCDM_SS_DriverFailure,
  PCDM_SS_WriteFailure,
  PCDM_SS_Failure,
  PCDM_SS_Doc_IsNull,
  PCDM_SS_No_Obj,
  PCDM_SS_Info_Section_Error,
  PCDM_SS_UserBreak,
  PCDM_SS_UnrecognizedFormat
};

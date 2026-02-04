#pragma once


//! Status of storage of a document on disk.
//! If it is PCDM_SS_OK, the document is successfully saved on disk.
//! Else - there is an error.
enum PCDM_StoreStatus
{
  PCDM_SS_OK,                 //!< Document is saved successfully
  PCDM_SS_DriverFailure,      //!< Storage driver is not found
  PCDM_SS_WriteFailure,       //!< Attempt to write a file on disk failed
  PCDM_SS_Failure,            //!< A general error occurred (unexpected)
  PCDM_SS_Doc_IsNull,         //!< Attempt to save a null document
  PCDM_SS_No_Obj,             //!< Document has no objects to be saved
  PCDM_SS_Info_Section_Error, //!< Error occurred on writing of an information-section
  PCDM_SS_UserBreak,          //!< User interrupted the process of storage of the document on disk
  PCDM_SS_UnrecognizedFormat  //!< No storage driver exist for this document format
};


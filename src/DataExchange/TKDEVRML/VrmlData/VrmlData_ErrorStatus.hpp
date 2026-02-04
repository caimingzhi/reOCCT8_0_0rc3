#pragma once


/**
 * Status of read/write or other operation.
 */
enum VrmlData_ErrorStatus
{
  VrmlData_StatusOK = 0,
  VrmlData_EmptyData,
  VrmlData_UnrecoverableError,
  VrmlData_GeneralError,
  VrmlData_EndOfFile,
  VrmlData_NotVrmlFile,
  VrmlData_CannotOpenFile,
  VrmlData_VrmlFormatError,
  VrmlData_NumericInputError,
  VrmlData_IrrelevantNumber,
  VrmlData_BooleanInputError,
  VrmlData_StringInputError,
  VrmlData_NodeNameUnknown,
  VrmlData_NonPositiveSize,
  VrmlData_ReadUnknownNode,
  VrmlData_NonSupportedFeature,
  VrmlData_OutputStreamUndefined,
  VrmlData_NotImplemented
};


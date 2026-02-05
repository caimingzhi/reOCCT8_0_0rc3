#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepToTopoDS_BuilderError.hpp>
#include <StepToTopoDS_TranslateShellError.hpp>
#include <StepToTopoDS_TranslateFaceError.hpp>
#include <StepToTopoDS_TranslateEdgeError.hpp>
#include <StepToTopoDS_TranslateVertexError.hpp>
#include <StepToTopoDS_TranslateVertexLoopError.hpp>
#include <StepToTopoDS_TranslatePolyLoopError.hpp>
#include <Standard_CString.hpp>

enum StepToTopoDS_GeometricToolError
{
  StepToTopoDS_GeometricToolDone,
  StepToTopoDS_GeometricToolIsDegenerated,
  StepToTopoDS_GeometricToolHasNoPCurve,
  StepToTopoDS_GeometricToolWrong3dParameters,
  StepToTopoDS_GeometricToolNoProjectiOnCurve,
  StepToTopoDS_GeometricToolOther
};

class TCollection_HAsciiString;

//! This package implements the mapping between AP214
//! Shape representation and CAS.CAD Shape Representation.
//! The source schema is Part42 (which is included in AP214)
class StepToTopoDS
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static occ::handle<TCollection_HAsciiString> DecodeBuilderError(
    const StepToTopoDS_BuilderError Error);

  Standard_EXPORT static occ::handle<TCollection_HAsciiString> DecodeShellError(
    const StepToTopoDS_TranslateShellError Error);

  Standard_EXPORT static occ::handle<TCollection_HAsciiString> DecodeFaceError(
    const StepToTopoDS_TranslateFaceError Error);

  Standard_EXPORT static occ::handle<TCollection_HAsciiString> DecodeEdgeError(
    const StepToTopoDS_TranslateEdgeError Error);

  Standard_EXPORT static occ::handle<TCollection_HAsciiString> DecodeVertexError(
    const StepToTopoDS_TranslateVertexError Error);

  Standard_EXPORT static occ::handle<TCollection_HAsciiString> DecodeVertexLoopError(
    const StepToTopoDS_TranslateVertexLoopError Error);

  Standard_EXPORT static occ::handle<TCollection_HAsciiString> DecodePolyLoopError(
    const StepToTopoDS_TranslatePolyLoopError Error);

  Standard_EXPORT static const char* DecodeGeometricToolError(
    const StepToTopoDS_GeometricToolError Error);
};

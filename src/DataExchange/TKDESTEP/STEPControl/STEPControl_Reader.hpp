#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <XSControl_Reader.hpp>
#include <Standard_Integer.hpp>
#include <DESTEP_Parameters.hpp>
#include <TCollection_AsciiString.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_Array1.hpp>
class XSControl_WorkSession;
class StepData_StepModel;
class StepRepr_RepresentationContext;

class STEPControl_Reader : public XSControl_Reader
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT STEPControl_Reader();

  Standard_EXPORT STEPControl_Reader(const occ::handle<XSControl_WorkSession>& WS,
                                     const bool                                scratch = true);

  Standard_EXPORT occ::handle<StepData_StepModel> StepModel() const;

  Standard_EXPORT IFSelect_ReturnStatus ReadFile(const char* filename) override;

  Standard_EXPORT IFSelect_ReturnStatus ReadStream(const char*   theName,
                                                   std::istream& theIStream) override;

  Standard_EXPORT IFSelect_ReturnStatus ReadFile(const char*              filename,
                                                 const DESTEP_Parameters& theParams);

  Standard_EXPORT IFSelect_ReturnStatus ReadStream(const char*              theName,
                                                   const DESTEP_Parameters& theParams,
                                                   std::istream&            theIStream);

  Standard_EXPORT bool TransferRoot(
    const int                    num         = 1,
    const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT int NbRootsForTransfer() override;

  Standard_EXPORT void FileUnits(
    NCollection_Sequence<TCollection_AsciiString>& theUnitLengthNames,
    NCollection_Sequence<TCollection_AsciiString>& theUnitAngleNames,
    NCollection_Sequence<TCollection_AsciiString>& theUnitSolidAngleNames);

  Standard_EXPORT void SetSystemLengthUnit(const double theLengthUnit);

  Standard_EXPORT double SystemLengthUnit() const;

protected:
  Standard_EXPORT DE_ShapeFixParameters GetDefaultShapeFixParameters() const override;

  Standard_EXPORT ShapeProcess::OperationsFlags GetDefaultShapeProcessFlags() const override;

private:
  Standard_EXPORT bool findUnits(const occ::handle<StepRepr_RepresentationContext>& theReprContext,
                                 NCollection_Array1<TCollection_AsciiString>&       theNameUnits,
                                 NCollection_Array1<double>&                        theFactorUnits);
};

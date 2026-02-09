#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Transient.hpp>
#include <NCollection_Sequence.hpp>
#include <STEPConstruct_Tool.hpp>
#include <Standard_Integer.hpp>
#include <Standard_CString.hpp>
class StepBasic_ProductRelatedProductCategory;
class StepBasic_DocumentType;
class StepBasic_ProductDefinitionContext;
class StepBasic_ProductContext;
class StepBasic_ApplicationProtocolDefinition;
class XSControl_WorkSession;
class StepBasic_ProductDefinition;
class TCollection_HAsciiString;
class StepAP214_AppliedDocumentReference;
class StepBasic_DocumentFile;

class STEPConstruct_ExternRefs : public STEPConstruct_Tool
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT STEPConstruct_ExternRefs();

  Standard_EXPORT STEPConstruct_ExternRefs(const occ::handle<XSControl_WorkSession>& WS);

  Standard_EXPORT bool Init(const occ::handle<XSControl_WorkSession>& WS);

  Standard_EXPORT void Clear();

  Standard_EXPORT bool LoadExternRefs();

  Standard_EXPORT int NbExternRefs() const;

  Standard_EXPORT const char* FileName(const int num) const;

  Standard_EXPORT occ::handle<StepBasic_ProductDefinition> ProdDef(const int num) const;

  Standard_EXPORT occ::handle<StepBasic_DocumentFile> DocFile(const int num) const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Format(const int num) const;

  Standard_EXPORT int AddExternRef(const char*                                     filename,
                                   const occ::handle<StepBasic_ProductDefinition>& PD,
                                   const char*                                     format);

  Standard_EXPORT void checkAP214Shared();

  Standard_EXPORT int WriteExternRefs(const int num) const;

  Standard_EXPORT void SetAP214APD(const occ::handle<StepBasic_ApplicationProtocolDefinition>& APD);

  Standard_EXPORT occ::handle<StepBasic_ApplicationProtocolDefinition> GetAP214APD();

protected:
  Standard_EXPORT bool addAP214ExterRef(const occ::handle<StepAP214_AppliedDocumentReference>& ADR,
                                        const occ::handle<StepBasic_ProductDefinition>&        PD,
                                        const occ::handle<StepBasic_DocumentFile>&             DF,
                                        const char* filename);

private:
  NCollection_Sequence<occ::handle<Standard_Transient>> myAEIAs;
  NCollection_Sequence<occ::handle<Standard_Transient>> myRoles;
  NCollection_Sequence<occ::handle<Standard_Transient>> myFormats;
  NCollection_Sequence<occ::handle<Standard_Transient>> myShapes;
  NCollection_Sequence<occ::handle<Standard_Transient>> myTypes;
  NCollection_Sequence<int>                             myIsAP214;
  NCollection_Sequence<int>                             myReplaceNum;
  NCollection_Sequence<occ::handle<Standard_Transient>> myDocFiles;
  occ::handle<StepBasic_ProductRelatedProductCategory>  mySharedPRPC;
  occ::handle<StepBasic_DocumentType>                   mySharedDocType;
  occ::handle<StepBasic_ProductDefinitionContext>       mySharedPDC;
  occ::handle<StepBasic_ProductContext>                 mySharedPC;
  occ::handle<StepBasic_ApplicationProtocolDefinition>  myAPD;
};

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

//! Provides a tool for analyzing (reading) and creating (writing)
//! references to external files in STEP
//!
//! It maintains a data structure in the form of sequences
//! of relevant STEP entities (roots), allowing either to create
//! them by convenient API, or load from existing model and
//! investigate
class STEPConstruct_ExternRefs : public STEPConstruct_Tool
{
public:
  DEFINE_STANDARD_ALLOC

  //! Creates an empty tool
  Standard_EXPORT STEPConstruct_ExternRefs();

  //! Creates a tool and initializes it
  Standard_EXPORT STEPConstruct_ExternRefs(const occ::handle<XSControl_WorkSession>& WS);

  //! Initializes tool; returns True if succeeded
  Standard_EXPORT bool Init(const occ::handle<XSControl_WorkSession>& WS);

  //! Clears internal fields (list of defined extern refs)
  Standard_EXPORT void Clear();

  //! Searches current STEP model for external references
  //! and loads them to the internal data structures
  //! NOTE: does not clear data structures before loading
  Standard_EXPORT bool LoadExternRefs();

  //! Returns number of defined extern references
  Standard_EXPORT int NbExternRefs() const;

  //! Returns filename for numth extern reference
  //! Returns Null if FileName is not defined or bad
  Standard_EXPORT const char* FileName(const int num) const;

  //! Returns ProductDefinition to which numth extern reference
  //! is associated.
  //! Returns Null if cannot be detected or if extern reference
  //! is not associated to SDR in a proper way.
  Standard_EXPORT occ::handle<StepBasic_ProductDefinition> ProdDef(const int num) const;

  //! Returns DocumentFile to which numth extern reference
  //! is associated.
  //! Returns Null if cannot be detected.
  Standard_EXPORT occ::handle<StepBasic_DocumentFile> DocFile(const int num) const;

  //! Returns format identification string for the extern document
  //! Returns Null handle if format is not defined
  Standard_EXPORT occ::handle<TCollection_HAsciiString> Format(const int num) const;

  //! Create a new external reference with specified attributes
  //! attached to a given SDR
  //! <format> can be Null string, in that case this information
  //! is not written. Else, it can be "STEP AP214" or "STEP AP203"
  //! Returns index of a new extern ref
  Standard_EXPORT int AddExternRef(const char*                                     filename,
                                   const occ::handle<StepBasic_ProductDefinition>& PD,
                                   const char*                                     format);

  //! Check (create if it is null) all shared entities for the model
  Standard_EXPORT void checkAP214Shared();

  //! Adds all the currently defined external refs to the model
  //! Returns number of written extern refs
  Standard_EXPORT int WriteExternRefs(const int num) const;

  //! Set the ApplicationProtocolDefinition of the PDM schema
  Standard_EXPORT void SetAP214APD(const occ::handle<StepBasic_ApplicationProtocolDefinition>& APD);

  //! Returns the ApplicationProtocolDefinition of the PDM schema
  //! NOTE: if not defined then create new APD with new Application Context
  Standard_EXPORT occ::handle<StepBasic_ApplicationProtocolDefinition> GetAP214APD();

protected:
  //! Create a new additional structure entities and add necessary references
  //! Note: do not refer from ADR to DF directly in AP214 (TRJ11).
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


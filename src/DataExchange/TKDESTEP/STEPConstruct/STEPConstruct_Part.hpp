#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class StepShape_ShapeDefinitionRepresentation;
class StepBasic_ProductRelatedProductCategory;
class StepShape_ShapeRepresentation;
class TCollection_HAsciiString;
class StepBasic_ApplicationContext;
class StepBasic_ProductContext;
class StepBasic_ProductDefinitionContext;
class StepBasic_Product;
class StepBasic_ProductDefinitionFormation;
class StepBasic_ProductDefinition;
class StepData_StepModel;
class StepRepr_ProductDefinitionShape;

class STEPConstruct_Part
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT STEPConstruct_Part();

  Standard_EXPORT void MakeSDR(const occ::handle<StepShape_ShapeRepresentation>& aShape,
                               const occ::handle<TCollection_HAsciiString>&      aName,
                               const occ::handle<StepBasic_ApplicationContext>&  AC,
                               occ::handle<StepData_StepModel>&                  theStepModel);

  Standard_EXPORT void ReadSDR(const occ::handle<StepShape_ShapeDefinitionRepresentation>& aShape);

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT occ::handle<StepShape_ShapeDefinitionRepresentation> SDRValue() const;

  Standard_EXPORT occ::handle<StepShape_ShapeRepresentation> SRValue() const;

  Standard_EXPORT occ::handle<StepBasic_ProductContext> PC() const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> PCname() const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> PCdisciplineType() const;

  Standard_EXPORT void SetPCname(const occ::handle<TCollection_HAsciiString>& name);

  Standard_EXPORT void SetPCdisciplineType(const occ::handle<TCollection_HAsciiString>& label);

  Standard_EXPORT occ::handle<StepBasic_ApplicationContext> AC() const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> ACapplication() const;

  Standard_EXPORT void SetACapplication(const occ::handle<TCollection_HAsciiString>& text);

  Standard_EXPORT occ::handle<StepBasic_ProductDefinitionContext> PDC() const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> PDCname() const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> PDCstage() const;

  Standard_EXPORT void SetPDCname(const occ::handle<TCollection_HAsciiString>& label);

  Standard_EXPORT void SetPDCstage(const occ::handle<TCollection_HAsciiString>& label);

  Standard_EXPORT occ::handle<StepBasic_Product> Product() const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Pid() const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Pname() const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Pdescription() const;

  Standard_EXPORT void SetPid(const occ::handle<TCollection_HAsciiString>& id);

  Standard_EXPORT void SetPname(const occ::handle<TCollection_HAsciiString>& label);

  Standard_EXPORT void SetPdescription(const occ::handle<TCollection_HAsciiString>& text);

  Standard_EXPORT occ::handle<StepBasic_ProductDefinitionFormation> PDF() const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> PDFid() const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> PDFdescription() const;

  Standard_EXPORT void SetPDFid(const occ::handle<TCollection_HAsciiString>& id);

  Standard_EXPORT void SetPDFdescription(const occ::handle<TCollection_HAsciiString>& text);

  Standard_EXPORT occ::handle<StepBasic_ProductDefinition> PD() const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> PDdescription() const;

  Standard_EXPORT void SetPDdescription(const occ::handle<TCollection_HAsciiString>& text);

  Standard_EXPORT occ::handle<StepRepr_ProductDefinitionShape> PDS() const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> PDSname() const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> PDSdescription() const;

  Standard_EXPORT void SetPDSname(const occ::handle<TCollection_HAsciiString>& label);

  Standard_EXPORT void SetPDSdescription(const occ::handle<TCollection_HAsciiString>& text);

  Standard_EXPORT occ::handle<StepBasic_ProductRelatedProductCategory> PRPC() const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> PRPCname() const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> PRPCdescription() const;

  Standard_EXPORT void SetPRPCname(const occ::handle<TCollection_HAsciiString>& label);

  Standard_EXPORT void SetPRPCdescription(const occ::handle<TCollection_HAsciiString>& text);

private:
  bool                                                 myDone;
  occ::handle<StepShape_ShapeDefinitionRepresentation> mySDR;
  occ::handle<StepBasic_ProductRelatedProductCategory> myPRPC;
};

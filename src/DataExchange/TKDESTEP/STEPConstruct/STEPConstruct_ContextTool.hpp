#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <NCollection_Sequence.hpp>
#include <STEPConstruct_AP203Context.hpp>
#include <StepData_Factors.hpp>
#include <StepData_StepModel.hpp>
#include <Standard_Transient.hpp>
#include <NCollection_HSequence.hpp>
class StepBasic_ApplicationProtocolDefinition;
class StepGeom_Axis2Placement3d;
class TCollection_HAsciiString;
class STEPConstruct_Part;
class STEPConstruct_Assembly;

class STEPConstruct_ContextTool
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT STEPConstruct_ContextTool();

  Standard_EXPORT STEPConstruct_ContextTool(const occ::handle<StepData_StepModel>& aStepModel);

  Standard_EXPORT void SetModel(const occ::handle<StepData_StepModel>& aStepModel);

  Standard_EXPORT void SetGlobalFactor(const StepData_Factors& theGlobalFactor);

  Standard_EXPORT occ::handle<StepBasic_ApplicationProtocolDefinition> GetAPD();

  Standard_EXPORT void AddAPD(const bool enforce = false);

  Standard_EXPORT bool IsAP203() const;

  Standard_EXPORT bool IsAP214() const;

  Standard_EXPORT bool IsAP242() const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> GetACstatus();

  Standard_EXPORT occ::handle<TCollection_HAsciiString> GetACschemaName();

  Standard_EXPORT int GetACyear();

  Standard_EXPORT occ::handle<TCollection_HAsciiString> GetACname();

  Standard_EXPORT void SetACstatus(const occ::handle<TCollection_HAsciiString>& status);

  Standard_EXPORT void SetACschemaName(const occ::handle<TCollection_HAsciiString>& schemaName);

  Standard_EXPORT void SetACyear(const int year);

  Standard_EXPORT void SetACname(const occ::handle<TCollection_HAsciiString>& name);

  Standard_EXPORT occ::handle<StepGeom_Axis2Placement3d> GetDefaultAxis();

  Standard_EXPORT STEPConstruct_AP203Context& AP203Context();

  Standard_EXPORT int Level() const;

  Standard_EXPORT void NextLevel();

  Standard_EXPORT void PrevLevel();

  Standard_EXPORT void SetLevel(const int lev);

  Standard_EXPORT int Index() const;

  Standard_EXPORT void NextIndex();

  Standard_EXPORT void PrevIndex();

  Standard_EXPORT void SetIndex(const int ind);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> GetProductName() const;

  Standard_EXPORT occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>>
                  GetRootsForPart(const STEPConstruct_Part& SDRTool);

  Standard_EXPORT occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>>
                  GetRootsForAssemblyLink(const STEPConstruct_Assembly& assembly);

private:
  NCollection_Sequence<int>                            myLevel;
  occ::handle<StepBasic_ApplicationProtocolDefinition> theAPD;
  STEPConstruct_AP203Context                           theAP203;
  occ::handle<StepGeom_Axis2Placement3d>               myAxis;
  StepData_Factors                                     myGlobalFactor;
  DESTEP_Parameters::WriteMode_StepSchema              mySchema;
  TCollection_AsciiString                              myProductName;
};

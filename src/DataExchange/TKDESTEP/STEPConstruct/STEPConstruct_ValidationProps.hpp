#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepBasic_Unit.hpp>
#include <STEPConstruct_Tool.hpp>
#include <Standard_CString.hpp>
#include <Standard_Transient.hpp>
#include <NCollection_Sequence.hpp>
class StepBasic_ProductDefinition;
class XSControl_WorkSession;
class TopoDS_Shape;
class StepRepr_RepresentationItem;
class StepRepr_CharacterizedDefinition;
class StepRepr_RepresentationContext;
class gp_Pnt;
class StepRepr_NextAssemblyUsageOccurrence;
class StepRepr_PropertyDefinition;

class STEPConstruct_ValidationProps : public STEPConstruct_Tool
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT STEPConstruct_ValidationProps();

  Standard_EXPORT STEPConstruct_ValidationProps(const occ::handle<XSControl_WorkSession>& WS);

  Standard_EXPORT bool Init(const occ::handle<XSControl_WorkSession>& WS);

  Standard_EXPORT bool AddProp(const TopoDS_Shape&                             Shape,
                               const occ::handle<StepRepr_RepresentationItem>& Prop,
                               const char*                                     Descr,
                               const bool                                      instance = false);

  Standard_EXPORT bool AddProp(const StepRepr_CharacterizedDefinition&            target,
                               const occ::handle<StepRepr_RepresentationContext>& Context,
                               const occ::handle<StepRepr_RepresentationItem>&    Prop,
                               const char*                                        Descr);

  Standard_EXPORT bool AddArea(const TopoDS_Shape& Shape, const double Area);

  Standard_EXPORT bool AddVolume(const TopoDS_Shape& Shape, const double Vol);

  Standard_EXPORT bool AddCentroid(const TopoDS_Shape& Shape,
                                   const gp_Pnt&       Pnt,
                                   const bool          instance = false);

  Standard_EXPORT bool FindTarget(const TopoDS_Shape&                          S,
                                  StepRepr_CharacterizedDefinition&            target,
                                  occ::handle<StepRepr_RepresentationContext>& Context,
                                  const bool                                   instance = false);

  Standard_EXPORT bool LoadProps(NCollection_Sequence<occ::handle<Standard_Transient>>& seq) const;

  Standard_EXPORT occ::handle<StepRepr_NextAssemblyUsageOccurrence> GetPropNAUO(
    const occ::handle<StepRepr_PropertyDefinition>& PD) const;

  Standard_EXPORT occ::handle<StepBasic_ProductDefinition> GetPropPD(
    const occ::handle<StepRepr_PropertyDefinition>& PD) const;

  Standard_EXPORT TopoDS_Shape
    GetPropShape(const occ::handle<StepBasic_ProductDefinition>& ProdDef) const;

  Standard_EXPORT TopoDS_Shape
    GetPropShape(const occ::handle<StepRepr_PropertyDefinition>& PD) const;

  Standard_EXPORT bool GetPropReal(
    const occ::handle<StepRepr_RepresentationItem>& item,
    double&                                         Val,
    bool&                                           isArea,
    const StepData_Factors&                         theLocalFactors = StepData_Factors()) const;

  Standard_EXPORT bool GetPropPnt(
    const occ::handle<StepRepr_RepresentationItem>&    item,
    const occ::handle<StepRepr_RepresentationContext>& Context,
    gp_Pnt&                                            Pnt,
    const StepData_Factors&                            theLocalFactors = StepData_Factors()) const;

  Standard_EXPORT void SetAssemblyShape(const TopoDS_Shape& shape);

private:
  StepBasic_Unit                           areaUnit;
  StepBasic_Unit                           volUnit;
  occ::handle<StepBasic_ProductDefinition> myAssemblyPD;
};

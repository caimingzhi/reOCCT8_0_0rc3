#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Transient.hpp>
#include <NCollection_Sequence.hpp>
#include <STEPConstruct_Tool.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_HSequence.hpp>
#include <STEPConstruct_RenderingProperties.hpp>
#include <TCollection_AsciiString.hpp>
#include <NCollection_DataMap.hpp>
#include <gp_Pnt.hpp>

class XSControl_WorkSession;
class StepVisual_StyledItem;
class StepRepr_RepresentationItem;
class StepVisual_PresentationStyleAssignment;
class TopoDS_Shape;
class StepRepr_RepresentationContext;
class StepVisual_MechanicalDesignGeometricPresentationRepresentation;
class StepData_StepModel;
class StepShape_ContextDependentShapeRepresentation;
class StepRepr_ProductDefinitionShape;
class StepVisual_Colour;
class Quantity_Color;

class STEPConstruct_Styles : public STEPConstruct_Tool
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT STEPConstruct_Styles();

  Standard_EXPORT STEPConstruct_Styles(const occ::handle<XSControl_WorkSession>& WS);

  Standard_EXPORT bool Init(const occ::handle<XSControl_WorkSession>& WS);

  Standard_EXPORT int NbStyles() const;

  Standard_EXPORT occ::handle<StepVisual_StyledItem> Style(const int i) const;

  Standard_EXPORT int NbRootStyles() const;

  Standard_EXPORT occ::handle<StepVisual_StyledItem> RootStyle(const int i) const;

  Standard_EXPORT void ClearStyles();

  Standard_EXPORT void AddStyle(const occ::handle<StepVisual_StyledItem>& style);

  Standard_EXPORT occ::handle<StepVisual_StyledItem> AddStyle(
    const occ::handle<StepRepr_RepresentationItem>&            item,
    const occ::handle<StepVisual_PresentationStyleAssignment>& PSA,
    const occ::handle<StepVisual_StyledItem>&                  Override);

  Standard_EXPORT occ::handle<StepVisual_StyledItem> AddStyle(
    const TopoDS_Shape&                                        Shape,
    const occ::handle<StepVisual_PresentationStyleAssignment>& PSA,
    const occ::handle<StepVisual_StyledItem>&                  Override);

  Standard_EXPORT bool CreateMDGPR(
    const occ::handle<StepRepr_RepresentationContext>&                           Context,
    occ::handle<StepVisual_MechanicalDesignGeometricPresentationRepresentation>& MDGPR,
    occ::handle<StepData_StepModel>&                                             theStepModel);

  Standard_EXPORT bool CreateNAUOSRD(
    const occ::handle<StepRepr_RepresentationContext>&                Context,
    const occ::handle<StepShape_ContextDependentShapeRepresentation>& CDSR,
    const occ::handle<StepRepr_ProductDefinitionShape>&               initPDS);

  Standard_EXPORT occ::handle<StepRepr_RepresentationContext> FindContext(
    const TopoDS_Shape& Shape) const;

  Standard_EXPORT bool LoadStyles();

  Standard_EXPORT bool LoadInvisStyles(
    occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>>& InvSyles) const;

  Standard_EXPORT occ::handle<StepVisual_PresentationStyleAssignment> MakeColorPSA(
    const occ::handle<StepRepr_RepresentationItem>& item,
    const occ::handle<StepVisual_Colour>&           SurfCol,
    const occ::handle<StepVisual_Colour>&           CurveCol,
    const STEPConstruct_RenderingProperties&        theRenderingProps,
    const bool                                      isForNAUO = false) const;

  Standard_EXPORT occ::handle<StepVisual_PresentationStyleAssignment> GetColorPSA(
    const occ::handle<StepRepr_RepresentationItem>& item,
    const occ::handle<StepVisual_Colour>&           Col);

  Standard_EXPORT bool GetColors(const occ::handle<StepVisual_StyledItem>& theStyle,
                                 occ::handle<StepVisual_Colour>&           theSurfaceColour,
                                 occ::handle<StepVisual_Colour>&           theBoundaryColour,
                                 occ::handle<StepVisual_Colour>&           theCurveColour,
                                 STEPConstruct_RenderingProperties&        theRenderingProps,
                                 bool&                                     theIsComponent) const;

  Standard_EXPORT static occ::handle<StepVisual_Colour> EncodeColor(const Quantity_Color& Col);

  Standard_EXPORT static occ::handle<StepVisual_Colour> EncodeColor(
    const Quantity_Color&                                                          Col,
    NCollection_DataMap<TCollection_AsciiString, occ::handle<Standard_Transient>>& DPDCs,
    NCollection_DataMap<gp_Pnt, occ::handle<Standard_Transient>>&                  ColRGBs);

  Standard_EXPORT static bool DecodeColor(const occ::handle<StepVisual_Colour>& Colour,
                                          Quantity_Color&                       Col);

private:
  NCollection_IndexedDataMap<occ::handle<Standard_Transient>, occ::handle<Standard_Transient>>
                                                          myMapOfStyles;
  NCollection_IndexedMap<occ::handle<Standard_Transient>> myStyles;
  NCollection_IndexedMap<occ::handle<Standard_Transient>> myRootStyles;
  NCollection_Sequence<occ::handle<Standard_Transient>>   myPSA;
};

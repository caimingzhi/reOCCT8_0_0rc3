#pragma once

#include <Standard.hpp>

#include <StepGeom_Axis2Placement.hpp>
#include <StepVisual_TextPath.hpp>
#include <StepVisual_FontSelect.hpp>
#include <StepGeom_GeometricRepresentationItem.hpp>
class TCollection_HAsciiString;

class StepVisual_TextLiteral : public StepGeom_GeometricRepresentationItem
{

public:
  //! Returns a TextLiteral
  Standard_EXPORT StepVisual_TextLiteral();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aName,
                            const occ::handle<TCollection_HAsciiString>& aLiteral,
                            const StepGeom_Axis2Placement&               aPlacement,
                            const occ::handle<TCollection_HAsciiString>& aAlignment,
                            const StepVisual_TextPath                    aPath,
                            const StepVisual_FontSelect&                 aFont);

  Standard_EXPORT void SetLiteral(const occ::handle<TCollection_HAsciiString>& aLiteral);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Literal() const;

  Standard_EXPORT void SetPlacement(const StepGeom_Axis2Placement& aPlacement);

  Standard_EXPORT StepGeom_Axis2Placement Placement() const;

  Standard_EXPORT void SetAlignment(const occ::handle<TCollection_HAsciiString>& aAlignment);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Alignment() const;

  Standard_EXPORT void SetPath(const StepVisual_TextPath aPath);

  Standard_EXPORT StepVisual_TextPath Path() const;

  Standard_EXPORT void SetFont(const StepVisual_FontSelect& aFont);

  Standard_EXPORT StepVisual_FontSelect Font() const;

  DEFINE_STANDARD_RTTIEXT(StepVisual_TextLiteral, StepGeom_GeometricRepresentationItem)

private:
  occ::handle<TCollection_HAsciiString> literal;
  StepGeom_Axis2Placement               placement;
  occ::handle<TCollection_HAsciiString> alignment;
  StepVisual_TextPath                   path;
  StepVisual_FontSelect                 font;
};

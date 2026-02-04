#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepRepr_Transformation.hpp>
#include <StepRepr_ShapeRepresentationRelationship.hpp>
class TCollection_HAsciiString;
class StepRepr_Representation;

class StepRepr_RepresentationRelationshipWithTransformation
    : public StepRepr_ShapeRepresentationRelationship
{

public:
  Standard_EXPORT StepRepr_RepresentationRelationshipWithTransformation();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aName,
                            const occ::handle<TCollection_HAsciiString>& aDescription,
                            const occ::handle<StepRepr_Representation>&  aRep1,
                            const occ::handle<StepRepr_Representation>&  aRep2,
                            const StepRepr_Transformation&               aTransf);

  Standard_EXPORT StepRepr_Transformation TransformationOperator() const;

  Standard_EXPORT void SetTransformationOperator(const StepRepr_Transformation& aTrans);

  DEFINE_STANDARD_RTTIEXT(StepRepr_RepresentationRelationshipWithTransformation,
                          StepRepr_ShapeRepresentationRelationship)

private:
  StepRepr_Transformation theTrans;
};


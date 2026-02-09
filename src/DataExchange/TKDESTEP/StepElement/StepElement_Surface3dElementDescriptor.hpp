#pragma once

#include <Standard.hpp>

#include <StepElement_SurfaceElementPurposeMember.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

enum StepElement_Element2dShape
{
  StepElement_Quadrilateral,
  StepElement_Triangle
};

#include <StepElement_ElementDescriptor.hpp>
#include <StepElement_ElementOrder.hpp>
class TCollection_HAsciiString;

class StepElement_Surface3dElementDescriptor : public StepElement_ElementDescriptor
{

public:
  Standard_EXPORT StepElement_Surface3dElementDescriptor();

  Standard_EXPORT void Init(
    const StepElement_ElementOrder               aElementDescriptor_TopologyOrder,
    const occ::handle<TCollection_HAsciiString>& aElementDescriptor_Description,
    const occ::handle<NCollection_HArray1<
      occ::handle<NCollection_HSequence<occ::handle<StepElement_SurfaceElementPurposeMember>>>>>&
                                     aPurpose,
    const StepElement_Element2dShape aShape);

  Standard_EXPORT occ::handle<NCollection_HArray1<
    occ::handle<NCollection_HSequence<occ::handle<StepElement_SurfaceElementPurposeMember>>>>>
                  Purpose() const;

  Standard_EXPORT void SetPurpose(
    const occ::handle<NCollection_HArray1<
      occ::handle<NCollection_HSequence<occ::handle<StepElement_SurfaceElementPurposeMember>>>>>&
      Purpose);

  Standard_EXPORT StepElement_Element2dShape Shape() const;

  Standard_EXPORT void SetShape(const StepElement_Element2dShape Shape);

  DEFINE_STANDARD_RTTIEXT(StepElement_Surface3dElementDescriptor, StepElement_ElementDescriptor)

private:
  occ::handle<NCollection_HArray1<
    occ::handle<NCollection_HSequence<occ::handle<StepElement_SurfaceElementPurposeMember>>>>>
                             thePurpose;
  StepElement_Element2dShape theShape;
};

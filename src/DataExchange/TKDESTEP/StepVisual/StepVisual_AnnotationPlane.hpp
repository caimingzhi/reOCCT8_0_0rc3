#pragma once

#include <Standard.hpp>

#include <StepVisual_AnnotationOccurrence.hpp>
#include <StepVisual_AnnotationPlaneElement.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

class StepVisual_AnnotationPlane : public StepVisual_AnnotationOccurrence
{
public:
  //! Returns a AnnotationPlane
  Standard_EXPORT StepVisual_AnnotationPlane();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>& theName,
    const occ::handle<NCollection_HArray1<occ::handle<StepVisual_PresentationStyleAssignment>>>&
                                                                               theStyles,
    const occ::handle<Standard_Transient>&                                     theItem,
    const occ::handle<NCollection_HArray1<StepVisual_AnnotationPlaneElement>>& theElements);

  //! Returns field Elements
  inline occ::handle<NCollection_HArray1<StepVisual_AnnotationPlaneElement>> Elements() const
  {
    return myElements;
  }

  //! Set field Elements
  inline void SetElements(
    const occ::handle<NCollection_HArray1<StepVisual_AnnotationPlaneElement>>& theElements)
  {
    myElements = theElements;
  }

  //! Returns number of Elements
  inline int NbElements() const { return (myElements.IsNull() ? 0 : myElements->Length()); }

  //! Returns Elements with the given number
  inline StepVisual_AnnotationPlaneElement ElementsValue(const int theNum) const
  {
    return myElements->Value(theNum);
  }

  //! Sets Elements with given number
  inline void SetElementsValue(const int theNum, const StepVisual_AnnotationPlaneElement& theItem)
  {
    myElements->SetValue(theNum, theItem);
  }

  DEFINE_STANDARD_RTTIEXT(StepVisual_AnnotationPlane, StepVisual_AnnotationOccurrence)

private:
  occ::handle<NCollection_HArray1<StepVisual_AnnotationPlaneElement>> myElements;
};

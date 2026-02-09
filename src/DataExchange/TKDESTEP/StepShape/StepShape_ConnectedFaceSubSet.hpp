#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepShape_ConnectedFaceSet.hpp>
#include <StepShape_Face.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
class TCollection_HAsciiString;

class StepShape_ConnectedFaceSubSet : public StepShape_ConnectedFaceSet
{

public:
  Standard_EXPORT StepShape_ConnectedFaceSubSet();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&                         aRepresentationItem_Name,
    const occ::handle<NCollection_HArray1<occ::handle<StepShape_Face>>>& aConnectedFaceSet_CfsFaces,
    const occ::handle<StepShape_ConnectedFaceSet>&                       aParentFaceSet);

  Standard_EXPORT occ::handle<StepShape_ConnectedFaceSet> ParentFaceSet() const;

  Standard_EXPORT void SetParentFaceSet(
    const occ::handle<StepShape_ConnectedFaceSet>& ParentFaceSet);

  DEFINE_STANDARD_RTTIEXT(StepShape_ConnectedFaceSubSet, StepShape_ConnectedFaceSet)

private:
  occ::handle<StepShape_ConnectedFaceSet> theParentFaceSet;
};

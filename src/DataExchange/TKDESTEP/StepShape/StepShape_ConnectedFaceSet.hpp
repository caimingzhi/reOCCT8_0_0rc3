#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepShape_Face.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepShape_TopologicalRepresentationItem.hpp>
#include <Standard_Integer.hpp>
class TCollection_HAsciiString;
class StepShape_Face;

class StepShape_ConnectedFaceSet : public StepShape_TopologicalRepresentationItem
{

public:
  Standard_EXPORT StepShape_ConnectedFaceSet();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&                         aName,
    const occ::handle<NCollection_HArray1<occ::handle<StepShape_Face>>>& aCfsFaces);

  Standard_EXPORT virtual void SetCfsFaces(
    const occ::handle<NCollection_HArray1<occ::handle<StepShape_Face>>>& aCfsFaces);

  Standard_EXPORT virtual occ::handle<NCollection_HArray1<occ::handle<StepShape_Face>>> CfsFaces()
    const;

  Standard_EXPORT virtual occ::handle<StepShape_Face> CfsFacesValue(const int num) const;

  Standard_EXPORT virtual int NbCfsFaces() const;

  DEFINE_STANDARD_RTTIEXT(StepShape_ConnectedFaceSet, StepShape_TopologicalRepresentationItem)

private:
  occ::handle<NCollection_HArray1<occ::handle<StepShape_Face>>> cfsFaces;
};

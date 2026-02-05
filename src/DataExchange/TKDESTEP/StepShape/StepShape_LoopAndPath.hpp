#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepShape_TopologicalRepresentationItem.hpp>
#include <StepShape_OrientedEdge.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Integer.hpp>
class StepShape_Loop;
class StepShape_Path;
class TCollection_HAsciiString;
class StepShape_OrientedEdge;

class StepShape_LoopAndPath : public StepShape_TopologicalRepresentationItem
{

public:
  //! Returns a LoopAndPath
  Standard_EXPORT StepShape_LoopAndPath();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aName,
                            const occ::handle<StepShape_Loop>&           aLoop,
                            const occ::handle<StepShape_Path>&           aPath);

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&                                 aName,
    const occ::handle<NCollection_HArray1<occ::handle<StepShape_OrientedEdge>>>& aEdgeList);

  Standard_EXPORT void SetLoop(const occ::handle<StepShape_Loop>& aLoop);

  Standard_EXPORT occ::handle<StepShape_Loop> Loop() const;

  Standard_EXPORT void SetPath(const occ::handle<StepShape_Path>& aPath);

  Standard_EXPORT occ::handle<StepShape_Path> Path() const;

  Standard_EXPORT void SetEdgeList(
    const occ::handle<NCollection_HArray1<occ::handle<StepShape_OrientedEdge>>>& aEdgeList);

  Standard_EXPORT occ::handle<NCollection_HArray1<occ::handle<StepShape_OrientedEdge>>> EdgeList()
    const;

  Standard_EXPORT occ::handle<StepShape_OrientedEdge> EdgeListValue(const int num) const;

  Standard_EXPORT int NbEdgeList() const;

  DEFINE_STANDARD_RTTIEXT(StepShape_LoopAndPath, StepShape_TopologicalRepresentationItem)

private:
  occ::handle<StepShape_Loop> loop;
  occ::handle<StepShape_Path> path;
};

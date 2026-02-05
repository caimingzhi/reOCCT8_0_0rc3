#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepShape_OrientedEdge.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepShape_Loop.hpp>
#include <Standard_Integer.hpp>
class TCollection_HAsciiString;
class StepShape_OrientedEdge;

class StepShape_EdgeLoop : public StepShape_Loop
{

public:
  //! Returns a EdgeLoop
  Standard_EXPORT StepShape_EdgeLoop();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&                                 aName,
    const occ::handle<NCollection_HArray1<occ::handle<StepShape_OrientedEdge>>>& aEdgeList);

  Standard_EXPORT void SetEdgeList(
    const occ::handle<NCollection_HArray1<occ::handle<StepShape_OrientedEdge>>>& aEdgeList);

  Standard_EXPORT occ::handle<NCollection_HArray1<occ::handle<StepShape_OrientedEdge>>> EdgeList()
    const;

  Standard_EXPORT occ::handle<StepShape_OrientedEdge> EdgeListValue(const int num) const;

  Standard_EXPORT int NbEdgeList() const;

  DEFINE_STANDARD_RTTIEXT(StepShape_EdgeLoop, StepShape_Loop)

private:
  occ::handle<NCollection_HArray1<occ::handle<StepShape_OrientedEdge>>> edgeList;
};

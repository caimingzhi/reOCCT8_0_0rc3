#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepShape_OrientedEdge.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepShape_TopologicalRepresentationItem.hpp>
#include <Standard_Integer.hpp>
class TCollection_HAsciiString;
class StepShape_OrientedEdge;

class StepShape_Path : public StepShape_TopologicalRepresentationItem
{

public:
  //! Returns a Path
  Standard_EXPORT StepShape_Path();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&                                 aName,
    const occ::handle<NCollection_HArray1<occ::handle<StepShape_OrientedEdge>>>& aEdgeList);

  Standard_EXPORT virtual void SetEdgeList(
    const occ::handle<NCollection_HArray1<occ::handle<StepShape_OrientedEdge>>>& aEdgeList);

  Standard_EXPORT virtual occ::handle<NCollection_HArray1<occ::handle<StepShape_OrientedEdge>>>
    EdgeList() const;

  Standard_EXPORT virtual occ::handle<StepShape_OrientedEdge> EdgeListValue(const int num) const;

  Standard_EXPORT virtual int NbEdgeList() const;

  DEFINE_STANDARD_RTTIEXT(StepShape_Path, StepShape_TopologicalRepresentationItem)

private:
  occ::handle<NCollection_HArray1<occ::handle<StepShape_OrientedEdge>>> edgeList;
};


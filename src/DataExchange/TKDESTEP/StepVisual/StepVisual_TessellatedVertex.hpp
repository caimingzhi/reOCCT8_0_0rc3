#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>
#include <StepVisual_TessellatedStructuredItem.hpp>

#include <StepVisual_CoordinatesList.hpp>
#include <StepShape_VertexPoint.hpp>

class StepVisual_TessellatedVertex : public StepVisual_TessellatedStructuredItem
{

public:
  Standard_EXPORT StepVisual_TessellatedVertex();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& theRepresentationItem_Name,
                            const occ::handle<StepVisual_CoordinatesList>& theCoordinates,
                            const bool                                     theHasTopologicalLink,
                            const occ::handle<StepShape_VertexPoint>&      theTopologicalLink,
                            const int                                      thePointIndex);

  Standard_EXPORT occ::handle<StepVisual_CoordinatesList> Coordinates() const;

  Standard_EXPORT void SetCoordinates(
    const occ::handle<StepVisual_CoordinatesList>& theCoordinates);

  Standard_EXPORT occ::handle<StepShape_VertexPoint> TopologicalLink() const;

  Standard_EXPORT void SetTopologicalLink(
    const occ::handle<StepShape_VertexPoint>& theTopologicalLink);

  Standard_EXPORT bool HasTopologicalLink() const;

  Standard_EXPORT int PointIndex() const;

  Standard_EXPORT void SetPointIndex(const int thePointIndex);

  DEFINE_STANDARD_RTTIEXT(StepVisual_TessellatedVertex, StepVisual_TessellatedStructuredItem)

private:
  occ::handle<StepVisual_CoordinatesList> myCoordinates;
  occ::handle<StepShape_VertexPoint>      myTopologicalLink;
  int                                     myPointIndex;
  bool                                    myHasTopologicalLink;
};

#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>
#include <StepVisual_TessellatedStructuredItem.hpp>

#include <StepVisual_CoordinatesList.hpp>
#include <StepShape_VertexPoint.hpp>

//! Representation of STEP entity TessellatedVertex
class StepVisual_TessellatedVertex : public StepVisual_TessellatedStructuredItem
{

public:
  //! default constructor
  Standard_EXPORT StepVisual_TessellatedVertex();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& theRepresentationItem_Name,
                            const occ::handle<StepVisual_CoordinatesList>& theCoordinates,
                            const bool                                     theHasTopologicalLink,
                            const occ::handle<StepShape_VertexPoint>&      theTopologicalLink,
                            const int                                      thePointIndex);

  //! Returns field Coordinates
  Standard_EXPORT occ::handle<StepVisual_CoordinatesList> Coordinates() const;

  //! Sets field Coordinates
  Standard_EXPORT void SetCoordinates(
    const occ::handle<StepVisual_CoordinatesList>& theCoordinates);

  //! Returns field TopologicalLink
  Standard_EXPORT occ::handle<StepShape_VertexPoint> TopologicalLink() const;

  //! Sets field TopologicalLink
  Standard_EXPORT void SetTopologicalLink(
    const occ::handle<StepShape_VertexPoint>& theTopologicalLink);

  //! Returns True if optional field TopologicalLink is defined
  Standard_EXPORT bool HasTopologicalLink() const;

  //! Returns field PointIndex
  Standard_EXPORT int PointIndex() const;

  //! Sets field PointIndex
  Standard_EXPORT void SetPointIndex(const int thePointIndex);

  DEFINE_STANDARD_RTTIEXT(StepVisual_TessellatedVertex, StepVisual_TessellatedStructuredItem)

private:
  occ::handle<StepVisual_CoordinatesList> myCoordinates;
  occ::handle<StepShape_VertexPoint>      myTopologicalLink; //!< optional
  int                                     myPointIndex;
  bool myHasTopologicalLink; //!< flag "is TopologicalLink defined"
};

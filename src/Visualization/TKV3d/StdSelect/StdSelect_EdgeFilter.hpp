#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

enum StdSelect_TypeOfEdge
{
  StdSelect_AnyEdge,
  StdSelect_Line,
  StdSelect_Circle
};

#include <SelectMgr_Filter.hpp>
#include <TopAbs_ShapeEnum.hpp>
class SelectMgr_EntityOwner;

//! A framework to define a filter to select a specific type of edge.
//! The types available include:
//! -   any edge
//! -   a linear edge
//! -   a circular edge.
class StdSelect_EdgeFilter : public SelectMgr_Filter
{

public:
  //! Constructs an edge filter object defined by the type of edge Edge.
  Standard_EXPORT StdSelect_EdgeFilter(const StdSelect_TypeOfEdge Edge);

  //! Sets the type of edge aNewType. aNewType is to be highlighted in selection.
  Standard_EXPORT void SetType(const StdSelect_TypeOfEdge aNewType);

  //! Returns the type of edge to be highlighted in selection.
  Standard_EXPORT StdSelect_TypeOfEdge Type() const;

  Standard_EXPORT bool IsOk(const occ::handle<SelectMgr_EntityOwner>& anobj) const override;

  Standard_EXPORT bool ActsOn(const TopAbs_ShapeEnum aStandardMode) const override;

  DEFINE_STANDARD_RTTIEXT(StdSelect_EdgeFilter, SelectMgr_Filter)

private:
  StdSelect_TypeOfEdge mytype;
};

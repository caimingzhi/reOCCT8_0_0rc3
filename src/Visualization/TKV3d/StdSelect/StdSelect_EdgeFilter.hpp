#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>
// Created on: 1995-03-08
// Created by: Mister rmi
// Copyright (c) 1995-1999 Matra Datavision
// Copyright (c) 1999-2014 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.


//! Provides values for different types of edges. These
//! values are used to filter edges in frameworks
//! inheriting StdSelect_EdgeFilter.
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


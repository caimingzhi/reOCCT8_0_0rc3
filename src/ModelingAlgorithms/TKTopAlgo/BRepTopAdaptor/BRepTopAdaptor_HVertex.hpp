#pragma once

#include <Adaptor3d_HVertex.hpp>
#include <BRepAdaptor_Curve2d.hpp>
#include <Standard.hpp>
#include <Standard_Type.hpp>
#include <TopAbs_Orientation.hpp>
#include <TopoDS_Vertex.hpp>

class gp_Pnt2d;

class BRepTopAdaptor_HVertex : public Adaptor3d_HVertex
{

public:
  Standard_EXPORT BRepTopAdaptor_HVertex(const TopoDS_Vertex&                    Vtx,
                                         const occ::handle<BRepAdaptor_Curve2d>& Curve);

  const TopoDS_Vertex& Vertex() const;

  TopoDS_Vertex& ChangeVertex();

  Standard_EXPORT gp_Pnt2d Value() override;

  Standard_EXPORT double Parameter(const occ::handle<Adaptor2d_Curve2d>& C) override;

  //! Parametric resolution (2d).
  Standard_EXPORT double Resolution(const occ::handle<Adaptor2d_Curve2d>& C) override;

  Standard_EXPORT TopAbs_Orientation Orientation() override;

  Standard_EXPORT bool IsSame(const occ::handle<Adaptor3d_HVertex>& Other) override;

  DEFINE_STANDARD_RTTIEXT(BRepTopAdaptor_HVertex, Adaptor3d_HVertex)

private:
  TopoDS_Vertex                    myVtx;
  occ::handle<BRepAdaptor_Curve2d> myCurve;
};

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

inline const TopoDS_Vertex& BRepTopAdaptor_HVertex::Vertex() const
{
  return myVtx;
}

inline TopoDS_Vertex& BRepTopAdaptor_HVertex::ChangeVertex()
{
  return myVtx;
}

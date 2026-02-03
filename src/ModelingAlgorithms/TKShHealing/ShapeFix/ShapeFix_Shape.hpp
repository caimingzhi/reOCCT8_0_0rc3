// Created on: 1998-08-12
// Created by: DATA EXCHANGE TEAM
// Copyright (c) 1998-1999 Matra Datavision
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

#ifndef _ShapeFix_Shape_HeaderFile
#define _ShapeFix_Shape_HeaderFile

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TopoDS_Shape.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_Map.hpp>
#include <Standard_Integer.hpp>
#include <ShapeFix_Root.hpp>
#include <ShapeExtend_Status.hpp>
#include <Message_ProgressRange.hpp>

class ShapeFix_Solid;
class ShapeFix_Shell;
class ShapeFix_Face;
class ShapeFix_Wire;
class ShapeFix_Edge;
class ShapeExtend_BasicMsgRegistrator;

// resolve name collisions with X11 headers
#ifdef Status
  #undef Status
#endif

//! Fixing shape in general
class ShapeFix_Shape : public ShapeFix_Root
{

public:
  //! Empty Constructor
  Standard_EXPORT ShapeFix_Shape();

  //! Initislises by shape.
  Standard_EXPORT ShapeFix_Shape(const TopoDS_Shape& shape);

  //! Initislises by shape.
  Standard_EXPORT void Init(const TopoDS_Shape& shape);

  //! Iterates on sub- shape and performs fixes
  Standard_EXPORT bool Perform(const Message_ProgressRange& theProgress = Message_ProgressRange());

  //! Returns resulting shape
  Standard_EXPORT TopoDS_Shape Shape() const;

  //! Returns tool for fixing solids.
  occ::handle<ShapeFix_Solid> FixSolidTool() const;

  //! Returns tool for fixing shells.
  occ::handle<ShapeFix_Shell> FixShellTool() const;

  //! Returns tool for fixing faces.
  occ::handle<ShapeFix_Face> FixFaceTool() const;

  //! Returns tool for fixing wires.
  occ::handle<ShapeFix_Wire> FixWireTool() const;

  //! Returns tool for fixing edges.
  occ::handle<ShapeFix_Edge> FixEdgeTool() const;

  //! Returns the status of the last Fix.
  //! This can be a combination of the following flags:
  //! ShapeExtend_DONE1: some free edges were fixed
  //! ShapeExtend_DONE2: some free wires were fixed
  //! ShapeExtend_DONE3: some free faces were fixed
  //! ShapeExtend_DONE4: some free shells were fixed
  //! ShapeExtend_DONE5: some free solids were fixed
  //! ShapeExtend_DONE6: shapes in compound(s) were fixed
  Standard_EXPORT bool Status(const ShapeExtend_Status status) const;

  //! Sets message registrator
  Standard_EXPORT void SetMsgRegistrator(
    const occ::handle<ShapeExtend_BasicMsgRegistrator>& msgreg) override;

  //! Sets basic precision value (also to FixSolidTool)
  Standard_EXPORT void SetPrecision(const double preci) override;

  //! Sets minimal allowed tolerance (also to FixSolidTool)
  Standard_EXPORT void SetMinTolerance(const double mintol) override;

  //! Sets maximal allowed tolerance (also to FixSolidTool)
  Standard_EXPORT void SetMaxTolerance(const double maxtol) override;

  //! Returns (modifiable) the mode for applying fixes of
  //! ShapeFix_Solid, by default True.
  int& FixSolidMode();

  //! Returns (modifiable) the mode for applying fixes of
  //! ShapeFix_Shell, by default True.
  int& FixFreeShellMode();

  //! Returns (modifiable) the mode for applying fixes of
  //! ShapeFix_Face, by default True.
  int& FixFreeFaceMode();

  //! Returns (modifiable) the mode for applying fixes of
  //! ShapeFix_Wire, by default True.
  int& FixFreeWireMode();

  //! Returns (modifiable) the mode for applying
  //! ShapeFix::SameParameter after all fixes, by default True.
  int& FixSameParameterMode();

  //! Returns (modifiable) the mode for applying
  //! ShapeFix::FixVertexPosition before all fixes, by default False.
  int& FixVertexPositionMode();

  //! Returns (modifiable) the mode for fixing tolerances of vertices on whole shape
  //! after performing all fixes
  int& FixVertexTolMode();

  DEFINE_STANDARD_RTTIEXT(ShapeFix_Shape, ShapeFix_Root)

protected:
  //! Fixes same parameterization problem on the passed shape
  //! by updating tolerances of the corresponding topological
  //! entities.
  Standard_EXPORT void SameParameter(
    const TopoDS_Shape&          shape,
    const bool                   enforce,
    const Message_ProgressRange& theProgress = Message_ProgressRange());

  TopoDS_Shape                                           myResult;
  occ::handle<ShapeFix_Solid>                            myFixSolid;
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> myMapFixingShape;
  int                                                    myFixSolidMode;
  int                                                    myFixShellMode;
  int                                                    myFixFaceMode;
  int                                                    myFixWireMode;
  int                                                    myFixSameParameterMode;
  int                                                    myFixVertexPositionMode;
  int                                                    myFixVertexTolMode;
  int                                                    myStatus;
};
// Created on: 1999-06-25
// Created by: data exchange team
// Copyright (c) 1999-1999 Matra Datavision
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

#include <ShapeFix_Solid.hpp>
#include <ShapeFix_Shell.hpp>
#include <ShapeFix_Face.hpp>
#include <ShapeFix_Wire.hpp>

//=================================================================================================

inline occ::handle<ShapeFix_Solid> ShapeFix_Shape::FixSolidTool() const
{
  return myFixSolid;
}

//=================================================================================================

inline occ::handle<ShapeFix_Shell> ShapeFix_Shape::FixShellTool() const
{
  return myFixSolid->FixShellTool();
}

//=================================================================================================

inline occ::handle<ShapeFix_Face> ShapeFix_Shape::FixFaceTool() const
{
  return myFixSolid->FixShellTool()->FixFaceTool();
}

//=================================================================================================

inline occ::handle<ShapeFix_Wire> ShapeFix_Shape::FixWireTool() const
{
  return myFixSolid->FixShellTool()->FixFaceTool()->FixWireTool();
}

//=================================================================================================

inline occ::handle<ShapeFix_Edge> ShapeFix_Shape::FixEdgeTool() const
{
  return myFixSolid->FixShellTool()->FixFaceTool()->FixWireTool()->FixEdgeTool();
}

//=================================================================================================

inline int& ShapeFix_Shape::FixSolidMode()
{
  return myFixSolidMode;
}

//=================================================================================================

inline int& ShapeFix_Shape::FixFreeShellMode()
{
  return myFixShellMode;
}

//=================================================================================================

inline int& ShapeFix_Shape::FixFreeFaceMode()
{
  return myFixFaceMode;
}

//=================================================================================================

inline int& ShapeFix_Shape::FixFreeWireMode()
{
  return myFixWireMode;
}

//=================================================================================================

inline int& ShapeFix_Shape::FixSameParameterMode()
{
  return myFixSameParameterMode;
}

//=================================================================================================

inline int& ShapeFix_Shape::FixVertexPositionMode()
{
  return myFixVertexPositionMode;
}

//=================================================================================================

inline int& ShapeFix_Shape::FixVertexTolMode()
{
  return myFixVertexTolMode;
}


#endif // _ShapeFix_Shape_HeaderFile

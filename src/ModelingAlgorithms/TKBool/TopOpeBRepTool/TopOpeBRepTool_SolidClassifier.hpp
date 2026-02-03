// Created on: 1996-08-27
// Created by: Jean Yves LEBEY
// Copyright (c) 1996-1999 Matra Datavision
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

#ifndef _TopOpeBRepTool_SolidClassifier_HeaderFile
#define _TopOpeBRepTool_SolidClassifier_HeaderFile

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
// Created on: 1993-06-17
// Created by: Jean Yves LEBEY
// Copyright (c) 1993-1999 Matra Datavision
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

#ifndef _TopOpeBRepTool_PSoClassif_HeaderFile
#define _TopOpeBRepTool_PSoClassif_HeaderFile

class BRepClass3d_SolidClassifier;
typedef BRepClass3d_SolidClassifier* TopOpeBRepTool_PSoClassif;

#endif // _TopOpeBRepTool_PSoClassif_HeaderFile

#include <TopoDS_Shape.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <TopAbs_State.hpp>
#include <BRep_Builder.hpp>
class gp_Pnt;

class TopOpeBRepTool_SolidClassifier
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopOpeBRepTool_SolidClassifier();

  Standard_EXPORT void Clear();

  Standard_EXPORT ~TopOpeBRepTool_SolidClassifier();

  Standard_EXPORT void LoadSolid(const TopoDS_Solid& S);

  //! compute the position of point <P> regarding with the
  //! geometric domain of the solid <S>.
  Standard_EXPORT TopAbs_State Classify(const TopoDS_Solid& S, const gp_Pnt& P, const double Tol);

  Standard_EXPORT void LoadShell(const TopoDS_Shell& S);

  //! compute the position of point <P> regarding with the
  //! geometric domain of the shell <S>.
  Standard_EXPORT TopAbs_State Classify(const TopoDS_Shell& S, const gp_Pnt& P, const double Tol);

  Standard_EXPORT TopAbs_State State() const;

private:
  TopOpeBRepTool_PSoClassif                                                myPClassifier;
  NCollection_IndexedDataMap<TopoDS_Shape, void*, TopTools_ShapeMapHasher> myShapeClassifierMap;
  TopAbs_State                                                             myState;
  TopoDS_Shell                                                             myShell;
  TopoDS_Solid                                                             mySolid;
  BRep_Builder                                                             myBuilder;
};

#endif // _TopOpeBRepTool_SolidClassifier_HeaderFile

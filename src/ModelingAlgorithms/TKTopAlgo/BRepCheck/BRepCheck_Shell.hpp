// Created on: 1996-01-02
// Created by: Jacques GOUSSARD
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

#ifndef _BRepCheck_Shell_HeaderFile
#define _BRepCheck_Shell_HeaderFile

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <BRepCheck_Result.hpp>
class TopoDS_Shell;
class TopoDS_Shape;

class BRepCheck_Shell : public BRepCheck_Result
{

public:
  Standard_EXPORT BRepCheck_Shell(const TopoDS_Shell& S);

  Standard_EXPORT void InContext(const TopoDS_Shape& ContextShape) override;

  Standard_EXPORT void Minimum() override;

  Standard_EXPORT void Blind() override;

  //! Checks if the oriented faces of the shell give a
  //! closed shell. If the wire is closed, returns
  //! BRepCheck_NoError. If <Update> is set to
  //! true, registers the status in the list.
  Standard_EXPORT BRepCheck_Status Closed(const bool Update = false);

  //! Checks if the oriented faces of the shell are
  //! correctly oriented. An internal call is made to
  //! the method Closed. If <Update> is set to
  //! true, registers the status in the list.
  Standard_EXPORT BRepCheck_Status Orientation(const bool Update = false);

  Standard_EXPORT void SetUnorientable();

  Standard_EXPORT bool IsUnorientable() const;

  Standard_EXPORT int NbConnectedSet(NCollection_List<TopoDS_Shape>& theSets);

  DEFINE_STANDARD_RTTIEXT(BRepCheck_Shell, BRepCheck_Result)

private:
  int              myNbori;
  bool             myCdone;
  BRepCheck_Status myCstat;
  bool             myOdone;
  BRepCheck_Status myOstat;
  NCollection_IndexedDataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
    myMapEF;
};

#endif // _BRepCheck_Shell_HeaderFile

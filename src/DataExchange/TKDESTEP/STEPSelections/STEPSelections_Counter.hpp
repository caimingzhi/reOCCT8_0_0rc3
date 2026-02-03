// Created on: 1999-02-11
// Created by: Pavel DURANDIN
// Copyright (c) 1999 Matra Datavision
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

#ifndef _STEPSelections_Counter_HeaderFile
#define _STEPSelections_Counter_HeaderFile

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <Standard_Transient.hpp>
#include <NCollection_Map.hpp>
class Interface_Graph;
class Standard_Transient;
class StepShape_ConnectedFaceSet;
class StepGeom_CompositeCurve;

class STEPSelections_Counter
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT STEPSelections_Counter();

  Standard_EXPORT void Count(const Interface_Graph&                 graph,
                             const occ::handle<Standard_Transient>& start);

  Standard_EXPORT void Clear();

  int NbInstancesOfFaces() const;

  int POP() const;

  int POP2() const;

  int NbInstancesOfShells() const;

  int NbInstancesOfSolids() const;

  int NbInstancesOfEdges() const;

  int NbInstancesOfWires() const;

  int NbSourceFaces() const;

  int NbSourceShells() const;

  int NbSourceSolids() const;

  int NbSourceEdges() const;

  int NbSourceWires() const;

private:
  Standard_EXPORT void AddShell(const occ::handle<StepShape_ConnectedFaceSet>& cfs);

  Standard_EXPORT void AddCompositeCurve(const occ::handle<StepGeom_CompositeCurve>& ccurve);

  int                                              myNbFaces;
  int                                              myNbShells;
  int                                              myNbSolids;
  int                                              myNbEdges;
  int                                              myNbWires;
  NCollection_Map<occ::handle<Standard_Transient>> myMapOfFaces;
  NCollection_Map<occ::handle<Standard_Transient>> myMapOfShells;
  NCollection_Map<occ::handle<Standard_Transient>> myMapOfSolids;
  NCollection_Map<occ::handle<Standard_Transient>> myMapOfEdges;
  NCollection_Map<occ::handle<Standard_Transient>> myMapOfWires;
};
// Created on: 1999-02-11
// Created by: Pavel DURANDIN
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

inline int STEPSelections_Counter::NbInstancesOfFaces() const
{
  return myNbFaces;
}

inline int STEPSelections_Counter::NbInstancesOfShells() const
{
  return myNbShells;
}

inline int STEPSelections_Counter::NbInstancesOfSolids() const
{
  return myNbSolids;
}

inline int STEPSelections_Counter::NbInstancesOfEdges() const
{
  return myNbEdges;
}

inline int STEPSelections_Counter::NbInstancesOfWires() const
{
  return myNbWires;
}

inline int STEPSelections_Counter::NbSourceFaces() const
{
  return myMapOfFaces.Extent();
}

inline int STEPSelections_Counter::NbSourceShells() const
{
  return myMapOfShells.Extent();
}

inline int STEPSelections_Counter::NbSourceSolids() const
{
  return myMapOfSolids.Extent();
}

inline int STEPSelections_Counter::NbSourceEdges() const
{
  return myMapOfEdges.Extent();
}

inline int STEPSelections_Counter::NbSourceWires() const
{
  return myMapOfWires.Extent();
}


#endif // _STEPSelections_Counter_HeaderFile

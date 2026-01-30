// Created on: 1996-04-10
// Created by: Joelle CHAUVET
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

#ifndef _AdvApp2Var_Framework_HeaderFile
#define _AdvApp2Var_Framework_HeaderFile

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <AdvApp2Var_Node.hpp>
#include <NCollection_Sequence.hpp>
#include <AdvApp2Var_Iso.hpp>
#include <Standard_Boolean.hpp>
#include <Standard_Integer.hpp>
#include <GeomAbs_IsoType.hpp>
#include <Standard_Real.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
class AdvApp2Var_Iso;
class AdvApp2Var_Node;

class AdvApp2Var_Framework
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT AdvApp2Var_Framework();

  Standard_EXPORT AdvApp2Var_Framework(
    const NCollection_Sequence<occ::handle<AdvApp2Var_Node>>&                      Frame,
    const NCollection_Sequence<NCollection_Sequence<occ::handle<AdvApp2Var_Iso>>>& UFrontier,
    const NCollection_Sequence<NCollection_Sequence<occ::handle<AdvApp2Var_Iso>>>& VFrontier);

  //! search the Index of the first Iso not approximated,
  //! if all Isos are approximated NULL is returned.
  Standard_EXPORT occ::handle<AdvApp2Var_Iso> FirstNotApprox(int& IndexIso, int& IndexStrip) const;

  Standard_EXPORT int FirstNode(const GeomAbs_IsoType Type,
                                const int             IndexIso,
                                const int             IndexStrip) const;

  Standard_EXPORT int LastNode(const GeomAbs_IsoType Type,
                               const int             IndexIso,
                               const int             IndexStrip) const;

  Standard_EXPORT void ChangeIso(const int                          IndexIso,
                                 const int                          IndexStrip,
                                 const occ::handle<AdvApp2Var_Iso>& anIso);

  const occ::handle<AdvApp2Var_Node>& Node(const int IndexNode) const
  {
    return myNodeConstraints.Value(IndexNode);
  }

  Standard_EXPORT const occ::handle<AdvApp2Var_Node>& Node(const double U, const double V) const;

  Standard_EXPORT const AdvApp2Var_Iso& IsoU(const double U,
                                             const double V0,
                                             const double V1) const;

  Standard_EXPORT const AdvApp2Var_Iso& IsoV(const double U0,
                                             const double U1,
                                             const double V) const;

  Standard_EXPORT void UpdateInU(const double CuttingValue);

  Standard_EXPORT void UpdateInV(const double CuttingValue);

  Standard_EXPORT const occ::handle<NCollection_HArray1<double>>& UEquation(
    const int IndexIso,
    const int IndexStrip) const;

  Standard_EXPORT const occ::handle<NCollection_HArray1<double>>& VEquation(
    const int IndexIso,
    const int IndexStrip) const;

private:
  NCollection_Sequence<occ::handle<AdvApp2Var_Node>>                      myNodeConstraints;
  NCollection_Sequence<NCollection_Sequence<occ::handle<AdvApp2Var_Iso>>> myUConstraints;
  NCollection_Sequence<NCollection_Sequence<occ::handle<AdvApp2Var_Iso>>> myVConstraints;
};

#endif // _AdvApp2Var_Framework_HeaderFile

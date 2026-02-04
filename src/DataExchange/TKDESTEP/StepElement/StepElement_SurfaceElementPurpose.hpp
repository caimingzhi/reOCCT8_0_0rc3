#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
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


enum StepElement_EnumeratedSurfaceElementPurpose
{
  StepElement_MembraneDirect,
  StepElement_MembraneShear,
  StepElement_BendingDirect,
  StepElement_BendingTorsion,
  StepElement_NormalToPlaneShear
};


class Standard_Transient;
class StepData_SelectMember;
class TCollection_HAsciiString;

//! Representation of STEP SELECT type SurfaceElementPurpose
class StepElement_SurfaceElementPurpose : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  Standard_EXPORT StepElement_SurfaceElementPurpose();

  //! Recognizes a kind of SurfaceElementPurpose select type
  //! return 0
  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  //! Recognizes a items of select member SurfaceElementPurposeMember
  //! 1 -> EnumeratedSurfaceElementPurpose
  //! 2 -> ApplicationDefinedElementPurpose
  //! 0 else
  Standard_EXPORT int CaseMem(const occ::handle<StepData_SelectMember>& ent) const override;

  //! Returns a new select member the type SurfaceElementPurposeMember
  Standard_EXPORT occ::handle<StepData_SelectMember> NewMember() const override;

  //! Set Value for EnumeratedSurfaceElementPurpose
  Standard_EXPORT void SetEnumeratedSurfaceElementPurpose(
    const StepElement_EnumeratedSurfaceElementPurpose aVal);

  //! Returns Value as EnumeratedSurfaceElementPurpose (or Null if another type)
  Standard_EXPORT StepElement_EnumeratedSurfaceElementPurpose
    EnumeratedSurfaceElementPurpose() const;

  //! Set Value for ApplicationDefinedElementPurpose
  Standard_EXPORT void SetApplicationDefinedElementPurpose(
    const occ::handle<TCollection_HAsciiString>& aVal);

  //! Returns Value as ApplicationDefinedElementPurpose (or Null if another type)
  Standard_EXPORT occ::handle<TCollection_HAsciiString> ApplicationDefinedElementPurpose() const;
};


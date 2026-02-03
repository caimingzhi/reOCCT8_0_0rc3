// Created on: 2000-02-07
// Created by: data exchange team
// Copyright (c) 2000-2014 OPEN CASCADE SAS
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

#ifndef _IGESToBRep_AlgoContainer_HeaderFile
#define _IGESToBRep_AlgoContainer_HeaderFile

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class IGESToBRep_ToolContainer;

class IGESToBRep_AlgoContainer : public Standard_Transient
{

public:
  //! Empty constructor
  Standard_EXPORT IGESToBRep_AlgoContainer();

  //! Sets ToolContainer
  void SetToolContainer(const occ::handle<IGESToBRep_ToolContainer>& TC);

  //! Returns ToolContainer
  occ::handle<IGESToBRep_ToolContainer> ToolContainer() const;

  DEFINE_STANDARD_RTTIEXT(IGESToBRep_AlgoContainer, Standard_Transient)

private:
  occ::handle<IGESToBRep_ToolContainer> myTC;
};
// Created on: 2000-02-07
// Created by: data exchange team
// Copyright (c) 2000-2014 OPEN CASCADE SAS
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

#include <IGESToBRep_AlgoContainer.hpp>

//=================================================================================================

inline void IGESToBRep_AlgoContainer::SetToolContainer(
  const occ::handle<IGESToBRep_ToolContainer>& TC)
{
  myTC = TC;
}

//=================================================================================================

inline occ::handle<IGESToBRep_ToolContainer> IGESToBRep_AlgoContainer::ToolContainer() const
{
  return myTC;
}


#endif // _IGESToBRep_AlgoContainer_HeaderFile

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

#include <IGESData_FreeFormatEntity.hpp>
#include <IGESData_IGESModel.hpp>
#include <IGESData_Protocol.hpp>
#include <IGESData_UndefinedEntity.hpp>
#include <Interface_InterfaceModel.hpp>
#include <Interface_Protocol.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESData_Protocol, Interface_Protocol)

IGESData_Protocol::IGESData_Protocol() = default;

int IGESData_Protocol::NbResources() const
{
  return 0;
}

occ::handle<Interface_Protocol> IGESData_Protocol::Resource(const int /*num*/) const
{
  occ::handle<Interface_Protocol> nulpro;
  return nulpro;
}

//  TypeNumber : Here, we recognize UndefinedEntity (someone has to)

int IGESData_Protocol::TypeNumber(const occ::handle<Standard_Type>& atype) const
{
  if (atype->SubType(STANDARD_TYPE(IGESData_UndefinedEntity)))
    return 1;
  return 0;
}

occ::handle<Interface_InterfaceModel> IGESData_Protocol::NewModel() const
{
  return new IGESData_IGESModel;
}

bool IGESData_Protocol::IsSuitableModel(const occ::handle<Interface_InterfaceModel>& model) const
{
  return model->IsKind(STANDARD_TYPE(IGESData_IGESModel));
}

occ::handle<Standard_Transient> IGESData_Protocol::UnknownEntity() const
{
  return new IGESData_UndefinedEntity;
}

bool IGESData_Protocol::IsUnknownEntity(const occ::handle<Standard_Transient>& ent) const
{
  return ent->IsKind(STANDARD_TYPE(IGESData_UndefinedEntity));
}

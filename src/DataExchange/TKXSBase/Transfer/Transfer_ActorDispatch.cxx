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

#include <Interface_GeneralLib.hpp>
#include <Interface_InterfaceModel.hpp>
#include <Interface_Protocol.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>
#include <Transfer_ActorDispatch.hpp>
#include <Transfer_ActorOfTransientProcess.hpp>
#include <Transfer_Binder.hpp>
#include <Transfer_TransferDispatch.hpp>
#include <Transfer_TransientProcess.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Transfer_ActorDispatch, Transfer_ActorOfTransientProcess)

Transfer_ActorDispatch::Transfer_ActorDispatch(const occ::handle<Interface_InterfaceModel>& amodel,
                                               const Interface_GeneralLib&                  lib)
    : thetool(amodel, lib)
{
  SetLast(true); // actor par defaut
  thetool.TransientProcess()->SetActor(this);
}

Transfer_ActorDispatch::Transfer_ActorDispatch(const occ::handle<Interface_InterfaceModel>& amodel,
                                               const occ::handle<Interface_Protocol>& protocol)
    : thetool(amodel, protocol)
{
  SetLast(true); // actor par defaut
  thetool.TransientProcess()->SetActor(this);
}

Transfer_ActorDispatch::Transfer_ActorDispatch(const occ::handle<Interface_InterfaceModel>& amodel)
    : thetool(amodel)
{
  SetLast(true); // actor par defaut
  thetool.TransientProcess()->SetActor(this);
}

void Transfer_ActorDispatch::AddActor(const occ::handle<Transfer_ActorOfTransientProcess>& actor)
{
  thetool.TransientProcess()->SetActor(actor);
}

Transfer_TransferDispatch& Transfer_ActorDispatch::TransferDispatch()
{
  return thetool;
}

occ::handle<Transfer_Binder> Transfer_ActorDispatch::Transfer(
  const occ::handle<Standard_Transient>& start,
  const occ::handle<Transfer_TransientProcess>& /*TP*/,
  const Message_ProgressRange&)
{
  thetool.TransferEntity(start);
  return thetool.TransientProcess()->Find(start);
}

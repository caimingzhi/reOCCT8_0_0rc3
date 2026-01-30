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

#include <Standard_Transient.hpp>
#include <Transfer_ActorOfFinderProcess.hpp>
#include <Transfer_Binder.hpp>
#include <Transfer_Finder.hpp>
#include <Transfer_FinderProcess.hpp>
#include <Transfer_ProcessForFinder.hpp>
#include <Transfer_SimpleBinderOfTransient.hpp>
#include <Transfer_TransientMapper.hpp>
#include <XSAlgo_ShapeProcessor.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Transfer_ActorOfFinderProcess, Transfer_ActorOfProcessForFinder)

//=============================================================================

Transfer_ActorOfFinderProcess::Transfer_ActorOfFinderProcess()
{
  themodetrans = 0;
}

//=============================================================================

int& Transfer_ActorOfFinderProcess::ModeTrans()
{
  return themodetrans;
}

//=============================================================================

occ::handle<Transfer_Binder> Transfer_ActorOfFinderProcess::Transfer(
  const occ::handle<Transfer_Finder>&        fnd,
  const occ::handle<Transfer_FinderProcess>& FP,
  const Message_ProgressRange&               theProgress)
{
  occ::handle<Transfer_TransientMapper> tm = occ::down_cast<Transfer_TransientMapper>(fnd);
  if (tm.IsNull())
    return NullResult();
  occ::handle<Standard_Transient> res = TransferTransient(tm->Value(), FP, theProgress);
  if (res.IsNull())
    return NullResult();
  return TransientResult(res);
}

//=============================================================================

occ::handle<Transfer_Binder> Transfer_ActorOfFinderProcess::Transferring(
  const occ::handle<Transfer_Finder>&           ent,
  const occ::handle<Transfer_ProcessForFinder>& TP,
  const Message_ProgressRange&                  theProgress)
{
  return Transfer(ent, occ::down_cast<Transfer_FinderProcess>(TP), theProgress);
}

//=============================================================================

occ::handle<Standard_Transient> Transfer_ActorOfFinderProcess::TransferTransient(
  const occ::handle<Standard_Transient>& /*ent*/,
  const occ::handle<Transfer_FinderProcess>&,
  const Message_ProgressRange&)
{
  occ::handle<Standard_Transient> nulres;
  return nulres;
}

//=============================================================================

void Transfer_ActorOfFinderProcess::SetShapeFixParameters(
  const XSAlgo_ShapeProcessor::ParameterMap& theParameters)
{
  myShapeProcParams = theParameters;
}

//=============================================================================

void Transfer_ActorOfFinderProcess::SetShapeFixParameters(
  XSAlgo_ShapeProcessor::ParameterMap&& theParameters)
{
  myShapeProcParams = std::move(theParameters);
}

//=============================================================================

void Transfer_ActorOfFinderProcess::SetShapeFixParameters(
  const DE_ShapeFixParameters&               theParameters,
  const XSAlgo_ShapeProcessor::ParameterMap& theAdditionalParameters)
{
  XSAlgo_ShapeProcessor::SetShapeFixParameters(theParameters,
                                               theAdditionalParameters,
                                               myShapeProcParams);
}

//=============================================================================

void Transfer_ActorOfFinderProcess::SetShapeProcessFlags(
  const ShapeProcess::OperationsFlags& theFlags)
{
  myShapeProcFlags.first  = theFlags;
  myShapeProcFlags.second = true;
}

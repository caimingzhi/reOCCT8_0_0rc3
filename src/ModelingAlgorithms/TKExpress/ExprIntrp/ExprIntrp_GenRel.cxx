// Created on: 1992-08-18
// Created by: Arnaud BOUZY
// Copyright (c) 1992-1999 Matra Datavision
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

#include <Expr_GeneralRelation.hpp>
#include <ExprIntrp.hpp>
#include <ExprIntrp_GenRel.hpp>
#include <ExprIntrp_yaccanal.hpp>
#include <Standard_NoSuchObject.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(ExprIntrp_GenRel, ExprIntrp_Generator)

ExprIntrp_GenRel::ExprIntrp_GenRel()
{
  done = false;
}

occ::handle<ExprIntrp_GenRel> ExprIntrp_GenRel::Create()
{
  return new ExprIntrp_GenRel();
}

void ExprIntrp_GenRel::Process(const TCollection_AsciiString& str)
{
  occ::handle<ExprIntrp_GenRel> me = this;
  done                             = false;
  if (ExprIntrp::Parse(me, str))
  {
    if (!ExprIntrp_Recept.IsRelStackEmpty())
    {
      myRelation = ExprIntrp_Recept.PopRelation();
      done       = true;
    }
    else
    {
      myRelation.Nullify();
    }
  }
  else
  {
    myRelation.Nullify();
  }
}

bool ExprIntrp_GenRel::IsDone() const
{
  return done;
}

occ::handle<Expr_GeneralRelation> ExprIntrp_GenRel::Relation() const
{
  if (!done)
  {
    throw Standard_NoSuchObject();
  }
  return myRelation;
}

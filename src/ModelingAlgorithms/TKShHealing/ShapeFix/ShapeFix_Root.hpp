// Created on: 1999-08-09
// Created by: Galina KULIKOVA
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

#ifndef _ShapeFix_Root_HeaderFile
#define _ShapeFix_Root_HeaderFile

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TopoDS_Shape.hpp>
#include <Standard_Transient.hpp>
#include <Message_Gravity.hpp>
#include <Standard_Integer.hpp>

#include <ShapeExtend_BasicMsgRegistrator.hpp>

class ShapeBuild_ReShape;
class ShapeExtend_BasicMsgRegistrator;
class Message_Msg;

//! Root class for fixing operations
//! Provides context for recording changes (optional),
//! basic precision value and limit (minimal and
//! maximal) values for tolerances,
//! and message registrator
class ShapeFix_Root : public Standard_Transient
{

public:
  //! Empty Constructor (no context is created)
  Standard_EXPORT ShapeFix_Root();

  //! Copy all fields from another Root object
  Standard_EXPORT virtual void Set(const occ::handle<ShapeFix_Root>& Root);

  //! Sets context
  Standard_EXPORT virtual void SetContext(const occ::handle<ShapeBuild_ReShape>& context);

  //! Returns context
  occ::handle<ShapeBuild_ReShape> Context() const;

  //! Sets message registrator
  Standard_EXPORT virtual void SetMsgRegistrator(
    const occ::handle<ShapeExtend_BasicMsgRegistrator>& msgreg);

  //! Returns message registrator
  occ::handle<ShapeExtend_BasicMsgRegistrator> MsgRegistrator() const;

  //! Sets basic precision value
  Standard_EXPORT virtual void SetPrecision(const double preci);

  //! Returns basic precision value
  double Precision() const;

  //! Sets minimal allowed tolerance
  Standard_EXPORT virtual void SetMinTolerance(const double mintol);

  //! Returns minimal allowed tolerance
  double MinTolerance() const;

  //! Sets maximal allowed tolerance
  Standard_EXPORT virtual void SetMaxTolerance(const double maxtol);

  //! Returns maximal allowed tolerance
  double MaxTolerance() const;

  //! Returns tolerance limited by [myMinTol,myMaxTol]
  double LimitTolerance(const double toler) const;

  //! Sends a message to be attached to the shape.
  //! Calls corresponding message of message registrator.
  Standard_EXPORT void SendMsg(const TopoDS_Shape&   shape,
                               const Message_Msg&    message,
                               const Message_Gravity gravity = Message_Info) const;

  //! Sends a message to be attached to myShape.
  //! Calls previous method.
  void SendMsg(const Message_Msg& message, const Message_Gravity gravity = Message_Info) const;

  //! Sends a warning to be attached to the shape.
  //! Calls SendMsg with gravity set to Message_Warning.
  void SendWarning(const TopoDS_Shape& shape, const Message_Msg& message) const;

  //! Calls previous method for myShape.
  void SendWarning(const Message_Msg& message) const;

  //! Sends a fail to be attached to the shape.
  //! Calls SendMsg with gravity set to Message_Fail.
  void SendFail(const TopoDS_Shape& shape, const Message_Msg& message) const;

  //! Calls previous method for myShape.
  void SendFail(const Message_Msg& message) const;

  DEFINE_STANDARD_RTTIEXT(ShapeFix_Root, Standard_Transient)

protected:
  //! Auxiliary method for work with three-position
  //! (on/off/default) flags (modes) in ShapeFix.
  static bool NeedFix(const int flag, const bool def = true);

  TopoDS_Shape myShape;

private:
  occ::handle<ShapeBuild_ReShape>              myContext;
  occ::handle<ShapeExtend_BasicMsgRegistrator> myMsgReg;
  double                                       myPrecision;
  double                                       myMinTol;
  double                                       myMaxTol;
};
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

#include <Precision.hpp>

//=================================================================================================

inline occ::handle<ShapeBuild_ReShape> ShapeFix_Root::Context() const
{
  return myContext;
}

//=================================================================================================

inline occ::handle<ShapeExtend_BasicMsgRegistrator> ShapeFix_Root::MsgRegistrator() const
{
  return myMsgReg;
}

//=================================================================================================

inline double ShapeFix_Root::Precision() const
{
  return myPrecision;
}

//=================================================================================================

inline double ShapeFix_Root::MinTolerance() const
{
  return myMinTol;
}

//=================================================================================================

inline double ShapeFix_Root::MaxTolerance() const
{
  return myMaxTol;
}

//=================================================================================================

inline double ShapeFix_Root::LimitTolerance(const double toler) const
{
  // only maximal restriction implemented.
  return std::min(myMaxTol, toler);
}

//=================================================================================================

inline void ShapeFix_Root::SendMsg(const Message_Msg& message, const Message_Gravity gravity) const
{
  SendMsg(myShape, message, gravity);
}

//=================================================================================================

inline void ShapeFix_Root::SendWarning(const TopoDS_Shape& shape, const Message_Msg& message) const
{
  SendMsg(shape, message, Message_Warning);
}

//=================================================================================================

inline void ShapeFix_Root::SendWarning(const Message_Msg& message) const
{
  SendWarning(myShape, message);
}

//=================================================================================================

inline void ShapeFix_Root::SendFail(const TopoDS_Shape& shape, const Message_Msg& message) const
{
  SendMsg(shape, message, Message_Fail);
}

//=================================================================================================

inline void ShapeFix_Root::SendFail(const Message_Msg& message) const
{
  SendFail(myShape, message);
}

//=======================================================================
// function : NeedFix
// purpose  : Function used to define if the fixing method needs to be called
//           according to its specific flag if it is set, or
//           to some additional criteria (if Flag is default)
//=======================================================================

inline bool ShapeFix_Root::NeedFix(const int Flag, const bool need)
{
  return Flag < 0 ? need : (Flag > 0);
}


#endif // _ShapeFix_Root_HeaderFile

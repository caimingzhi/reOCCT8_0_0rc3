#pragma once

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

class ShapeFix_Root : public Standard_Transient
{

public:
  Standard_EXPORT ShapeFix_Root();

  Standard_EXPORT virtual void Set(const occ::handle<ShapeFix_Root>& Root);

  Standard_EXPORT virtual void SetContext(const occ::handle<ShapeBuild_ReShape>& context);

  occ::handle<ShapeBuild_ReShape> Context() const;

  Standard_EXPORT virtual void SetMsgRegistrator(
    const occ::handle<ShapeExtend_BasicMsgRegistrator>& msgreg);

  occ::handle<ShapeExtend_BasicMsgRegistrator> MsgRegistrator() const;

  Standard_EXPORT virtual void SetPrecision(const double preci);

  double Precision() const;

  Standard_EXPORT virtual void SetMinTolerance(const double mintol);

  double MinTolerance() const;

  Standard_EXPORT virtual void SetMaxTolerance(const double maxtol);

  double MaxTolerance() const;

  double LimitTolerance(const double toler) const;

  Standard_EXPORT void SendMsg(const TopoDS_Shape&   shape,
                               const Message_Msg&    message,
                               const Message_Gravity gravity = Message_Info) const;

  void SendMsg(const Message_Msg& message, const Message_Gravity gravity = Message_Info) const;

  void SendWarning(const TopoDS_Shape& shape, const Message_Msg& message) const;

  void SendWarning(const Message_Msg& message) const;

  void SendFail(const TopoDS_Shape& shape, const Message_Msg& message) const;

  void SendFail(const Message_Msg& message) const;

  DEFINE_STANDARD_RTTIEXT(ShapeFix_Root, Standard_Transient)

protected:
  static bool NeedFix(const int flag, const bool def = true);

  TopoDS_Shape myShape;

private:
  occ::handle<ShapeBuild_ReShape>              myContext;
  occ::handle<ShapeExtend_BasicMsgRegistrator> myMsgReg;
  double                                       myPrecision;
  double                                       myMinTol;
  double                                       myMaxTol;
};

#include <Precision.hpp>

inline occ::handle<ShapeBuild_ReShape> ShapeFix_Root::Context() const
{
  return myContext;
}

inline occ::handle<ShapeExtend_BasicMsgRegistrator> ShapeFix_Root::MsgRegistrator() const
{
  return myMsgReg;
}

inline double ShapeFix_Root::Precision() const
{
  return myPrecision;
}

inline double ShapeFix_Root::MinTolerance() const
{
  return myMinTol;
}

inline double ShapeFix_Root::MaxTolerance() const
{
  return myMaxTol;
}

inline double ShapeFix_Root::LimitTolerance(const double toler) const
{

  return std::min(myMaxTol, toler);
}

inline void ShapeFix_Root::SendMsg(const Message_Msg& message, const Message_Gravity gravity) const
{
  SendMsg(myShape, message, gravity);
}

inline void ShapeFix_Root::SendWarning(const TopoDS_Shape& shape, const Message_Msg& message) const
{
  SendMsg(shape, message, Message_Warning);
}

inline void ShapeFix_Root::SendWarning(const Message_Msg& message) const
{
  SendWarning(myShape, message);
}

inline void ShapeFix_Root::SendFail(const TopoDS_Shape& shape, const Message_Msg& message) const
{
  SendMsg(shape, message, Message_Fail);
}

inline void ShapeFix_Root::SendFail(const Message_Msg& message) const
{
  SendFail(myShape, message);
}

inline bool ShapeFix_Root::NeedFix(const int Flag, const bool need)
{
  return Flag < 0 ? need : (Flag > 0);
}

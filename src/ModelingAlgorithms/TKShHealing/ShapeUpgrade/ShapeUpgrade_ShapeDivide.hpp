#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDS_Shape.hpp>
#include <Standard_Integer.hpp>
#include <Message_Gravity.hpp>
#include <ShapeExtend_Status.hpp>
class ShapeUpgrade_FaceDivide;
class ShapeBuild_ReShape;
class ShapeExtend_BasicMsgRegistrator;
class Message_Msg;

#ifdef Status
  #undef Status
#endif

class ShapeUpgrade_ShapeDivide
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT ShapeUpgrade_ShapeDivide();

  Standard_EXPORT ShapeUpgrade_ShapeDivide(const TopoDS_Shape& S);

  Standard_EXPORT void Init(const TopoDS_Shape& S);

  Standard_EXPORT virtual ~ShapeUpgrade_ShapeDivide();

  Standard_EXPORT void SetPrecision(const double Prec);

  Standard_EXPORT void SetMaxTolerance(const double maxtol);

  Standard_EXPORT void SetMinTolerance(const double mintol);

  Standard_EXPORT void SetSurfaceSegmentMode(const bool Segment);

  Standard_EXPORT virtual bool Perform(const bool newContext = true);

  Standard_EXPORT TopoDS_Shape Result() const;

  Standard_EXPORT occ::handle<ShapeBuild_ReShape> GetContext() const;

  Standard_EXPORT void SetContext(const occ::handle<ShapeBuild_ReShape>& context);

  Standard_EXPORT virtual void SetMsgRegistrator(
    const occ::handle<ShapeExtend_BasicMsgRegistrator>& msgreg);

  Standard_EXPORT occ::handle<ShapeExtend_BasicMsgRegistrator> MsgRegistrator() const;

  Standard_EXPORT void SendMsg(const TopoDS_Shape&   shape,
                               const Message_Msg&    message,
                               const Message_Gravity gravity = Message_Info) const;

  Standard_EXPORT bool Status(const ShapeExtend_Status status) const;

  Standard_EXPORT void SetSplitFaceTool(const occ::handle<ShapeUpgrade_FaceDivide>& splitFaceTool);

  Standard_EXPORT void SetEdgeMode(const int aEdgeMode);

protected:
  Standard_EXPORT virtual occ::handle<ShapeUpgrade_FaceDivide> GetSplitFaceTool() const;

  Standard_EXPORT virtual Message_Msg GetFaceMsg() const;

  Standard_EXPORT virtual Message_Msg GetWireMsg() const;

  Standard_EXPORT virtual Message_Msg GetEdgeMsg() const;

  occ::handle<ShapeBuild_ReShape>              myContext;
  occ::handle<ShapeExtend_BasicMsgRegistrator> myMsgReg;
  TopoDS_Shape                                 myShape;
  TopoDS_Shape                                 myResult;
  double                                       myPrecision;
  double                                       myMinTol;
  double                                       myMaxTol;
  bool                                         mySegmentMode;
  int                                          myStatus;
  int                                          myEdgeMode;

private:
  occ::handle<ShapeUpgrade_FaceDivide> mySplitFaceTool;
};

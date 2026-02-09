

#include <Message_Msg.hpp>
#include <ShapeBuild_ReShape.hpp>
#include <ShapeFix_Root.hpp>
#include <Standard_Type.hpp>
#include <TopoDS_Shape.hpp>

IMPLEMENT_STANDARD_RTTIEXT(ShapeFix_Root, Standard_Transient)

ShapeFix_Root::ShapeFix_Root()
{
  myPrecision = myMinTol = myMaxTol = Precision::Confusion();
  myMsgReg                          = new ShapeExtend_BasicMsgRegistrator;
}

void ShapeFix_Root::Set(const occ::handle<ShapeFix_Root>& Root)
{
  myContext   = Root->myContext;
  myMsgReg    = Root->myMsgReg;
  myPrecision = Root->myPrecision;
  myMinTol    = Root->myMinTol;
  myMaxTol    = Root->myMaxTol;
  myShape     = Root->myShape;
}

void ShapeFix_Root::SetContext(const occ::handle<ShapeBuild_ReShape>& context)
{
  myContext = context;
}

void ShapeFix_Root::SetMsgRegistrator(const occ::handle<ShapeExtend_BasicMsgRegistrator>& msgreg)
{
  myMsgReg = msgreg;
}

void ShapeFix_Root::SetPrecision(const double preci)
{
  myPrecision = preci;
  if (myMaxTol < myPrecision)
    myMaxTol = myPrecision;
  if (myMinTol > myPrecision)
    myMinTol = myPrecision;
}

void ShapeFix_Root::SetMinTolerance(const double mintol)
{
  myMinTol = mintol;
}

void ShapeFix_Root::SetMaxTolerance(const double maxtol)
{
  myMaxTol = maxtol;
}

void ShapeFix_Root::SendMsg(const TopoDS_Shape&   shape,
                            const Message_Msg&    message,
                            const Message_Gravity gravity) const
{
  if (!myMsgReg.IsNull())
    myMsgReg->Send(shape, message, gravity);
}

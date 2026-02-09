#include <Message_Messenger.hpp>
#include <Standard_Type.hpp>
#include <TFunction_GraphNode.hpp>
#include <XmlMFunction_GraphNodeDriver.hpp>
#include <XmlObjMgt.hpp>
#include <XmlObjMgt_Persistent.hpp>

IMPLEMENT_STANDARD_RTTIEXT(XmlMFunction_GraphNodeDriver, XmlMDF_ADriver)
IMPLEMENT_DOMSTRING(LastPreviousIndex, "lastprev")
IMPLEMENT_DOMSTRING(LastNextIndex, "lastnext")
IMPLEMENT_DOMSTRING(ExecutionStatus, "exec")

XmlMFunction_GraphNodeDriver::XmlMFunction_GraphNodeDriver(
  const occ::handle<Message_Messenger>& theMsgDriver)
    : XmlMDF_ADriver(theMsgDriver, nullptr)
{
}

occ::handle<TDF_Attribute> XmlMFunction_GraphNodeDriver::NewEmpty() const
{
  return (new TFunction_GraphNode());
}

bool XmlMFunction_GraphNodeDriver::Paste(const XmlObjMgt_Persistent&       theSource,
                                         const occ::handle<TDF_Attribute>& theTarget,
                                         XmlObjMgt_RRelocationTable&) const
{
  occ::handle<TFunction_GraphNode> G = occ::down_cast<TFunction_GraphNode>(theTarget);

  int                      aFirstIndPrev, aLastIndPrev, aFirstIndNext, aLastIndNext, aValue, ind;
  const XmlObjMgt_Element& anElement = theSource;

  aFirstIndPrev = 1;

  if (!anElement.getAttribute(::LastPreviousIndex()).GetInteger(aLastIndPrev))
  {
    TCollection_ExtendedString aMessageString =
      TCollection_ExtendedString("Cannot retrieve the last index"
                                 " for previous functions of GraphNode attribute");
    myMessageDriver->Send(aMessageString, Message_Fail);
    return false;
  }

  if (aFirstIndPrev == aLastIndPrev)
  {
    int anInteger;
    if (!XmlObjMgt::GetStringValue(anElement).GetInteger(anInteger))
    {
      TCollection_ExtendedString aMessageString =
        TCollection_ExtendedString("Cannot retrieve integer member"
                                   " for previous functions of GraphNode attribute");
      myMessageDriver->Send(aMessageString, Message_Fail);
      return false;
    }
    G->AddPrevious(anInteger);
  }
  else
  {
    const char* aValueStr =
      static_cast<const char*>(XmlObjMgt::GetStringValue(anElement).GetString());

    for (ind = aFirstIndPrev; ind <= aLastIndPrev; ind++)
    {
      if (!XmlObjMgt::GetInteger(aValueStr, aValue))
      {
        TCollection_ExtendedString aMessageString =
          TCollection_ExtendedString("Cannot retrieve integer member"
                                     " for previous functions of GraphNode attribute as \"")
          + aValueStr + "\"";
        myMessageDriver->Send(aMessageString, Message_Fail);
        return false;
      }
      G->AddPrevious(aValue);
    }
  }

  aFirstIndNext = aLastIndPrev + 1;

  if (!anElement.getAttribute(::LastNextIndex()).GetInteger(aLastIndNext))
  {
    TCollection_ExtendedString aMessageString =
      TCollection_ExtendedString("Cannot retrieve the last index"
                                 " for next functions of GraphNode attribute");
    myMessageDriver->Send(aMessageString, Message_Fail);
    return false;
  }
  aLastIndNext += aLastIndPrev;

  const char* aValueStr =
    static_cast<const char*>(XmlObjMgt::GetStringValue(anElement).GetString());

  for (ind = 1; ind <= aLastIndNext; ind++)
  {
    if (!XmlObjMgt::GetInteger(aValueStr, aValue))
    {
      TCollection_ExtendedString aMessageString =
        TCollection_ExtendedString("Cannot retrieve integer member"
                                   " for next functions of GraphNode attribute as \"")
        + aValueStr + "\"";
      myMessageDriver->Send(aMessageString, Message_Fail);
      return false;
    }
    if (ind < aFirstIndNext)
      continue;
    G->AddNext(aValue);
  }

  int exec = 0;
  if (!anElement.getAttribute(::ExecutionStatus()).GetInteger(exec))
  {
    TCollection_ExtendedString aMessageString =
      TCollection_ExtendedString("Cannot retrieve the execution status"
                                 " for GraphNode attribute");
    myMessageDriver->Send(aMessageString, Message_Fail);
    return false;
  }
  G->SetStatus((TFunction_ExecutionStatus)exec);

  return true;
}

void XmlMFunction_GraphNodeDriver::Paste(const occ::handle<TDF_Attribute>& theSource,
                                         XmlObjMgt_Persistent&             theTarget,
                                         XmlObjMgt_SRelocationTable&) const
{
  occ::handle<TFunction_GraphNode> G = occ::down_cast<TFunction_GraphNode>(theSource);

  theTarget.Element().setAttribute(::LastPreviousIndex(), G->GetPrevious().Extent());

  TCollection_AsciiString        aValueStr;
  NCollection_Map<int>::Iterator itrm(G->GetPrevious());
  for (; itrm.More(); itrm.Next())
  {
    const int ID = itrm.Key();
    aValueStr += TCollection_AsciiString(ID);
    aValueStr += ' ';
  }

  aValueStr += "   ";

  theTarget.Element().setAttribute(::LastNextIndex(), G->GetNext().Extent());

  itrm.Initialize(G->GetNext());
  for (; itrm.More(); itrm.Next())
  {
    const int ID = itrm.Key();
    aValueStr += TCollection_AsciiString(ID);
    aValueStr += ' ';
  }

  XmlObjMgt::SetStringValue(theTarget, aValueStr.ToCString(), true);

  theTarget.Element().setAttribute(::ExecutionStatus(), (int)G->GetStatus());
}

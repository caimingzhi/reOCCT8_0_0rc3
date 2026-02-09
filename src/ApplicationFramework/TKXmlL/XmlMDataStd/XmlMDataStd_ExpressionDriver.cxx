#include <Message_Messenger.hpp>
#include <Standard_Type.hpp>
#include <TDataStd_Expression.hpp>
#include <TDataStd_Variable.hpp>
#include <TDF_Attribute.hpp>
#include <NCollection_List.hpp>
#include <XmlMDataStd_ExpressionDriver.hpp>
#include <XmlObjMgt.hpp>
#include <XmlObjMgt_Persistent.hpp>

IMPLEMENT_STANDARD_RTTIEXT(XmlMDataStd_ExpressionDriver, XmlMDF_ADriver)
IMPLEMENT_DOMSTRING(VariablesString, "variables")

XmlMDataStd_ExpressionDriver::XmlMDataStd_ExpressionDriver(
  const occ::handle<Message_Messenger>& theMsgDriver)
    : XmlMDF_ADriver(theMsgDriver, nullptr)
{
}

occ::handle<TDF_Attribute> XmlMDataStd_ExpressionDriver::NewEmpty() const
{
  return (new TDataStd_Expression());
}

bool XmlMDataStd_ExpressionDriver::Paste(const XmlObjMgt_Persistent&       theSource,
                                         const occ::handle<TDF_Attribute>& theTarget,
                                         XmlObjMgt_RRelocationTable&       theRelocTable) const
{
  occ::handle<TDataStd_Expression> aC     = occ::down_cast<TDataStd_Expression>(theTarget);
  const XmlObjMgt_Element&         anElem = theSource;

  int                        aNb;
  TCollection_ExtendedString aMsgString;

  TCollection_ExtendedString aString;
  if (!XmlObjMgt::GetExtendedString(theSource, aString))
  {
    myMessageDriver->Send("error retrieving ExtendedString for type TDataStd_Expression",
                          Message_Fail);
    return false;
  }
  aC->SetExpression(aString);

  XmlObjMgt_DOMString aDOMStr = anElem.getAttribute(::VariablesString());
  if (aDOMStr != nullptr)
  {
    const char* aVs = static_cast<const char*>(aDOMStr.GetString());

    if (!XmlObjMgt::GetInteger(aVs, aNb))
    {
      aMsgString =
        TCollection_ExtendedString(
          "XmlMDataStd_ExpressionDriver: Cannot retrieve reference on first variable from \"")
        + aDOMStr + "\"";
      myMessageDriver->Send(aMsgString, Message_Fail);
      return false;
    }
    while (aNb > 0)
    {
      occ::handle<TDF_Attribute> aV;
      if (theRelocTable.IsBound(aNb))
        aV = occ::down_cast<TDataStd_Variable>(theRelocTable.Find(aNb));
      else
      {
        aV = new TDataStd_Variable;
        theRelocTable.Bind(aNb, aV);
      }
      aC->GetVariables().Append(aV);

      if (!XmlObjMgt::GetInteger(aVs, aNb))
        aNb = 0;
    }
  }

  return true;
}

void XmlMDataStd_ExpressionDriver::Paste(const occ::handle<TDF_Attribute>& theSource,
                                         XmlObjMgt_Persistent&             theTarget,
                                         XmlObjMgt_SRelocationTable&       theRelocTable) const
{
  occ::handle<TDataStd_Expression> aC     = occ::down_cast<TDataStd_Expression>(theSource);
  XmlObjMgt_Element&               anElem = theTarget;

  int                        aNb;
  occ::handle<TDF_Attribute> TV;

  XmlObjMgt::SetExtendedString(theTarget, aC->Name());

  int nbvar = aC->GetVariables().Extent();
  if (nbvar >= 1)
  {
    TCollection_AsciiString                                aGsStr;
    NCollection_List<occ::handle<TDF_Attribute>>::Iterator it;
    for (it.Initialize(aC->GetVariables()); it.More(); it.Next())
    {
      TV = it.Value();
      if (!TV.IsNull())
      {
        aNb = theRelocTable.FindIndex(TV);
        if (aNb == 0)
        {
          aNb = theRelocTable.Add(TV);
        }
        aGsStr += TCollection_AsciiString(aNb) + " ";
      }
      else
        aGsStr += "0 ";
    }
    anElem.setAttribute(::VariablesString(), aGsStr.ToCString());
  }
}



#include <MoniTool_AttrList.hpp>
#include <MoniTool_IntVal.hpp>
#include <MoniTool_RealVal.hpp>
#include <Standard_Transient.hpp>
#include <TCollection_HAsciiString.hpp>

MoniTool_AttrList::MoniTool_AttrList() = default;

MoniTool_AttrList::MoniTool_AttrList(const MoniTool_AttrList& other)
    : theattrib(other.AttrList())
{
}

void MoniTool_AttrList::SetAttribute(const char* name, const occ::handle<Standard_Transient>& val)
{
  theattrib.Bind(name, val);
}

bool MoniTool_AttrList::RemoveAttribute(const char* name)
{
  if (theattrib.IsEmpty())
    return false;
  return theattrib.UnBind(name);
}

bool MoniTool_AttrList::GetAttribute(const char*                       name,
                                     const occ::handle<Standard_Type>& type,
                                     occ::handle<Standard_Transient>&  val) const
{
  if (theattrib.IsEmpty())
  {
    val.Nullify();
    return false;
  }
  if (!theattrib.Find(name, val))
  {
    val.Nullify();
    return false;
  }
  if (!val->IsKind(type))
  {
    val.Nullify();
    return false;
  }
  return true;
}

occ::handle<Standard_Transient> MoniTool_AttrList::Attribute(const char* name) const
{
  occ::handle<Standard_Transient> atr;
  if (theattrib.IsEmpty())
    return atr;
  if (!theattrib.Find(name, atr))
    atr.Nullify();
  return atr;
}

MoniTool_ValueType MoniTool_AttrList::AttributeType(const char* name) const
{
  occ::handle<Standard_Transient> atr = Attribute(name);
  if (atr.IsNull())
    return MoniTool_ValueVoid;
  if (atr->DynamicType() == STANDARD_TYPE(MoniTool_IntVal))
    return MoniTool_ValueInteger;
  if (atr->DynamicType() == STANDARD_TYPE(MoniTool_RealVal))
    return MoniTool_ValueReal;
  if (atr->DynamicType() == STANDARD_TYPE(TCollection_HAsciiString))
    return MoniTool_ValueText;
  return MoniTool_ValueIdent;
}

void MoniTool_AttrList::SetIntegerAttribute(const char* name, const int val)
{
  occ::handle<MoniTool_IntVal> ival = new MoniTool_IntVal;
  ival->CValue()                    = val;
  SetAttribute(name, ival);
}

bool MoniTool_AttrList::GetIntegerAttribute(const char* name, int& val) const
{
  occ::handle<MoniTool_IntVal> ival = occ::down_cast<MoniTool_IntVal>(Attribute(name));
  if (ival.IsNull())
  {
    val = 0;
    return false;
  }
  val = ival->Value();
  return true;
}

int MoniTool_AttrList::IntegerAttribute(const char* name) const
{
  occ::handle<MoniTool_IntVal> ival = occ::down_cast<MoniTool_IntVal>(Attribute(name));
  if (ival.IsNull())
    return 0;
  return ival->Value();
}

void MoniTool_AttrList::SetRealAttribute(const char* name, const double val)
{
  occ::handle<MoniTool_RealVal> rval = new MoniTool_RealVal;
  rval->CValue()                     = val;
  SetAttribute(name, rval);
}

bool MoniTool_AttrList::GetRealAttribute(const char* name, double& val) const
{
  occ::handle<MoniTool_RealVal> rval = occ::down_cast<MoniTool_RealVal>(Attribute(name));
  if (rval.IsNull())
  {
    val = 0.0;
    return false;
  }
  val = rval->Value();
  return true;
}

double MoniTool_AttrList::RealAttribute(const char* name) const
{
  occ::handle<MoniTool_RealVal> rval = occ::down_cast<MoniTool_RealVal>(Attribute(name));
  if (rval.IsNull())
    return 0;
  return rval->Value();
}

void MoniTool_AttrList::SetStringAttribute(const char* name, const char* val)
{
  occ::handle<TCollection_HAsciiString> hval = new TCollection_HAsciiString(val);
  SetAttribute(name, hval);
}

bool MoniTool_AttrList::GetStringAttribute(const char* name, const char*& val) const
{
  occ::handle<TCollection_HAsciiString> hval =
    occ::down_cast<TCollection_HAsciiString>(Attribute(name));
  if (hval.IsNull())
  {
    val = "";
    return false;
  }
  val = hval->ToCString();
  return true;
}

const char* MoniTool_AttrList::StringAttribute(const char* name) const
{
  occ::handle<TCollection_HAsciiString> hval =
    occ::down_cast<TCollection_HAsciiString>(Attribute(name));
  if (hval.IsNull())
    return "";
  return hval->ToCString();
}

const NCollection_DataMap<TCollection_AsciiString, occ::handle<Standard_Transient>>&
  MoniTool_AttrList::AttrList() const
{
  return theattrib;
}

void MoniTool_AttrList::SameAttributes(const MoniTool_AttrList& other)
{
  theattrib = other.AttrList();
}

void MoniTool_AttrList::GetAttributes(const MoniTool_AttrList& other,
                                      const char*              fromname,
                                      const bool               copied)
{
  const NCollection_DataMap<TCollection_AsciiString, occ::handle<Standard_Transient>>& list =
    other.AttrList();
  if (list.IsEmpty())
    return;

  NCollection_DataMap<TCollection_AsciiString, occ::handle<Standard_Transient>>::Iterator iter(
    list);
  for (; iter.More(); iter.Next())
  {
    const TCollection_AsciiString& name = iter.Key();
    if (!name.StartsWith(fromname))
      continue;
    const occ::handle<Standard_Transient>& atr    = iter.Value();
    occ::handle<Standard_Transient>        newatr = atr;

    if (copied)
    {
      occ::handle<MoniTool_IntVal> ival = occ::down_cast<MoniTool_IntVal>(atr);
      if (!ival.IsNull())
      {
        int intval     = ival->Value();
        ival           = new MoniTool_IntVal;
        ival->CValue() = intval;
        newatr         = ival;
      }
      occ::handle<MoniTool_RealVal> rval = occ::down_cast<MoniTool_RealVal>(atr);
      if (!rval.IsNull())
      {
        double realval = rval->Value();
        rval           = new MoniTool_RealVal;
        rval->CValue() = realval;
        newatr         = rval;
      }
      occ::handle<TCollection_HAsciiString> hval = occ::down_cast<TCollection_HAsciiString>(atr);
      if (!hval.IsNull())
      {
        occ::handle<TCollection_HAsciiString> strval =
          new TCollection_HAsciiString(hval->ToCString());
        newatr = strval;
      }
    }
    theattrib.Bind(name, newatr);
  }
}

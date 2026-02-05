#include <XCAFDoc_Area.hpp>

#include <Standard_Dump.hpp>
#include <Standard_GUID.hpp>
#include <Standard_Type.hpp>
#include <TDF_Attribute.hpp>
#include <TDF_Label.hpp>
#include <TDF_RelocationTable.hpp>

IMPLEMENT_DERIVED_ATTRIBUTE_WITH_TYPE(XCAFDoc_Area, TDataStd_Real, "xcaf", "Area")

//=================================================================================================

XCAFDoc_Area::XCAFDoc_Area() = default;

//=================================================================================================

const Standard_GUID& XCAFDoc_Area::GetID()
{
  static Standard_GUID AreaID("efd212f2-6dfd-11d4-b9c8-0060b0ee281b");
  return AreaID;
}

//=================================================================================================

const Standard_GUID& XCAFDoc_Area::ID() const
{
  return GetID();
}

//=================================================================================================

occ::handle<XCAFDoc_Area> XCAFDoc_Area::Set(const TDF_Label& L, const double V)
{
  occ::handle<XCAFDoc_Area> A;
  if (!L.FindAttribute(XCAFDoc_Area::GetID(), A))
  {
    A = new XCAFDoc_Area;
    L.AddAttribute(A);
  }
  A->Set(V);
  return A;
}

//=================================================================================================

void XCAFDoc_Area::Set(const double V)
{
  TDataStd_Real::Set(V);
}

//=================================================================================================

double XCAFDoc_Area::Get() const
{
  return TDataStd_Real::Get();
}

//=================================================================================================

bool XCAFDoc_Area::Get(const TDF_Label& label, double& area)
{
  occ::handle<XCAFDoc_Area> anArea;
  if (!label.FindAttribute(XCAFDoc_Area::GetID(), anArea))
    return false;

  area = anArea->Get();
  return true;
}

//=================================================================================================

Standard_OStream& XCAFDoc_Area::Dump(Standard_OStream& anOS) const
{
  anOS << "Area ";
  anOS << Get();
  return anOS;
}

//=================================================================================================

void XCAFDoc_Area::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)

  OCCT_DUMP_BASE_CLASS(theOStream, theDepth, TDF_Attribute)

  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myValue)
}

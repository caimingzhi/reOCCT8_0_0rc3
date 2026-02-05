#include <XCAFDoc_Volume.hpp>

#include <Standard_Dump.hpp>
#include <Standard_GUID.hpp>
#include <Standard_Type.hpp>
#include <TDF_Attribute.hpp>
#include <TDF_Label.hpp>
#include <TDF_RelocationTable.hpp>

IMPLEMENT_DERIVED_ATTRIBUTE_WITH_TYPE(XCAFDoc_Volume, TDataStd_Real, "xcaf", "Volume")

//=================================================================================================

XCAFDoc_Volume::XCAFDoc_Volume() = default;

//=================================================================================================

const Standard_GUID& XCAFDoc_Volume::GetID()
{
  static Standard_GUID VolumeID("efd212f1-6dfd-11d4-b9c8-0060b0ee281b");
  return VolumeID;
}

//=================================================================================================

const Standard_GUID& XCAFDoc_Volume::ID() const
{
  return GetID();
}

//=================================================================================================

occ::handle<XCAFDoc_Volume> XCAFDoc_Volume::Set(const TDF_Label& L, const double V)
{
  occ::handle<XCAFDoc_Volume> A;
  if (!L.FindAttribute(XCAFDoc_Volume::GetID(), A))
  {
    A = new XCAFDoc_Volume;
    L.AddAttribute(A);
  }
  A->Set(V);
  return A;
}

//=================================================================================================

void XCAFDoc_Volume::Set(const double V)
{
  TDataStd_Real::Set(V);
}

//=================================================================================================

double XCAFDoc_Volume::Get() const
{
  return TDataStd_Real::Get();
}

//=================================================================================================

bool XCAFDoc_Volume::Get(const TDF_Label& label, double& vol)
{
  occ::handle<XCAFDoc_Volume> aVolume;
  if (!label.FindAttribute(XCAFDoc_Volume::GetID(), aVolume))
    return false;

  vol = aVolume->Get();
  return true;
}

//=================================================================================================

Standard_OStream& XCAFDoc_Volume::Dump(Standard_OStream& anOS) const
{
  anOS << "Volume ";
  anOS << Get();
  return anOS;
}

//=================================================================================================

void XCAFDoc_Volume::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)

  OCCT_DUMP_BASE_CLASS(theOStream, theDepth, TDF_Attribute)

  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myValue)
}

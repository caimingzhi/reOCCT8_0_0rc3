#include <Standard_GUID.hpp>
#include <Standard_Type.hpp>
#include <TDataXtd_Placement.hpp>
#include <TDF_Attribute.hpp>
#include <TDF_Label.hpp>
#include <TDF_RelocationTable.hpp>

IMPLEMENT_DERIVED_ATTRIBUTE(TDataXtd_Placement, TDataStd_GenericEmpty)

const Standard_GUID& TDataXtd_Placement::GetID()
{
  static Standard_GUID TDataXtd_PlacementID("2a96b60b-ec8b-11d0-bee7-080009dc3333");
  return TDataXtd_PlacementID;
}

occ::handle<TDataXtd_Placement> TDataXtd_Placement::Set(const TDF_Label& L)
{
  occ::handle<TDataXtd_Placement> A;
  if (!L.FindAttribute(TDataXtd_Placement::GetID(), A))
  {
    A = new TDataXtd_Placement();
    L.AddAttribute(A);
  }
  return A;
}

TDataXtd_Placement::TDataXtd_Placement() = default;

const Standard_GUID& TDataXtd_Placement::ID() const
{
  return GetID();
}

Standard_OStream& TDataXtd_Placement::Dump(Standard_OStream& anOS) const
{
  anOS << "Placement";
  return anOS;
}

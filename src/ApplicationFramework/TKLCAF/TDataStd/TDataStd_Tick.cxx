#include <TDataStd_Tick.hpp>

#include <TDF_Label.hpp>
#include <Standard_GUID.hpp>

IMPLEMENT_DERIVED_ATTRIBUTE(TDataStd_Tick, TDataStd_GenericEmpty)

const Standard_GUID& TDataStd_Tick::GetID()
{
  static Standard_GUID TDataStd_TickID("40DC60CD-30B9-41be-B002-4169EFB34EA5");
  return TDataStd_TickID;
}

occ::handle<TDataStd_Tick> TDataStd_Tick::Set(const TDF_Label& L)
{
  occ::handle<TDataStd_Tick> A;
  if (!L.FindAttribute(TDataStd_Tick::GetID(), A))
  {
    A = new TDataStd_Tick();
    L.AddAttribute(A);
  }
  return A;
}

TDataStd_Tick::TDataStd_Tick() = default;

const Standard_GUID& TDataStd_Tick::ID() const
{
  return GetID();
}

Standard_OStream& TDataStd_Tick::Dump(Standard_OStream& anOS) const
{
  anOS << "Tick";
  return anOS;
}

#include <Standard_GUID.hpp>
#include <Standard_Type.hpp>
#include <TDataXtd_Pattern.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TDataXtd_Pattern, TDF_Attribute)

const Standard_GUID& TDataXtd_Pattern::GetID()
{
  static Standard_GUID myID("2a96b618-ec8b-11d0-bee7-080009dc3333");
  return myID;
}

const Standard_GUID& TDataXtd_Pattern::ID() const
{
  return GetID();
}

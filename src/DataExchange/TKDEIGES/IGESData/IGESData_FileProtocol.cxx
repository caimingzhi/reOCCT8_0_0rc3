

#include <IGESData_FileProtocol.hpp>
#include <IGESData_Protocol.hpp>
#include <Interface_Protocol.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESData_FileProtocol, IGESData_Protocol)

IGESData_FileProtocol::IGESData_FileProtocol() = default;

void IGESData_FileProtocol::Add(const occ::handle<IGESData_Protocol>& protocol)
{
  if (theresource.IsNull())
    theresource = protocol;
  else if (theresource->IsInstance(protocol->DynamicType()))
    return;
  else if (!thenext.IsNull())
    thenext->Add(protocol);
  else
  {
    thenext = new IGESData_FileProtocol;
    thenext->Add(protocol);
  }
}

int IGESData_FileProtocol::NbResources() const
{
  int nb = (theresource.IsNull() ? 0 : 1);
  if (!thenext.IsNull())
    nb += thenext->NbResources();
  return nb;
}

occ::handle<Interface_Protocol> IGESData_FileProtocol::Resource(const int num) const
{
  occ::handle<IGESData_Protocol> res;
  if (num == 1)
    return occ::handle<Interface_Protocol>(theresource);
  else if (!thenext.IsNull())
    return thenext->Resource(num - 1);
  return res;
}

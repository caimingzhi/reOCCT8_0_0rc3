

#include <Interface_Check.hpp>
#include <Interface_Graph.hpp>
#include <Standard_Type.hpp>
#include <StepData_FileProtocol.hpp>
#include <StepData_Protocol.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepData_FileProtocol, StepData_Protocol)

static const char* thename = "";

StepData_FileProtocol::StepData_FileProtocol() = default;

void StepData_FileProtocol::Add(const occ::handle<StepData_Protocol>& protocol)
{

  if (protocol.IsNull())
    return;
  occ::handle<Standard_Type> ptype = protocol->DynamicType();
  int                        nb    = thecomps.Length();

  for (int i = 1; i <= nb; i++)
  {
    if (thecomps.Value(i)->IsInstance(ptype))
      return;
  }
  thecomps.Append(protocol);
}

int StepData_FileProtocol::NbResources() const
{

  return thecomps.Length();
}

occ::handle<Interface_Protocol> StepData_FileProtocol::Resource(const int num) const
{
  return occ::down_cast<Interface_Protocol>(thecomps.Value(num));
}

int StepData_FileProtocol::TypeNumber(const occ::handle<Standard_Type>&) const
{

  return 0;
}

bool StepData_FileProtocol::GlobalCheck(const Interface_Graph&        G,
                                        occ::handle<Interface_Check>& ach) const
{

  bool res = false;
  int  i, nb = NbResources();
  for (i = 1; i <= nb; i++)
    res |= Resource(i)->GlobalCheck(G, ach);
  return res;
}

const char* StepData_FileProtocol::SchemaName(const occ::handle<Interface_InterfaceModel>&) const
{
  return thename;
}

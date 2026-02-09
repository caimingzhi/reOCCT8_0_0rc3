

#include <Interface_Check.hpp>
#include <Interface_Graph.hpp>
#include <Interface_InterfaceModel.hpp>
#include <Interface_Protocol.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Interface_Protocol, Standard_Transient)

static occ::handle<Interface_Protocol>& theactive()
{
  static occ::handle<Interface_Protocol> theact;
  return theact;
}

occ::handle<Interface_Protocol> Interface_Protocol::Active()
{
  return theactive();
}

void Interface_Protocol::SetActive(const occ::handle<Interface_Protocol>& aprotocol)
{
  theactive() = aprotocol;
}

void Interface_Protocol::ClearActive()
{
  theactive().Nullify();
}

int Interface_Protocol::CaseNumber(const occ::handle<Standard_Transient>& obj) const
{
  if (obj.IsNull())
    return 0;
  return TypeNumber(Type(obj));
}

bool Interface_Protocol::IsDynamicType(const occ::handle<Standard_Transient>&) const
{
  return true;
}

int Interface_Protocol::NbTypes(const occ::handle<Standard_Transient>&) const
{
  return 1;
}

occ::handle<Standard_Type> Interface_Protocol::Type(const occ::handle<Standard_Transient>& obj,
                                                    const int) const
{
  if (obj.IsNull())
    return STANDARD_TYPE(Standard_Transient);
  return obj->DynamicType();
}

bool Interface_Protocol::GlobalCheck(const Interface_Graph&, occ::handle<Interface_Check>&) const
{
  return true;
}

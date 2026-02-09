

#include <HeaderSection_FileDescription.hpp>
#include <HeaderSection_FileName.hpp>
#include <HeaderSection_FileSchema.hpp>
#include <HeaderSection_Protocol.hpp>
#include <Standard_Type.hpp>
#include <StepData_UndefinedEntity.hpp>

IMPLEMENT_STANDARD_RTTIEXT(HeaderSection_Protocol, StepData_Protocol)

static const char* schemaName = "header_section";

HeaderSection_Protocol::HeaderSection_Protocol() = default;

int HeaderSection_Protocol::TypeNumber(const occ::handle<Standard_Type>& atype) const
{
  if (atype == STANDARD_TYPE(HeaderSection_FileName))
    return 1;
  else if (atype == STANDARD_TYPE(HeaderSection_FileDescription))
    return 2;
  else if (atype == STANDARD_TYPE(HeaderSection_FileSchema))
    return 3;
  else if (atype == STANDARD_TYPE(StepData_UndefinedEntity))
    return 4;
  else
    return 0;
}

const char* HeaderSection_Protocol::SchemaName(const occ::handle<Interface_InterfaceModel>&) const
{
  return schemaName;
}

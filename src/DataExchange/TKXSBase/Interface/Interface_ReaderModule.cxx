

#include <Interface_Check.hpp>
#include <Interface_FileReaderData.hpp>
#include <Interface_ReaderModule.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Interface_ReaderModule, Standard_Transient)

bool Interface_ReaderModule::NewRead(const int,
                                     const occ::handle<Interface_FileReaderData>&,
                                     const int,
                                     occ::handle<Interface_Check>&,
                                     occ::handle<Standard_Transient>&) const
{
  return false;
}

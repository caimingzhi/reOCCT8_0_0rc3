

#include <IGESData_IGESReaderData.hpp>
#include <IGESData_IGESType.hpp>
#include <IGESData_IGESWriter.hpp>
#include <IGESData_ReadWriteModule.hpp>
#include <Interface_Check.hpp>
#include <Interface_FileReaderData.hpp>
#include <MoniTool_Macros.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESData_ReadWriteModule, Interface_ReaderModule)

int IGESData_ReadWriteModule::CaseNum(const occ::handle<Interface_FileReaderData>& data,
                                      const int                                    num) const
{
  IGESData_IGESType DT = GetCasted(IGESData_IGESReaderData, data)->DirType(num);
  return CaseIGES(DT.Type(), DT.Form());
}

void IGESData_ReadWriteModule::Read(const int,
                                    const occ::handle<Interface_FileReaderData>&,
                                    const int,
                                    occ::handle<Interface_Check>&,
                                    const occ::handle<Standard_Transient>&) const
{
#ifdef OCCT_DEBUG
  std::cout << "IGESData_ReadWriteModule, Read called" << std::endl;
#endif
}

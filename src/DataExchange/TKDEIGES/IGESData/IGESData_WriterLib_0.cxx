#include <IGESData_WriterLib.hpp>

#include <IGESData_NodeOfWriterLib.hpp>
#include <Standard_NoSuchObject.hpp>
#include <IGESData_IGESEntity.hpp>
#include <IGESData_ReadWriteModule.hpp>
#include <IGESData_Protocol.hpp>
#include <IGESData_GlobalNodeOfWriterLib.hpp>
#include <Standard_Transient.hpp>

#define TheObject occ::handle<IGESData_IGESEntity>
#define TheObject_hxx <IGESData_IGESEntity.hpp>
#define Handle_TheModule occ::handle<IGESData_ReadWriteModule>
#define TheModule IGESData_ReadWriteModule
#define TheModule_hxx <IGESData_ReadWriteModule.hpp>
#define Handle_TheProtocol occ::handle<IGESData_Protocol>
#define TheProtocol IGESData_Protocol
#define TheProtocol_hxx <IGESData_Protocol.hpp>
#define LibCtl_GlobalNode IGESData_GlobalNodeOfWriterLib
#define LibCtl_GlobalNode_hxx <IGESData_GlobalNodeOfWriterLib.hpp>
#define LibCtl_Node IGESData_NodeOfWriterLib
#define LibCtl_Node_hxx <IGESData_NodeOfWriterLib.hpp>
#define Handle_LibCtl_GlobalNode occ::handle<IGESData_GlobalNodeOfWriterLib>
#define Handle_LibCtl_Node occ::handle<IGESData_NodeOfWriterLib>
#define LibCtl_Library IGESData_WriterLib
#define LibCtl_Library_hxx <IGESData_WriterLib.hpp>
#include <LibCtl_Library.hpp>

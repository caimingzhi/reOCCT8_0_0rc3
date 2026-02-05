#include <StepData_WriterLib.hpp>

#include <StepData_NodeOfWriterLib.hpp>
#include <Standard_NoSuchObject.hpp>
#include <Standard_Transient.hpp>
#include <StepData_ReadWriteModule.hpp>
#include <StepData_Protocol.hpp>
#include <StepData_GlobalNodeOfWriterLib.hpp>

#define TheObject occ::handle<Standard_Transient>
#define TheObject_hxx <Standard_Transient.hpp>
#define Handle_TheModule occ::handle<StepData_ReadWriteModule>
#define TheModule StepData_ReadWriteModule
#define TheModule_hxx <StepData_ReadWriteModule.hpp>
#define Handle_TheProtocol occ::handle<StepData_Protocol>
#define TheProtocol StepData_Protocol
#define TheProtocol_hxx <StepData_Protocol.hpp>
#define LibCtl_GlobalNode StepData_GlobalNodeOfWriterLib
#define LibCtl_GlobalNode_hxx <StepData_GlobalNodeOfWriterLib.hpp>
#define LibCtl_Node StepData_NodeOfWriterLib
#define LibCtl_Node_hxx <StepData_NodeOfWriterLib.hpp>
#define Handle_LibCtl_GlobalNode occ::handle<StepData_GlobalNodeOfWriterLib>
#define Handle_LibCtl_Node occ::handle<StepData_NodeOfWriterLib>
#define LibCtl_Library StepData_WriterLib
#define LibCtl_Library_hxx <StepData_WriterLib.hpp>
#include <LibCtl_Library.hpp>

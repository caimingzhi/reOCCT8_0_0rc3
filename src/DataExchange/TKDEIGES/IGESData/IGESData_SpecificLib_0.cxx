#include <IGESData_SpecificLib.hpp>

#include <IGESData_NodeOfSpecificLib.hpp>
#include <Standard_NoSuchObject.hpp>
#include <IGESData_IGESEntity.hpp>
#include <IGESData_SpecificModule.hpp>
#include <IGESData_Protocol.hpp>
#include <IGESData_GlobalNodeOfSpecificLib.hpp>
#include <Standard_Transient.hpp>

#define TheObject occ::handle<IGESData_IGESEntity>
#define TheObject_hxx <IGESData_IGESEntity.hpp>
#define Handle_TheModule occ::handle<IGESData_SpecificModule>
#define TheModule IGESData_SpecificModule
#define TheModule_hxx <IGESData_SpecificModule.hpp>
#define Handle_TheProtocol occ::handle<IGESData_Protocol>
#define TheProtocol IGESData_Protocol
#define TheProtocol_hxx <IGESData_Protocol.hpp>
#define LibCtl_GlobalNode IGESData_GlobalNodeOfSpecificLib
#define LibCtl_GlobalNode_hxx <IGESData_GlobalNodeOfSpecificLib.hpp>
#define LibCtl_Node IGESData_NodeOfSpecificLib
#define LibCtl_Node_hxx <IGESData_NodeOfSpecificLib.hpp>
#define Handle_LibCtl_GlobalNode occ::handle<IGESData_GlobalNodeOfSpecificLib>
#define Handle_LibCtl_Node occ::handle<IGESData_NodeOfSpecificLib>
#define LibCtl_Library IGESData_SpecificLib
#define LibCtl_Library_hxx <IGESData_SpecificLib.hpp>
#include <LibCtl_Library.hpp>

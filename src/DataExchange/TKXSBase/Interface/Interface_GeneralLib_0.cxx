#include <Interface_GeneralLib.hpp>

#include <Interface_NodeOfGeneralLib.hpp>
#include <Standard_NoSuchObject.hpp>
#include <Standard_Transient.hpp>
#include <Interface_GeneralModule.hpp>
#include <Interface_Protocol.hpp>
#include <Interface_GlobalNodeOfGeneralLib.hpp>

#define TheObject occ::handle<Standard_Transient>
#define TheObject_hxx <Standard_Transient.hpp>
#define Handle_TheModule occ::handle<Interface_GeneralModule>
#define TheModule Interface_GeneralModule
#define TheModule_hxx <Interface_GeneralModule.hpp>
#define Handle_TheProtocol occ::handle<Interface_Protocol>
#define TheProtocol Interface_Protocol
#define TheProtocol_hxx <Interface_Protocol.hpp>
#define LibCtl_GlobalNode Interface_GlobalNodeOfGeneralLib
#define LibCtl_GlobalNode_hxx <Interface_GlobalNodeOfGeneralLib.hpp>
#define LibCtl_Node Interface_NodeOfGeneralLib
#define LibCtl_Node_hxx <Interface_NodeOfGeneralLib.hpp>
#define Handle_LibCtl_GlobalNode occ::handle<Interface_GlobalNodeOfGeneralLib>
#define Handle_LibCtl_Node occ::handle<Interface_NodeOfGeneralLib>
#define LibCtl_Library Interface_GeneralLib
#define LibCtl_Library_hxx <Interface_GeneralLib.hpp>
#include <LibCtl_Library.hpp>

#include <Interface_ReaderLib.hpp>

#include <Interface_NodeOfReaderLib.hpp>
#include <Standard_NoSuchObject.hpp>
#include <Standard_Transient.hpp>
#include <Interface_ReaderModule.hpp>
#include <Interface_Protocol.hpp>
#include <Interface_GlobalNodeOfReaderLib.hpp>

#define TheObject occ::handle<Standard_Transient>
#define TheObject_hxx <Standard_Transient.hpp>
#define Handle_TheModule occ::handle<Interface_ReaderModule>
#define TheModule Interface_ReaderModule
#define TheModule_hxx <Interface_ReaderModule.hpp>
#define Handle_TheProtocol occ::handle<Interface_Protocol>
#define TheProtocol Interface_Protocol
#define TheProtocol_hxx <Interface_Protocol.hpp>
#define LibCtl_GlobalNode Interface_GlobalNodeOfReaderLib
#define LibCtl_GlobalNode_hxx <Interface_GlobalNodeOfReaderLib.hpp>
#define LibCtl_Node Interface_NodeOfReaderLib
#define LibCtl_Node_hxx <Interface_NodeOfReaderLib.hpp>
#define Handle_LibCtl_GlobalNode occ::handle<Interface_GlobalNodeOfReaderLib>
#define Handle_LibCtl_Node occ::handle<Interface_NodeOfReaderLib>
#define LibCtl_Library Interface_ReaderLib
#define LibCtl_Library_hxx <Interface_ReaderLib.hpp>
#include <LibCtl_Library.hpp>

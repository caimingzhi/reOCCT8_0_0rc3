#include <Graphic3d_DataStructureManager.hpp>
#include <Standard_Dump.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Graphic3d_DataStructureManager, Standard_Transient)

//-Aliases
//-Global data definitions
//-Constructors
Graphic3d_DataStructureManager::Graphic3d_DataStructureManager() = default;

//=================================================================================================

void Graphic3d_DataStructureManager::DumpJson(Standard_OStream& theOStream, int) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)
}

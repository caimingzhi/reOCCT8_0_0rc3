#include <BRepMesh_DiscretRoot.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BRepMesh_DiscretRoot, Standard_Transient)

//=================================================================================================

BRepMesh_DiscretRoot::BRepMesh_DiscretRoot()
    : myIsDone(false)
{
}

//=================================================================================================

BRepMesh_DiscretRoot::~BRepMesh_DiscretRoot() = default;

//=================================================================================================

void BRepMesh_DiscretRoot::init() {}

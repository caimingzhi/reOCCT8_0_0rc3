#include <MeshVS_SensitiveSegment.hpp>

IMPLEMENT_STANDARD_RTTIEXT(MeshVS_SensitiveSegment, Select3D_SensitiveSegment)

MeshVS_SensitiveSegment::MeshVS_SensitiveSegment(
  const occ::handle<SelectMgr_EntityOwner>& theOwnerId,
  const gp_Pnt&                             theFirstPnt,
  const gp_Pnt&                             theLastPnt)
    : Select3D_SensitiveSegment(theOwnerId, theFirstPnt, theLastPnt)
{
}

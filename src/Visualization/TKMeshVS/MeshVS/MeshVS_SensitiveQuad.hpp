#pragma once


#include <SelectMgr_EntityOwner.hpp>

#include <gp_Pnt.hpp>
#include <NCollection_Array1.hpp>

//! This class contains description of planar quadrangle and defines methods
//! for its detection by OCCT BVH selection mechanism
class MeshVS_SensitiveQuad : public Select3D_SensitiveEntity
{
public:
  //! Creates a new instance and initializes quadrangle vertices with the given points
  Standard_EXPORT MeshVS_SensitiveQuad(const occ::handle<SelectMgr_EntityOwner>& theOwner,
                                       const NCollection_Array1<gp_Pnt>&         theQuadVerts);

  //! Creates a new instance and initializes quadrangle vertices with the given points
  Standard_EXPORT MeshVS_SensitiveQuad(const occ::handle<SelectMgr_EntityOwner>& theOwner,
                                       const gp_Pnt&                             thePnt1,
                                       const gp_Pnt&                             thePnt2,
                                       const gp_Pnt&                             thePnt3,
                                       const gp_Pnt&                             thePnt4);

  //! Returns the amount of sub-entities in sensitive
  int NbSubElements() const override { return 1; };

  //! Returns a copy of this sensitive quadrangle
  Standard_EXPORT occ::handle<Select3D_SensitiveEntity> GetConnected() override;

  //! Checks whether the box overlaps current selecting volume
  Standard_EXPORT bool Matches(SelectBasics_SelectingVolumeManager& theMgr,
                               SelectBasics_PickResult&             thePickResult) override;

  //! Returns center of the box
  Standard_EXPORT gp_Pnt CenterOfGeometry() const override;

  //! Returns coordinates of the box
  Standard_EXPORT Select3D_BndBox3d BoundingBox() override;

  DEFINE_STANDARD_RTTIEXT(MeshVS_SensitiveQuad, Select3D_SensitiveEntity)

private:
  gp_Pnt myVertices[4]; //!< 3d coordinates of quad's corners
};


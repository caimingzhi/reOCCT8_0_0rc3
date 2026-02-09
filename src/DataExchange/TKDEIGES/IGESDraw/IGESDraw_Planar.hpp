#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <IGESData_IGESEntity.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
class IGESGeom_TransformationMatrix;

class IGESDraw_Planar : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESDraw_Planar();

  Standard_EXPORT void Init(
    const int                                                                 nbMats,
    const occ::handle<IGESGeom_TransformationMatrix>&                         aTransformationMatrix,
    const occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>& allEntities);

  Standard_EXPORT int NbMatrices() const;

  Standard_EXPORT int NbEntities() const;

  Standard_EXPORT bool IsIdentityMatrix() const;

  Standard_EXPORT occ::handle<IGESGeom_TransformationMatrix> TransformMatrix() const;

  Standard_EXPORT occ::handle<IGESData_IGESEntity> Entity(const int EntityIndex) const;

  DEFINE_STANDARD_RTTIEXT(IGESDraw_Planar, IGESData_IGESEntity)

private:
  int                                                                theNbMatrices;
  occ::handle<IGESGeom_TransformationMatrix>                         theTransformationMatrix;
  occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>> theEntities;
};

#pragma once

#include <Standard.hpp>

#include <IGESData_IGESEntity.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <IGESGeom_TransformationMatrix.hpp>
#include <Standard_Integer.hpp>
class IGESGeom_TransformationMatrix;

class IGESSolid_SolidAssembly : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESSolid_SolidAssembly();

  Standard_EXPORT void Init(
    const occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>& allItems,
    const occ::handle<NCollection_HArray1<occ::handle<IGESGeom_TransformationMatrix>>>&
      allMatrices);

  Standard_EXPORT bool HasBrep() const;

  Standard_EXPORT void SetBrep(const bool hasbrep);

  Standard_EXPORT int NbItems() const;

  Standard_EXPORT occ::handle<IGESData_IGESEntity> Item(const int Index) const;

  Standard_EXPORT occ::handle<IGESGeom_TransformationMatrix> TransfMatrix(const int Index) const;

  DEFINE_STANDARD_RTTIEXT(IGESSolid_SolidAssembly, IGESData_IGESEntity)

private:
  occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>           theItems;
  occ::handle<NCollection_HArray1<occ::handle<IGESGeom_TransformationMatrix>>> theMatrices;
};

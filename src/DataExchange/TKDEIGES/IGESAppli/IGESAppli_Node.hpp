#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <gp_XYZ.hpp>
#include <IGESData_IGESEntity.hpp>
#include <Standard_Integer.hpp>
class IGESGeom_TransformationMatrix;
class gp_Pnt;
class IGESData_TransfEntity;

class IGESAppli_Node : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESAppli_Node();

  Standard_EXPORT void Init(const gp_XYZ&                                     aCoord,
                            const occ::handle<IGESGeom_TransformationMatrix>& aCoordSystem);

  Standard_EXPORT gp_Pnt Coord() const;

  Standard_EXPORT occ::handle<IGESData_TransfEntity> System() const;

  Standard_EXPORT int SystemType() const;

  Standard_EXPORT gp_Pnt TransformedNodalCoord() const;

  DEFINE_STANDARD_RTTIEXT(IGESAppli_Node, IGESData_IGESEntity)

private:
  gp_XYZ                                     theCoord;
  occ::handle<IGESGeom_TransformationMatrix> theSystem;
};

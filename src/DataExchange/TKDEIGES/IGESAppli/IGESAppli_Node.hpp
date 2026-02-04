#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <gp_XYZ.hpp>
#include <IGESData_IGESEntity.hpp>
#include <Standard_Integer.hpp>
class IGESGeom_TransformationMatrix;
class gp_Pnt;
class IGESData_TransfEntity;

//! defines Node, Type <134> Form <0>
//! in package IGESAppli
//! Geometric point used in the definition of a finite element.
class IGESAppli_Node : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESAppli_Node();

  //! This method is used to set the fields of the class Node
  //! - aCoord       : Nodal Coordinates
  //! - aCoordSystem : the Nodal Displacement Coordinate
  //! System Entity (default 0 is Global
  //! Cartesian Coordinate system)
  Standard_EXPORT void Init(const gp_XYZ&                                     aCoord,
                            const occ::handle<IGESGeom_TransformationMatrix>& aCoordSystem);

  //! returns the nodal coordinates
  Standard_EXPORT gp_Pnt Coord() const;

  //! returns TransfEntity if a Nodal Displacement Coordinate
  //! System Entity is defined
  //! else (for Global Cartesien) returns Null Handle
  Standard_EXPORT occ::handle<IGESData_TransfEntity> System() const;

  //! Computes & returns the Type of Coordinate System :
  //! 0 GlobalCartesian, 1 Cartesian, 2 Cylindrical, 3 Spherical
  Standard_EXPORT int SystemType() const;

  //! returns the Nodal coordinates after transformation
  Standard_EXPORT gp_Pnt TransformedNodalCoord() const;

  DEFINE_STANDARD_RTTIEXT(IGESAppli_Node, IGESData_IGESEntity)

private:
  gp_XYZ                                     theCoord;
  occ::handle<IGESGeom_TransformationMatrix> theSystem;
};


#pragma once


#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <IGESData_IGESEntity.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
class IGESGeom_TransformationMatrix;

//! defines IGESPlanar, Type <402> Form <16>
//! in package IGESDraw
//!
//! Indicates that a collection of entities is coplanar.The
//! entities may be geometric, annotative, and/or structural.
class IGESDraw_Planar : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESDraw_Planar();

  //! This method is used to set the fields of the class Planar
  //! - nbMats                : Number of Transformation matrices
  //! - aTransformationMatrix : Pointer to the Transformation matrix
  //! - allEntities           : Pointers to the entities specified
  Standard_EXPORT void Init(
    const int                                                                 nbMats,
    const occ::handle<IGESGeom_TransformationMatrix>&                         aTransformationMatrix,
    const occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>& allEntities);

  //! returns the number of Transformation matrices in <me>
  Standard_EXPORT int NbMatrices() const;

  //! returns the number of Entities in the plane pointed to by this
  //! associativity
  Standard_EXPORT int NbEntities() const;

  //! returns True if TransformationMatrix is Identity Matrix,
  //! i.e:- No Matrix defined.
  Standard_EXPORT bool IsIdentityMatrix() const;

  //! returns the Transformation matrix moving data from the XY plane
  //! into space or zero
  Standard_EXPORT occ::handle<IGESGeom_TransformationMatrix> TransformMatrix() const;

  //! returns the Entity on the specified plane, indicated by EntityIndex
  //! raises an exception if EntityIndex <= 0 or
  //! EntityIndex > NbEntities()
  Standard_EXPORT occ::handle<IGESData_IGESEntity> Entity(const int EntityIndex) const;

  DEFINE_STANDARD_RTTIEXT(IGESDraw_Planar, IGESData_IGESEntity)

private:
  int                                                                theNbMatrices;
  occ::handle<IGESGeom_TransformationMatrix>                         theTransformationMatrix;
  occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>> theEntities;
};


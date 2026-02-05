#pragma once

#include <Standard.hpp>

#include <IGESData_IGESEntity.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <IGESGeom_TransformationMatrix.hpp>
#include <Standard_Integer.hpp>
class IGESGeom_TransformationMatrix;

//! defines SolidAssembly, Type <184> Form <0>
//! in package IGESSolid
//! Solid assembly is a collection of items which possess a
//! shared fixed geometric relationship.
//!
//! From IGES-5.3, From 1 says that at least one item is a Brep
//! else all are Primitives, Boolean Trees, Solid Instances or
//! other Assemblies
class IGESSolid_SolidAssembly : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESSolid_SolidAssembly();

  //! This method is used to set the fields of the class
  //! SolidAssembly
  //! - allItems    : the collection of items
  //! - allMatrices : transformation matrices corresponding to each
  //! item
  //! raises exception if the length of allItems & allMatrices
  //! do not match
  Standard_EXPORT void Init(
    const occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>& allItems,
    const occ::handle<NCollection_HArray1<occ::handle<IGESGeom_TransformationMatrix>>>&
      allMatrices);

  //! Tells if at least one item is a Brep, from FormNumber
  Standard_EXPORT bool HasBrep() const;

  //! Sets or Unsets the status "HasBrep" from FormNumber
  //! Default is False
  Standard_EXPORT void SetBrep(const bool hasbrep);

  //! returns the number of items in the collection
  Standard_EXPORT int NbItems() const;

  //! returns the Index'th item
  //! raises exception if Index <= 0 or Index > NbItems()
  Standard_EXPORT occ::handle<IGESData_IGESEntity> Item(const int Index) const;

  //! returns the transformation matrix of the Index'th item
  //! raises exception if Index <= 0 or Index > NbItems()
  Standard_EXPORT occ::handle<IGESGeom_TransformationMatrix> TransfMatrix(const int Index) const;

  DEFINE_STANDARD_RTTIEXT(IGESSolid_SolidAssembly, IGESData_IGESEntity)

private:
  occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>           theItems;
  occ::handle<NCollection_HArray1<occ::handle<IGESGeom_TransformationMatrix>>> theMatrices;
};

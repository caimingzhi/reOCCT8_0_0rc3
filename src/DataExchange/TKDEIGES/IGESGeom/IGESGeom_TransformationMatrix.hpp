#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <NCollection_Array2.hpp>
#include <NCollection_HArray2.hpp>
#include <IGESData_TransfEntity.hpp>
#include <Standard_Integer.hpp>
class gp_GTrsf;

//! defines IGESTransformationMatrix, Type <124> Form <0>
//! in package IGESGeom
//! The transformation matrix entity transforms three-row column
//! vectors by means of matrix multiplication and then a vector
//! addition. This entity can be considered as an "operator"
//! entity in that it starts with the input vector, operates on
//! it as described above, and produces the output vector.
class IGESGeom_TransformationMatrix : public IGESData_TransfEntity
{

public:
  Standard_EXPORT IGESGeom_TransformationMatrix();

  //! This method is used to set the fields of the class
  //! TransformationMatrix
  //! - aMatrix : 3 x 4 array containing elements of the
  //! transformation matrix
  //! raises exception if aMatrix is not 3 x 4 array
  Standard_EXPORT void Init(const occ::handle<NCollection_HArray2<double>>& aMatrix);

  //! Changes FormNumber (indicates the Type of Transf :
  //! Transformation 0-1 or Coordinate System 10-11-12)
  //! Error if not in ranges [0-1] or [10-12]
  Standard_EXPORT void SetFormNumber(const int form);

  //! returns individual Data
  //! Error if I not in [1-3] or J not in [1-4]
  Standard_EXPORT double Data(const int I, const int J) const;

  //! returns the transformation matrix
  //! 4th row elements of GTrsf will always be 0, 0, 0, 1 (not defined)
  Standard_EXPORT gp_GTrsf Value() const override;

  DEFINE_STANDARD_RTTIEXT(IGESGeom_TransformationMatrix, IGESData_TransfEntity)

private:
  occ::handle<NCollection_HArray2<double>> theData;
};

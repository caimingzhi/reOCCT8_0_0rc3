#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <NCollection_Array2.hpp>
#include <NCollection_HArray2.hpp>
#include <IGESData_TransfEntity.hpp>
#include <Standard_Integer.hpp>
class gp_GTrsf;

class IGESGeom_TransformationMatrix : public IGESData_TransfEntity
{

public:
  Standard_EXPORT IGESGeom_TransformationMatrix();

  Standard_EXPORT void Init(const occ::handle<NCollection_HArray2<double>>& aMatrix);

  Standard_EXPORT void SetFormNumber(const int form);

  Standard_EXPORT double Data(const int I, const int J) const;

  Standard_EXPORT gp_GTrsf Value() const override;

  DEFINE_STANDARD_RTTIEXT(IGESGeom_TransformationMatrix, IGESData_TransfEntity)

private:
  occ::handle<NCollection_HArray2<double>> theData;
};

#pragma once

#include <IMeshData_Curve.hpp>
#include <Standard_Type.hpp>
#include <NCollection_IncAllocator.hpp>
#include <IMeshData_Types.hpp>

class BRepMeshData_Curve : public IMeshData_Curve
{
public:
  DEFINE_INC_ALLOC

  Standard_EXPORT BRepMeshData_Curve(const occ::handle<NCollection_IncAllocator>& theAllocator);

  Standard_EXPORT ~BRepMeshData_Curve() override;

  Standard_EXPORT void InsertPoint(const int     thePosition,
                                   const gp_Pnt& thePoint,
                                   const double  theParamOnPCurve) override;

  Standard_EXPORT void AddPoint(const gp_Pnt& thePoint, const double theParamOnCurve) override;

  Standard_EXPORT gp_Pnt& GetPoint(const int theIndex) override;

  Standard_EXPORT void RemovePoint(const int theIndex) override;

  Standard_EXPORT double& GetParameter(const int theIndex) override;

  Standard_EXPORT int ParametersNb() const override;

  Standard_EXPORT void Clear(const bool isKeepEndPoints) override;

  DEFINE_STANDARD_RTTIEXT(BRepMeshData_Curve, IMeshData_Curve)

protected:
  Standard_EXPORT void removeParameter(const int theIndex) override;

private:
  IMeshData::Model::SequenceOfPnt  myPoints;
  IMeshData::Model::SequenceOfReal myParameters;
};

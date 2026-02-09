#pragma once

#include <IMeshData_PCurve.hpp>
#include <Standard_Type.hpp>
#include <NCollection_IncAllocator.hpp>

class BRepMeshData_PCurve : public IMeshData_PCurve
{
public:
  DEFINE_INC_ALLOC

  Standard_EXPORT BRepMeshData_PCurve(const IMeshData::IFacePtr&                   theDFace,
                                      const TopAbs_Orientation                     theOrientation,
                                      const occ::handle<NCollection_IncAllocator>& theAllocator);

  Standard_EXPORT ~BRepMeshData_PCurve() override;

  Standard_EXPORT void InsertPoint(const int       thePosition,
                                   const gp_Pnt2d& thePoint,
                                   const double    theParamOnPCurve) override;

  Standard_EXPORT void AddPoint(const gp_Pnt2d& thePoint, const double theParamOnPCurve) override;

  Standard_EXPORT gp_Pnt2d& GetPoint(const int theIndex) override;

  Standard_EXPORT int& GetIndex(const int theIndex) override;

  Standard_EXPORT void RemovePoint(const int theIndex) override;

  Standard_EXPORT double& GetParameter(const int theIndex) override;

  Standard_EXPORT int ParametersNb() const override;

  Standard_EXPORT void Clear(const bool isKeepEndPoints) override;

  DEFINE_STANDARD_RTTIEXT(BRepMeshData_PCurve, IMeshData_PCurve)

protected:
  Standard_EXPORT void removeParameter(const int theIndex) override;

private:
  IMeshData::Model::SequenceOfPnt2d   myPoints2d;
  IMeshData::Model::SequenceOfReal    myParameters;
  IMeshData::Model::SequenceOfInteger myIndices;
};

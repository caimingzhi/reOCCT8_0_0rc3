#pragma once


#include <IMeshData_Curve.hpp>
#include <Standard_Type.hpp>
#include <NCollection_IncAllocator.hpp>
#include <IMeshData_Types.hpp>

//! Default implementation of curve data model entity.
class BRepMeshData_Curve : public IMeshData_Curve
{
public:
  DEFINE_INC_ALLOC

  //! Constructor.
  Standard_EXPORT BRepMeshData_Curve(const occ::handle<NCollection_IncAllocator>& theAllocator);

  //! Destructor.
  Standard_EXPORT ~BRepMeshData_Curve() override;

  //! Inserts new discretization point at the given position.
  Standard_EXPORT void InsertPoint(const int     thePosition,
                                   const gp_Pnt& thePoint,
                                   const double  theParamOnPCurve) override;

  //! Adds new discretization point to pcurve.
  Standard_EXPORT void AddPoint(const gp_Pnt& thePoint, const double theParamOnCurve) override;

  //! Returns discretization point with the given index.
  Standard_EXPORT gp_Pnt& GetPoint(const int theIndex) override;

  //! Removes point with the given index.
  Standard_EXPORT void RemovePoint(const int theIndex) override;

  //! Returns parameter with the given index.
  Standard_EXPORT double& GetParameter(const int theIndex) override;

  //! Returns number of parameters stored in curve.
  Standard_EXPORT int ParametersNb() const override;

  //! Clears parameters list.
  Standard_EXPORT void Clear(const bool isKeepEndPoints) override;

  DEFINE_STANDARD_RTTIEXT(BRepMeshData_Curve, IMeshData_Curve)

protected:
  //! Removes parameter with the given index.
  Standard_EXPORT void removeParameter(const int theIndex) override;

private:
  IMeshData::Model::SequenceOfPnt  myPoints;
  IMeshData::Model::SequenceOfReal myParameters;
};


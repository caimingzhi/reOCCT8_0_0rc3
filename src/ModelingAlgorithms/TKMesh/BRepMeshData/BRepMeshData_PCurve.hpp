#pragma once


#include <IMeshData_PCurve.hpp>
#include <Standard_Type.hpp>
#include <NCollection_IncAllocator.hpp>

//! Default implementation of pcurve data model entity.
class BRepMeshData_PCurve : public IMeshData_PCurve
{
public:
  DEFINE_INC_ALLOC

  //! Constructor.
  Standard_EXPORT BRepMeshData_PCurve(const IMeshData::IFacePtr&                   theDFace,
                                      const TopAbs_Orientation                     theOrientation,
                                      const occ::handle<NCollection_IncAllocator>& theAllocator);

  //! Destructor.
  Standard_EXPORT ~BRepMeshData_PCurve() override;

  //! Inserts new discretization point at the given position.
  Standard_EXPORT void InsertPoint(const int       thePosition,
                                   const gp_Pnt2d& thePoint,
                                   const double    theParamOnPCurve) override;

  //! Adds new discretization point to pcurve.
  Standard_EXPORT void AddPoint(const gp_Pnt2d& thePoint, const double theParamOnPCurve) override;

  //! Returns discretization point with the given index.
  Standard_EXPORT gp_Pnt2d& GetPoint(const int theIndex) override;

  //! Returns index in mesh corresponded to discretization point with the given index.
  Standard_EXPORT int& GetIndex(const int theIndex) override;

  //! Removes point with the given index.
  Standard_EXPORT void RemovePoint(const int theIndex) override;

  //! Returns parameter with the given index.
  Standard_EXPORT double& GetParameter(const int theIndex) override;

  //! Returns number of parameters stored in pcurve.
  Standard_EXPORT int ParametersNb() const override;

  //! Clears parameters list.
  Standard_EXPORT void Clear(const bool isKeepEndPoints) override;

  DEFINE_STANDARD_RTTIEXT(BRepMeshData_PCurve, IMeshData_PCurve)

protected:
  //! Removes parameter with the given index.
  Standard_EXPORT void removeParameter(const int theIndex) override;

private:
  IMeshData::Model::SequenceOfPnt2d   myPoints2d;
  IMeshData::Model::SequenceOfReal    myParameters;
  IMeshData::Model::SequenceOfInteger myIndices;
};


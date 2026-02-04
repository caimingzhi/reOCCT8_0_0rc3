#pragma once


#include <IMeshData_ParametersList.hpp>
#include <Standard_Type.hpp>

class gp_Pnt;

//! Interface class representing discrete 3d curve of edge.
//! Indexation of points starts from zero.
class IMeshData_Curve : public IMeshData_ParametersList
{
public:
  //! Destructor.
  ~IMeshData_Curve() override = default;

  //! Inserts new discretization point at the given position.
  Standard_EXPORT virtual void InsertPoint(const int     thePosition,
                                           const gp_Pnt& thePoint,
                                           const double  theParamOnPCurve) = 0;

  //! Adds new discretization point to curve.
  Standard_EXPORT virtual void AddPoint(const gp_Pnt& thePoint, const double theParamOnCurve) = 0;

  //! Returns discretization point with the given index.
  Standard_EXPORT virtual gp_Pnt& GetPoint(const int theIndex) = 0;

  //! Removes point with the given index.
  Standard_EXPORT virtual void RemovePoint(const int theIndex) = 0;

  DEFINE_STANDARD_RTTIEXT(IMeshData_Curve, IMeshData_ParametersList)

protected:
  //! Constructor.
  IMeshData_Curve() {}
};


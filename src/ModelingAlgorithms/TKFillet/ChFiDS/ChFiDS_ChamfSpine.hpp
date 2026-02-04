#pragma once


#include <Standard.hpp>

#include <Standard_Real.hpp>
#include <ChFiDS_ChamfMethod.hpp>
#include <ChFiDS_Spine.hpp>

//! Provides data specific to chamfers
//! distances on each of faces.
class ChFiDS_ChamfSpine : public ChFiDS_Spine
{

public:
  Standard_EXPORT ChFiDS_ChamfSpine();

  Standard_EXPORT ChFiDS_ChamfSpine(const double Tol);

  Standard_EXPORT void SetDist(const double Dis);

  Standard_EXPORT void GetDist(double& Dis) const;

  Standard_EXPORT void SetDists(const double Dis1, const double Dis2);

  Standard_EXPORT void Dists(double& Dis1, double& Dis2) const;

  Standard_EXPORT void GetDistAngle(double& Dis, double& Angle) const;

  Standard_EXPORT void SetDistAngle(const double Dis, const double Angle);

  Standard_EXPORT void SetMode(const ChFiDS_ChamfMode theMode);

  //! Return the method of chamfers used
  Standard_EXPORT ChFiDS_ChamfMethod IsChamfer() const;

  //! Return the mode of chamfers used
  // Standard_EXPORT ChFiDS_ChamfMode Mode() const;

  DEFINE_STANDARD_RTTIEXT(ChFiDS_ChamfSpine, ChFiDS_Spine)

private:
  double d1;
  double d2;
  // bool dison1;
  double             angle;
  ChFiDS_ChamfMethod mChamf;
};


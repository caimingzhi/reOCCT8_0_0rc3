#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDS_Shape.hpp>
#include <Standard_Integer.hpp>
class Geom_Curve;
class TopOpeBRepDS_Interference;
class Geom2d_Curve;

class TopOpeBRepDS_Curve
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopOpeBRepDS_Curve();

  Standard_EXPORT TopOpeBRepDS_Curve(const occ::handle<Geom_Curve>& P,
                                     const double                   T,
                                     const bool                     IsWalk = false);

  Standard_EXPORT void DefineCurve(const occ::handle<Geom_Curve>& P,
                                   const double                   T,
                                   const bool                     IsWalk);

  Standard_EXPORT void Tolerance(const double tol);

  Standard_EXPORT void SetSCI(const occ::handle<TopOpeBRepDS_Interference>& I1,
                              const occ::handle<TopOpeBRepDS_Interference>& I2);

  Standard_EXPORT const occ::handle<TopOpeBRepDS_Interference>& GetSCI1() const;

  Standard_EXPORT const occ::handle<TopOpeBRepDS_Interference>& GetSCI2() const;

  Standard_EXPORT void GetSCI(occ::handle<TopOpeBRepDS_Interference>& I1,
                              occ::handle<TopOpeBRepDS_Interference>& I2) const;

  Standard_EXPORT void SetShapes(const TopoDS_Shape& S1, const TopoDS_Shape& S2);

  Standard_EXPORT void GetShapes(TopoDS_Shape& S1, TopoDS_Shape& S2) const;

  Standard_EXPORT const TopoDS_Shape& Shape1() const;

  Standard_EXPORT TopoDS_Shape& ChangeShape1();

  Standard_EXPORT const TopoDS_Shape& Shape2() const;

  Standard_EXPORT TopoDS_Shape& ChangeShape2();

  Standard_EXPORT const occ::handle<Geom_Curve>& Curve() const;

  Standard_EXPORT void SetRange(const double First, const double Last);

  Standard_EXPORT bool Range(double& First, double& Last) const;

  Standard_EXPORT double Tolerance() const;

  Standard_EXPORT occ::handle<Geom_Curve>& ChangeCurve();

  Standard_EXPORT void Curve(const occ::handle<Geom_Curve>& C3D, const double Tol);

  Standard_EXPORT const occ::handle<Geom2d_Curve>& Curve1() const;

  Standard_EXPORT void Curve1(const occ::handle<Geom2d_Curve>& PC1);

  Standard_EXPORT const occ::handle<Geom2d_Curve>& Curve2() const;

  Standard_EXPORT void Curve2(const occ::handle<Geom2d_Curve>& PC2);

  Standard_EXPORT bool IsWalk() const;

  Standard_EXPORT void ChangeIsWalk(const bool B);

  Standard_EXPORT bool Keep() const;

  Standard_EXPORT void ChangeKeep(const bool B);

  Standard_EXPORT int Mother() const;

  Standard_EXPORT void ChangeMother(const int I);

  Standard_EXPORT int DSIndex() const;

  Standard_EXPORT void ChangeDSIndex(const int I);

private:
  occ::handle<Geom_Curve>                myCurve;
  double                                 myFirst;
  double                                 myLast;
  bool                                   myRangeDefined;
  double                                 myTolerance;
  bool                                   myIsWalk;
  TopoDS_Shape                           myS1;
  TopoDS_Shape                           myS2;
  occ::handle<TopOpeBRepDS_Interference> mySCI1;
  occ::handle<TopOpeBRepDS_Interference> mySCI2;
  bool                                   myKeep;
  int                                    myMother;
  int                                    myDSIndex;
};

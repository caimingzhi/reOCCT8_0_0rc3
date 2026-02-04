#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <gp_XYZ.hpp>
#include <IGESData_IGESEntity.hpp>
#include <Standard_Integer.hpp>
class gp_Pnt;

//! defines IGESPlane, Type <108> Form <-1,0,1>
//! in package IGESGeom
//! A plane entity can be used to represent unbounded plane,
//! as well as bounded portion of a plane. In either of the
//! above cases the plane is defined within definition space
//! by means of coefficients A, B, C, D where at least one of
//! A, B, C is non-zero and A * XT + B * YT + C * ZT = D
class IGESGeom_Plane : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESGeom_Plane();

  Standard_EXPORT void Init(const double                            A,
                            const double                            B,
                            const double                            C,
                            const double                            D,
                            const occ::handle<IGESData_IGESEntity>& aCurve,
                            const gp_XYZ&                           attach,
                            const double                            aSize);

  //! Changes FormNumber (indicates the Type of Bound :
  //! 0 no Bound, 1 (External) Bound, -1 Hole)
  //! Remark that Init keeps this Value and must be consistent :
  //! aCurve Null if FormNumber = 0, Non-Null else
  //! Error if not in ranges [0-1] or [10-12]
  Standard_EXPORT void SetFormNumber(const int form);

  Standard_EXPORT void Equation(double& A, double& B, double& C, double& D) const;

  Standard_EXPORT void TransformedEquation(double& A, double& B, double& C, double& D) const;

  //! returns True if there exists a bounding curve
  Standard_EXPORT bool HasBoundingCurve() const;

  //! returns True if bounding curve exists and bounded portion is negative
  Standard_EXPORT bool HasBoundingCurveHole() const;

  //! returns Optional Bounding Curve, can be positive (normal clipping)
  //! or negative (hole) according to Form Number
  Standard_EXPORT occ::handle<IGESData_IGESEntity> BoundingCurve() const;

  //! returns True if SymbolSize() > 0, False if SymbolSize() = 0
  Standard_EXPORT bool HasSymbolAttach() const;

  //! returns (X, Y, Z) if symbol exists else returns (0, 0, 0)
  Standard_EXPORT gp_Pnt SymbolAttach() const;

  //! returns (X, Y, Z) if symbol exists after applying Transf. Matrix
  //! else returns (0, 0, 0)
  Standard_EXPORT gp_Pnt TransformedSymbolAttach() const;

  //! Size of optional display symbol
  Standard_EXPORT double SymbolSize() const;

  DEFINE_STANDARD_RTTIEXT(IGESGeom_Plane, IGESData_IGESEntity)

private:
  double                           theA;
  double                           theB;
  double                           theC;
  double                           theD;
  occ::handle<IGESData_IGESEntity> theCurve;
  gp_XYZ                           theAttach;
  double                           theSize;
};


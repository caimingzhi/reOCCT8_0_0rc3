#pragma once

#include <gp_Trsf.hpp>
#include <Standard.hpp>
#include <Standard_Integer.hpp>
#include <Standard_Real.hpp>
#include <Standard_Type.hpp>
#include <Standard_Transient.hpp>

class Geom_Transformation : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(Geom_Transformation, Standard_Transient)
public:
  Standard_EXPORT Geom_Transformation();

  Standard_EXPORT Geom_Transformation(const gp_Trsf& T);

  void SetMirror(const gp_Pnt& thePnt) { gpTrsf.SetMirror(thePnt); }

  void SetMirror(const gp_Ax1& theA1) { gpTrsf.SetMirror(theA1); }

  void SetMirror(const gp_Ax2& theA2) { gpTrsf.SetMirror(theA2); }

  void SetRotation(const gp_Ax1& theA1, const double theAng) { gpTrsf.SetRotation(theA1, theAng); }

  void SetScale(const gp_Pnt& thePnt, const double theScale) { gpTrsf.SetScale(thePnt, theScale); }

  void SetTransformation(const gp_Ax3& theFromSystem1, const gp_Ax3& theToSystem2)
  {
    gpTrsf.SetTransformation(theFromSystem1, theToSystem2);
  }

  void SetTransformation(const gp_Ax3& theToSystem) { gpTrsf.SetTransformation(theToSystem); }

  void SetTranslation(const gp_Vec& theVec) { gpTrsf.SetTranslation(theVec); }

  void SetTranslation(const gp_Pnt& P1, const gp_Pnt& P2) { gpTrsf.SetTranslation(P1, P2); }

  void SetTrsf(const gp_Trsf& theTrsf) { gpTrsf = theTrsf; }

  bool IsNegative() const { return gpTrsf.IsNegative(); }

  gp_TrsfForm Form() const { return gpTrsf.Form(); }

  double ScaleFactor() const { return gpTrsf.ScaleFactor(); }

  const gp_Trsf& Trsf() const { return gpTrsf; }

  double Value(const int theRow, const int theCol) const { return gpTrsf.Value(theRow, theCol); }

  void Invert() { gpTrsf.Invert(); }

  [[nodiscard]] Standard_EXPORT occ::handle<Geom_Transformation> Inverted() const;

  [[nodiscard]] Standard_EXPORT occ::handle<Geom_Transformation> Multiplied(
    const occ::handle<Geom_Transformation>& Other) const;

  void Multiply(const occ::handle<Geom_Transformation>& theOther)
  {
    gpTrsf.Multiply(theOther->Trsf());
  }

  void Power(const int N) { gpTrsf.Power(N); }

  Standard_EXPORT occ::handle<Geom_Transformation> Powered(const int N) const;

  Standard_EXPORT void PreMultiply(const occ::handle<Geom_Transformation>& Other);

  void Transforms(double& theX, double& theY, double& theZ) const
  {
    gpTrsf.Transforms(theX, theY, theZ);
  }

  Standard_EXPORT occ::handle<Geom_Transformation> Copy() const;

  Standard_EXPORT virtual void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

private:
  gp_Trsf gpTrsf;
};

#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <Plate_PinpointConstraint.hpp>
#include <NCollection_Sequence.hpp>
#include <Plate_LinearXYZConstraint.hpp>
#include <Plate_LinearScalarConstraint.hpp>
#include <gp_XYZ.hpp>
#include <NCollection_Array2.hpp>
#include <NCollection_HArray2.hpp>
#include <gp_XY.hpp>
#include <Message_ProgressScope.hpp>

class Plate_PinpointConstraint;
class Plate_LinearXYZConstraint;
class Plate_LinearScalarConstraint;
class Plate_GlobalTranslationConstraint;
class Plate_LineConstraint;
class Plate_PlaneConstraint;
class Plate_SampledCurveConstraint;
class Plate_GtoCConstraint;
class Plate_FreeGtoCConstraint;
class gp_XYZ;
class gp_XY;
class math_Matrix;

//! This class implement a variational spline algorithm able
//! to define a two variable function satisfying some constraints
//! and minimizing an energy like criterion.
class Plate_Plate
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Plate_Plate();

  Standard_EXPORT Plate_Plate(const Plate_Plate& Ref);

  Standard_EXPORT Plate_Plate& Copy(const Plate_Plate& Ref);

  Plate_Plate& operator=(const Plate_Plate& Ref) { return Copy(Ref); }

  Standard_EXPORT void Load(const Plate_PinpointConstraint& PConst);

  Standard_EXPORT void Load(const Plate_LinearXYZConstraint& LXYZConst);

  Standard_EXPORT void Load(const Plate_LinearScalarConstraint& LScalarConst);

  Standard_EXPORT void Load(const Plate_GlobalTranslationConstraint& GTConst);

  Standard_EXPORT void Load(const Plate_LineConstraint& LConst);

  Standard_EXPORT void Load(const Plate_PlaneConstraint& PConst);

  Standard_EXPORT void Load(const Plate_SampledCurveConstraint& SCConst);

  Standard_EXPORT void Load(const Plate_GtoCConstraint& GtoCConst);

  Standard_EXPORT void Load(const Plate_FreeGtoCConstraint& FGtoCConst);

  Standard_EXPORT void SolveTI(const int                    ord         = 4,
                               const double                 anisotropie = 1.0,
                               const Message_ProgressRange& theProgress = Message_ProgressRange());

  //! returns True if all has been correctly done.
  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT void destroy();

  ~Plate_Plate() { destroy(); }

  //! reset the Plate in the initial state
  //! ( same as after Create())
  Standard_EXPORT void Init();

  Standard_EXPORT gp_XYZ Evaluate(const gp_XY& point2d) const;

  Standard_EXPORT gp_XYZ EvaluateDerivative(const gp_XY& point2d, const int iu, const int iv) const;

  Standard_EXPORT void CoefPol(occ::handle<NCollection_HArray2<gp_XYZ>>& Coefs) const;

  Standard_EXPORT void SetPolynomialPartOnly(const bool PPOnly = true);

  Standard_EXPORT int Continuity() const;

  Standard_EXPORT void UVBox(double& UMin, double& UMax, double& VMin, double& VMax) const;

  Standard_EXPORT void UVConstraints(NCollection_Sequence<gp_XY>& Seq) const;

private:
  Standard_EXPORT double SolEm(const gp_XY& point2d, const int iu, const int iv) const;

  double Polm(const gp_XY& point2d, const int iu, const int iv, const int idu, const int idv) const;

  int& Deru(const int index) const;

  int& Derv(const int index) const;

  gp_XYZ& Solution(const int index) const;

  gp_XY& Points(const int index) const;

  Standard_EXPORT void SolveTI1(const int                    IterationNumber,
                                const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT void SolveTI2(const int                    IterationNumber,
                                const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT void SolveTI3(const int                    IterationNumber,
                                const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT void fillXYZmatrix(math_Matrix& mat,
                                     const int    i0,
                                     const int    j0,
                                     const int    ncc1,
                                     const int    ncc2) const;

  int                                                order;
  int                                                n_el;
  int                                                n_dim;
  void*                                              solution;
  void*                                              points;
  void*                                              deru;
  void*                                              derv;
  bool                                               OK;
  NCollection_Sequence<Plate_PinpointConstraint>     myConstraints;
  NCollection_Sequence<Plate_LinearXYZConstraint>    myLXYZConstraints;
  NCollection_Sequence<Plate_LinearScalarConstraint> myLScalarConstraints;
  double                                             ddu[10];
  double                                             ddv[10];
  int                                                maxConstraintOrder;
  bool                                               PolynomialPartOnly;
  double                                             Uold;
  double                                             Vold;
  double                                             U2;
  double                                             R;
  double                                             L;
};

#include <gp_XY.hpp>
#include <gp_XYZ.hpp>

inline double Plate_Plate::Polm(const gp_XY& point2d,
                                const int    iu,
                                const int    iv,
                                const int    idu,
                                const int    idv) const
{
  if (idu > iu)
    return 0;
  if (idv > iv)
    return 0;
  double u = point2d.X();
  double v = point2d.Y();

  double value = 1;

  int degu = iu - idu;
  int i;
  for (i = 0; i < degu; i++)
    value *= u;
  for (i = iu; i > degu; i--)
    value *= i;

  int degv = iv - idv;
  for (i = 0; i < degv; i++)
    value *= v;
  for (i = iv; i > degv; i--)
    value *= i;

  // le produit par ddu[iu]*ddv[iv] n'est pas indispensable !! (il change
  // les valeurs claculles pour la partie coef polynomiaux de Sol
  // de telle facon que les methodes Evaluate et EvaluateDerivative donnent
  // en theorie les memes valeurs. Toutefois, il nous semble que ce produit
  // ameliore le conditionnmenet de la matrice
  return value * ddu[iu] * ddv[iv];
  // return value;
}

inline int& Plate_Plate::Deru(const int index) const
{
  return ((int*)deru)[index];
}

inline int& Plate_Plate::Derv(const int index) const
{
  return ((int*)derv)[index];
}

inline gp_XYZ& Plate_Plate::Solution(const int index) const
{
  return ((gp_XYZ*)solution)[index];
}

inline gp_XY& Plate_Plate::Points(const int index) const
{
  return ((gp_XY*)points)[index];
}

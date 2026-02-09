#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Integer.hpp>
#include <Standard_Boolean.hpp>
#include <Standard_Real.hpp>
class Law_BSpFunc;
class Law_Linear;
class Law_BSpline;
class Adaptor3d_Curve;

class Law
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static occ::handle<Law_BSpFunc> MixBnd(const occ::handle<Law_Linear>& Lin);

  Standard_EXPORT static occ::handle<NCollection_HArray1<double>> MixBnd(
    const int                         Degree,
    const NCollection_Array1<double>& Knots,
    const NCollection_Array1<int>&    Mults,
    const occ::handle<Law_Linear>&    Lin);

  Standard_EXPORT static occ::handle<NCollection_HArray1<double>> MixTgt(
    const int                         Degree,
    const NCollection_Array1<double>& Knots,
    const NCollection_Array1<int>&    Mults,
    const bool                        NulOnTheRight,
    const int                         Index);

  Standard_EXPORT static occ::handle<Law_BSpline> Reparametrize(const Adaptor3d_Curve& Curve,
                                                                const double           First,
                                                                const double           Last,
                                                                const bool             HasDF,
                                                                const bool             HasDL,
                                                                const double           DFirst,
                                                                const double           DLast,
                                                                const bool             Rev,
                                                                const int              NbPoints);

  Standard_EXPORT static occ::handle<Law_BSpline> Scale(const double First,
                                                        const double Last,
                                                        const bool   HasF,
                                                        const bool   HasL,
                                                        const double VFirst,
                                                        const double VLast);

  Standard_EXPORT static occ::handle<Law_BSpline> ScaleCub(const double First,
                                                           const double Last,
                                                           const bool   HasF,
                                                           const bool   HasL,
                                                           const double VFirst,
                                                           const double VLast);
};

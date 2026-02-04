#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <NLPlate_HGPPConstraint.hpp>
#include <NCollection_Sequence.hpp>
#include <Plate_Plate.hpp>
#include <NCollection_List.hpp>
#include <Standard_Integer.hpp>
class Geom_Surface;
class NLPlate_HGPPConstraint;
class gp_XYZ;
class gp_XY;

class NLPlate_NLPlate
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT NLPlate_NLPlate(const occ::handle<Geom_Surface>& InitialSurface);

  Standard_EXPORT void Load(const occ::handle<NLPlate_HGPPConstraint>& GConst);

  Standard_EXPORT void Solve(const int ord = 2, const int InitialConsraintOrder = 1);

  Standard_EXPORT void Solve2(const int ord = 2, const int InitialConsraintOrder = 1);

  Standard_EXPORT void IncrementalSolve(const int  ord                   = 2,
                                        const int  InitialConsraintOrder = 1,
                                        const int  NbIncrements          = 4,
                                        const bool UVSliding             = false);

  //! returns True if all has been correctly done.
  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT void destroy();

  ~NLPlate_NLPlate() { destroy(); }

  //! reset the Plate in the initial state
  //! ( same as after Create((Surface))
  Standard_EXPORT void Init();

  Standard_EXPORT gp_XYZ Evaluate(const gp_XY& point2d) const;

  Standard_EXPORT gp_XYZ EvaluateDerivative(const gp_XY& point2d, const int iu, const int iv) const;

  Standard_EXPORT int Continuity() const;

  Standard_EXPORT void ConstraintsSliding(const int NbIterations = 3);

  Standard_EXPORT int MaxActiveConstraintOrder() const;

private:
  Standard_EXPORT bool Iterate(const int    ConstraintOrder,
                               const int    ResolutionOrder,
                               const double IncrementalLoading = 1.0);

  occ::handle<Geom_Surface>                                 myInitialSurface;
  NCollection_Sequence<occ::handle<NLPlate_HGPPConstraint>> myHGPPConstraints;
  NCollection_List<Plate_Plate>                             mySOP;
  bool                                                      OK;
};


#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <IntCurve_IntImpConicParConic.hpp>
#include <IntRes2d_Intersection.hpp>
class gp_Lin2d;
class IntRes2d_Domain;
class gp_Circ2d;
class gp_Elips2d;
class gp_Parab2d;
class gp_Hypr2d;

class IntCurve_IntConicConic : public IntRes2d_Intersection
{
public:
  DEFINE_STANDARD_ALLOC

  IntCurve_IntConicConic();

  IntCurve_IntConicConic(const gp_Lin2d&        L1,
                         const IntRes2d_Domain& D1,
                         const gp_Lin2d&        L2,
                         const IntRes2d_Domain& D2,
                         const double           TolConf,
                         const double           Tol);

  Standard_EXPORT void Perform(const gp_Lin2d&        L1,
                               const IntRes2d_Domain& D1,
                               const gp_Lin2d&        L2,
                               const IntRes2d_Domain& D2,
                               const double           TolConf,
                               const double           Tol);

  IntCurve_IntConicConic(const gp_Lin2d&        L,
                         const IntRes2d_Domain& DL,
                         const gp_Circ2d&       C,
                         const IntRes2d_Domain& DC,
                         const double           TolConf,
                         const double           Tol);

  Standard_EXPORT void Perform(const gp_Lin2d&        L,
                               const IntRes2d_Domain& DL,
                               const gp_Circ2d&       C,
                               const IntRes2d_Domain& DC,
                               const double           TolConf,
                               const double           Tol);

  IntCurve_IntConicConic(const gp_Lin2d&        L,
                         const IntRes2d_Domain& DL,
                         const gp_Elips2d&      E,
                         const IntRes2d_Domain& DE,
                         const double           TolConf,
                         const double           Tol);

  Standard_EXPORT void Perform(const gp_Lin2d&        L,
                               const IntRes2d_Domain& DL,
                               const gp_Elips2d&      E,
                               const IntRes2d_Domain& DE,
                               const double           TolConf,
                               const double           Tol);

  IntCurve_IntConicConic(const gp_Lin2d&        L,
                         const IntRes2d_Domain& DL,
                         const gp_Parab2d&      P,
                         const IntRes2d_Domain& DP,
                         const double           TolConf,
                         const double           Tol);

  Standard_EXPORT void Perform(const gp_Lin2d&        L,
                               const IntRes2d_Domain& DL,
                               const gp_Parab2d&      P,
                               const IntRes2d_Domain& DP,
                               const double           TolConf,
                               const double           Tol);

  IntCurve_IntConicConic(const gp_Lin2d&        L,
                         const IntRes2d_Domain& DL,
                         const gp_Hypr2d&       H,
                         const IntRes2d_Domain& DH,
                         const double           TolConf,
                         const double           Tol);

  Standard_EXPORT void Perform(const gp_Lin2d&        L,
                               const IntRes2d_Domain& DL,
                               const gp_Hypr2d&       H,
                               const IntRes2d_Domain& DH,
                               const double           TolConf,
                               const double           Tol);

  IntCurve_IntConicConic(const gp_Circ2d&       C1,
                         const IntRes2d_Domain& D1,
                         const gp_Circ2d&       C2,
                         const IntRes2d_Domain& D2,
                         const double           TolConf,
                         const double           Tol);

  Standard_EXPORT void Perform(const gp_Circ2d&       C1,
                               const IntRes2d_Domain& D1,
                               const gp_Circ2d&       C2,
                               const IntRes2d_Domain& D2,
                               const double           TolConf,
                               const double           Tol);

  IntCurve_IntConicConic(const gp_Circ2d&       C,
                         const IntRes2d_Domain& DC,
                         const gp_Elips2d&      E,
                         const IntRes2d_Domain& DE,
                         const double           TolConf,
                         const double           Tol);

  Standard_EXPORT void Perform(const gp_Circ2d&       C,
                               const IntRes2d_Domain& DC,
                               const gp_Elips2d&      E,
                               const IntRes2d_Domain& DE,
                               const double           TolConf,
                               const double           Tol);

  IntCurve_IntConicConic(const gp_Circ2d&       C,
                         const IntRes2d_Domain& DC,
                         const gp_Parab2d&      P,
                         const IntRes2d_Domain& DP,
                         const double           TolConf,
                         const double           Tol);

  Standard_EXPORT void Perform(const gp_Circ2d&       C,
                               const IntRes2d_Domain& DC,
                               const gp_Parab2d&      P,
                               const IntRes2d_Domain& DP,
                               const double           TolConf,
                               const double           Tol);

  IntCurve_IntConicConic(const gp_Circ2d&       C,
                         const IntRes2d_Domain& DC,
                         const gp_Hypr2d&       H,
                         const IntRes2d_Domain& DH,
                         const double           TolConf,
                         const double           Tol);

  Standard_EXPORT void Perform(const gp_Circ2d&       C,
                               const IntRes2d_Domain& DC,
                               const gp_Hypr2d&       H,
                               const IntRes2d_Domain& DH,
                               const double           TolConf,
                               const double           Tol);

  IntCurve_IntConicConic(const gp_Elips2d&      E1,
                         const IntRes2d_Domain& D1,
                         const gp_Elips2d&      E2,
                         const IntRes2d_Domain& D2,
                         const double           TolConf,
                         const double           Tol);

  Standard_EXPORT void Perform(const gp_Elips2d&      E1,
                               const IntRes2d_Domain& D1,
                               const gp_Elips2d&      E2,
                               const IntRes2d_Domain& D2,
                               const double           TolConf,
                               const double           Tol);

  IntCurve_IntConicConic(const gp_Elips2d&      E,
                         const IntRes2d_Domain& DE,
                         const gp_Parab2d&      P,
                         const IntRes2d_Domain& DP,
                         const double           TolConf,
                         const double           Tol);

  Standard_EXPORT void Perform(const gp_Elips2d&      E,
                               const IntRes2d_Domain& DE,
                               const gp_Parab2d&      P,
                               const IntRes2d_Domain& DP,
                               const double           TolConf,
                               const double           Tol);

  IntCurve_IntConicConic(const gp_Elips2d&      E,
                         const IntRes2d_Domain& DE,
                         const gp_Hypr2d&       H,
                         const IntRes2d_Domain& DH,
                         const double           TolConf,
                         const double           Tol);

  Standard_EXPORT void Perform(const gp_Elips2d&      E,
                               const IntRes2d_Domain& DE,
                               const gp_Hypr2d&       H,
                               const IntRes2d_Domain& DH,
                               const double           TolConf,
                               const double           Tol);

  IntCurve_IntConicConic(const gp_Parab2d&      P1,
                         const IntRes2d_Domain& D1,
                         const gp_Parab2d&      P2,
                         const IntRes2d_Domain& D2,
                         const double           TolConf,
                         const double           Tol);

  Standard_EXPORT void Perform(const gp_Parab2d&      P1,
                               const IntRes2d_Domain& D1,
                               const gp_Parab2d&      P2,
                               const IntRes2d_Domain& D2,
                               const double           TolConf,
                               const double           Tol);

  IntCurve_IntConicConic(const gp_Parab2d&      P,
                         const IntRes2d_Domain& DP,
                         const gp_Hypr2d&       H,
                         const IntRes2d_Domain& DH,
                         const double           TolConf,
                         const double           Tol);

  Standard_EXPORT void Perform(const gp_Parab2d&      P,
                               const IntRes2d_Domain& DP,
                               const gp_Hypr2d&       H,
                               const IntRes2d_Domain& DH,
                               const double           TolConf,
                               const double           Tol);

  IntCurve_IntConicConic(const gp_Hypr2d&       H1,
                         const IntRes2d_Domain& D1,
                         const gp_Hypr2d&       H2,
                         const IntRes2d_Domain& D2,
                         const double           TolConf,
                         const double           Tol);

  Standard_EXPORT void Perform(const gp_Hypr2d&       H1,
                               const IntRes2d_Domain& D1,
                               const gp_Hypr2d&       H2,
                               const IntRes2d_Domain& D2,
                               const double           TolConf,
                               const double           Tol);

private:
  IntCurve_IntImpConicParConic Inter;
};

#define CONSTRUCTOR IntCurve_IntConicConic::IntCurve_IntConicConic
#define PERFORM void IntCurve_IntConicConic::Perform

inline CONSTRUCTOR() {}

inline CONSTRUCTOR(const gp_Lin2d&        L,
                   const IntRes2d_Domain& DL,
                   const gp_Parab2d&      P,
                   const IntRes2d_Domain& DP,
                   const double           TolConf,
                   const double           Tol)
{
  Perform(L, DL, P, DP, TolConf, Tol);
}

inline CONSTRUCTOR(const gp_Lin2d&        L,
                   const IntRes2d_Domain& DL,
                   const gp_Elips2d&      E,
                   const IntRes2d_Domain& DE,
                   const double           TolConf,
                   const double           Tol)
{

  Perform(L, DL, E, DE, TolConf, Tol);
}

inline CONSTRUCTOR(const gp_Lin2d&        L,
                   const IntRes2d_Domain& DL,
                   const gp_Hypr2d&       H,
                   const IntRes2d_Domain& DH,
                   const double           TolConf,
                   const double           Tol)
{

  Perform(L, DL, H, DH, TolConf, Tol);
}

inline CONSTRUCTOR(const gp_Circ2d&       C,
                   const IntRes2d_Domain& DC,
                   const gp_Parab2d&      P,
                   const IntRes2d_Domain& DP,
                   const double           TolConf,
                   const double           Tol)
{

  Perform(C, DC, P, DP, TolConf, Tol);
}

inline CONSTRUCTOR(const gp_Circ2d&       C,
                   const IntRes2d_Domain& DC,
                   const gp_Elips2d&      E,
                   const IntRes2d_Domain& DE,
                   const double           TolConf,
                   const double           Tol)
{

  Perform(C, DC, E, DE, TolConf, Tol);
}

inline CONSTRUCTOR(const gp_Circ2d&       C,
                   const IntRes2d_Domain& DC,
                   const gp_Hypr2d&       H,
                   const IntRes2d_Domain& DH,
                   const double           TolConf,
                   const double           Tol)
{

  Perform(C, DC, H, DH, TolConf, Tol);
}

inline CONSTRUCTOR(const gp_Parab2d&      P1,
                   const IntRes2d_Domain& D1,
                   const gp_Parab2d&      P2,
                   const IntRes2d_Domain& D2,
                   const double           TolConf,
                   const double           Tol)
{

  Perform(P1, D1, P2, D2, TolConf, Tol);
}

inline CONSTRUCTOR(const gp_Elips2d&      E,
                   const IntRes2d_Domain& DE,
                   const gp_Parab2d&      P,
                   const IntRes2d_Domain& DP,
                   const double           TolConf,
                   const double           Tol)
{
  Perform(E, DE, P, DP, TolConf, Tol);
}

inline CONSTRUCTOR(const gp_Parab2d&      P,
                   const IntRes2d_Domain& DP,
                   const gp_Hypr2d&       H,
                   const IntRes2d_Domain& DH,
                   const double           TolConf,
                   const double           Tol)
{

  Perform(P, DP, H, DH, TolConf, Tol);
}

inline CONSTRUCTOR(const gp_Elips2d&      E1,
                   const IntRes2d_Domain& D1,
                   const gp_Elips2d&      E2,
                   const IntRes2d_Domain& D2,
                   const double           TolConf,
                   const double           Tol)
{

  Perform(E1, D1, E2, D2, TolConf, Tol);
}

inline CONSTRUCTOR(const gp_Elips2d&      E,
                   const IntRes2d_Domain& DE,
                   const gp_Hypr2d&       H,
                   const IntRes2d_Domain& DH,
                   const double           TolConf,
                   const double           Tol)
{

  Perform(E, DE, H, DH, TolConf, Tol);
}

inline CONSTRUCTOR(const gp_Hypr2d&       H1,
                   const IntRes2d_Domain& DH1,
                   const gp_Hypr2d&       H2,
                   const IntRes2d_Domain& DH2,
                   const double           TolConf,
                   const double           Tol)
{

  Perform(H1, DH1, H2, DH2, TolConf, Tol);
}

inline CONSTRUCTOR(const gp_Lin2d&        L1,
                   const IntRes2d_Domain& D1,
                   const gp_Lin2d&        L2,
                   const IntRes2d_Domain& D2,
                   const double           TolConf,
                   const double           Tol)
{
  Perform(L1, D1, L2, D2, TolConf, Tol);
}

inline CONSTRUCTOR(const gp_Lin2d&        L1,
                   const IntRes2d_Domain& D1,
                   const gp_Circ2d&       C2,
                   const IntRes2d_Domain& D2,
                   const double           TolConf,
                   const double           Tol)
{

  Perform(L1, D1, C2, D2, TolConf, Tol);
}

inline CONSTRUCTOR(const gp_Circ2d&       C1,
                   const IntRes2d_Domain& D1,
                   const gp_Circ2d&       C2,
                   const IntRes2d_Domain& D2,
                   const double           TolConf,
                   const double           Tol)
{
  SetReversedParameters(false);
  Perform(C1, D1, C2, D2, TolConf, Tol);
}

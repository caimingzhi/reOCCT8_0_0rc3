

#include <gp_Circ2d.hpp>
#include <gp_Elips2d.hpp>
#include <gp_Hypr2d.hpp>
#include <gp_Lin2d.hpp>
#include <gp_Parab2d.hpp>
#include <IntAna2d_AnaIntersection.hpp>
#include <IntAna2d_Conic.hpp>
#include <StdFail_NotDone.hpp>

IntAna2d_AnaIntersection::IntAna2d_AnaIntersection()
    : done(false),
      para(false),
      iden(false),
      empt(true),
      nbp(0)
{
}

IntAna2d_AnaIntersection::IntAna2d_AnaIntersection(const gp_Lin2d& L1, const gp_Lin2d& L2)
{
  Perform(L1, L2);
}

IntAna2d_AnaIntersection::IntAna2d_AnaIntersection(const gp_Circ2d& C1, const gp_Circ2d& C2)
{
  Perform(C1, C2);
}

IntAna2d_AnaIntersection::IntAna2d_AnaIntersection(const gp_Lin2d& L, const gp_Circ2d& C)
{
  Perform(L, C);
}

IntAna2d_AnaIntersection::IntAna2d_AnaIntersection(const gp_Lin2d& L, const IntAna2d_Conic& Conic)
{
  Perform(L, Conic);
}

IntAna2d_AnaIntersection::IntAna2d_AnaIntersection(const gp_Parab2d& P, const IntAna2d_Conic& Conic)
{
  Perform(P, Conic);
}

IntAna2d_AnaIntersection::IntAna2d_AnaIntersection(const gp_Circ2d& C, const IntAna2d_Conic& Conic)
{
  Perform(C, Conic);
}

IntAna2d_AnaIntersection::IntAna2d_AnaIntersection(const gp_Elips2d& E, const IntAna2d_Conic& Conic)
{
  Perform(E, Conic);
}

IntAna2d_AnaIntersection::IntAna2d_AnaIntersection(const gp_Hypr2d& E, const IntAna2d_Conic& Conic)
{
  Perform(E, Conic);
}

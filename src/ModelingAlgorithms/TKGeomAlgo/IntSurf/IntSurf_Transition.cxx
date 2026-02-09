

#include <IntSurf_Transition.hpp>
#include <Standard_DomainError.hpp>

IntSurf_Transition::IntSurf_Transition(const bool Tangent, const IntSurf_TypeTrans Type)
    : tangent(Tangent),
      typetra(Type),
      situat(IntSurf_Unknown),
      oppos(false)

{
}

IntSurf_Transition::IntSurf_Transition(const bool              Tangent,
                                       const IntSurf_Situation Situ,
                                       const bool              Oppos)
    : tangent(Tangent),
      typetra(IntSurf_Touch),
      situat(Situ),
      oppos(Oppos)
{
}

IntSurf_Transition::IntSurf_Transition()
    : tangent(false),
      typetra(IntSurf_Undecided),
      situat(IntSurf_Unknown),
      oppos(false)
{
}

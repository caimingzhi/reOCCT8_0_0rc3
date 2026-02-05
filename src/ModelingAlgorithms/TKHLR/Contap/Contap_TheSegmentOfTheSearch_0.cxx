#include <Contap_TheSegmentOfTheSearch.hpp>

#include <Adaptor2d_Curve2d.hpp>
#include <Standard_DomainError.hpp>
#include <Adaptor3d_HVertex.hpp>
#include <Contap_ThePathPointOfTheSearch.hpp>

Contap_TheSegmentOfTheSearch::Contap_TheSegmentOfTheSearch()
    : hasfp(false),
      haslp(false)
{
}

void Contap_TheSegmentOfTheSearch::SetLimitPoint(const Contap_ThePathPointOfTheSearch& V,
                                                 const bool                            First)
{
  if (First)
  {
    hasfp = true;
    thefp = V;
  }
  else
  {
    haslp = true;
    thelp = V;
  }
}

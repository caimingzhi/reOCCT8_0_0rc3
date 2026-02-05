#include <IntPatch_TheSegmentOfTheSOnBounds.hpp>

#include <Adaptor2d_Curve2d.hpp>
#include <Standard_DomainError.hpp>
#include <Adaptor3d_HVertex.hpp>
#include <IntPatch_ThePathPointOfTheSOnBounds.hpp>

IntPatch_TheSegmentOfTheSOnBounds::IntPatch_TheSegmentOfTheSOnBounds()
    : hasfp(false),
      haslp(false)
{
}

void IntPatch_TheSegmentOfTheSOnBounds::SetLimitPoint(const IntPatch_ThePathPointOfTheSOnBounds& V,
                                                      const bool First)
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

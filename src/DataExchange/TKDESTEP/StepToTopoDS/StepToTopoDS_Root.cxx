#include <Precision.hpp>
#include <StepToTopoDS_Root.hpp>

//=================================================================================================

StepToTopoDS_Root::StepToTopoDS_Root()
    : done(false)
{
  myPrecision = myMaxTol = Precision::Confusion();
}

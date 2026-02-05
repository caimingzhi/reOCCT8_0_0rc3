#include <TDF_ClosureMode.hpp>

//=================================================================================================

TDF_ClosureMode::TDF_ClosureMode(const bool aMode)
    : myFlags(aMode ? ~0 : 0)
{
}

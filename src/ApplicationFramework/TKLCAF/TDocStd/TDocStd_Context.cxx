#include <TDocStd_Context.hpp>

//=================================================================================================

TDocStd_Context::TDocStd_Context()
    : modifiedRef(false)
{
}

//=================================================================================================

void TDocStd_Context::SetModifiedReferences(const bool Mod)
{
  modifiedRef = Mod;
}

bool TDocStd_Context::ModifiedReferences() const
{
  return modifiedRef;
}

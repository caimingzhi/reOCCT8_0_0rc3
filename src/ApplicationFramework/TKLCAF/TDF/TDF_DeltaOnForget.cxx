#include <TDF_DeltaOnForget.hpp>
#include <TDF_Label.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TDF_DeltaOnForget, TDF_AttributeDelta)

//=================================================================================================

TDF_DeltaOnForget::TDF_DeltaOnForget(const occ::handle<TDF_Attribute>& anAtt)
    : TDF_AttributeDelta(anAtt)
{
}

//=================================================================================================

void TDF_DeltaOnForget::Apply()
{
  // Undo = Resume.
  Label().ResumeAttribute(Attribute());
  Attribute()->mySavedTransaction = 0;
#ifdef OCCT_DEBUG
  std::cout << "Resume attribute" << std::endl;
#endif
}

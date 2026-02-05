#include <TDF_DeltaOnResume.hpp>

#include <Standard_Dump.hpp>
#include <Standard_Type.hpp>
#include <TDF_Attribute.hpp>
#include <TDF_Label.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TDF_DeltaOnResume, TDF_AttributeDelta)

//=================================================================================================

TDF_DeltaOnResume::TDF_DeltaOnResume(const occ::handle<TDF_Attribute>& anAtt)
    : TDF_AttributeDelta(anAtt)
{
}

//=================================================================================================

void TDF_DeltaOnResume::Apply()
{
  // Undo = Forget.
  Label().ForgetAttribute(Attribute());
#ifdef OCCT_DEBUG
  std::cout << "Forget attribute" << std::endl;
#endif
}

//=================================================================================================

void TDF_DeltaOnResume::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)

  OCCT_DUMP_BASE_CLASS(theOStream, theDepth, TDF_AttributeDelta)
}

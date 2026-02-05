#include <OpenGl_Element.hpp>

#include <Graphic3d_FrameStatsData.hpp>
#include <Standard_Dump.hpp>

//=================================================================================================

OpenGl_Element::OpenGl_Element() = default;

//=================================================================================================

OpenGl_Element::~OpenGl_Element() = default;

//=================================================================================================

void OpenGl_Element::UpdateMemStats(Graphic3d_FrameStatsDataTmp& theStats) const
{
  theStats[Graphic3d_FrameStatsCounter_EstimatedBytesGeom] += EstimatedDataSize();
}

//=================================================================================================

void OpenGl_Element::UpdateDrawStats(Graphic3d_FrameStatsDataTmp&, bool) const {}

//=================================================================================================

void OpenGl_Element::DumpJson(Standard_OStream& theOStream, int) const
{
  OCCT_DUMP_CLASS_BEGIN(theOStream, OpenGl_Element)
  OCCT_DUMP_FIELD_VALUE_POINTER(theOStream, this)
}

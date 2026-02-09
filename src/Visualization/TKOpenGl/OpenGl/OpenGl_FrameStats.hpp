#pragma once

#include <Graphic3d_FrameStats.hpp>
#include <NCollection_IndexedMap.hpp>

class Graphic3d_CStructure;

class OpenGl_FrameStats : public Graphic3d_FrameStats
{
  DEFINE_STANDARD_RTTIEXT(OpenGl_FrameStats, Graphic3d_FrameStats)
public:
  Standard_EXPORT OpenGl_FrameStats();

  Standard_EXPORT ~OpenGl_FrameStats() override;

public:
  Standard_EXPORT virtual bool IsFrameUpdated(occ::handle<OpenGl_FrameStats>& thePrev) const;

protected:
  Standard_EXPORT void updateStatistics(const occ::handle<Graphic3d_CView>& theView,
                                        bool theIsImmediateOnly) override;

  Standard_EXPORT virtual void updateStructures(
    int                                                        theViewId,
    const NCollection_IndexedMap<const Graphic3d_CStructure*>& theStructures,
    bool                                                       theToCountElems,
    bool                                                       theToCountTris,
    bool                                                       theToCountMem);
};

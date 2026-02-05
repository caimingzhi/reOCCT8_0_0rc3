#pragma once

#include <Graphic3d_FrameStats.hpp>
#include <NCollection_IndexedMap.hpp>

class Graphic3d_CStructure;

//! Class storing the frame statistics.
class OpenGl_FrameStats : public Graphic3d_FrameStats
{
  DEFINE_STANDARD_RTTIEXT(OpenGl_FrameStats, Graphic3d_FrameStats)
public:
  //! Default constructor.
  Standard_EXPORT OpenGl_FrameStats();

  //! Destructor.
  Standard_EXPORT ~OpenGl_FrameStats() override;

public:
  //! Copy stats values into another instance (create new instance, if not exists).
  //! The main use of this method is to track changes in statistics (e.g. in conjunction with
  //! IsEqual() method).
  //! @return TRUE if frame data has been changed so that the presentation should be updated
  Standard_EXPORT virtual bool IsFrameUpdated(occ::handle<OpenGl_FrameStats>& thePrev) const;

protected:
  //! Method to collect statistics from the View; called by FrameEnd().
  Standard_EXPORT void updateStatistics(const occ::handle<Graphic3d_CView>& theView,
                                        bool theIsImmediateOnly) override;

  //! Updates counters for structures.
  Standard_EXPORT virtual void updateStructures(
    int                                                        theViewId,
    const NCollection_IndexedMap<const Graphic3d_CStructure*>& theStructures,
    bool                                                       theToCountElems,
    bool                                                       theToCountTris,
    bool                                                       theToCountMem);
};

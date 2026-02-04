#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <BOPAlgo_PaveFiller.hpp>

//! Checks the shape on self-interference.
//!
//! The algorithm can set the following errors:
//! - *BOPAlgo_AlertMultipleArguments* - The number of the input arguments is not one;
//! - *BOPALgo_ErrorIntersectionFailed* - The check has been aborted during intersection of
//! sub-shapes. In case the error has occurred during intersection of sub-shapes, i.e. in
//! BOPAlgo_PaveFiller::PerformInternal() method, the errors from this method directly will be
//! returned.

class BOPAlgo_CheckerSI : public BOPAlgo_PaveFiller
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BOPAlgo_CheckerSI();
  Standard_EXPORT ~BOPAlgo_CheckerSI() override;

  Standard_EXPORT void Perform(
    const Message_ProgressRange& theRange = Message_ProgressRange()) override;

  //! Sets the level of checking shape on self-interference.
  //! It defines which interferences will be checked:
  //! 0 - only V/V;
  //! 1 - V/V and V/E;
  //! 2 - V/V, V/E and E/E;
  //! 3 - V/V, V/E, E/E and V/F;
  //! 4 - V/V, V/E, E/E, V/F and E/F;
  //! 5 - V/V, V/E, E/E, V/F, E/F and F/F;
  //! 6 - V/V, V/E, E/E, V/F, E/F, F/F and V/S;
  //! 7 - V/V, V/E, E/E, V/F, E/F, F/F, V/S and E/S;
  //! 8 - V/V, V/E, E/E, V/F, E/F, F/F, V/S, E/S and F/S;
  //! 9 - V/V, V/E, E/E, V/F, E/F, F/F, V/S, E/S, F/S and S/S - all interferences (Default value)
  Standard_EXPORT void SetLevelOfCheck(const int theLevel);

protected:
  Standard_EXPORT void Init(const Message_ProgressRange& theRange) override;

  //! Treats the intersection results
  Standard_EXPORT void PostTreat();

  Standard_EXPORT void CheckFaceSelfIntersection(const Message_ProgressRange& theRange);

  //! Methods for intersection with solids

  //! Vertex/Solid intersection
  Standard_EXPORT virtual void PerformVZ(const Message_ProgressRange& theRange);

  //! Edge/Solid intersection
  Standard_EXPORT virtual void PerformEZ(const Message_ProgressRange& theRange);

  //! Face/Solid intersection
  Standard_EXPORT virtual void PerformFZ(const Message_ProgressRange& theRange);

  //! Solid/Solid intersection
  Standard_EXPORT virtual void PerformZZ(const Message_ProgressRange& theRange);

  //! Used for intersection of edges and faces with solids
  Standard_EXPORT virtual void PerformSZ(const TopAbs_ShapeEnum       aTS,
                                         const Message_ProgressRange& theRange);

  int myLevelOfCheck;
};


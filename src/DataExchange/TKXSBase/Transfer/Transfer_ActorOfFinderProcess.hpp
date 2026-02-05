#pragma once

#include <Standard.hpp>
#include <ShapeProcess.hpp>
#include <Transfer_ActorOfProcessForFinder.hpp>
#include <XSAlgo_ShapeProcessor.hpp>

struct DE_ShapeFixParameters;
class Transfer_Binder;
class Transfer_Finder;
class Transfer_ProcessForFinder;
class Transfer_FinderProcess;
class Standard_Transient;

//! The original class was renamed. Compatibility only
//!
//! ModeTrans : a simple way of transmitting a transfer mode from
//! a user. To be interpreted for each norm
class Transfer_ActorOfFinderProcess : public Transfer_ActorOfProcessForFinder
{
public:
  Standard_EXPORT Transfer_ActorOfFinderProcess();

  //! Returns the Transfer Mode, modifiable
  Standard_EXPORT int& ModeTrans();

  Standard_EXPORT occ::handle<Transfer_Binder> Transferring(
    const occ::handle<Transfer_Finder>&           start,
    const occ::handle<Transfer_ProcessForFinder>& TP,
    const Message_ProgressRange&                  theProgress = Message_ProgressRange()) override;

  Standard_EXPORT virtual occ::handle<Transfer_Binder> Transfer(
    const occ::handle<Transfer_Finder>&        start,
    const occ::handle<Transfer_FinderProcess>& TP,
    const Message_ProgressRange&               theProgress = Message_ProgressRange());

  Standard_EXPORT virtual occ::handle<Standard_Transient> TransferTransient(
    const occ::handle<Standard_Transient>&     start,
    const occ::handle<Transfer_FinderProcess>& TP,
    const Message_ProgressRange&               theProgress = Message_ProgressRange());

  //! Sets parameters for shape processing.
  //! @param theParameters the parameters for shape processing.
  Standard_EXPORT void SetShapeFixParameters(
    const XSAlgo_ShapeProcessor::ParameterMap& theParameters);

  //! Sets parameters for shape processing.
  //! Parameters are moved from the input map.
  //! @param theParameters the parameters for shape processing.
  Standard_EXPORT void SetShapeFixParameters(XSAlgo_ShapeProcessor::ParameterMap&& theParameters);

  //! Sets parameters for shape processing.
  //! Parameters from @p theParameters are copied to the internal map.
  //! Parameters from @p theAdditionalParameters are copied to the internal map
  //! if they are not present in @p theParameters.
  //! @param theParameters the parameters for shape processing.
  //! @param theAdditionalParameters the additional parameters for shape processing.
  Standard_EXPORT void SetShapeFixParameters(
    const DE_ShapeFixParameters&               theParameters,
    const XSAlgo_ShapeProcessor::ParameterMap& theAdditionalParameters = {});

  //! Returns parameters for shape processing that was set by SetParameters() method.
  //! @return the parameters for shape processing. Empty map if no parameters were set.
  inline const XSAlgo_ShapeProcessor::ParameterMap& GetShapeFixParameters() const
  {
    return myShapeProcParams;
  }

  //! Sets flags defining operations to be performed on shapes.
  //! @param theFlags The flags defining operations to be performed on shapes.
  Standard_EXPORT void SetShapeProcessFlags(const ShapeProcess::OperationsFlags& theFlags);

  //! Returns flags defining operations to be performed on shapes.
  //! @return Pair of values defining operations to be performed on shapes and a boolean value
  //!         that indicates whether the flags were set.
  inline const XSAlgo_ShapeProcessor::ProcessingFlags& GetShapeProcessFlags() const
  {
    return myShapeProcFlags;
  }

  DEFINE_STANDARD_RTTIEXT(Transfer_ActorOfFinderProcess, Transfer_ActorOfProcessForFinder)

protected:
  int themodetrans;

private:
  // clang-format off
  XSAlgo_ShapeProcessor::ParameterMap myShapeProcParams;   //!< Parameters for shape processing.
  XSAlgo_ShapeProcessor::ProcessingFlags myShapeProcFlags; //!< Flags defining operations to be performed on shapes.
  // clang-format on
};

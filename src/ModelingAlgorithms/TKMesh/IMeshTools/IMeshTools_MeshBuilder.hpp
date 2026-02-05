#pragma once

#include <IMeshTools_Context.hpp>
#include <Standard_Type.hpp>
#include <Message_ProgressRange.hpp>

//! Builds mesh for each face of shape without triangulation.
//! In case if some faces of shape have already been triangulated
//! checks deflection of existing polygonal model and re-uses it
//! if deflection satisfies the specified parameter. Otherwise
//! nullifies existing triangulation and build triangulation anew.
//!
//! The following statuses are used:
//! Message_Done1 - algorithm has finished without errors.
//! Message_Fail1 - invalid context.
//! Message_Fail2 - algorithm has faced unexpected error.
//! Message_Fail3 - fail to discretize edges.
//! Message_Fail4 - can't heal discrete model.
//! Message_Fail5 - fail to pre-process model.
//! Message_Fail6 - fail to discretize faces.
//! Message_Fail7 - fail to post-process model.
//! Message_Warn1 - shape contains no objects to mesh.
class IMeshTools_MeshBuilder : public Message_Algorithm
{
public:
  //! Constructor.
  Standard_EXPORT IMeshTools_MeshBuilder();

  //! Constructor.
  Standard_EXPORT IMeshTools_MeshBuilder(const occ::handle<IMeshTools_Context>& theContext);

  //! Destructor.
  Standard_EXPORT ~IMeshTools_MeshBuilder() override;

  //! Sets context for algorithm.
  void SetContext(const occ::handle<IMeshTools_Context>& theContext) { myContext = theContext; }

  //! Gets context of algorithm.
  const occ::handle<IMeshTools_Context>& GetContext() const { return myContext; }

  //! Performs meshing to the shape using current context.
  Standard_EXPORT virtual void Perform(const Message_ProgressRange& theRange);

  DEFINE_STANDARD_RTTIEXT(IMeshTools_MeshBuilder, Message_Algorithm)

private:
  occ::handle<IMeshTools_Context> myContext;
};

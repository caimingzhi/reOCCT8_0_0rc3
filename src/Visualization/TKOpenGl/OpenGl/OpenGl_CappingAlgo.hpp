#pragma once

#include <OpenGl_Group.hpp>

// Forward declaration
class OpenGl_Structure;

//! Capping surface rendering algorithm.
class OpenGl_CappingAlgo
{
public:
  //! Draw capping surfaces by OpenGl for the clipping planes enabled in current context state.
  //! Depth buffer must be generated for the passed groups.
  //! @param[in] theWorkspace  the GL workspace, context state
  //! @param[in] theStructure  the structure to be capped
  Standard_EXPORT static void RenderCapping(const occ::handle<OpenGl_Workspace>& theWorkspace,
                                            const OpenGl_Structure&              theStructure);
};

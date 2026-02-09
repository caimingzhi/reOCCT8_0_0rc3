#pragma once

#include <OpenGl_Group.hpp>

class OpenGl_Structure;

class OpenGl_CappingAlgo
{
public:
  Standard_EXPORT static void RenderCapping(const occ::handle<OpenGl_Workspace>& theWorkspace,
                                            const OpenGl_Structure&              theStructure);
};

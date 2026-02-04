#pragma once


#include <TopOpeBRepTool_HBoxTool.hpp>

#ifdef OCCT_DEBUG
Standard_EXPORT bool TopOpeBRepTool_GettraceBOX();
#endif

Standard_EXPORT void FBOX_Prepare();
Standard_EXPORT occ::handle<TopOpeBRepTool_HBoxTool> FBOX_GetHBoxTool();
Standard_EXPORT const Bnd_Box&                       FBOX_Box(const TopoDS_Shape& S);


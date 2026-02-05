#pragma once

#include <Adaptor3d_Surface.hpp>

class IntPatch_Line;
class Adaptor3d_TopolTool;

//! trouver les points d intersection entre la ligne de
//! cheminement et les arcs de restriction
class IntPatch_RstInt
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void PutVertexOnLine(const occ::handle<IntPatch_Line>&       L,
                                              const occ::handle<Adaptor3d_Surface>&   Surf,
                                              const occ::handle<Adaptor3d_TopolTool>& Domain,
                                              const occ::handle<Adaptor3d_Surface>&   OtherSurf,
                                              const bool                              OnFirst,
                                              const double                            Tol);
};

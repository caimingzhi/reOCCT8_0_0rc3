#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopOpeBRepDS_Kind.hpp>
#include <Standard_Integer.hpp>
#include <TopOpeBRepDS_Config.hpp>
class TopOpeBRepDS_Interference;
class TopOpeBRepDS_Transition;
class Geom2d_Curve;

class TopOpeBRepDS_InterferenceTool
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static occ::handle<TopOpeBRepDS_Interference> MakeEdgeInterference(
    const TopOpeBRepDS_Transition& T,
    const TopOpeBRepDS_Kind        SK,
    const int                      SI,
    const TopOpeBRepDS_Kind        GK,
    const int                      GI,
    const double                   P);

  Standard_EXPORT static occ::handle<TopOpeBRepDS_Interference> MakeCurveInterference(
    const TopOpeBRepDS_Transition& T,
    const TopOpeBRepDS_Kind        SK,
    const int                      SI,
    const TopOpeBRepDS_Kind        GK,
    const int                      GI,
    const double                   P);

  Standard_EXPORT static occ::handle<TopOpeBRepDS_Interference> DuplicateCurvePointInterference(
    const occ::handle<TopOpeBRepDS_Interference>& I);

  Standard_EXPORT static occ::handle<TopOpeBRepDS_Interference> MakeFaceCurveInterference(
    const TopOpeBRepDS_Transition&   Transition,
    const int                        FaceI,
    const int                        CurveI,
    const occ::handle<Geom2d_Curve>& PC);

  Standard_EXPORT static occ::handle<TopOpeBRepDS_Interference> MakeSolidSurfaceInterference(
    const TopOpeBRepDS_Transition& Transition,
    const int                      SolidI,
    const int                      SurfaceI);

  Standard_EXPORT static occ::handle<TopOpeBRepDS_Interference> MakeEdgeVertexInterference(
    const TopOpeBRepDS_Transition& Transition,
    const int                      EdgeI,
    const int                      VertexI,
    const bool                     VertexIsBound,
    const TopOpeBRepDS_Config      Config,
    const double                   param);

  Standard_EXPORT static occ::handle<TopOpeBRepDS_Interference> MakeFaceEdgeInterference(
    const TopOpeBRepDS_Transition& Transition,
    const int                      FaceI,
    const int                      EdgeI,
    const bool                     EdgeIsBound,
    const TopOpeBRepDS_Config      Config);

  Standard_EXPORT static double Parameter(const occ::handle<TopOpeBRepDS_Interference>& CPI);

  Standard_EXPORT static void Parameter(const occ::handle<TopOpeBRepDS_Interference>& CPI,
                                        const double                                  Par);
};

#pragma once

#include <Adaptor3d_Surface.hpp>
#include <TopAbs_Orientation.hpp>

class TopOpeBRepDS_DataStructure;
class ChFiDS_SurfData;
class ChFiDS_Spine;
class gp_Pnt2d;

class ChFiKPart_ComputeData
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static bool Compute(TopOpeBRepDS_DataStructure&           DStr,
                                      occ::handle<ChFiDS_SurfData>&         Data,
                                      const occ::handle<Adaptor3d_Surface>& S1,
                                      const occ::handle<Adaptor3d_Surface>& S2,
                                      const TopAbs_Orientation              Or1,
                                      const TopAbs_Orientation              Or2,
                                      const occ::handle<ChFiDS_Spine>&      Sp,
                                      const int                             Iedge);

  Standard_EXPORT static bool ComputeCorner(TopOpeBRepDS_DataStructure&           DStr,
                                            const occ::handle<ChFiDS_SurfData>&   Data,
                                            const occ::handle<Adaptor3d_Surface>& S1,
                                            const occ::handle<Adaptor3d_Surface>& S2,
                                            const TopAbs_Orientation              OrFace1,
                                            const TopAbs_Orientation              OrFace2,
                                            const TopAbs_Orientation              Or1,
                                            const TopAbs_Orientation              Or2,
                                            const double                          minRad,
                                            const double                          majRad,
                                            const gp_Pnt2d&                       P1S1,
                                            const gp_Pnt2d&                       P2S1,
                                            const gp_Pnt2d&                       P1S2,
                                            const gp_Pnt2d&                       P2S2);

  Standard_EXPORT static bool ComputeCorner(TopOpeBRepDS_DataStructure&           DStr,
                                            const occ::handle<ChFiDS_SurfData>&   Data,
                                            const occ::handle<Adaptor3d_Surface>& S1,
                                            const occ::handle<Adaptor3d_Surface>& S2,
                                            const TopAbs_Orientation              OrFace1,
                                            const TopAbs_Orientation              OrFace2,
                                            const TopAbs_Orientation              Or1,
                                            const TopAbs_Orientation              Or2,
                                            const double                          Rad,
                                            const gp_Pnt2d&                       PS1,
                                            const gp_Pnt2d&                       P1S2,
                                            const gp_Pnt2d&                       P2S2);

  Standard_EXPORT static bool ComputeCorner(TopOpeBRepDS_DataStructure&           DStr,
                                            const occ::handle<ChFiDS_SurfData>&   Data,
                                            const occ::handle<Adaptor3d_Surface>& S,
                                            const occ::handle<Adaptor3d_Surface>& S1,
                                            const occ::handle<Adaptor3d_Surface>& S2,
                                            const TopAbs_Orientation              OfS,
                                            const TopAbs_Orientation              OS,
                                            const TopAbs_Orientation              OS1,
                                            const TopAbs_Orientation              OS2,
                                            const double                          Radius);
};

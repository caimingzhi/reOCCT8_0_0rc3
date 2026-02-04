#pragma once


bool ChFiKPart_Sphere(TopOpeBRepDS_DataStructure&           DStr,
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


#pragma once


#include <Adaptor3d_Surface.hpp>
#include <gp_Cylinder.hpp>
#include <gp_Circ.hpp>

void ChFiKPart_CornerSpine(const occ::handle<Adaptor3d_Surface>& S1,
                           const occ::handle<Adaptor3d_Surface>& S2,
                           const gp_Pnt2d&                       P1S1,
                           const gp_Pnt2d&                       P2S1,
                           const gp_Pnt2d&                       P1S2,
                           const gp_Pnt2d&                       P2S2,
                           const double                          R,
                           gp_Cylinder&                          cyl,
                           gp_Circ&                              circ,
                           double&                               First,
                           double&                               Last);


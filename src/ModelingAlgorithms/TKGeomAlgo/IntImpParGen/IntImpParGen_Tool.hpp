#pragma once

#include <IntRes2d_Domain.hpp>
#include <IntRes2d_Transition.hpp>
#include <gp_Pnt2d.hpp>

double NormalizeOnDomain(double&, const IntRes2d_Domain&);

void Determine_Position(IntRes2d_Position&, const IntRes2d_Domain&, const gp_Pnt2d&, const double);

void Determine_Transition(const IntRes2d_Position Pos1,
                          gp_Vec2d&               Tan1,
                          const gp_Vec2d&         Norm1,
                          IntRes2d_Transition&    Trans1,
                          const IntRes2d_Position Pos2,
                          gp_Vec2d&               Tan2,
                          const gp_Vec2d&         Norm2,
                          IntRes2d_Transition&    Trans2,
                          const double            ToleranceAng);

#pragma once


#include <gp_Vec.hpp>
#include <IntImp_ConstIsoparametric.hpp>

Standard_EXPORT IntImp_ConstIsoparametric ChoixRef(int theIndex);

Standard_EXPORT bool IntImp_ComputeTangence(const gp_Vec              DPuv[],
                                            const double              EpsUV[],
                                            double                    Tgduv[],
                                            IntImp_ConstIsoparametric TabIso[]);


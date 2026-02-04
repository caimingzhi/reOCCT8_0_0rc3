#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <FairCurve_BattenLaw.hpp>
#include <FairCurve_DistributionOfEnergy.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <gp_Pnt2d.hpp>
#include <math_Vector.hpp>

//! Compute the Tension Distribution
class FairCurve_DistributionOfTension : public FairCurve_DistributionOfEnergy
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT FairCurve_DistributionOfTension(
    const int                                         BSplOrder,
    const occ::handle<NCollection_HArray1<double>>&   FlatKnots,
    const occ::handle<NCollection_HArray1<gp_Pnt2d>>& Poles,
    const int                                         DerivativeOrder,
    const double                                      LengthSliding,
    const FairCurve_BattenLaw&                        Law,
    const int                                         NbValAux = 0,
    const bool                                        Uniform  = false);

  //! change the length sliding
  void SetLengthSliding(const double LengthSliding);

  //! computes the values <F> of the functions for the
  //! variable <X>.
  //! returns True if the computation was done successfully,
  //! False otherwise.
  Standard_EXPORT bool Value(const math_Vector& X, math_Vector& F) override;

private:
  double              MyLengthSliding;
  FairCurve_BattenLaw MyLaw;
  double              MyHeight;
};
// Copyright (c) 1999-2014 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.

inline void FairCurve_DistributionOfTension::SetLengthSliding(const double LengthSliding)
{
  MyLengthSliding = LengthSliding;
}



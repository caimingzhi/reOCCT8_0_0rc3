#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GeomFill_Filling.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array1.hpp>

class GeomFill_Stretch : public GeomFill_Filling
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomFill_Stretch();

  Standard_EXPORT GeomFill_Stretch(const NCollection_Array1<gp_Pnt>& P1,
                                   const NCollection_Array1<gp_Pnt>& P2,
                                   const NCollection_Array1<gp_Pnt>& P3,
                                   const NCollection_Array1<gp_Pnt>& P4);

  Standard_EXPORT GeomFill_Stretch(const NCollection_Array1<gp_Pnt>& P1,
                                   const NCollection_Array1<gp_Pnt>& P2,
                                   const NCollection_Array1<gp_Pnt>& P3,
                                   const NCollection_Array1<gp_Pnt>& P4,
                                   const NCollection_Array1<double>& W1,
                                   const NCollection_Array1<double>& W2,
                                   const NCollection_Array1<double>& W3,
                                   const NCollection_Array1<double>& W4);

  Standard_EXPORT void Init(const NCollection_Array1<gp_Pnt>& P1,
                            const NCollection_Array1<gp_Pnt>& P2,
                            const NCollection_Array1<gp_Pnt>& P3,
                            const NCollection_Array1<gp_Pnt>& P4);

  Standard_EXPORT void Init(const NCollection_Array1<gp_Pnt>& P1,
                            const NCollection_Array1<gp_Pnt>& P2,
                            const NCollection_Array1<gp_Pnt>& P3,
                            const NCollection_Array1<gp_Pnt>& P4,
                            const NCollection_Array1<double>& W1,
                            const NCollection_Array1<double>& W2,
                            const NCollection_Array1<double>& W3,
                            const NCollection_Array1<double>& W4);
};

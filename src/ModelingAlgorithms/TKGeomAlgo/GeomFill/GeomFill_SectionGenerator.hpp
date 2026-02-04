#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <GeomFill_Profiler.hpp>
#include <Standard_Integer.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Vec2d.hpp>

//! gives the functions needed for instantiation from
//! AppSurf in AppBlend. Allow to evaluate a surface
//! passing by all the curves if the Profiler.
class GeomFill_SectionGenerator : public GeomFill_Profiler
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomFill_SectionGenerator();

  Standard_EXPORT void SetParam(const occ::handle<NCollection_HArray1<double>>& Params);

  Standard_EXPORT void GetShape(int& NbPoles, int& NbKnots, int& Degree, int& NbPoles2d) const;

  Standard_EXPORT void Knots(NCollection_Array1<double>& TKnots) const;

  Standard_EXPORT void Mults(NCollection_Array1<int>& TMults) const;

  //! Used for the first and last section
  //! The method returns true if the derivatives
  //! are computed, otherwise it returns false.
  Standard_EXPORT bool Section(const int                     P,
                               NCollection_Array1<gp_Pnt>&   Poles,
                               NCollection_Array1<gp_Vec>&   DPoles,
                               NCollection_Array1<gp_Pnt2d>& Poles2d,
                               NCollection_Array1<gp_Vec2d>& DPoles2d,
                               NCollection_Array1<double>&   Weigths,
                               NCollection_Array1<double>&   DWeigths) const;

  Standard_EXPORT void Section(const int                     P,
                               NCollection_Array1<gp_Pnt>&   Poles,
                               NCollection_Array1<gp_Pnt2d>& Poles2d,
                               NCollection_Array1<double>&   Weigths) const;

  //! Returns the parameter of Section<P>, to impose it for the
  //! approximation.
  Standard_EXPORT double Parameter(const int P) const;

protected:
  occ::handle<NCollection_HArray1<double>> myParams;
};


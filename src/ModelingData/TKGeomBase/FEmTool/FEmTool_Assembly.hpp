#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <NCollection_Array2.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <NCollection_HArray2.hpp>
#include <math_Vector.hpp>
#include <NCollection_List.hpp>
#include <NCollection_Sequence.hpp>
#include <Standard_Real.hpp>
class FEmTool_ProfileMatrix;
class math_Matrix;

class FEmTool_Assembly
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT FEmTool_Assembly(
    const NCollection_Array2<int>&                                                 Dependence,
    const occ::handle<NCollection_HArray2<occ::handle<NCollection_HArray1<int>>>>& Table);

  Standard_EXPORT void NullifyMatrix();

  Standard_EXPORT void AddMatrix(const int          Element,
                                 const int          Dimension1,
                                 const int          Dimension2,
                                 const math_Matrix& Mat);

  Standard_EXPORT void NullifyVector();

  Standard_EXPORT void AddVector(const int Element, const int Dimension, const math_Vector& Vec);

  Standard_EXPORT void ResetConstraint();

  Standard_EXPORT void NullifyConstraint();

  Standard_EXPORT void AddConstraint(const int          IndexofConstraint,
                                     const int          Element,
                                     const int          Dimension,
                                     const math_Vector& LinearForm,
                                     const double       Value);

  Standard_EXPORT bool Solve();

  Standard_EXPORT void Solution(math_Vector& Solution) const;

  Standard_EXPORT int NbGlobVar() const;

  Standard_EXPORT void GetAssemblyTable(
    occ::handle<NCollection_HArray2<occ::handle<NCollection_HArray1<int>>>>& AssTable) const;

private:
  NCollection_Array2<int>                                                          myDepTable;
  occ::handle<NCollection_HArray2<occ::handle<NCollection_HArray1<int>>>>          myRefTable;
  bool                                                                             IsSolved;
  occ::handle<FEmTool_ProfileMatrix>                                               H;
  math_Vector                                                                      B;
  occ::handle<FEmTool_ProfileMatrix>                                               GHGt;
  NCollection_Sequence<NCollection_List<occ::handle<NCollection_HArray1<double>>>> G;
  NCollection_Sequence<double>                                                     C;
};

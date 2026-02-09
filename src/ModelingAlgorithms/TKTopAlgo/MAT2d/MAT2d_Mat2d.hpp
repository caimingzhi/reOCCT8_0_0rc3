#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_DataMap.hpp>
#include <MAT_Bisector.hpp>
#include <Standard_Real.hpp>
class MAT_ListOfEdge;
class MAT_ListOfBisector;
class MAT2d_Tool2d;
class MAT_Bisector;

class MAT2d_Mat2d
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT MAT2d_Mat2d(const bool IsOpenResult = false);

  Standard_EXPORT ~MAT2d_Mat2d();

  Standard_EXPORT void CreateMat(MAT2d_Tool2d& aTool);

  Standard_EXPORT void CreateMatOpen(MAT2d_Tool2d& aTool);

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT void Init();

  Standard_EXPORT bool More() const;

  Standard_EXPORT void Next();

  Standard_EXPORT occ::handle<MAT_Bisector> Bisector() const;

  Standard_EXPORT bool SemiInfinite() const;

  Standard_EXPORT int NumberOfBisectors() const;

private:
  Standard_EXPORT void LoadBisectorsToRemove(int&                             noofbisectorstoremove,
                                             const double                     distance1,
                                             const double                     distance2,
                                             const occ::handle<MAT_Bisector>& bisector1,
                                             const occ::handle<MAT_Bisector>& bisector2,
                                             const occ::handle<MAT_Bisector>& bisector3,
                                             const occ::handle<MAT_Bisector>& bisector4);

  Standard_EXPORT void Intersect(MAT2d_Tool2d&                    atool,
                                 const int                        aside,
                                 int&                             noofbisectorstoremove,
                                 const occ::handle<MAT_Bisector>& bisector1,
                                 const occ::handle<MAT_Bisector>& bisector2);

  bool                                                myIsOpenResult;
  int                                                 thenumberofbisectors;
  int                                                 thenumberofedges;
  bool                                                semiInfinite;
  occ::handle<MAT_ListOfEdge>                         theedgelist;
  occ::handle<MAT_ListOfEdge>                         RemovedEdgesList;
  NCollection_DataMap<int, int>                       typeofbisectortoremove;
  NCollection_DataMap<int, occ::handle<MAT_Bisector>> bisectoronetoremove;
  NCollection_DataMap<int, occ::handle<MAT_Bisector>> bisectortwotoremove;
  NCollection_DataMap<int, occ::handle<MAT_Bisector>> bisectormap;
  occ::handle<MAT_ListOfBisector>                     roots;
  bool                                                isDone;
};

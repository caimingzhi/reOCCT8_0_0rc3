#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <TColStd_PackedMapOfInteger.hpp>
#include <Standard_Boolean.hpp>
class Poly_Triangulation;

class Poly_Connect
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Poly_Connect();

  Standard_EXPORT Poly_Connect(const occ::handle<Poly_Triangulation>& theTriangulation);

  Standard_EXPORT void Load(const occ::handle<Poly_Triangulation>& theTriangulation);

  const occ::handle<Poly_Triangulation>& Triangulation() const { return myTriangulation; }

  int Triangle(const int N) const { return myTriangles(N); }

  void Triangles(const int T, int& t1, int& t2, int& t3) const
  {
    int index = 6 * (T - 1);
    t1        = myAdjacents(index + 1);
    t2        = myAdjacents(index + 2);
    t3        = myAdjacents(index + 3);
  }

  void Nodes(const int T, int& n1, int& n2, int& n3) const
  {
    int index = 6 * (T - 1);
    n1        = myAdjacents(index + 4);
    n2        = myAdjacents(index + 5);
    n3        = myAdjacents(index + 6);
  }

public:
  Standard_EXPORT void Initialize(const int N);

  bool More() const { return mymore; }

  Standard_EXPORT void Next();

  int Value() const { return mytr; }

private:
  occ::handle<Poly_Triangulation> myTriangulation;
  NCollection_Array1<int>         myTriangles;
  NCollection_Array1<int>         myAdjacents;
  int                             mytr;
  int                             myfirst;
  int                             mynode;
  int                             myothernode;
  bool                            mysense;
  bool                            mymore;
  TColStd_PackedMapOfInteger      myPassedTr;
};

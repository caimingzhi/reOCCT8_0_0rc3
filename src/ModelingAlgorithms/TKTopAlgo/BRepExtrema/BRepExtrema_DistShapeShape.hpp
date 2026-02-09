#pragma once

#include <Bnd_Box.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_Sequence.hpp>
#include <BRepExtrema_SolutionElem.hpp>
#include <BRepExtrema_SupportType.hpp>
#include <Extrema_ExtAlgo.hpp>
#include <Extrema_ExtFlag.hpp>
#include <Message_ProgressRange.hpp>
#include <TopoDS_Shape.hpp>
#include <Standard_OStream.hpp>
#include <Standard_DefineAlloc.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedMap.hpp>

class BRepExtrema_DistShapeShape
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepExtrema_DistShapeShape();

  Standard_EXPORT BRepExtrema_DistShapeShape(
    const TopoDS_Shape&          Shape1,
    const TopoDS_Shape&          Shape2,
    const Extrema_ExtFlag        F        = Extrema_ExtFlag_MINMAX,
    const Extrema_ExtAlgo        A        = Extrema_ExtAlgo_Grad,
    const Message_ProgressRange& theRange = Message_ProgressRange());

  Standard_EXPORT BRepExtrema_DistShapeShape(
    const TopoDS_Shape&          Shape1,
    const TopoDS_Shape&          Shape2,
    const double                 theDeflection,
    const Extrema_ExtFlag        F        = Extrema_ExtFlag_MINMAX,
    const Extrema_ExtAlgo        A        = Extrema_ExtAlgo_Grad,
    const Message_ProgressRange& theRange = Message_ProgressRange());

  void SetDeflection(const double theDeflection) { myEps = theDeflection; }

  Standard_EXPORT void LoadS1(const TopoDS_Shape& Shape1);

  Standard_EXPORT void LoadS2(const TopoDS_Shape& Shape1);

  Standard_EXPORT bool Perform(const Message_ProgressRange& theRange = Message_ProgressRange());

  bool IsDone() const { return myIsDone; }

  int NbSolution() const { return mySolutionsShape1.Length(); }

  Standard_EXPORT double Value() const;

  bool InnerSolution() const { return myInnerSol; }

  const gp_Pnt& PointOnShape1(const int N) const { return mySolutionsShape1.Value(N).Point(); }

  const gp_Pnt& PointOnShape2(const int N) const { return mySolutionsShape2.Value(N).Point(); }

  BRepExtrema_SupportType SupportTypeShape1(const int N) const
  {
    return mySolutionsShape1.Value(N).SupportKind();
  }

  BRepExtrema_SupportType SupportTypeShape2(const int N) const
  {
    return mySolutionsShape2.Value(N).SupportKind();
  }

  Standard_EXPORT TopoDS_Shape SupportOnShape1(const int N) const;

  Standard_EXPORT TopoDS_Shape SupportOnShape2(const int N) const;

  Standard_EXPORT void ParOnEdgeS1(const int N, double& t) const;

  Standard_EXPORT void ParOnEdgeS2(const int N, double& t) const;

  Standard_EXPORT void ParOnFaceS1(const int N, double& u, double& v) const;

  Standard_EXPORT void ParOnFaceS2(const int N, double& u, double& v) const;

  Standard_EXPORT void Dump(Standard_OStream& o) const;

  void SetFlag(const Extrema_ExtFlag F) { myFlag = F; }

  void SetAlgo(const Extrema_ExtAlgo A) { myAlgo = A; }

  void SetMultiThread(bool theIsMultiThread) { myIsMultiThread = theIsMultiThread; }

  bool IsMultiThread() const { return myIsMultiThread; }

private:
  bool DistanceMapMap(const NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& Map1,
                      const NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& Map2,
                      const NCollection_Array1<Bnd_Box>&                                   LBox1,
                      const NCollection_Array1<Bnd_Box>&                                   LBox2,
                      const Message_ProgressRange& theRange);

  bool DistanceVertVert(
    const NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& theMap1,
    const NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& theMap2,
    const Message_ProgressRange&                                         theRange);

  bool SolidTreatment(const TopoDS_Shape&                                                  theShape,
                      const NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& theMap,
                      const Message_ProgressRange& theRange);

private:
  double                                                        myDistRef;
  bool                                                          myIsDone;
  NCollection_Sequence<BRepExtrema_SolutionElem>                mySolutionsShape1;
  NCollection_Sequence<BRepExtrema_SolutionElem>                mySolutionsShape2;
  bool                                                          myInnerSol;
  double                                                        myEps;
  TopoDS_Shape                                                  myShape1;
  TopoDS_Shape                                                  myShape2;
  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> myMapV1;
  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> myMapV2;
  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> myMapE1;
  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> myMapE2;
  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> myMapF1;
  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> myMapF2;
  bool                                                          myIsInitS1;
  bool                                                          myIsInitS2;
  Extrema_ExtFlag                                               myFlag;
  Extrema_ExtAlgo                                               myAlgo;
  NCollection_Array1<Bnd_Box>                                   myBV1;
  NCollection_Array1<Bnd_Box>                                   myBV2;
  NCollection_Array1<Bnd_Box>                                   myBE1;
  NCollection_Array1<Bnd_Box>                                   myBE2;
  NCollection_Array1<Bnd_Box>                                   myBF1;
  NCollection_Array1<Bnd_Box>                                   myBF2;
  bool                                                          myIsMultiThread;
};

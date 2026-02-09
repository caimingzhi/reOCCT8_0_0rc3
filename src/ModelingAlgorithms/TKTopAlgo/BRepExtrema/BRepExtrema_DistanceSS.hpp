#pragma once

#include <NCollection_Sequence.hpp>
#include <BRepExtrema_SolutionElem.hpp>
#include <Extrema_ExtFlag.hpp>
#include <Extrema_ExtAlgo.hpp>
#include <Precision.hpp>
#include <Standard_DefineAlloc.hpp>

class TopoDS_Shape;
class Bnd_Box;
class TopoDS_Vertex;
class TopoDS_Edge;
class TopoDS_Face;

class BRepExtrema_DistanceSS
{
public:
  DEFINE_STANDARD_ALLOC

public:
  BRepExtrema_DistanceSS(const TopoDS_Shape&   theS1,
                         const TopoDS_Shape&   theS2,
                         const Bnd_Box&        theBox1,
                         const Bnd_Box&        theBox2,
                         const double          theDstRef,
                         const double          theDeflection = Precision::Confusion(),
                         const Extrema_ExtFlag theExtFlag    = Extrema_ExtFlag_MINMAX,
                         const Extrema_ExtAlgo theExtAlgo    = Extrema_ExtAlgo_Grad)
      : myDstRef(theDstRef),
        myModif(false),
        myEps(theDeflection),
        myFlag(theExtFlag),
        myAlgo(theExtAlgo)
  {
    Perform(theS1, theS2, theBox1, theBox2);
  }

public:
  bool IsDone() const { return myModif; }

  double DistValue() const { return myDstRef; }

  const NCollection_Sequence<BRepExtrema_SolutionElem>& Seq1Value() const { return mySeqSolShape1; }

  const NCollection_Sequence<BRepExtrema_SolutionElem>& Seq2Value() const { return mySeqSolShape2; }

private:
  Standard_EXPORT void Perform(const TopoDS_Shape& theS1,
                               const TopoDS_Shape& theS2,
                               const Bnd_Box&      theBox1,
                               const Bnd_Box&      theBox2);

  void Perform(const TopoDS_Vertex&                            S1,
               const TopoDS_Vertex&                            S2,
               NCollection_Sequence<BRepExtrema_SolutionElem>& theSeqSolShape1,
               NCollection_Sequence<BRepExtrema_SolutionElem>& theSeqSolShape2);

  void Perform(const TopoDS_Vertex&                            theS1,
               const TopoDS_Edge&                              theS2,
               NCollection_Sequence<BRepExtrema_SolutionElem>& theSeqSolShape1,
               NCollection_Sequence<BRepExtrema_SolutionElem>& theSeqSolShape2);

  void Perform(const TopoDS_Vertex&                            theS1,
               const TopoDS_Face&                              theS2,
               NCollection_Sequence<BRepExtrema_SolutionElem>& theSeqSolShape1,
               NCollection_Sequence<BRepExtrema_SolutionElem>& theSeqSolShape2);

  void Perform(const TopoDS_Edge&                              theS1,
               const TopoDS_Edge&                              theS2,
               NCollection_Sequence<BRepExtrema_SolutionElem>& theSeqSolShape1,
               NCollection_Sequence<BRepExtrema_SolutionElem>& theSeqSolShape2);

  void Perform(const TopoDS_Edge&                              theS1,
               const TopoDS_Face&                              theS2,
               NCollection_Sequence<BRepExtrema_SolutionElem>& theSeqSolShape1,
               NCollection_Sequence<BRepExtrema_SolutionElem>& theSeqSolShape2);

  void Perform(const TopoDS_Face&                              theS1,
               const TopoDS_Face&                              theS2,
               NCollection_Sequence<BRepExtrema_SolutionElem>& theSeqSolShape1,
               NCollection_Sequence<BRepExtrema_SolutionElem>& theSeqSolShape2);

private:
  NCollection_Sequence<BRepExtrema_SolutionElem> mySeqSolShape1;
  NCollection_Sequence<BRepExtrema_SolutionElem> mySeqSolShape2;
  double                                         myDstRef;
  bool                                           myModif;
  double                                         myEps;
  Extrema_ExtFlag                                myFlag;
  Extrema_ExtAlgo                                myAlgo;
};

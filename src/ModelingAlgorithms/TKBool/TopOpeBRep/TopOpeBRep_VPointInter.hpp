#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

class IntPatch_Point;
typedef IntPatch_Point* TopOpeBRep_PThePointOfIntersection;

#include <Standard_Integer.hpp>
#include <TopAbs_State.hpp>
#include <TopoDS_Shape.hpp>
#include <IntSurf_Transition.hpp>
#include <Standard_OStream.hpp>
class gp_Pnt;
class gp_Pnt2d;
class TopoDS_Edge;
class TopoDS_Face;

class TopOpeBRep_VPointInter
{
public:
  DEFINE_STANDARD_ALLOC

  TopOpeBRep_VPointInter();

  Standard_EXPORT void SetPoint(const IntPatch_Point& P);

  void SetShapes(const int I1, const int I2);

  void GetShapes(int& I1, int& I2) const;

  IntSurf_Transition TransitionOnS1() const;

  IntSurf_Transition TransitionOnS2() const;

  IntSurf_Transition TransitionLineArc1() const;

  IntSurf_Transition TransitionLineArc2() const;

  bool IsOnDomS1() const;

  bool IsOnDomS2() const;

  void ParametersOnS1(double& u, double& v) const;

  void ParametersOnS2(double& u, double& v) const;

  const gp_Pnt& Value() const;

  double Tolerance() const;

  Standard_EXPORT const TopoDS_Shape& ArcOnS1() const;

  Standard_EXPORT const TopoDS_Shape& ArcOnS2() const;

  double ParameterOnLine() const;

  double ParameterOnArc1() const;

  bool IsVertexOnS1() const;

  Standard_EXPORT const TopoDS_Shape& VertexOnS1() const;

  double ParameterOnArc2() const;

  bool IsVertexOnS2() const;

  Standard_EXPORT const TopoDS_Shape& VertexOnS2() const;

  bool IsInternal() const;

  bool IsMultiple() const;

  Standard_EXPORT TopAbs_State State(const int I) const;

  Standard_EXPORT void State(const TopAbs_State S, const int I);

  Standard_EXPORT void EdgeON(const TopoDS_Shape& Eon, const double Par, const int I);

  Standard_EXPORT const TopoDS_Shape& EdgeON(const int I) const;

  Standard_EXPORT double EdgeONParameter(const int I) const;

  int ShapeIndex() const;

  void ShapeIndex(const int I);

  Standard_EXPORT const TopoDS_Shape& Edge(const int I) const;

  Standard_EXPORT double EdgeParameter(const int I) const;

  Standard_EXPORT gp_Pnt2d SurfaceParameters(const int I) const;

  Standard_EXPORT bool IsVertex(const int I) const;

  Standard_EXPORT const TopoDS_Shape& Vertex(const int I) const;

  Standard_EXPORT void UpdateKeep();

  bool Keep() const;

  void ChangeKeep(const bool keep);

  Standard_EXPORT bool EqualpP(const TopOpeBRep_VPointInter& VP) const;

  Standard_EXPORT bool ParonE(const TopoDS_Edge& E, double& par) const;

  void Index(const int I);

  int Index() const;

  Standard_EXPORT Standard_OStream& Dump(const int          I,
                                         const TopoDS_Face& F,
                                         Standard_OStream&  OS) const;

  Standard_EXPORT Standard_OStream& Dump(const TopoDS_Face& F1,
                                         const TopoDS_Face& F2,
                                         Standard_OStream&  OS) const;

  Standard_EXPORT TopOpeBRep_PThePointOfIntersection PThePointOfIntersectionDummy() const;

private:
  TopOpeBRep_PThePointOfIntersection myPPOI;
  int                                myShapeIndex;
  TopAbs_State                       myState1;
  TopAbs_State                       myState2;
  bool                               myKeep;
  TopoDS_Shape                       myEdgeON1;
  TopoDS_Shape                       myEdgeON2;
  double                             myEdgeONPar1;
  double                             myEdgeONPar2;
  int                                myIndex;
  TopoDS_Shape                       myNullShape;
  int                                myS1;
  int                                myS2;
};

#include <IntPatch_Point.hpp>

inline TopOpeBRep_VPointInter::TopOpeBRep_VPointInter()
    : myPPOI(nullptr),
      myShapeIndex(0),
      myState1(TopAbs_UNKNOWN),
      myState2(TopAbs_UNKNOWN),
      myKeep(false),
      myEdgeONPar1(0.),
      myEdgeONPar2(0.),
      myIndex(0),
      myS1(0),
      myS2(0)
{
}

inline void TopOpeBRep_VPointInter::SetShapes(const int I1, const int I2)
{
  myS1 = I1;
  myS2 = I2;
}

inline void TopOpeBRep_VPointInter::GetShapes(int& I1, int& I2) const
{
  I1 = myS1;
  I2 = myS2;
}

inline IntSurf_Transition TopOpeBRep_VPointInter::TransitionOnS1() const
{
  return myPPOI->TransitionOnS1();
}

inline IntSurf_Transition TopOpeBRep_VPointInter::TransitionOnS2() const
{
  return myPPOI->TransitionOnS2();
}

inline IntSurf_Transition TopOpeBRep_VPointInter::TransitionLineArc1() const
{
  return myPPOI->TransitionLineArc1();
}

inline IntSurf_Transition TopOpeBRep_VPointInter::TransitionLineArc2() const
{
  return myPPOI->TransitionLineArc2();
}

inline bool TopOpeBRep_VPointInter::IsOnDomS1() const
{
  return myPPOI->IsOnDomS1();
}

inline bool TopOpeBRep_VPointInter::IsOnDomS2() const
{
  return myPPOI->IsOnDomS2();
}

inline void TopOpeBRep_VPointInter::ParametersOnS1(double& u, double& v) const
{
  myPPOI->ParametersOnS1(u, v);
}

inline void TopOpeBRep_VPointInter::ParametersOnS2(double& u, double& v) const
{
  myPPOI->ParametersOnS2(u, v);
}

inline const gp_Pnt& TopOpeBRep_VPointInter::Value() const
{
  return myPPOI->Value();
}

inline double TopOpeBRep_VPointInter::Tolerance() const
{
  return myPPOI->Tolerance();
}

inline double TopOpeBRep_VPointInter::ParameterOnLine() const
{
  return myPPOI->ParameterOnLine();
}

inline double TopOpeBRep_VPointInter::ParameterOnArc1() const
{
  return myPPOI->ParameterOnArc1();
}

inline double TopOpeBRep_VPointInter::ParameterOnArc2() const
{
  return myPPOI->ParameterOnArc2();
}

inline bool TopOpeBRep_VPointInter::IsVertexOnS1() const
{
  return myPPOI->IsVertexOnS1();
}

inline bool TopOpeBRep_VPointInter::IsVertexOnS2() const
{
  return myPPOI->IsVertexOnS2();
}

inline bool TopOpeBRep_VPointInter::IsMultiple() const
{
  return myPPOI->IsMultiple();
}

inline bool TopOpeBRep_VPointInter::IsInternal() const
{
  return false;
}

inline int TopOpeBRep_VPointInter::ShapeIndex() const
{
  return myShapeIndex;
}

inline void TopOpeBRep_VPointInter::ShapeIndex(const int I)
{
  myShapeIndex = I;
}

inline bool TopOpeBRep_VPointInter::Keep() const
{
  return myKeep;
}

inline void TopOpeBRep_VPointInter::ChangeKeep(const bool keep)
{
  myKeep = keep;
}

inline void TopOpeBRep_VPointInter::Index(const int I)
{
  myIndex = I;
}

inline int TopOpeBRep_VPointInter::Index() const
{
  return myIndex;
}

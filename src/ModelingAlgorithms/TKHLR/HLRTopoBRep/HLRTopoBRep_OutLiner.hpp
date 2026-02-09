#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TopoDS_Shape.hpp>
#include <HLRTopoBRep_Data.hpp>
#include <Standard_Transient.hpp>
#include <BRepTopAdaptor_Tool.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <Standard_Integer.hpp>
class HLRAlgo_Projector;
class TopoDS_Face;

class HLRTopoBRep_OutLiner : public Standard_Transient
{

public:
  Standard_EXPORT HLRTopoBRep_OutLiner();

  Standard_EXPORT HLRTopoBRep_OutLiner(const TopoDS_Shape& OriSh);

  Standard_EXPORT HLRTopoBRep_OutLiner(const TopoDS_Shape& OriS, const TopoDS_Shape& OutS);

  void OriginalShape(const TopoDS_Shape& OriS);

  TopoDS_Shape& OriginalShape();

  void OutLinedShape(const TopoDS_Shape& OutS);

  TopoDS_Shape& OutLinedShape();

  HLRTopoBRep_Data& DataStructure();

  Standard_EXPORT void Fill(
    const HLRAlgo_Projector&                                                         P,
    NCollection_DataMap<TopoDS_Shape, BRepTopAdaptor_Tool, TopTools_ShapeMapHasher>& MST,
    const int                                                                        nbIso);

  DEFINE_STANDARD_RTTIEXT(HLRTopoBRep_OutLiner, Standard_Transient)

private:
  Standard_EXPORT void ProcessFace(
    const TopoDS_Face&                                                               F,
    TopoDS_Shape&                                                                    S,
    NCollection_DataMap<TopoDS_Shape, BRepTopAdaptor_Tool, TopTools_ShapeMapHasher>& M);

  Standard_EXPORT void BuildShape(
    NCollection_DataMap<TopoDS_Shape, BRepTopAdaptor_Tool, TopTools_ShapeMapHasher>& M);

  TopoDS_Shape     myOriginalShape;
  TopoDS_Shape     myOutLinedShape;
  HLRTopoBRep_Data myDS;
};

inline void HLRTopoBRep_OutLiner::OriginalShape(const TopoDS_Shape& OriS)
{
  myOriginalShape = OriS;
}

inline TopoDS_Shape& HLRTopoBRep_OutLiner::OriginalShape()
{
  return myOriginalShape;
}

inline void HLRTopoBRep_OutLiner::OutLinedShape(const TopoDS_Shape& OutS)
{
  myOutLinedShape = OutS;
}

inline TopoDS_Shape& HLRTopoBRep_OutLiner::OutLinedShape()
{
  return myOutLinedShape;
}

inline HLRTopoBRep_Data& HLRTopoBRep_OutLiner::DataStructure()
{
  return myDS;
}

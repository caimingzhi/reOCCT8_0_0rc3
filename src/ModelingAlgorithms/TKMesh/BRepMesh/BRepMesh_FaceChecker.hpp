#pragma once

#include <IMeshTools_Parameters.hpp>
#include <Standard_Transient.hpp>
#include <IMeshData_Face.hpp>
#include <Standard_Type.hpp>
#include <NCollection_Shared.hpp>

class BRepMesh_FaceChecker : public Standard_Transient
{
public:
  struct Segment
  {
    IMeshData::IEdgePtr EdgePtr;
    gp_Pnt2d*           Point1;
    gp_Pnt2d*           Point2;

    Segment()
        : EdgePtr(nullptr),
          Point1(nullptr),
          Point2(nullptr)
    {
    }

    Segment(const IMeshData::IEdgePtr& theEdgePtr, gp_Pnt2d* thePoint1, gp_Pnt2d* thePoint2)
        : EdgePtr(theEdgePtr),
          Point1(thePoint1),
          Point2(thePoint2)
    {
    }
  };

  typedef NCollection_Shared<NCollection_Vector<Segment>>                         Segments;
  typedef NCollection_Shared<NCollection_Array1<occ::handle<Segments>>>           ArrayOfSegments;
  typedef NCollection_Shared<NCollection_Array1<Handle(IMeshData::BndBox2dTree)>> ArrayOfBndBoxTree;
  typedef NCollection_Shared<NCollection_Array1<Handle(IMeshData::MapOfIEdgePtr)>>
    ArrayOfMapOfIEdgePtr;

  Standard_EXPORT BRepMesh_FaceChecker(const IMeshData::IFaceHandle& theFace,
                                       const IMeshTools_Parameters&  theParameters);

  Standard_EXPORT ~BRepMesh_FaceChecker() override;

  Standard_EXPORT bool Perform();

  const Handle(IMeshData::MapOfIEdgePtr)& GetIntersectingEdges() const
  {
    return myIntersectingEdges;
  }

  void operator()(const int theWireIndex) const { perform(theWireIndex); }

  DEFINE_STANDARD_RTTIEXT(BRepMesh_FaceChecker, Standard_Transient)

private:
  bool isParallel() const { return (myParameters.InParallel && myDFace->WiresNb() > 1); }

  void collectSegments();

  void collectResult();

  void perform(const int theWireIndex) const;

private:
  BRepMesh_FaceChecker(const BRepMesh_FaceChecker& theOther) = delete;

  void operator=(const BRepMesh_FaceChecker& theOther) = delete;

private:
  IMeshData::IFaceHandle       myDFace;
  const IMeshTools_Parameters& myParameters;

  occ::handle<ArrayOfSegments>      myWiresSegments;
  occ::handle<ArrayOfBndBoxTree>    myWiresBndBoxTree;
  occ::handle<ArrayOfMapOfIEdgePtr> myWiresIntersectingEdges;
  Handle(IMeshData::MapOfIEdgePtr)  myIntersectingEdges;
};

#pragma once

#include <IMeshTools_Parameters.hpp>
#include <Standard_Transient.hpp>
#include <IMeshData_Face.hpp>
#include <Standard_Type.hpp>
#include <NCollection_Shared.hpp>

//! Auxiliary class checking wires of target face for self-intersections.
//! Explodes wires of discrete face on sets of segments using tessellation
//! data stored in model. Each segment is then checked for intersection with
//! other ones. All collisions are registered and returned as result of check.
class BRepMesh_FaceChecker : public Standard_Transient
{
public: //! @name mesher API
  //! Identifies segment inside face.
  struct Segment
  {
    IMeshData::IEdgePtr EdgePtr;
    gp_Pnt2d*           Point1; // \ Use explicit pointers to points instead of accessing
    gp_Pnt2d*           Point2; // / using indices.

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

  //! Default constructor
  Standard_EXPORT BRepMesh_FaceChecker(const IMeshData::IFaceHandle& theFace,
                                       const IMeshTools_Parameters&  theParameters);

  //! Destructor
  Standard_EXPORT ~BRepMesh_FaceChecker() override;

  //! Performs check wires of the face for intersections.
  //! @return True if there is no intersection, False elsewhere.
  Standard_EXPORT bool Perform();

  //! Returns intersecting edges.
  const Handle(IMeshData::MapOfIEdgePtr)& GetIntersectingEdges() const
  {
    return myIntersectingEdges;
  }

  //! Checks wire with the given index for intersection with others.
  void operator()(const int theWireIndex) const { perform(theWireIndex); }

  DEFINE_STANDARD_RTTIEXT(BRepMesh_FaceChecker, Standard_Transient)

private:
  //! Returns True in case if check can be performed in parallel mode.
  bool isParallel() const { return (myParameters.InParallel && myDFace->WiresNb() > 1); }

  //! Collects face segments.
  void collectSegments();

  //! Collects intersecting edges.
  void collectResult();

  //! Checks wire with the given index for intersection with others.
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

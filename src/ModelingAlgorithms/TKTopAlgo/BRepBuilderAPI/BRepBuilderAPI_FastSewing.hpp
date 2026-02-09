#pragma once

#include <Standard_Transient.hpp>
#include <BRep_Builder.hpp>

#include <NCollection_List.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_Vector.hpp>
#include <NCollection_CellFilter.hpp>

#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Vertex.hpp>
#include <TopoDS_Wire.hpp>

class BRepBuilderAPI_FastSewing : public Standard_Transient
{
public:
  typedef unsigned int FS_VARStatuses;

  enum FS_Statuses
  {
    FS_OK                   = 0x00000000,
    FS_Degenerated          = 0x00000001,
    FS_FindVertexError      = 0x00000002,
    FS_FindEdgeError        = 0x00000004,
    FS_FaceWithNullSurface  = 0x00000008,
    FS_NotNaturalBoundsFace = 0x00000010,
    FS_InfiniteSurface      = 0x00000020,
    FS_EmptyInput           = 0x00000040,
    FS_Exception            = 0x00000080
  };

  Standard_EXPORT BRepBuilderAPI_FastSewing(const double theTolerance = 1.0e-06);

  Standard_EXPORT bool Add(const TopoDS_Shape& theShape);

  Standard_EXPORT bool Add(const occ::handle<Geom_Surface>& theSurface);

  Standard_EXPORT void Perform();

  void SetTolerance(const double theToler) { myTolerance = theToler; }

  double GetTolerance() const { return myTolerance; }

  const TopoDS_Shape& GetResult() const { return myResShape; }

  Standard_EXPORT FS_VARStatuses GetStatuses(Standard_OStream* const theOS = nullptr);

  DEFINE_STANDARD_RTTIEXT(BRepBuilderAPI_FastSewing, Standard_Transient)

protected:
  class NodeInspector;

  Standard_EXPORT void FindVertexes(const int                              theSurfID,
                                    NCollection_CellFilter<NodeInspector>& theCells);
  Standard_EXPORT void FindEdges(const int theSurfID);
  Standard_EXPORT void UpdateEdgeInfo(const int theIDPrevVertex,
                                      const int theIDCurrVertex,
                                      const int theFaceID,
                                      const int theIDCurvOnFace);
  Standard_EXPORT void CreateNewEdge(const int theIDPrevVertex,
                                     const int theIDCurrVertex,
                                     const int theFaceID,
                                     const int theIDCurvOnFace);

  Standard_EXPORT double Compute3DRange();

  FS_VARStatuses SetStatus(FS_Statuses theStatus)
  {
    const FS_VARStatuses aStatusID = (FS_VARStatuses)(theStatus);
    myStatusList |= aStatusID;
    return aStatusID;
  }

  class FS_Edge;

  struct FS_Vertex
  {
  public:
    FS_Vertex()
        : myID(-1) {};

    void CreateTopologicalVertex(const double theToler)
    {
      BRep_Builder aBuilder;
      aBuilder.MakeVertex(myTopoVert, myPnt, theToler);
    }

    gp_Pnt        myPnt;
    TopoDS_Vertex myTopoVert;

    NCollection_List<int> myFaces;
    NCollection_List<int> myEdges;

    int myID;
  };

  struct FS_Face
  {
    FS_Face()
        : myID(-1)
    {
      for (int i = 0; i < 4; i++)
      {
        myVertices[i] = -1;
        myEdges[i]    = -1;
      }
    };

    void CreateTopologicalWire(const NCollection_Vector<FS_Edge>& theEdgeVec,
                               const double                       theToler);
    void CreateTopologicalFace();

    void SetVertex(const int thePlaceID, const int theVertID)
    {
      Standard_RangeError_Raise_if((thePlaceID < 0) || (thePlaceID > 3),
                                   "FS_Face::SetVertex(): OUT of Range");

      myVertices[thePlaceID] = theVertID;
    }

    void SetEdge(const int thePlaceID, const int theEdgeID)
    {
      Standard_RangeError_Raise_if((thePlaceID < 0) || (thePlaceID > 3),
                                   "FS_Face::SetEdge(): OUT of Range");

      myEdges[thePlaceID] = theEdgeID;
    }

    TopoDS_Face mySrcFace;
    TopoDS_Wire myWire;
    TopoDS_Face myRetFace;

    int myEdges[4];

    int myVertices[4];

    int myID;
  };

  class FS_Edge
  {
  public:
    FS_Edge()
        : myID(-1)
    {
      myVertices[0] = -1;
      myVertices[1] = -1;
    }

    FS_Edge(const int theIDVert1, const int theIDVert2)
        : myID(-1)
    {
      myVertices[0] = theIDVert1;
      myVertices[1] = theIDVert2;
    };

    void CreateTopologicalEdge(const NCollection_Vector<FS_Vertex>& theVertexVec,
                               const NCollection_Vector<FS_Face>&   theFaceVec,
                               const double                         theTol);

    void SetVertex(const int thePlaceID, const int theVertID)
    {
      Standard_RangeError_Raise_if((thePlaceID < 0) || (thePlaceID > 1),
                                   "FS_Face::SetVertex(): OUT of Range");

      myVertices[thePlaceID] = theVertID;
    }

    bool IsDegenerated() const { return (myVertices[0] == myVertices[1]); }

    NCollection_Sequence<int> myFaces;

    int myID;

    TopoDS_Edge myTopoEdge;

  private:
    int myVertices[2];
  };

  class NodeInspector : public NCollection_CellFilter_InspectorXYZ
  {
  public:
    typedef int Target;

    NodeInspector(const NCollection_Vector<FS_Vertex>& theVec,
                  const gp_Pnt&                        thePnt,
                  const double                         theTol);

    Standard_EXPORT NCollection_CellFilter_Action Inspect(const Target theId);

    Target GetResult() { return myResID; }

  private:
    NodeInspector&                       operator=(const NodeInspector&) = delete;
    const NCollection_Vector<FS_Vertex>& myVecOfVertexes;
    gp_Pnt                               myPoint;
    double                               mySQToler;
    Target                               myResID;
  };

private:
  TopoDS_Shape myResShape;

  NCollection_Vector<FS_Face> myFaceVec;

  NCollection_Vector<FS_Vertex> myVertexVec;

  NCollection_Vector<FS_Edge> myEdgeVec;

  double myTolerance;

  FS_VARStatuses myStatusList;
};

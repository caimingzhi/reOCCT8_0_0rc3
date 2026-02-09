#pragma once

#include <Standard_Transient.hpp>
#include <BRepMesh_DataStructureOfDelaun.hpp>
#include <BRepMesh_CircleTool.hpp>
#include <gp_Lin2d.hpp>
#include <IMeshData_Types.hpp>
#include <BRepMesh_Edge.hpp>

#include <stack>

class BRepMesh_MeshTool : public Standard_Transient
{
public:
  class NodeClassifier
  {
  public:
    NodeClassifier(const BRepMesh_Edge&                               theConstraint,
                   const occ::handle<BRepMesh_DataStructureOfDelaun>& theStructure)
        : myStructure(theStructure)
    {
      const BRepMesh_Vertex& aVertex1 = myStructure->GetNode(theConstraint.FirstNode());
      const BRepMesh_Vertex& aVertex2 = myStructure->GetNode(theConstraint.LastNode());

      myConstraint.SetLocation(aVertex1.Coord());
      myConstraint.SetDirection(gp_Vec2d(aVertex1.Coord(), aVertex2.Coord()));
      mySign = myConstraint.Direction().X() > 0;
    }

    bool IsAbove(const int theNodeIndex) const
    {
      const BRepMesh_Vertex& aVertex = myStructure->GetNode(theNodeIndex);
      const gp_Vec2d         aNodeVec(myConstraint.Location(), aVertex.Coord());
      if (aNodeVec.SquareMagnitude() > gp::Resolution())
      {
        const double aCross = aNodeVec.Crossed(myConstraint.Direction());
        if (std::abs(aCross) > gp::Resolution())
        {
          return mySign ? aCross < 0. : aCross > 0.;
        }
      }

      return false;
    }

  private:
    NodeClassifier(const NodeClassifier& theOther) = delete;

    void operator=(const NodeClassifier& theOther) = delete;

  private:
    const occ::handle<BRepMesh_DataStructureOfDelaun>& myStructure;
    gp_Lin2d                                           myConstraint;
    bool                                               mySign;
  };

  Standard_EXPORT BRepMesh_MeshTool(
    const occ::handle<BRepMesh_DataStructureOfDelaun>& theStructure);

  Standard_EXPORT ~BRepMesh_MeshTool() override;

  const occ::handle<BRepMesh_DataStructureOfDelaun>& GetStructure() const { return myStructure; }

  void DumpTriangles(const char* theFileName, IMeshData::MapOfInteger* theTriangles);

  void AddAndLegalizeTriangle(const int thePoint1, const int thePoint2, const int thePoint3)
  {
    int aEdges[3];
    AddTriangle(thePoint1, thePoint2, thePoint3, aEdges);

    Legalize(aEdges[0]);
    Legalize(aEdges[1]);
    Legalize(aEdges[2]);
  }

  void AddTriangle(const int thePoint1,
                   const int thePoint2,
                   const int thePoint3,
                   int (&theEdges)[3])
  {
    bool aOri[3];
    AddLink(thePoint1, thePoint2, theEdges[0], aOri[0]);
    AddLink(thePoint2, thePoint3, theEdges[1], aOri[1]);
    AddLink(thePoint3, thePoint1, theEdges[2], aOri[2]);

    myStructure->AddElement(BRepMesh_Triangle(theEdges, aOri, BRepMesh_Free));
  }

  void AddLink(const int theFirstNode, const int theLastNode, int& theLinkIndex, bool& theLinkOri)
  {
    const int aLinkIt =
      myStructure->AddLink(BRepMesh_Edge(theFirstNode, theLastNode, BRepMesh_Free));

    theLinkIndex = std::abs(aLinkIt);
    theLinkOri   = (aLinkIt > 0);
  }

  Standard_EXPORT void Legalize(const int theLinkIndex);

  Standard_EXPORT void EraseItemsConnectedTo(const int theNodeIndex);

  Standard_EXPORT void CleanFrontierLinks();

  void EraseTriangles(const IMeshData::MapOfInteger&  theTriangles,
                      IMeshData::MapOfIntegerInteger& theLoopEdges);

  Standard_EXPORT void EraseTriangle(const int                       theTriangleIndex,
                                     IMeshData::MapOfIntegerInteger& theLoopEdges);

  Standard_EXPORT void EraseFreeLinks();

  Standard_EXPORT void EraseFreeLinks(const IMeshData::MapOfIntegerInteger& theLinks);

  Standard_EXPORT Handle(IMeshData::MapOfInteger) GetEdgesByType(
    const BRepMesh_DegreeOfFreedom theEdgeType) const;

  DEFINE_STANDARD_RTTIEXT(BRepMesh_MeshTool, Standard_Transient)

private:
  bool checkCircle(const int (&aNodes)[3], const int thePoint)
  {
    const BRepMesh_Vertex& aVertex0 = myStructure->GetNode(aNodes[0]);
    const BRepMesh_Vertex& aVertex1 = myStructure->GetNode(aNodes[1]);
    const BRepMesh_Vertex& aVertex2 = myStructure->GetNode(aNodes[2]);

    gp_XY      aLocation;
    double     aRadius;
    const bool isOk = BRepMesh_CircleTool::MakeCircle(aVertex0.Coord(),
                                                      aVertex1.Coord(),
                                                      aVertex2.Coord(),
                                                      aLocation,
                                                      aRadius);

    if (isOk)
    {
      const BRepMesh_Vertex& aVertex = myStructure->GetNode(thePoint);
      const double aDist = (aVertex.Coord() - aLocation).SquareModulus() - (aRadius * aRadius);
      return (aDist < Precision::SquareConfusion());
    }

    return false;
  }

  void addTriangleAndUpdateStack(const int                      theNode0,
                                 const int                      theNode1,
                                 const int                      theNode2,
                                 const IMeshData::MapOfInteger& theUsedLinks,
                                 std::stack<int>&               theStack)
  {
    int aEdges[3];
    AddTriangle(theNode0, theNode1, theNode2, aEdges);

    for (int i = 0; i < 3; ++i)
    {
      if (!theUsedLinks.Contains(aEdges[i]))
      {
        theStack.push(aEdges[i]);
      }
    }
  }

  void collectTrianglesOnFreeLinksAroundNodesOf(const BRepMesh_Edge&     theConstraint,
                                                const int                theStartLink,
                                                IMeshData::MapOfInteger& theTriangles);

private:
  occ::handle<BRepMesh_DataStructureOfDelaun> myStructure;
};

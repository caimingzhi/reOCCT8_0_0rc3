#pragma once

#include <Poly_Triangulation.hpp>
#include <RWMesh_CoordinateSystemConverter.hpp>

#include <mutex>

class OSD_FileSystem;
class RWMesh_TriangulationSource;

class RWMesh_TriangulationReader : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(RWMesh_TriangulationReader, Standard_Transient)
public:
  struct LoadingStatistic
  {
    LoadingStatistic()
        : ExpectedNodesNb(0),
          LoadedNodesNb(0),
          ExpectedTrianglesNb(0),
          DegeneratedTrianglesNb(0),
          LoadedTrianglesNb(0)
    {
    }

    void Reset()
    {
      ExpectedNodesNb        = 0;
      LoadedNodesNb          = 0;
      ExpectedTrianglesNb    = 0;
      DegeneratedTrianglesNb = 0;
      LoadedTrianglesNb      = 0;
    }

    Standard_EXPORT void PrintStatistic(const TCollection_AsciiString& thePrefix = "") const;

    int ExpectedNodesNb;
    int LoadedNodesNb;
    int ExpectedTrianglesNb;
    int DegeneratedTrianglesNb;
    int LoadedTrianglesNb;
  };

  Standard_EXPORT RWMesh_TriangulationReader();

  Standard_EXPORT ~RWMesh_TriangulationReader() override;

  const TCollection_AsciiString& FileName() const { return myFileName; }

  void SetFileName(const TCollection_AsciiString& theFileName) { myFileName = theFileName; }

  const RWMesh_CoordinateSystemConverter& CoordinateSystemConverter() const
  {
    return myCoordSysConverter;
  }

  void SetCoordinateSystemConverter(const RWMesh_CoordinateSystemConverter& theConverter)
  {
    myCoordSysConverter = theConverter;
  }

  bool IsDoublePrecision() const { return myIsDoublePrecision; }

  void SetDoublePrecision(bool theIsDouble) { myIsDoublePrecision = theIsDouble; }

  bool ToSkipDegenerates() const { return myToSkipDegenerateTris; }

  void SetToSkipDegenerates(const bool theToSkip) { myToSkipDegenerateTris = theToSkip; }

  bool ToPrintDebugMessages() const { return myToPrintDebugMessages; }

  void SetToPrintDebugMessages(const bool theToPrint) { myToPrintDebugMessages = theToPrint; }

  void StartStatistic()
  {
    if (myLoadingStatistic)
    {
      myLoadingStatistic->Reset();
    }
    else
    {
      myLoadingStatistic = new LoadingStatistic();
    }
  }

  void StopStatistic()
  {
    if (myLoadingStatistic)
    {
      delete myLoadingStatistic;
      myLoadingStatistic = nullptr;
    }
  }

  void PrintStatistic() const
  {
    if (myLoadingStatistic)
    {
      myLoadingStatistic->PrintStatistic(TCollection_AsciiString("[Mesh reader. File '")
                                         + myFileName + "']. ");
    }
  }

  Standard_EXPORT bool Load(const occ::handle<RWMesh_TriangulationSource>& theSourceMesh,
                            const occ::handle<Poly_Triangulation>&         theDestMesh,
                            const occ::handle<OSD_FileSystem>&             theFileSystem) const;

protected:
  Standard_EXPORT virtual bool load(const occ::handle<RWMesh_TriangulationSource>& theSourceMesh,
                                    const occ::handle<Poly_Triangulation>&         theDestMesh,
                                    const occ::handle<OSD_FileSystem>& theFileSystem) const = 0;

  Standard_EXPORT virtual bool finalizeLoading(
    const occ::handle<RWMesh_TriangulationSource>& theSourceMesh,
    const occ::handle<Poly_Triangulation>&         theDestMesh) const;

protected:
  virtual bool setNbPositionNodes(const occ::handle<Poly_Triangulation>& theMesh,
                                  int                                    theNbNodes,
                                  bool theToCopyData = false) const
  {
    if (theNbNodes <= 0)
    {
      return false;
    }
    theMesh->ResizeNodes(theNbNodes, theToCopyData);
    return true;
  }

  virtual void setNodePosition(const occ::handle<Poly_Triangulation>& theMesh,
                               int                                    theIndex,
                               const gp_Pnt&                          thePnt) const
  {
    theMesh->SetNode(theIndex, thePnt);
  }

  virtual bool setNbUVNodes(const occ::handle<Poly_Triangulation>& theMesh, int theNbNodes) const
  {
    if (theNbNodes <= 0 || theMesh->NbNodes() != theNbNodes)
    {
      return false;
    }
    theMesh->AddUVNodes();
    return true;
  }

  virtual void setNodeUV(const occ::handle<Poly_Triangulation>& theMesh,
                         int                                    theIndex,
                         const gp_Pnt2d&                        theUV) const
  {
    theMesh->SetUVNode(theIndex, theUV);
  }

  virtual bool setNbNormalNodes(const occ::handle<Poly_Triangulation>& theMesh,
                                int                                    theNbNodes) const
  {
    if (theNbNodes <= 0 || theMesh->NbNodes() != theNbNodes)
    {
      return false;
    }
    theMesh->AddNormals();
    return true;
  }

  virtual void setNodeNormal(const occ::handle<Poly_Triangulation>& theMesh,
                             int                                    theIndex,
                             const NCollection_Vec3<float>&         theNormal) const
  {
    theMesh->SetNormal(theIndex, theNormal);
  }

  virtual bool setNbTriangles(const occ::handle<Poly_Triangulation>& theMesh,
                              int                                    theNbTris,
                              bool                                   theToCopyData = false) const
  {
    if (theNbTris >= 1)
    {
      theMesh->ResizeTriangles(theNbTris, theToCopyData);
      return true;
    }
    return false;
  }

  virtual int setTriangle(const occ::handle<Poly_Triangulation>& theMesh,
                          int                                    theIndex,
                          const Poly_Triangle&                   theTriangle) const
  {
    if (theTriangle.Value(1) < 1 || theTriangle.Value(1) > theMesh->NbNodes()
        || theTriangle.Value(2) < 1 || theTriangle.Value(2) > theMesh->NbNodes()
        || theTriangle.Value(3) < 1 || theTriangle.Value(3) > theMesh->NbNodes())
    {
      return 0;
    }
    if (myToSkipDegenerateTris
        && (theTriangle.Value(1) == theTriangle.Value(2)
            || theTriangle.Value(1) == theTriangle.Value(3)
            || theTriangle.Value(2) == theTriangle.Value(3)))
    {
      return -1;
    }
    theMesh->SetTriangle(theIndex, theTriangle);
    return 1;
  }

  Standard_EXPORT virtual bool setNbEdges(const occ::handle<Poly_Triangulation>& theMesh,
                                          const int                              theNbEdges,
                                          const bool theToCopyData = false) const;

  Standard_EXPORT virtual int setEdge(const occ::handle<Poly_Triangulation>& theMesh,
                                      const int                              theIndex,
                                      const int                              theEdge) const;

protected:
  RWMesh_CoordinateSystemConverter myCoordSysConverter;

  TCollection_AsciiString   myFileName;
  mutable std::mutex        myMutex;
  mutable LoadingStatistic* myLoadingStatistic;
  bool                      myIsDoublePrecision;
  bool                      myToSkipDegenerateTris;
  bool                      myToPrintDebugMessages;
};

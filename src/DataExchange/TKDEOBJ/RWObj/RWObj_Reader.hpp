#pragma once

#include <Message.hpp>
#include <Message_Messenger.hpp>
#include <Message_ProgressRange.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_DataMap.hpp>
#include <NCollection_IndexedMap.hpp>
#include <NCollection_Vector.hpp>
#include <NCollection_Shared.hpp>
#include <OSD_OpenFile.hpp>
#include <RWMesh_CoordinateSystemConverter.hpp>
#include <RWObj_Material.hpp>

#include <TCollection_AsciiString.hpp>

struct RWObj_SubMesh
{
  TCollection_AsciiString Object;
  TCollection_AsciiString Group;
  TCollection_AsciiString SmoothGroup;
  TCollection_AsciiString Material;
};

enum RWObj_SubMeshReason
{
  RWObj_SubMeshReason_NewObject,

  RWObj_SubMeshReason_NewGroup,
  RWObj_SubMeshReason_NewMaterial,
  RWObj_SubMeshReason_NewSmoothGroup
};

#include <RWObj_Tools.hpp>
#include <Standard_HashUtils.hpp>

#include <vector>

class RWObj_Reader : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(RWObj_Reader, Standard_Transient)
public:
  Standard_EXPORT RWObj_Reader();

  bool Read(const TCollection_AsciiString& theFile, const Message_ProgressRange& theProgress)
  {
    std::ifstream aStream;
    OSD_OpenStream(aStream, theFile, std::ios_base::in | std::ios_base::binary);
    return Read(aStream, theFile, theProgress);
  }

  bool Read(std::istream&                  theStream,
            const TCollection_AsciiString& theFile,
            const Message_ProgressRange&   theProgress)
  {
    return read(theStream, theFile, theProgress, false);
  }

  bool Probe(const TCollection_AsciiString& theFile, const Message_ProgressRange& theProgress)
  {
    std::ifstream aStream;
    OSD_OpenStream(aStream, theFile, std::ios_base::in | std::ios_base::binary);
    return Probe(aStream, theFile, theProgress);
  }

  bool Probe(std::istream&                  theStream,
             const TCollection_AsciiString& theFile,
             const Message_ProgressRange&   theProgress)
  {
    return read(theStream, theFile, theProgress, true);
  }

  const TCollection_AsciiString& FileComments() const { return myFileComments; }

  const NCollection_IndexedMap<TCollection_AsciiString>& ExternalFiles() const
  {
    return myExternalFiles;
  }

  int NbProbeNodes() const { return myNbProbeNodes; }

  int NbProbeElems() const { return myNbProbeElems; }

  size_t MemoryLimit() const { return myMemLimitBytes; }

  void SetMemoryLimit(size_t theMemLimit) { myMemLimitBytes = theMemLimit; }

  const RWMesh_CoordinateSystemConverter& Transformation() const { return myCSTrsf; }

  void SetTransformation(const RWMesh_CoordinateSystemConverter& theCSConverter)
  {
    myCSTrsf = theCSConverter;
  }

  bool IsSinglePrecision() const { return myObjVerts.IsSinglePrecision(); }

  void SetSinglePrecision(bool theIsSinglePrecision)
  {
    myObjVerts.SetSinglePrecision(theIsSinglePrecision);
  }

protected:
  Standard_EXPORT bool read(std::istream&                  theStream,
                            const TCollection_AsciiString& theFile,
                            const Message_ProgressRange&   theProgress,
                            const bool                     theToProbe);

protected:
  virtual bool addMesh(const RWObj_SubMesh& theMesh, const RWObj_SubMeshReason theReason) = 0;

  virtual gp_Pnt getNode(int theIndex) const = 0;

  virtual int addNode(const gp_Pnt& thePnt) = 0;

  virtual void setNodeNormal(const int theIndex, const NCollection_Vec3<float>& theNorm) = 0;

  virtual void setNodeUV(const int theIndex, const NCollection_Vec2<float>& theUV) = 0;

  virtual void addElement(int theN1, int theN2, int theN3, int theN4) = 0;

private:
  void pushVertex(const char* theXYZ)
  {
    char*  aNext = nullptr;
    gp_Pnt anXYZ;
    RWObj_Tools::ReadVec3(theXYZ, aNext, anXYZ.ChangeCoord());
    myCSTrsf.TransformPosition(anXYZ.ChangeCoord());

    myMemEstim += myObjVerts.IsSinglePrecision() ? sizeof(NCollection_Vec3<float>) : sizeof(gp_Pnt);
    myObjVerts.Append(anXYZ);
  }

  void pushNormal(const char* theXYZ)
  {
    char*                   aNext = nullptr;
    NCollection_Vec3<float> aNorm;
    RWObj_Tools::ReadVec3(theXYZ, aNext, aNorm);
    myCSTrsf.TransformNormal(aNorm);

    myMemEstim += sizeof(NCollection_Vec3<float>);
    myObjNorms.Append(aNorm);
  }

  void pushTexel(const char* theUV)
  {
    char*                   aNext = nullptr;
    NCollection_Vec2<float> anUV;
    anUV.x() = (float)Strtod(theUV, &aNext);
    theUV    = aNext;
    anUV.y() = (float)Strtod(theUV, &aNext);

    myMemEstim += sizeof(NCollection_Vec2<float>);
    myObjVertsUV.Append(anUV);
  }

  void pushIndices(const char* thePos);

  gp_XYZ polygonCenter(const NCollection_Array1<int>& theIndices);

  gp_XYZ polygonNormal(const NCollection_Array1<int>& theIndices);

  int triangulatePolygonFan(const NCollection_Array1<int>& theIndices);

  int triangulatePolygon(const NCollection_Array1<int>& theIndices);

  void pushObject(const char* theObjectName);

  void pushGroup(const char* theGroupName);

  void pushSmoothGroup(const char* theSmoothGroupIndex);

  void pushMaterial(const char* theMaterialName);

  void readMaterialLib(const char* theFileName);

  bool checkMemory();

protected:
  struct ObjVec3iHasher
  {
    std::size_t operator()(const NCollection_Vec3<int>& theKey) const noexcept
    {
      return opencascade::hashBytes(&theKey[0], 3 * sizeof(int));
    }

    bool operator()(const NCollection_Vec3<int>& theKey1,
                    const NCollection_Vec3<int>& theKey2) const noexcept
    {
      return theKey1[0] == theKey2[0] && theKey1[1] == theKey2[1] && theKey1[2] == theKey2[2];
    }
  };

  class VectorOfVertices
  {
  public:
    VectorOfVertices()
        : myIsSinglePrecision(false)
    {
    }

    bool IsSinglePrecision() const { return myIsSinglePrecision; }

    void SetSinglePrecision(bool theIsSinglePrecision)
    {
      myIsSinglePrecision = theIsSinglePrecision;
      myPntVec.Nullify();
      myVec3Vec.Nullify();
    }

    void Reset()
    {
      if (myIsSinglePrecision)
      {
        myVec3Vec = new NCollection_Shared<NCollection_Vector<NCollection_Vec3<float>>>();
      }
      else
      {
        myPntVec = new NCollection_Shared<NCollection_Vector<gp_Pnt>>();
      }
    }

    int Lower() const { return 0; }

    int Upper() const { return myIsSinglePrecision ? myVec3Vec->Upper() : myPntVec->Upper(); }

    gp_Pnt Value(int theIndex) const
    {
      if (myIsSinglePrecision)
      {
        const NCollection_Vec3<float>& aPnt = myVec3Vec->Value(theIndex);
        return gp_Pnt(aPnt.x(), aPnt.y(), aPnt.z());
      }
      else
      {
        return myPntVec->Value(theIndex);
      }
    }

    void Append(const gp_Pnt& thePnt)
    {
      if (myIsSinglePrecision)
      {
        myVec3Vec->Append(
          NCollection_Vec3<float>((float)thePnt.X(), (float)thePnt.Y(), (float)thePnt.Z()));
      }
      else
      {
        myPntVec->Append(thePnt);
      }
    }

  private:
    Handle(NCollection_Shared<NCollection_Vector<gp_Pnt>>)                  myPntVec;
    Handle(NCollection_Shared<NCollection_Vector<NCollection_Vec3<float>>>) myVec3Vec;
    bool                                                                    myIsSinglePrecision;
  };

protected:
  NCollection_IndexedMap<TCollection_AsciiString> myExternalFiles;
  TCollection_AsciiString                         myFileComments;
  TCollection_AsciiString                         myFolder;
  RWMesh_CoordinateSystemConverter                myCSTrsf;
  size_t                                          myMemLimitBytes;
  size_t                                          myMemEstim;

  int  myNbLines;
  int  myNbProbeNodes;
  int  myNbProbeElems;
  int  myNbElemsBig;
  bool myToAbort;

  VectorOfVertices                                                myObjVerts;
  NCollection_Vector<NCollection_Vec2<float>>                     myObjVertsUV;
  NCollection_Vector<NCollection_Vec3<float>>                     myObjNorms;
  NCollection_DataMap<NCollection_Vec3<int>, int, ObjVec3iHasher> myPackedIndices;
  NCollection_DataMap<TCollection_AsciiString, RWObj_Material>    myMaterials;

  RWObj_SubMesh    myActiveSubMesh;
  std::vector<int> myCurrElem;
};

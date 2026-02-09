#pragma once

#include <Bnd_Box.hpp>
#include <Poly_Triangle.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Poly_ArrayOfNodes.hpp>
#include <Poly_ArrayOfUVNodes.hpp>

typedef unsigned int Poly_MeshPurpose;

enum
{

  Poly_MeshPurpose_NONE         = 0,
  Poly_MeshPurpose_Calculation  = 0x0001,
  Poly_MeshPurpose_Presentation = 0x0002,

  Poly_MeshPurpose_Active      = 0x0004,
  Poly_MeshPurpose_Loaded      = 0x0008,
  Poly_MeshPurpose_AnyFallback = 0x0010,

  Poly_MeshPurpose_USER = 0x0020
};

#include <gp_Pnt.hpp>
#include <gp_Pnt2d.hpp>
#include <Standard_ShortReal.hpp>

class OSD_FileSystem;
class Poly_Triangulation;
class Poly_TriangulationParameters;

class Poly_Triangulation : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(Poly_Triangulation, Standard_Transient)
public:
  Standard_EXPORT Poly_Triangulation();

  Standard_EXPORT Poly_Triangulation(const int  theNbNodes,
                                     const int  theNbTriangles,
                                     const bool theHasUVNodes,
                                     const bool theHasNormals = false);

  Standard_EXPORT Poly_Triangulation(const NCollection_Array1<gp_Pnt>&        Nodes,
                                     const NCollection_Array1<Poly_Triangle>& Triangles);

  Standard_EXPORT Poly_Triangulation(const NCollection_Array1<gp_Pnt>&        Nodes,
                                     const NCollection_Array1<gp_Pnt2d>&      UVNodes,
                                     const NCollection_Array1<Poly_Triangle>& Triangles);

  Standard_EXPORT ~Poly_Triangulation() override;

  Standard_EXPORT virtual occ::handle<Poly_Triangulation> Copy() const;

  Standard_EXPORT Poly_Triangulation(const occ::handle<Poly_Triangulation>& theTriangulation);

  double Deflection() const { return myDeflection; }

  void Deflection(const double theDeflection) { myDeflection = theDeflection; }

  const occ::handle<Poly_TriangulationParameters>& Parameters() const { return myParams; }

  void Parameters(const occ::handle<Poly_TriangulationParameters>& theParams)
  {
    myParams = theParams;
  }

  Standard_EXPORT virtual void Clear();

  virtual bool HasGeometry() const { return !myNodes.IsEmpty() && !myTriangles.IsEmpty(); }

  int NbNodes() const { return myNodes.Length(); }

  int NbTriangles() const { return myTriangles.Length(); }

  bool HasUVNodes() const { return !myUVNodes.IsEmpty(); }

  bool HasNormals() const { return !myNormals.IsEmpty(); }

  gp_Pnt Node(int theIndex) const { return myNodes.Value(theIndex - 1); }

  void SetNode(int theIndex, const gp_Pnt& thePnt) { myNodes.SetValue(theIndex - 1, thePnt); }

  gp_Pnt2d UVNode(int theIndex) const { return myUVNodes.Value(theIndex - 1); }

  void SetUVNode(int theIndex, const gp_Pnt2d& thePnt) { myUVNodes.SetValue(theIndex - 1, thePnt); }

  const Poly_Triangle& Triangle(int theIndex) const { return myTriangles.Value(theIndex); }

  void SetTriangle(int theIndex, const Poly_Triangle& theTriangle)
  {
    myTriangles.SetValue(theIndex, theTriangle);
  }

  gp_Dir Normal(int theIndex) const
  {
    const NCollection_Vec3<float>& aNorm = myNormals.Value(theIndex - 1);
    return gp_Dir(aNorm.x(), aNorm.y(), aNorm.z());
  }

  void Normal(int theIndex, NCollection_Vec3<float>& theVec3) const
  {
    theVec3 = myNormals.Value(theIndex - 1);
  }

  void SetNormal(const int theIndex, const NCollection_Vec3<float>& theNormal)
  {
    myNormals.SetValue(theIndex - 1, theNormal);
  }

  void SetNormal(const int theIndex, const gp_Dir& theNormal)
  {
    SetNormal(
      theIndex,
      NCollection_Vec3<float>(float(theNormal.X()), float(theNormal.Y()), float(theNormal.Z())));
  }

  Poly_MeshPurpose MeshPurpose() const { return myPurpose; }

  void SetMeshPurpose(const Poly_MeshPurpose thePurpose) { myPurpose = thePurpose; }

  Standard_EXPORT const Bnd_Box& CachedMinMax() const;

  Standard_EXPORT void SetCachedMinMax(const Bnd_Box& theBox);

  Standard_EXPORT bool HasCachedMinMax() const { return myCachedMinMax != nullptr; }

  void UpdateCachedMinMax()
  {
    Bnd_Box aBox;
    MinMax(aBox, gp_Trsf(), true);
    SetCachedMinMax(aBox);
  }

  Standard_EXPORT bool MinMax(Bnd_Box&       theBox,
                              const gp_Trsf& theTrsf,
                              const bool     theIsAccurate = false) const;

  Standard_EXPORT virtual void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

public:
  bool IsDoublePrecision() const { return myNodes.IsDoublePrecision(); }

  Standard_EXPORT void SetDoublePrecision(bool theIsDouble);

  Standard_EXPORT void ResizeNodes(int theNbNodes, bool theToCopyOld);

  Standard_EXPORT void ResizeTriangles(int theNbTriangles, bool theToCopyOld);

  Standard_EXPORT void AddUVNodes();

  Standard_EXPORT void RemoveUVNodes();

  Standard_EXPORT void AddNormals();

  Standard_EXPORT void RemoveNormals();

  Standard_EXPORT void ComputeNormals();

public:
  Standard_EXPORT occ::handle<NCollection_HArray1<gp_Pnt>> MapNodeArray() const;

  Standard_EXPORT occ::handle<NCollection_HArray1<Poly_Triangle>> MapTriangleArray() const;

  Standard_EXPORT occ::handle<NCollection_HArray1<gp_Pnt2d>> MapUVNodeArray() const;

  Standard_EXPORT occ::handle<NCollection_HArray1<float>> MapNormalArray() const;

public:
  NCollection_Array1<Poly_Triangle>& InternalTriangles() { return myTriangles; }

  Poly_ArrayOfNodes& InternalNodes() { return myNodes; }

  Poly_ArrayOfUVNodes& InternalUVNodes() { return myUVNodes; }

  NCollection_Array1<NCollection_Vec3<float>>& InternalNormals() { return myNormals; }

  Standard_DEPRECATED("Deprecated method, SetNormal() should be used instead")
  Standard_EXPORT void SetNormals(const occ::handle<NCollection_HArray1<float>>& theNormals);

  Standard_DEPRECATED("Deprecated method, Triangle() should be used instead")

  const NCollection_Array1<Poly_Triangle>& Triangles() const { return myTriangles; }

  Standard_DEPRECATED("Deprecated method, SetTriangle() should be used instead")

  NCollection_Array1<Poly_Triangle>& ChangeTriangles() { return myTriangles; }

  Standard_DEPRECATED("Deprecated method, SetTriangle() should be used instead")

  Poly_Triangle& ChangeTriangle(const int theIndex) { return myTriangles.ChangeValue(theIndex); }

public:
  virtual int NbDeferredNodes() const { return 0; }

  virtual int NbDeferredTriangles() const { return 0; }

  virtual bool HasDeferredData() const { return NbDeferredTriangles() > 0; }

  Standard_EXPORT virtual bool LoadDeferredData(
    const occ::handle<OSD_FileSystem>& theFileSystem = occ::handle<OSD_FileSystem>());

  Standard_EXPORT virtual occ::handle<Poly_Triangulation> DetachedLoadDeferredData(
    const occ::handle<OSD_FileSystem>& theFileSystem = occ::handle<OSD_FileSystem>()) const;

  Standard_EXPORT virtual bool UnloadDeferredData();

protected:
  virtual occ::handle<Poly_Triangulation> createNewEntity() const
  {
    return new Poly_Triangulation();
  }

  virtual bool loadDeferredData(const occ::handle<OSD_FileSystem>&     theFileSystem,
                                const occ::handle<Poly_Triangulation>& theDestTriangulation) const
  {
    (void)theFileSystem;
    (void)theDestTriangulation;
    return false;
  }

protected:
  Standard_EXPORT void unsetCachedMinMax();

  Standard_EXPORT virtual Bnd_Box computeBoundingBox(const gp_Trsf& theTrsf) const;

protected:
  Bnd_Box*                                    myCachedMinMax;
  double                                      myDeflection;
  Poly_ArrayOfNodes                           myNodes;
  NCollection_Array1<Poly_Triangle>           myTriangles;
  Poly_ArrayOfUVNodes                         myUVNodes;
  NCollection_Array1<NCollection_Vec3<float>> myNormals;
  Poly_MeshPurpose                            myPurpose;

  occ::handle<Poly_TriangulationParameters> myParams;
};

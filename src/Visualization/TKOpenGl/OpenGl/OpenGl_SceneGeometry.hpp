#pragma once

#include <BVH_Geometry.hpp>
#include <BVH_Triangulation.hpp>
#include <BVH_BinnedBuilder.hpp>
#include <NCollection_OccAllocator.hpp>
#include <OpenGl_Texture.hpp>
#include <OpenGl_Sampler.hpp>

class OpenGl_Element;
struct OpenGl_ElementNode;
class OpenGl_Group;

namespace OpenGl_Raytrace
{

  Standard_EXPORT bool IsRaytracedGroup(const OpenGl_Group* theGroup);

  Standard_EXPORT bool IsRaytracedElement(const OpenGl_ElementNode* theNode);

  Standard_EXPORT bool IsRaytracedElement(const OpenGl_Element* theElement);
} // namespace OpenGl_Raytrace

struct OpenGl_RaytraceMaterial
{
  BVH_Vec4f Ambient;
  BVH_Vec4f Diffuse;
  BVH_Vec4f Specular;
  BVH_Vec4f Emission;
  BVH_Vec4f Reflection;
  BVH_Vec4f Refraction;
  BVH_Vec4f Transparency;
  BVH_Mat4f TextureTransform;

  struct Physical
  {
    BVH_Vec4f Kc;
    BVH_Vec4f Kd;
    BVH_Vec4f Ks;
    BVH_Vec4f Kt;
    BVH_Vec4f Le;
    BVH_Vec4f FresnelCoat;
    BVH_Vec4f FresnelBase;
    BVH_Vec4f Absorption;
  } BSDF;

public:
  Standard_EXPORT OpenGl_RaytraceMaterial();

  const float* Packed() { return reinterpret_cast<float*>(this); }
};

struct OpenGl_RaytraceLight
{

  BVH_Vec4f Emission;
  BVH_Vec4f Position;

public:
  OpenGl_RaytraceLight() = default;

  Standard_EXPORT OpenGl_RaytraceLight(const BVH_Vec4f& theEmission, const BVH_Vec4f& thePosition);

  const float* Packed() { return reinterpret_cast<float*>(this); }
};

typedef opencascade::handle<BVH_Tree<float, 3, BVH_QuadTree>> QuadBvhHandle;
typedef BVH_Triangulation<float, 3>                           OpenGl_BVHTriangulation3f;

class OpenGl_TriangleSet : public OpenGl_BVHTriangulation3f
{
  DEFINE_STANDARD_RTTIEXT(OpenGl_TriangleSet, OpenGl_BVHTriangulation3f)
public:
  static const int INVALID_MATERIAL = -1;

public:
  Standard_EXPORT OpenGl_TriangleSet(const size_t                                      theArrayID,
                                     const opencascade::handle<BVH_Builder<float, 3>>& theBuilder);

  size_t AssociatedPArrayID() const { return myArrayID; }

  int MaterialIndex() const
  {
    if (Elements.size() == 0)
    {
      return INVALID_MATERIAL;
    }

    return Elements.front().w();
  }

  void SetMaterialIndex(int theMatID)
  {
    for (size_t anIdx = 0; anIdx < Elements.size(); ++anIdx)
    {
      Elements[anIdx].w() = theMatID;
    }
  }

  BVH_BoxNt Box() const override;

  using BVH_Triangulation<float, 3>::Box;

  Standard_EXPORT float Center(const int theIndex, const int theAxis) const override;

  Standard_EXPORT const QuadBvhHandle& QuadBVH();

public:
  BVH_Array3f Normals;
  BVH_Array2f TexCrds;

private:
  size_t myArrayID;

  QuadBvhHandle myQuadBVH;
};

class OpenGl_RaytraceGeometry : public BVH_Geometry<float, 3>
{
public:
  static const int INVALID_OFFSET = -1;

  static const int MAX_TEX_NUMBER = 32;

public:
  std::vector<OpenGl_RaytraceLight, NCollection_OccAllocator<OpenGl_RaytraceLight>> Sources;

  std::vector<OpenGl_RaytraceMaterial, NCollection_OccAllocator<OpenGl_RaytraceMaterial>> Materials;

  BVH_Vec4f Ambient;

public:
  OpenGl_RaytraceGeometry()
      : myTopLevelTreeDepth(0),
        myBotLevelTreeDepth(0)
  {
  }

  ~OpenGl_RaytraceGeometry() override {}

  void ClearMaterials()
  {
    std::vector<OpenGl_RaytraceMaterial, NCollection_OccAllocator<OpenGl_RaytraceMaterial>>
      anEmptyMaterials;

    Materials.swap(anEmptyMaterials);

    myTextures.Clear();
  }

  Standard_EXPORT void Clear() override;

public:
  Standard_EXPORT bool ProcessAcceleration();

  Standard_EXPORT int AccelerationOffset(int theNodeIdx);

  Standard_EXPORT int VerticesOffset(int theNodeIdx);

  Standard_EXPORT int ElementsOffset(int theNodeIdx);

  Standard_EXPORT OpenGl_TriangleSet* TriangleSet(int theNodeIdx);

  Standard_EXPORT const QuadBvhHandle& QuadBVH();

public:
  bool HasTextures() const { return !myTextures.IsEmpty(); }

  Standard_EXPORT int AddTexture(const occ::handle<OpenGl_Texture>& theTexture);

  Standard_EXPORT bool UpdateTextureHandles(const occ::handle<OpenGl_Context>& theContext);

  Standard_EXPORT bool AcquireTextures(const occ::handle<OpenGl_Context>& theContext);

  Standard_EXPORT bool ReleaseTextures(const occ::handle<OpenGl_Context>& theContext) const;

  const std::vector<GLuint64>& TextureHandles() const { return myTextureHandles; }

  void ReleaseResources(const occ::handle<OpenGl_Context>&) {}

public:
  int TopLevelTreeDepth() const { return myTopLevelTreeDepth; }

  int BotLevelTreeDepth() const { return myBotLevelTreeDepth; }

protected:
  NCollection_Vector<occ::handle<OpenGl_Texture>> myTextures;
  std::vector<GLuint64>                           myTextureHandles;
  int                                             myTopLevelTreeDepth;
  int                                             myBotLevelTreeDepth;

  QuadBvhHandle myQuadBVH;
};

#include <OpenGl_SceneGeometry.hpp>

#include <OSD_Parallel.hpp>
#include <OSD_Timer.hpp>
#include <Standard_Assert.hpp>
#include <OpenGl_ArbTexBindless.hpp>
#include <OpenGl_PrimitiveArray.hpp>
#include <OpenGl_Structure.hpp>

namespace
{

  static const BVH_Vec4f ZERO_VEC_4F;
}

IMPLEMENT_STANDARD_RTTIEXT(OpenGl_TriangleSet, OpenGl_BVHTriangulation3f)

OpenGl_RaytraceMaterial::OpenGl_RaytraceMaterial()
    : Ambient(ZERO_VEC_4F),
      Diffuse(ZERO_VEC_4F),
      Specular(ZERO_VEC_4F),
      Emission(ZERO_VEC_4F),
      Reflection(ZERO_VEC_4F),
      Refraction(ZERO_VEC_4F),
      Transparency(ZERO_VEC_4F)
{
}

OpenGl_RaytraceLight::OpenGl_RaytraceLight(const BVH_Vec4f& theEmission,
                                           const BVH_Vec4f& thePosition)
    : Emission(theEmission),
      Position(thePosition)
{
}

const QuadBvhHandle& OpenGl_TriangleSet::QuadBVH()
{
  if (!myIsDirty)
  {
    Standard_ASSERT_RAISE(!myQuadBVH.IsNull(), "Error! BVH was not collapsed into QBVH");
  }
  else
  {
    myQuadBVH = BVH()->CollapseToQuadTree();

    myBVH->Clear();
  }

  return myQuadBVH;
}

float OpenGl_TriangleSet::Center(const int theIndex, const int theAxis) const
{

  const BVH_Vec4i& aTriangle = Elements[theIndex];

  const float aVertex0 = BVH::VecComp<float, 3>::Get(Vertices[aTriangle.x()], theAxis);
  const float aVertex1 = BVH::VecComp<float, 3>::Get(Vertices[aTriangle.y()], theAxis);
  const float aVertex2 = BVH::VecComp<float, 3>::Get(Vertices[aTriangle.z()], theAxis);

  return (std::min(std::min(aVertex0, aVertex1), aVertex2)
          + std::max(std::max(aVertex0, aVertex1), aVertex2))
         * 0.5f;
}

OpenGl_TriangleSet::BVH_BoxNt OpenGl_TriangleSet::Box() const
{
  BVH_BoxNt                      aBox = BVH_PrimitiveSet<float, 3>::Box();
  const BVH_Transform<float, 4>* aTransform =
    dynamic_cast<const BVH_Transform<float, 4>*>(Properties().get());
  if (aTransform == nullptr)
  {
    return aBox;
  }

  BVH_BoxNt aTransformedBox;
  for (int aX = 0; aX <= 1; ++aX)
  {
    for (int aY = 0; aY <= 1; ++aY)
    {
      for (int aZ = 0; aZ <= 1; ++aZ)
      {
        BVH_Vec4f aCorner = aTransform->Transform()
                            * BVH_Vec4f(aX == 0 ? aBox.CornerMin().x() : aBox.CornerMax().x(),
                                        aY == 0 ? aBox.CornerMin().y() : aBox.CornerMax().y(),
                                        aZ == 0 ? aBox.CornerMin().z() : aBox.CornerMax().z(),
                                        1.f);

        aTransformedBox.Add(aCorner.xyz());
      }
    }
  }
  return aTransformedBox;
}

OpenGl_TriangleSet::OpenGl_TriangleSet(const size_t                                      theArrayID,
                                       const opencascade::handle<BVH_Builder<float, 3>>& theBuilder)
    : BVH_Triangulation<float, 3>(theBuilder),
      myArrayID(theArrayID)
{
}

void OpenGl_RaytraceGeometry::Clear()
{
  BVH_Geometry<float, 3>::BVH_Geometry::Clear();

  std::vector<OpenGl_RaytraceLight, NCollection_OccAllocator<OpenGl_RaytraceLight>> anEmptySources;

  Sources.swap(anEmptySources);

  std::vector<OpenGl_RaytraceMaterial, NCollection_OccAllocator<OpenGl_RaytraceMaterial>>
    anEmptyMaterials;

  Materials.swap(anEmptyMaterials);
}

struct OpenGL_BVHParallelBuilder
{
  BVH_ObjectSet<float, 3>* Set;

  OpenGL_BVHParallelBuilder(BVH_ObjectSet<float, 3>* theSet)
      : Set(theSet)
  {
  }

  void operator()(const int theObjectIdx) const
  {
    OpenGl_TriangleSet* aTriangleSet = dynamic_cast<OpenGl_TriangleSet*>(
      Set->Objects().ChangeValue(static_cast<int>(theObjectIdx)).operator->());

    if (aTriangleSet != nullptr)
      aTriangleSet->QuadBVH();
  }
};

bool OpenGl_RaytraceGeometry::ProcessAcceleration()
{
#ifdef RAY_TRACE_PRINT_INFO
  OSD_Timer aTimer;
#endif

  MarkDirty();

#ifdef RAY_TRACE_PRINT_INFO
  aTimer.Reset();
  aTimer.Start();
#endif

  OSD_Parallel::For(0, Size(), OpenGL_BVHParallelBuilder(this));

  myBotLevelTreeDepth = 1;

  for (int anObjectIdx = 0; anObjectIdx < Size(); ++anObjectIdx)
  {
    OpenGl_TriangleSet* aTriangleSet =
      dynamic_cast<OpenGl_TriangleSet*>(myObjects.ChangeValue(anObjectIdx).operator->());

    Standard_ASSERT_RETURN(aTriangleSet != nullptr,
                           "Error! Failed to get triangulation of OpenGL element",
                           false);

    Standard_ASSERT_RETURN(!aTriangleSet->QuadBVH().IsNull(),
                           "Error! Failed to update bottom-level BVH of OpenGL element",
                           false);

    QuadBvhHandle aBVH = aTriangleSet->QuadBVH();

    for (int aNodeIdx = 0; aNodeIdx < aBVH->Length(); ++aNodeIdx)
    {
      if (aBVH->IsOuter(aNodeIdx))
      {
        aBVH->NodeInfoBuffer()[aNodeIdx].x() = -1;
      }
    }

    myBotLevelTreeDepth = std::max(myBotLevelTreeDepth, aTriangleSet->QuadBVH()->Depth());
  }

#ifdef RAY_TRACE_PRINT_INFO
  aTimer.Stop();

  std::cout << "Updating bottom-level BVHs (sec): " << aTimer.ElapsedTime() << std::endl;
#endif

#ifdef RAY_TRACE_PRINT_INFO
  aTimer.Reset();
  aTimer.Start();
#endif

  QuadBvhHandle aBVH = QuadBVH();

  Standard_ASSERT_RETURN(!aBVH.IsNull(),
                         "Error! Failed to update high-level BVH of ray-tracing scene",
                         false);

  myTopLevelTreeDepth = aBVH->Depth();

#ifdef RAY_TRACE_PRINT_INFO
  aTimer.Stop();

  std::cout << "Updating high-level BVH (sec): " << aTimer.ElapsedTime() << std::endl;
#endif

  int aVerticesOffset = 0;
  int aElementsOffset = 0;
  int aBvhNodesOffset = QuadBVH()->Length();

  for (int aNodeIdx = 0; aNodeIdx < aBVH->Length(); ++aNodeIdx)
  {
    if (aBVH->IsOuter(aNodeIdx))
    {
      Standard_ASSERT_RETURN(
        aBVH->BegPrimitive(aNodeIdx) == aBVH->EndPrimitive(aNodeIdx),
        "Error! Invalid leaf node in high-level BVH (contains several objects)",
        false);

      const int anObjectIdx = aBVH->BegPrimitive(aNodeIdx);

      Standard_ASSERT_RETURN(
        anObjectIdx < myObjects.Size(),
        "Error! Invalid leaf node in high-level BVH (contains out-of-range object)",
        false);

      OpenGl_TriangleSet* aTriangleSet =
        dynamic_cast<OpenGl_TriangleSet*>(myObjects(anObjectIdx).get());

      aBVH->NodeInfoBuffer()[aNodeIdx] =
        BVH_Vec4i(anObjectIdx + 1, aBvhNodesOffset, aVerticesOffset, aElementsOffset);

      aVerticesOffset += static_cast<int>(aTriangleSet->Vertices.size());
      aElementsOffset += static_cast<int>(aTriangleSet->Elements.size());

      aBvhNodesOffset += aTriangleSet->QuadBVH()->Length();
    }
  }

  return true;
}

const QuadBvhHandle& OpenGl_RaytraceGeometry::QuadBVH()
{
  if (!myIsDirty)
  {
    Standard_ASSERT_RAISE(!myQuadBVH.IsNull(), "Error! BVH was not collapsed into QBVH");
  }
  else
  {
    myQuadBVH = BVH()->CollapseToQuadTree();

    myBVH->Clear();
  }

  return myQuadBVH;
}

int OpenGl_RaytraceGeometry::AccelerationOffset(int theNodeIdx)
{
  const QuadBvhHandle& aBVH = QuadBVH();

  if (theNodeIdx >= aBVH->Length() || !aBVH->IsOuter(theNodeIdx))
    return INVALID_OFFSET;

  return aBVH->NodeInfoBuffer().at(theNodeIdx).y();
}

int OpenGl_RaytraceGeometry::VerticesOffset(int theNodeIdx)
{
  const QuadBvhHandle& aBVH = QuadBVH();

  if (theNodeIdx >= aBVH->Length() || !aBVH->IsOuter(theNodeIdx))
    return INVALID_OFFSET;

  return aBVH->NodeInfoBuffer().at(theNodeIdx).z();
}

int OpenGl_RaytraceGeometry::ElementsOffset(int theNodeIdx)
{
  const QuadBvhHandle& aBVH = QuadBVH();

  if (theNodeIdx >= aBVH->Length() || !aBVH->IsOuter(theNodeIdx))
    return INVALID_OFFSET;

  return aBVH->NodeInfoBuffer().at(theNodeIdx).w();
}

OpenGl_TriangleSet* OpenGl_RaytraceGeometry::TriangleSet(int theNodeIdx)
{
  const QuadBvhHandle& aBVH = QuadBVH();

  if (theNodeIdx >= aBVH->Length() || !aBVH->IsOuter(theNodeIdx))
    return nullptr;

  if (aBVH->NodeInfoBuffer().at(theNodeIdx).x() > myObjects.Size())
    return nullptr;

  return dynamic_cast<OpenGl_TriangleSet*>(
    myObjects(aBVH->NodeInfoBuffer().at(theNodeIdx).x() - 1).get());
}

bool OpenGl_RaytraceGeometry::AcquireTextures(const occ::handle<OpenGl_Context>& theContext)
{
  if (theContext->arbTexBindless == nullptr)
  {
    return true;
  }

  int aTexIter = 0;
  for (NCollection_Vector<occ::handle<OpenGl_Texture>>::Iterator aTexSrcIter(myTextures);
       aTexSrcIter.More();
       aTexSrcIter.Next(), ++aTexIter)
  {
    GLuint64&                          aHandle  = myTextureHandles[aTexIter];
    const occ::handle<OpenGl_Texture>& aTexture = aTexSrcIter.Value();
    if (!aTexture->Sampler()->IsValid() || !aTexture->Sampler()->IsImmutable())
    {

      aHandle = GLuint64(-1);

      if (!aTexture->InitSamplerObject(theContext))
      {
        continue;
      }

      aTexture->Sampler()->SetImmutable();
      aHandle =
        theContext->arbTexBindless->glGetTextureSamplerHandleARB(aTexture->TextureId(),
                                                                 aTexture->Sampler()->SamplerID());
      const GLenum anErr = theContext->core11fwd->glGetError();
      if (anErr != GL_NO_ERROR)
      {
        theContext->PushMessage(
          GL_DEBUG_SOURCE_APPLICATION,
          GL_DEBUG_TYPE_ERROR,
          0,
          GL_DEBUG_SEVERITY_HIGH,
          TCollection_AsciiString("Error: Failed to get 64-bit handle of OpenGL texture ")
            + OpenGl_Context::FormatGlError(anErr));
        myTextureHandles.clear();
        return false;
      }
    }

    theContext->arbTexBindless->glMakeTextureHandleResidentARB(aHandle);
    const GLenum anErr = theContext->core11fwd->glGetError();
    if (anErr != GL_NO_ERROR)
    {
      theContext->PushMessage(
        GL_DEBUG_SOURCE_APPLICATION,
        GL_DEBUG_TYPE_ERROR,
        0,
        GL_DEBUG_SEVERITY_HIGH,
        TCollection_AsciiString("Error: Failed to make OpenGL texture resident ")
          + OpenGl_Context::FormatGlError(anErr));
      return false;
    }
  }

  return true;
}

bool OpenGl_RaytraceGeometry::ReleaseTextures(const occ::handle<OpenGl_Context>& theContext) const
{
  if (theContext->arbTexBindless == nullptr)
  {
    return true;
  }

  for (size_t aTexIter = 0; aTexIter < myTextureHandles.size(); ++aTexIter)
  {
    theContext->arbTexBindless->glMakeTextureHandleNonResidentARB(myTextureHandles[aTexIter]);
    const GLenum anErr = theContext->core11fwd->glGetError();
    if (anErr != GL_NO_ERROR)
    {
      theContext->PushMessage(
        GL_DEBUG_SOURCE_APPLICATION,
        GL_DEBUG_TYPE_ERROR,
        0,
        GL_DEBUG_SEVERITY_HIGH,
        TCollection_AsciiString("Error: Failed to make OpenGL texture non-resident ")
          + OpenGl_Context::FormatGlError(anErr));
      return false;
    }
  }

  return true;
}

int OpenGl_RaytraceGeometry::AddTexture(const occ::handle<OpenGl_Texture>& theTexture)
{
  if (theTexture->TextureId() == OpenGl_Texture::NO_TEXTURE)
  {
    return -1;
  }

  NCollection_Vector<occ::handle<OpenGl_Texture>>::iterator anIter =
    std::find(myTextures.begin(), myTextures.end(), theTexture);

  if (anIter == myTextures.end())
  {
    if (myTextures.Size() >= MAX_TEX_NUMBER)
    {
      return -1;
    }

    myTextures.Append(theTexture);
  }

  return static_cast<int>(anIter - myTextures.begin());
}

bool OpenGl_RaytraceGeometry::UpdateTextureHandles(const occ::handle<OpenGl_Context>& theContext)
{
  if (theContext->arbTexBindless == nullptr)
  {
    return false;
  }

  myTextureHandles.clear();
  myTextureHandles.resize(myTextures.Size());

  int aTexIter = 0;
  for (NCollection_Vector<occ::handle<OpenGl_Texture>>::Iterator aTexSrcIter(myTextures);
       aTexSrcIter.More();
       aTexSrcIter.Next(), ++aTexIter)
  {
    GLuint64& aHandle = myTextureHandles[aTexIter];

    aHandle = GLuint64(-1);

    const occ::handle<OpenGl_Texture>& aTexture = aTexSrcIter.Value();
    if (!aTexture->Sampler()->IsValid() && !aTexture->InitSamplerObject(theContext))
    {
      continue;
    }

    aTexture->Sampler()->SetImmutable();
    aHandle =
      theContext->arbTexBindless->glGetTextureSamplerHandleARB(aTexture->TextureId(),
                                                               aTexture->Sampler()->SamplerID());
    const GLenum anErr = theContext->core11fwd->glGetError();
    if (anErr != GL_NO_ERROR)
    {
      theContext->PushMessage(
        GL_DEBUG_SOURCE_APPLICATION,
        GL_DEBUG_TYPE_ERROR,
        0,
        GL_DEBUG_SEVERITY_HIGH,
        TCollection_AsciiString("Error: Failed to get 64-bit handle of OpenGL texture ")
          + OpenGl_Context::FormatGlError(anErr));
      myTextureHandles.clear();
      return false;
    }
  }

  return true;
}

namespace OpenGl_Raytrace
{

  bool IsRaytracedElement(const OpenGl_ElementNode* theNode)
  {
    OpenGl_PrimitiveArray* anArray = dynamic_cast<OpenGl_PrimitiveArray*>(theNode->elem);
    return anArray != nullptr && anArray->DrawMode() >= GL_TRIANGLES;
  }

  bool IsRaytracedElement(const OpenGl_Element* theElement)
  {
    const OpenGl_PrimitiveArray* anArray = dynamic_cast<const OpenGl_PrimitiveArray*>(theElement);
    return anArray != nullptr && anArray->DrawMode() >= GL_TRIANGLES;
  }

  bool IsRaytracedGroup(const OpenGl_Group* theGroup)
  {
    if (theGroup->HasPersistence())
    {
      return false;
    }

    for (const OpenGl_ElementNode* aNode = theGroup->FirstNode(); aNode != nullptr;
         aNode                           = aNode->next)
    {
      if (IsRaytracedElement(aNode))
      {
        return true;
      }
    }
    return false;
  }
} // namespace OpenGl_Raytrace

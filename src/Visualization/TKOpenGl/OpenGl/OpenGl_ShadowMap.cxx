

#include <OpenGl_ShadowMap.hpp>

#include <OpenGl_FrameBuffer.hpp>
#include <OpenGl_ShaderManager.hpp>
#include <Graphic3d_CView.hpp>
#include <Message_Messenger.hpp>

IMPLEMENT_STANDARD_RTTIEXT(OpenGl_ShadowMap, OpenGl_NamedResource)

OpenGl_ShadowMap::OpenGl_ShadowMap()
    : OpenGl_NamedResource("shadow_map"),
      myShadowMapFbo(new OpenGl_FrameBuffer(myResourceId + ":fbo")),
      myShadowCamera(new Graphic3d_Camera()),
      myShadowMapBias(0.0f)
{
}

void OpenGl_ShadowMap::Release(OpenGl_Context* theCtx)
{
  myShadowMapFbo->Release(theCtx);
}

OpenGl_ShadowMap::~OpenGl_ShadowMap()
{
  Release(nullptr);
}

size_t OpenGl_ShadowMap::EstimatedDataSize() const
{
  return myShadowMapFbo->EstimatedDataSize();
}

bool OpenGl_ShadowMap::IsValid() const
{
  return myShadowMapFbo->IsValid();
}

const occ::handle<OpenGl_Texture>& OpenGl_ShadowMap::Texture() const
{
  return myShadowMapFbo->DepthStencilTexture();
}

bool OpenGl_ShadowMap::UpdateCamera(const Graphic3d_CView& theView, const gp_XYZ* theOrigin)
{

  const Bnd_Box aMinMaxBox = theOrigin == nullptr ? theView.MinMaxValues(false) : Bnd_Box();

  const Bnd_Box aGraphicBox = aMinMaxBox;

  switch (myShadowLight->Type())
  {
    case Graphic3d_TypeOfLightSource_Ambient:
    {
      return false;
    }
    case Graphic3d_TypeOfLightSource_Directional:
    {
      if (theOrigin != nullptr)
      {
        NCollection_Mat4<double> aTrans;
        aTrans.Translate(NCollection_Vec3<double>(theOrigin->X(), theOrigin->Y(), theOrigin->Z()));
        NCollection_Mat4<double> anOrientMat = myShadowCamera->OrientationMatrix() * aTrans;
        myLightMatrix = myShadowCamera->ProjectionMatrixF() * NCollection_Mat4<float>(anOrientMat);
        return true;
      }

      NCollection_Vec4<double> aDir(myShadowLight->Direction().X(),
                                    myShadowLight->Direction().Y(),
                                    myShadowLight->Direction().Z(),
                                    0.0);
      if (myShadowLight->IsHeadlight())
      {
        NCollection_Mat4<double> anOrientInv;
        theView.Camera()->OrientationMatrix().Inverted(anOrientInv);
        aDir = anOrientInv * aDir;
      }
      myShadowCamera->SetZeroToOneDepth(theView.Camera()->IsZeroToOneDepth());
      myShadowCamera->SetProjectionType(Graphic3d_Camera::Projection_Orthographic);
      myShadowCamera->SetDirection(gp_Dir(aDir.x(), aDir.y(), aDir.z()));
      myShadowCamera->SetUp(!myShadowCamera->Direction().IsParallel(gp::DY(), Precision::Angular())
                              ? gp::DY()
                              : gp::DX());
      myShadowCamera->OrthogonalizeUp();

      if (myShadowCamera->FitMinMax(aMinMaxBox, 10.0 * Precision::Confusion(), false))
      {

        myShadowCamera->SetScale(std::max(myShadowCamera->ViewDimensions().X() * 1.1,
                                          myShadowCamera->ViewDimensions().Y() * 1.1));
      }
      myShadowCamera->ZFitAll(1.0, aMinMaxBox, aGraphicBox);
      myLightMatrix = myShadowCamera->ProjectionMatrixF() * myShadowCamera->OrientationMatrixF();
      return true;
    }
    case Graphic3d_TypeOfLightSource_Positional:
    {

      return false;
    }
    case Graphic3d_TypeOfLightSource_Spot:
    {
      if (theOrigin != nullptr)
      {
        NCollection_Mat4<double> aTrans;
        aTrans.Translate(NCollection_Vec3<double>(theOrigin->X(), theOrigin->Y(), theOrigin->Z()));
        NCollection_Mat4<double> anOrientMat = myShadowCamera->OrientationMatrix() * aTrans;
        myLightMatrix = myShadowCamera->ProjectionMatrixF() * NCollection_Mat4<float>(anOrientMat);
        return true;
      }

      NCollection_Vec4<double> aDir(myShadowLight->Direction().X(),
                                    myShadowLight->Direction().Y(),
                                    myShadowLight->Direction().Z(),
                                    0.0);
      if (myShadowLight->IsHeadlight())
      {
        NCollection_Mat4<double> anOrientInv;
        theView.Camera()->OrientationMatrix().Inverted(anOrientInv);
        aDir = anOrientInv * aDir;
      }

      myShadowCamera->SetZeroToOneDepth(theView.Camera()->IsZeroToOneDepth());
      myShadowCamera->SetProjectionType(Graphic3d_Camera::Projection_Perspective);

      const gp_Pnt& aLightPos = myShadowLight->Position();
      double        aDistance(aMinMaxBox.Distance(Bnd_Box(aLightPos, aLightPos))
                       + aMinMaxBox.CornerMin().Distance(aMinMaxBox.CornerMax()));
      myShadowCamera->SetDistance(aDistance);
      myShadowCamera->MoveEyeTo(aLightPos);
      myShadowCamera->SetDirectionFromEye(myShadowLight->Direction());
      myShadowCamera->SetUp(!myShadowCamera->Direction().IsParallel(gp::DY(), Precision::Angular())
                              ? gp::DY()
                              : gp::DX());
      myShadowCamera->OrthogonalizeUp();
      myShadowCamera->SetZRange(1.0, aDistance);

      myLightMatrix = myShadowCamera->ProjectionMatrixF() * myShadowCamera->OrientationMatrixF();

      return true;
    }
  }
  return false;
}

void OpenGl_ShadowMapArray::Release(OpenGl_Context* theCtx)
{
  for (int anIter = Lower(); anIter <= Upper(); ++anIter)
  {
    if (const occ::handle<OpenGl_ShadowMap>& aShadow = ChangeValue(anIter))
    {
      aShadow->Release(theCtx);
    }
  }
}

size_t OpenGl_ShadowMapArray::EstimatedDataSize() const
{
  size_t aSize = 0;
  for (int anIter = Lower(); anIter <= Upper(); ++anIter)
  {
    if (const occ::handle<OpenGl_ShadowMap>& aShadow = Value(anIter))
    {
      aSize += aShadow->EstimatedDataSize();
    }
  }
  return aSize;
}

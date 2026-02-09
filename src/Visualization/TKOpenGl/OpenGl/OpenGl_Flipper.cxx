#include <OpenGl_Flipper.hpp>

#include <OpenGl_ShaderManager.hpp>
#include <OpenGl_Vec.hpp>
#include <OpenGl_Workspace.hpp>

#include <gp_Ax2.hpp>

OpenGl_Flipper::OpenGl_Flipper(const gp_Ax2& theReferenceSystem)
    : myReferenceOrigin((float)theReferenceSystem.Location().X(),
                        (float)theReferenceSystem.Location().Y(),
                        (float)theReferenceSystem.Location().Z(),
                        1.0f),
      myReferenceX((float)theReferenceSystem.XDirection().X(),
                   (float)theReferenceSystem.XDirection().Y(),
                   (float)theReferenceSystem.XDirection().Z(),
                   1.0f),
      myReferenceY((float)theReferenceSystem.YDirection().X(),
                   (float)theReferenceSystem.YDirection().Y(),
                   (float)theReferenceSystem.YDirection().Z(),
                   1.0f),
      myReferenceZ((float)theReferenceSystem.Axis().Direction().X(),
                   (float)theReferenceSystem.Axis().Direction().Y(),
                   (float)theReferenceSystem.Axis().Direction().Z(),
                   1.0f),
      myIsEnabled(true)
{
}

void OpenGl_Flipper::Release(OpenGl_Context*) {}

void OpenGl_Flipper::Render(const occ::handle<OpenGl_Workspace>& theWorkspace) const
{

  const occ::handle<OpenGl_Context>& aContext = theWorkspace->GetGlContext();
  if (!myIsEnabled)
  {

    aContext->ModelWorldState.Pop();

    aContext->ApplyModelWorldMatrix();
    return;
  }

  aContext->ModelWorldState.Push();

  NCollection_Mat4<float> aModelWorldMatrix;
  aModelWorldMatrix.Convert(aContext->ModelWorldState.Current());

  NCollection_Mat4<float> aMatrixMV = aContext->WorldViewState.Current() * aModelWorldMatrix;

  const NCollection_Vec4<float> aMVReferenceOrigin = aMatrixMV * myReferenceOrigin;
  const NCollection_Vec4<float> aMVReferenceX =
    aMatrixMV * NCollection_Vec4<float>(myReferenceX.xyz() + myReferenceOrigin.xyz(), 1.0f);
  const NCollection_Vec4<float> aMVReferenceY =
    aMatrixMV * NCollection_Vec4<float>(myReferenceY.xyz() + myReferenceOrigin.xyz(), 1.0f);
  const NCollection_Vec4<float> aMVReferenceZ =
    aMatrixMV * NCollection_Vec4<float>(myReferenceZ.xyz() + myReferenceOrigin.xyz(), 1.0f);

  const NCollection_Vec4<float> aDirX = aMVReferenceX - aMVReferenceOrigin;
  const NCollection_Vec4<float> aDirY = aMVReferenceY - aMVReferenceOrigin;
  const NCollection_Vec4<float> aDirZ = aMVReferenceZ - aMVReferenceOrigin;

  bool isReversedX = aDirX.xyz().Dot(NCollection_Vec3<float>::DX()) < 0.0f;
  bool isReversedY = aDirY.xyz().Dot(NCollection_Vec3<float>::DY()) < 0.0f;
  bool isReversedZ = aDirZ.xyz().Dot(NCollection_Vec3<float>::DZ()) < 0.0f;

  NCollection_Mat4<float> aTransform;
  if ((isReversedX || isReversedY) && !isReversedZ)
  {

    aTransform.SetColumn(0, -aTransform.GetColumn(0).xyz());
    aTransform.SetColumn(1, -aTransform.GetColumn(1).xyz());
  }
  else if (isReversedY && isReversedZ)
  {

    aTransform.SetColumn(1, -aTransform.GetColumn(1).xyz());
    aTransform.SetColumn(2, -aTransform.GetColumn(2).xyz());
  }
  else if (isReversedZ)
  {

    aTransform.SetColumn(0, -aTransform.GetColumn(0).xyz());
    aTransform.SetColumn(2, -aTransform.GetColumn(2).xyz());
  }
  else
  {
    return;
  }

  NCollection_Mat4<float> aRefAxes;
  NCollection_Mat4<float> aRefInv;
  aRefAxes.SetColumn(0, myReferenceX.xyz());
  aRefAxes.SetColumn(1, myReferenceY.xyz());
  aRefAxes.SetColumn(2, myReferenceZ.xyz());
  aRefAxes.SetColumn(3, myReferenceOrigin.xyz());
  aRefAxes.Inverted(aRefInv);

  aTransform = aRefAxes * aTransform * aRefInv;

  aModelWorldMatrix = aModelWorldMatrix * aTransform;

  aContext->ModelWorldState.SetCurrent(aModelWorldMatrix);
  aContext->ApplyModelWorldMatrix();
}

void OpenGl_Flipper::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_CLASS_BEGIN(theOStream, OpenGl_Flipper)

  OCCT_DUMP_BASE_CLASS(theOStream, theDepth, OpenGl_Element)
}

#include <OpenGl_ShaderStates.hpp>

OpenGl_StateInterface::OpenGl_StateInterface()
    : myIndex(0)
{
}

OpenGl_ProjectionState::OpenGl_ProjectionState()
    : myInverseNeedUpdate(false)
{
}

void OpenGl_ProjectionState::Set(const NCollection_Mat4<float>& theProjectionMatrix)
{
  myProjectionMatrix  = theProjectionMatrix;
  myInverseNeedUpdate = true;
}

const NCollection_Mat4<float>& OpenGl_ProjectionState::ProjectionMatrixInverse() const
{
  if (myInverseNeedUpdate)
  {
    myInverseNeedUpdate = false;
    myProjectionMatrix.Inverted(myProjectionMatrixInverse);
  }
  return myProjectionMatrixInverse;
}

OpenGl_ModelWorldState::OpenGl_ModelWorldState()
    : myInverseNeedUpdate(false)
{
}

void OpenGl_ModelWorldState::Set(const NCollection_Mat4<float>& theModelWorldMatrix)
{
  myModelWorldMatrix  = theModelWorldMatrix;
  myInverseNeedUpdate = true;
}

const NCollection_Mat4<float>& OpenGl_ModelWorldState::ModelWorldMatrixInverse() const
{
  if (myInverseNeedUpdate)
  {
    myInverseNeedUpdate = false;
    myModelWorldMatrix.Inverted(myModelWorldMatrixInverse);
  }
  return myModelWorldMatrixInverse;
}

OpenGl_WorldViewState::OpenGl_WorldViewState()
    : myInverseNeedUpdate(false)
{
}

void OpenGl_WorldViewState::Set(const NCollection_Mat4<float>& theWorldViewMatrix)
{
  myWorldViewMatrix   = theWorldViewMatrix;
  myInverseNeedUpdate = true;
}

const NCollection_Mat4<float>& OpenGl_WorldViewState::WorldViewMatrixInverse() const
{
  if (myInverseNeedUpdate)
  {
    myInverseNeedUpdate = false;
    myWorldViewMatrix.Inverted(myWorldViewMatrixInverse);
  }
  return myWorldViewMatrixInverse;
}

OpenGl_ClippingState::OpenGl_ClippingState()
    : myIndex(0),
      myNextIndex(1)
{
}

void OpenGl_ClippingState::Update()
{
  myStateStack.Prepend(myIndex);
  myIndex = myNextIndex;
  ++myNextIndex;
}

void OpenGl_ClippingState::Revert()
{
  if (!myStateStack.IsEmpty())
  {
    myIndex = myStateStack.First();
    myStateStack.RemoveFirst();
  }
  else
  {
    myIndex = 0;
  }
}

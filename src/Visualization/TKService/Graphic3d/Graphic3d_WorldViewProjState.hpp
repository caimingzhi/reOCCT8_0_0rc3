#pragma once

#include <Standard_Transient.hpp>
#include <Standard_TypeDef.hpp>

class Graphic3d_WorldViewProjState
{
public:
  Graphic3d_WorldViewProjState() { Reset(); }

  Graphic3d_WorldViewProjState(const size_t              theProjectionState,
                               const size_t              theWorldViewState,
                               const Standard_Transient* theCamera = nullptr)
  {
    Initialize(theProjectionState, theWorldViewState, theCamera);
  }

public:
  bool IsValid() { return myIsValid; }

  void Reset()
  {
    myIsValid         = false;
    myCamera          = nullptr;
    myProjectionState = 0;
    myWorldViewState  = 0;
  }

  void Initialize(const size_t              theProjectionState,
                  const size_t              theWorldViewState,
                  const Standard_Transient* theCamera = nullptr)
  {
    myIsValid         = true;
    myCamera          = const_cast<Standard_Transient*>(theCamera);
    myProjectionState = theProjectionState;
    myWorldViewState  = theWorldViewState;
  }

  void Initialize(const Standard_Transient* theCamera = nullptr)
  {
    myIsValid         = true;
    myCamera          = const_cast<Standard_Transient*>(theCamera);
    myProjectionState = 0;
    myWorldViewState  = 0;
  }

public:
  size_t& ProjectionState() { return myProjectionState; }

  size_t& WorldViewState() { return myWorldViewState; }

public:
  bool IsProjectionChanged(const Graphic3d_WorldViewProjState& theState)
  {
    return myIsValid != theState.myIsValid || myCamera != theState.myCamera
           || myProjectionState != theState.myProjectionState;
  }

  bool IsWorldViewChanged(const Graphic3d_WorldViewProjState& theState)
  {
    return myIsValid != theState.myIsValid || myCamera != theState.myCamera
           || myWorldViewState != theState.myWorldViewState;
  }

  bool IsChanged(const Graphic3d_WorldViewProjState& theState) { return *this != theState; }

public:
  bool operator!=(const Graphic3d_WorldViewProjState& theOther) const
  {
    return !(*this == theOther);
  }

  bool operator==(const Graphic3d_WorldViewProjState& theOther) const
  {
    return myIsValid == theOther.myIsValid && myCamera == theOther.myCamera
           && myProjectionState == theOther.myProjectionState
           && myWorldViewState == theOther.myWorldViewState;
  }

  void DumpJson(Standard_OStream& theOStream, int) const
  {
    OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myIsValid)
    OCCT_DUMP_FIELD_VALUE_POINTER(theOStream, myCamera)
    OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myProjectionState)
    OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myWorldViewState)
  }

private:
  bool                myIsValid;
  Standard_Transient* myCamera;
  size_t              myProjectionState;
  size_t              myWorldViewState;
};

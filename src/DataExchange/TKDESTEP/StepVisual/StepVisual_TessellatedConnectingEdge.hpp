#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>
#include <StepVisual_TessellatedEdge.hpp>

#include <StepData_Logical.hpp>
#include <StepVisual_TessellatedFace.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

class StepVisual_TessellatedConnectingEdge : public StepVisual_TessellatedEdge
{

public:
  Standard_EXPORT StepVisual_TessellatedConnectingEdge();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&   theRepresentationItem_Name,
    const occ::handle<StepVisual_CoordinatesList>& theTessellatedEdge_Coordinates,
    const bool                                     theHasTessellatedEdge_GeometricLink,
    const StepVisual_EdgeOrCurve&                  theTessellatedEdge_GeometricLink,
    const occ::handle<NCollection_HArray1<int>>&   theTessellatedEdge_LineStrip,
    const StepData_Logical                         theSmooth,
    const occ::handle<StepVisual_TessellatedFace>& theFace1,
    const occ::handle<StepVisual_TessellatedFace>& theFace2,
    const occ::handle<NCollection_HArray1<int>>&   theLineStripFace1,
    const occ::handle<NCollection_HArray1<int>>&   theLineStripFace2);

  Standard_EXPORT StepData_Logical Smooth() const;

  Standard_EXPORT void SetSmooth(const StepData_Logical theSmooth);

  Standard_EXPORT occ::handle<StepVisual_TessellatedFace> Face1() const;

  Standard_EXPORT void SetFace1(const occ::handle<StepVisual_TessellatedFace>& theFace1);

  Standard_EXPORT occ::handle<StepVisual_TessellatedFace> Face2() const;

  Standard_EXPORT void SetFace2(const occ::handle<StepVisual_TessellatedFace>& theFace2);

  Standard_EXPORT occ::handle<NCollection_HArray1<int>> LineStripFace1() const;

  Standard_EXPORT void SetLineStripFace1(
    const occ::handle<NCollection_HArray1<int>>& theLineStripFace1);

  Standard_EXPORT int NbLineStripFace1() const;

  Standard_EXPORT int LineStripFace1Value(const int theNum) const;

  Standard_EXPORT occ::handle<NCollection_HArray1<int>> LineStripFace2() const;

  Standard_EXPORT void SetLineStripFace2(
    const occ::handle<NCollection_HArray1<int>>& theLineStripFace2);

  Standard_EXPORT int NbLineStripFace2() const;

  Standard_EXPORT int LineStripFace2Value(const int theNum) const;

  DEFINE_STANDARD_RTTIEXT(StepVisual_TessellatedConnectingEdge, StepVisual_TessellatedEdge)

private:
  StepData_Logical                        mySmooth;
  occ::handle<StepVisual_TessellatedFace> myFace1;
  occ::handle<StepVisual_TessellatedFace> myFace2;
  occ::handle<NCollection_HArray1<int>>   myLineStripFace1;
  occ::handle<NCollection_HArray1<int>>   myLineStripFace2;
};

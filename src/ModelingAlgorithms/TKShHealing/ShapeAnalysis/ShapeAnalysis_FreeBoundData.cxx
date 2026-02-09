#include <ShapeAnalysis_FreeBoundData.hpp>
#include <Standard_Type.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Wire.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>

IMPLEMENT_STANDARD_RTTIEXT(ShapeAnalysis_FreeBoundData, Standard_Transient)

ShapeAnalysis_FreeBoundData::ShapeAnalysis_FreeBoundData()
{
  myNotches = new NCollection_HSequence<TopoDS_Shape>();
  Clear();
}

ShapeAnalysis_FreeBoundData::ShapeAnalysis_FreeBoundData(const TopoDS_Wire& freebound)
{
  myNotches = new NCollection_HSequence<TopoDS_Shape>();
  Clear();
  SetFreeBound(freebound);
}

void ShapeAnalysis_FreeBoundData::Clear()
{
  myArea      = -1;
  myPerimeter = -1;
  myRatio     = -1;
  myWidth     = -1;
  myNotches->Clear();
  myNotchesParams.Clear();
}

void ShapeAnalysis_FreeBoundData::AddNotch(const TopoDS_Wire& notch, const double width)
{
  if (myNotchesParams.IsBound(notch))
    return;
  myNotches->Append(notch);
  myNotchesParams.Bind(notch, width);
}

double ShapeAnalysis_FreeBoundData::NotchWidth(const int index) const
{
  TopoDS_Wire wire = TopoDS::Wire(myNotches->Value(index));
  return myNotchesParams.Find(wire);
}

double ShapeAnalysis_FreeBoundData::NotchWidth(const TopoDS_Wire& notch) const
{
  return myNotchesParams.Find(notch);
}

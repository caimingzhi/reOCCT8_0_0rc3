#pragma once

#include <Standard.hpp>

#include <TopoDS_Wire.hpp>
#include <Standard_Real.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Integer.hpp>

class ShapeAnalysis_FreeBoundData : public Standard_Transient
{

public:
  Standard_EXPORT ShapeAnalysis_FreeBoundData();

  Standard_EXPORT ShapeAnalysis_FreeBoundData(const TopoDS_Wire& freebound);

  Standard_EXPORT void Clear();

  void SetFreeBound(const TopoDS_Wire& freebound);

  void SetArea(const double area);

  void SetPerimeter(const double perimeter);

  void SetRatio(const double ratio);

  void SetWidth(const double width);

  Standard_EXPORT void AddNotch(const TopoDS_Wire& notch, const double width);

  TopoDS_Wire FreeBound() const;

  double Area() const;

  double Perimeter() const;

  double Ratio() const;

  double Width() const;

  int NbNotches() const;

  occ::handle<NCollection_HSequence<TopoDS_Shape>> Notches() const;

  TopoDS_Wire Notch(const int index) const;

  Standard_EXPORT double NotchWidth(const int index) const;

  Standard_EXPORT double NotchWidth(const TopoDS_Wire& notch) const;

  DEFINE_STANDARD_RTTIEXT(ShapeAnalysis_FreeBoundData, Standard_Transient)

private:
  TopoDS_Wire                                                        myBound;
  double                                                             myArea;
  double                                                             myPerimeter;
  double                                                             myRatio;
  double                                                             myWidth;
  occ::handle<NCollection_HSequence<TopoDS_Shape>>                   myNotches;
  NCollection_DataMap<TopoDS_Shape, double, TopTools_ShapeMapHasher> myNotchesParams;
};

#include <TopoDS.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>

inline void ShapeAnalysis_FreeBoundData::SetFreeBound(const TopoDS_Wire& freebound)
{
  myBound = freebound;
}

inline void ShapeAnalysis_FreeBoundData::SetArea(const double area)
{
  myArea = area;
}

inline void ShapeAnalysis_FreeBoundData::SetPerimeter(const double perimeter)
{
  myPerimeter = perimeter;
}

inline void ShapeAnalysis_FreeBoundData::SetRatio(const double ratio)
{
  myRatio = ratio;
}

inline void ShapeAnalysis_FreeBoundData::SetWidth(const double width)
{
  myWidth = width;
}

inline TopoDS_Wire ShapeAnalysis_FreeBoundData::FreeBound() const
{
  return myBound;
}

inline double ShapeAnalysis_FreeBoundData::Area() const
{
  return myArea;
}

inline double ShapeAnalysis_FreeBoundData::Perimeter() const
{
  return myPerimeter;
}

inline double ShapeAnalysis_FreeBoundData::Ratio() const
{
  return myRatio;
}

inline double ShapeAnalysis_FreeBoundData::Width() const
{
  return myWidth;
}

inline int ShapeAnalysis_FreeBoundData::NbNotches() const
{
  return myNotches->Length();
}

inline occ::handle<NCollection_HSequence<TopoDS_Shape>> ShapeAnalysis_FreeBoundData::Notches() const
{
  return myNotches;
}

inline TopoDS_Wire ShapeAnalysis_FreeBoundData::Notch(const int index) const
{
  return TopoDS::Wire(myNotches->Value(index));
}

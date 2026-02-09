#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDS_Shape.hpp>
#include <TopoDS_Compound.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <Standard_Integer.hpp>
#include <TopoDS_Wire.hpp>
class gp_Dir;
class gp_Pnt;

class BRepProj_Projection
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepProj_Projection(const TopoDS_Shape& Wire,
                                      const TopoDS_Shape& Shape,
                                      const gp_Dir&       D);

  Standard_EXPORT BRepProj_Projection(const TopoDS_Shape& Wire,
                                      const TopoDS_Shape& Shape,
                                      const gp_Pnt&       P);

  bool IsDone() const;

  void Init();

  bool More() const;

  void Next();

  TopoDS_Wire Current() const;

  TopoDS_Compound Shape() const;

private:
  Standard_EXPORT void BuildSection(const TopoDS_Shape& Shape, const TopoDS_Shape& Tool);

  bool                                             myIsDone;
  TopoDS_Shape                                     myLsh;
  TopoDS_Compound                                  myShape;
  occ::handle<NCollection_HSequence<TopoDS_Shape>> mySection;
  int                                              myItr;
};

#include <TopoDS.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>

inline bool BRepProj_Projection::IsDone() const
{
  return myIsDone;
}

inline TopoDS_Compound BRepProj_Projection::Shape() const
{
  return myShape;
}

inline void BRepProj_Projection::Init()
{
  myItr = 1;
}

inline bool BRepProj_Projection::More() const
{
  return myItr > 0 && !mySection.IsNull() && myItr <= mySection->Length();
}

inline void BRepProj_Projection::Next()
{
  myItr++;
}

inline TopoDS_Wire BRepProj_Projection::Current() const
{
  return TopoDS::Wire(mySection->Value(myItr));
}

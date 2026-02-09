#pragma once

#include <Standard.hpp>

#include <Standard_Boolean.hpp>
#include <TopoDS_Shape.hpp>
#include <TopOpeBRepBuild_BlockIterator.hpp>
#include <Standard_Transient.hpp>

class TopOpeBRepBuild_Loop : public Standard_Transient
{

public:
  Standard_EXPORT TopOpeBRepBuild_Loop(const TopoDS_Shape& S);

  Standard_EXPORT TopOpeBRepBuild_Loop(const TopOpeBRepBuild_BlockIterator& BI);

  Standard_EXPORT virtual bool IsShape() const;

  Standard_EXPORT virtual const TopoDS_Shape& Shape() const;

  Standard_EXPORT const TopOpeBRepBuild_BlockIterator& BlockIterator() const;

  Standard_EXPORT virtual void Dump() const;

  DEFINE_STANDARD_RTTIEXT(TopOpeBRepBuild_Loop, Standard_Transient)

protected:
  bool                          myIsShape;
  TopoDS_Shape                  myShape;
  TopOpeBRepBuild_BlockIterator myBlockIterator;
};

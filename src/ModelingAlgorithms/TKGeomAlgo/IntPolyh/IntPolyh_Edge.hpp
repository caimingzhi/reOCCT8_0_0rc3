#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class IntPolyh_Edge
{
public:
  DEFINE_STANDARD_ALLOC

  IntPolyh_Edge()
      : myPoint1(-1),
        myPoint2(-1),
        myTriangle1(-1),
        myTriangle2(-1)
  {
  }

  IntPolyh_Edge(const int thePoint1,
                const int thePoint2,
                const int theTriangle1,
                const int theTriangle2)
      : myPoint1(thePoint1),
        myPoint2(thePoint2),
        myTriangle1(theTriangle1),
        myTriangle2(theTriangle2)
  {
  }

  int FirstPoint() const { return myPoint1; }

  int SecondPoint() const { return myPoint2; }

  int FirstTriangle() const { return myTriangle1; }

  int SecondTriangle() const { return myTriangle2; }

  void SetFirstPoint(const int thePoint) { myPoint1 = thePoint; }

  void SetSecondPoint(const int thePoint) { myPoint2 = thePoint; }

  void SetFirstTriangle(const int theTriangle) { myTriangle1 = theTriangle; }

  void SetSecondTriangle(const int theTriangle) { myTriangle2 = theTriangle; }

  Standard_EXPORT void Dump(const int v) const;

private:
  int myPoint1;
  int myPoint2;
  int myTriangle1;
  int myTriangle2;
};

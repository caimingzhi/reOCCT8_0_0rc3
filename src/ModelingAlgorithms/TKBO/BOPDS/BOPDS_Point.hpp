#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <gp_Pnt.hpp>
#include <gp_Pnt2d.hpp>
#include <Standard_Integer.hpp>
class gp_Pnt;
class gp_Pnt2d;

class BOPDS_Point
{
public:
  DEFINE_STANDARD_ALLOC

  BOPDS_Point();
  virtual ~BOPDS_Point();

  void SetPnt(const gp_Pnt& thePnt);

  const gp_Pnt& Pnt() const;

  void SetPnt2D1(const gp_Pnt2d& thePnt);

  const gp_Pnt2d& Pnt2D1() const;

  void SetPnt2D2(const gp_Pnt2d& thePnt);

  const gp_Pnt2d& Pnt2D2() const;

  void SetIndex(const int theIndex);

  int Index() const;

protected:
  gp_Pnt   myPnt;
  gp_Pnt2d myPnt2D1;
  gp_Pnt2d myPnt2D2;
  int      myIndex;
};

inline BOPDS_Point::BOPDS_Point()
{
  myPnt.SetCoord(99., 99., 99.);
  myPnt2D1.SetCoord(99., 99.);
  myPnt2D2 = myPnt2D1;
  myIndex  = -1;
}

inline BOPDS_Point::~BOPDS_Point() = default;

inline void BOPDS_Point::SetIndex(const int theIndex)
{
  myIndex = theIndex;
}

inline int BOPDS_Point::Index() const
{
  return myIndex;
}

inline void BOPDS_Point::SetPnt(const gp_Pnt& thePnt)
{
  myPnt = thePnt;
}

inline const gp_Pnt& BOPDS_Point::Pnt() const
{
  return myPnt;
}

inline void BOPDS_Point::SetPnt2D1(const gp_Pnt2d& thePnt)
{
  myPnt2D1 = thePnt;
}

inline const gp_Pnt2d& BOPDS_Point::Pnt2D1() const
{
  return myPnt2D1;
}

inline void BOPDS_Point::SetPnt2D2(const gp_Pnt2d& thePnt)
{
  myPnt2D2 = thePnt;
}

inline const gp_Pnt2d& BOPDS_Point::Pnt2D2() const
{
  return myPnt2D2;
}

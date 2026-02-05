#include <IntTools_PntOn2Faces.hpp>
#include <IntTools_PntOnFace.hpp>

//=================================================================================================

IntTools_PntOn2Faces::IntTools_PntOn2Faces()
    : myIsValid(false)
{
}

//=================================================================================================

IntTools_PntOn2Faces::IntTools_PntOn2Faces(const IntTools_PntOnFace& aP1,
                                           const IntTools_PntOnFace& aP2)
    : myIsValid(false)
{
  myPnt1 = aP1;
  myPnt2 = aP2;
}

//=================================================================================================

void IntTools_PntOn2Faces::SetP1(const IntTools_PntOnFace& aP)
{
  myPnt1 = aP;
}

//=================================================================================================

void IntTools_PntOn2Faces::SetP2(const IntTools_PntOnFace& aP)
{
  myPnt2 = aP;
}

//=================================================================================================

const IntTools_PntOnFace& IntTools_PntOn2Faces::P1() const
{
  return myPnt1;
}

//=================================================================================================

const IntTools_PntOnFace& IntTools_PntOn2Faces::P2() const
{
  return myPnt2;
}

//=================================================================================================

void IntTools_PntOn2Faces::SetValid(const bool bF)
{
  myIsValid = bF;
}

//=================================================================================================

bool IntTools_PntOn2Faces::IsValid() const
{
  return myIsValid;
}

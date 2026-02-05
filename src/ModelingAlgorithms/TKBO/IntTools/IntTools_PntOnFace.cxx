#include <IntTools_PntOnFace.hpp>
#include <TopoDS_Face.hpp>

//=================================================================================================

IntTools_PntOnFace::IntTools_PntOnFace()
    : myIsValid(false),
      myU(99.),
      myV(99.)
{
}

//=================================================================================================

void IntTools_PntOnFace::Init(const TopoDS_Face& aF,
                              const gp_Pnt&      aP,
                              const double       anU,
                              const double       aV)
{
  myFace = aF;
  myPnt  = aP;
  myU    = anU;
  myV    = aV;
}

//=================================================================================================

void IntTools_PntOnFace::SetFace(const TopoDS_Face& aF)
{
  myFace = aF;
}

//=================================================================================================

void IntTools_PntOnFace::SetPnt(const gp_Pnt& aP)
{
  myPnt = aP;
}

//=================================================================================================

void IntTools_PntOnFace::SetParameters(const double anU, const double aV)
{
  myU = anU;
  myV = aV;
}

//=================================================================================================

void IntTools_PntOnFace::SetValid(const bool bF)
{
  myIsValid = bF;
}

//=================================================================================================

const TopoDS_Face& IntTools_PntOnFace::Face() const
{
  return myFace;
}

//=================================================================================================

const gp_Pnt& IntTools_PntOnFace::Pnt() const
{
  return myPnt;
}

//=================================================================================================

void IntTools_PntOnFace::Parameters(double& anU, double& aV) const
{
  anU = myU;
  aV  = myV;
}

//=================================================================================================

bool IntTools_PntOnFace::Valid() const
{
  return myIsValid;
}

//=================================================================================================

#include <Precision.hpp>
#include <TopOpeBRepTool_GeomTool.hpp>

//=================================================================================================

TopOpeBRepTool_GeomTool::TopOpeBRepTool_GeomTool(const TopOpeBRepTool_OutCurveType TypeC3D,
                                                 const bool                        CompC3D,
                                                 const bool                        CompPC1,
                                                 const bool                        CompPC2)
    : myTypeC3D(TypeC3D),
      myCompC3D(CompC3D),
      myCompPC1(CompPC1),
      myCompPC2(CompPC2),
      myTol3d(Precision::Approximation()),
      myTol2d(Precision::PApproximation()),
      myNbPntMax(30)
{
}

//=================================================================================================

void TopOpeBRepTool_GeomTool::Define(const TopOpeBRepTool_OutCurveType TypeC3D,
                                     const bool                        CompC3D,
                                     const bool                        CompPC1,
                                     const bool                        CompPC2)
{
  myTypeC3D = TypeC3D;
  myCompC3D = CompC3D;
  myCompPC1 = CompPC1;
  myCompPC2 = CompPC2;
}

//=================================================================================================

void TopOpeBRepTool_GeomTool::Define(const TopOpeBRepTool_OutCurveType TypeC3D)
{
  myTypeC3D = TypeC3D;
}

//=================================================================================================

void TopOpeBRepTool_GeomTool::DefineCurves(const bool CompC3D)
{
  myCompC3D = CompC3D;
}

//=================================================================================================

void TopOpeBRepTool_GeomTool::DefinePCurves1(const bool CompPC1)
{
  myCompPC1 = CompPC1;
}

//=================================================================================================

void TopOpeBRepTool_GeomTool::DefinePCurves2(const bool CompPC2)
{
  myCompPC2 = CompPC2;
}

//=================================================================================================

void TopOpeBRepTool_GeomTool::Define(const TopOpeBRepTool_GeomTool& GT)
{
  *this = GT;
}

//=================================================================================================

void TopOpeBRepTool_GeomTool::GetTolerances(double& tol3d, double& tol2d) const
{
  tol3d = myTol3d;
  tol2d = myTol2d;
}

//=================================================================================================

void TopOpeBRepTool_GeomTool::SetTolerances(const double tol3d, const double tol2d)
{
  myTol3d = tol3d;
  myTol2d = tol2d;
}

//=================================================================================================

int TopOpeBRepTool_GeomTool::NbPntMax() const
{
  return myNbPntMax;
}

//=================================================================================================

void TopOpeBRepTool_GeomTool::SetNbPntMax(const int NbPntMax)
{
  myNbPntMax = NbPntMax;
}

//=================================================================================================

bool TopOpeBRepTool_GeomTool::CompC3D() const
{
  return myCompC3D;
}

//=================================================================================================

TopOpeBRepTool_OutCurveType TopOpeBRepTool_GeomTool::TypeC3D() const
{
  return myTypeC3D;
}

//=================================================================================================

bool TopOpeBRepTool_GeomTool::CompPC1() const
{
  return myCompPC1;
}

//=================================================================================================

bool TopOpeBRepTool_GeomTool::CompPC2() const
{
  return myCompPC2;
}

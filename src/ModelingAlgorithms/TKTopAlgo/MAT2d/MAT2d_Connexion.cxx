#include <gp_Pnt2d.hpp>
#include <gp_Vec2d.hpp>
#include <MAT2d_Connexion.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(MAT2d_Connexion, Standard_Transient)

//=================================================================================================

MAT2d_Connexion::MAT2d_Connexion()
    : lineA(0),
      lineB(0),
      itemA(0),
      itemB(0),
      distance(0.0),
      parameterOnA(0.0),
      parameterOnB(0.0)
{
}

//=================================================================================================

MAT2d_Connexion::MAT2d_Connexion(const int       LineA,
                                 const int       LineB,
                                 const int       ItemA,
                                 const int       ItemB,
                                 const double    Distance,
                                 const double    ParameterOnA,
                                 const double    ParameterOnB,
                                 const gp_Pnt2d& PointA,
                                 const gp_Pnt2d& PointB)
    : lineA(LineA),
      lineB(LineB),
      itemA(ItemA),
      itemB(ItemB),
      distance(Distance),
      parameterOnA(ParameterOnA),
      parameterOnB(ParameterOnB),
      pointA(PointA),
      pointB(PointB)
{
}

//=================================================================================================

int MAT2d_Connexion::IndexFirstLine() const
{
  return lineA;
}

//=================================================================================================

int MAT2d_Connexion::IndexSecondLine() const
{
  return lineB;
}

//=================================================================================================

int MAT2d_Connexion::IndexItemOnFirst() const
{
  return itemA;
}

//=================================================================================================

int MAT2d_Connexion::IndexItemOnSecond() const
{
  return itemB;
}

//=================================================================================================

double MAT2d_Connexion::ParameterOnFirst() const
{
  return parameterOnA;
}

//=================================================================================================

double MAT2d_Connexion::ParameterOnSecond() const
{
  return parameterOnB;
}

//=================================================================================================

gp_Pnt2d MAT2d_Connexion::PointOnFirst() const
{
  return pointA;
}

//=================================================================================================

gp_Pnt2d MAT2d_Connexion::PointOnSecond() const
{
  return pointB;
}

//=================================================================================================

double MAT2d_Connexion::Distance() const
{
  return distance;
}

//=================================================================================================

void MAT2d_Connexion::IndexFirstLine(const int anIndex)
{
  lineA = anIndex;
}

//=================================================================================================

void MAT2d_Connexion::IndexSecondLine(const int anIndex)
{
  lineB = anIndex;
}

//=================================================================================================

void MAT2d_Connexion::IndexItemOnFirst(const int anIndex)
{
  itemA = anIndex;
}

//=================================================================================================

void MAT2d_Connexion::IndexItemOnSecond(const int anIndex)
{
  itemB = anIndex;
}

//=================================================================================================

void MAT2d_Connexion::ParameterOnFirst(const double aParameter)
{
  parameterOnA = aParameter;
}

//=================================================================================================

void MAT2d_Connexion::ParameterOnSecond(const double aParameter)
{
  parameterOnB = aParameter;
}

//=================================================================================================

void MAT2d_Connexion::PointOnFirst(const gp_Pnt2d& aPoint)
{
  pointA = aPoint;
}

//=================================================================================================

void MAT2d_Connexion::PointOnSecond(const gp_Pnt2d& aPoint)
{
  pointB = aPoint;
}

//=================================================================================================

void MAT2d_Connexion::Distance(const double d)
{
  distance = d;
}

//=================================================================================================

occ::handle<MAT2d_Connexion> MAT2d_Connexion::Reverse() const
{
  return new MAT2d_Connexion(lineB,
                             lineA,
                             itemB,
                             itemA,
                             distance,
                             parameterOnB,
                             parameterOnA,
                             pointB,
                             pointA);
}

//=================================================================================================

bool MAT2d_Connexion::IsAfter(const occ::handle<MAT2d_Connexion>& C2, const double Sense) const
{
  if (lineA != C2->IndexFirstLine())
  {
    return false;
  }

  if (itemA > C2->IndexItemOnFirst())
  {
    return true;
  }
  else if (itemA == C2->IndexItemOnFirst())
  {
    if (parameterOnA > C2->ParameterOnFirst())
    {
      return true;
    }
    else if (parameterOnA == C2->ParameterOnFirst())
    {
      gp_Vec2d Vect1(C2->PointOnFirst(), C2->PointOnSecond());
      gp_Vec2d Vect2(pointA, pointB);
      if ((Vect1 ^ Vect2) * Sense > 0)
      {
        return true;
      }
    }
  }
  return false;
}

static void Indent(const int Offset)
{
  if (Offset > 0)
  {
    for (int i = 0; i < Offset; i++)
    {
      std::cout << " ";
    }
  }
}

//=================================================================================================

void MAT2d_Connexion::Dump(const int, const int Offset) const
{
  int MyOffset = Offset;
  Indent(Offset);
  std::cout << "MAT2d_Connexion :" << std::endl;
  MyOffset++;
  Indent(MyOffset);
  std::cout << "IndexFirstLine    :" << lineA << std::endl;
  Indent(MyOffset);
  std::cout << "IndexSecondLine   :" << lineB << std::endl;
  Indent(MyOffset);
  std::cout << "IndexItemOnFirst  :" << itemA << std::endl;
  Indent(MyOffset);
  std::cout << "IndexItemOnSecond :" << itemB << std::endl;
  Indent(MyOffset);
  std::cout << "ParameterOnFirst  :" << parameterOnA << std::endl;
  Indent(MyOffset);
  std::cout << "ParameterOnSecond :" << parameterOnB << std::endl;
  Indent(MyOffset);
  std::cout << "PointOnFirst      :" << std::endl;
  std::cout << "  X = " << pointA.X() << std::endl;
  std::cout << "  Y = " << pointA.Y() << std::endl;
  Indent(MyOffset);
  std::cout << "PointOnSecond     :" << std::endl;
  std::cout << "  X = " << pointB.X() << std::endl;
  std::cout << "  Y = " << pointB.Y() << std::endl;
  Indent(MyOffset);
  std::cout << "Distance          :" << distance << std::endl;
}

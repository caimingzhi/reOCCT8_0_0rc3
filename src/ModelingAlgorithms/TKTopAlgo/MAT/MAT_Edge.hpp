#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <Standard_Transient.hpp>
class MAT_Bisector;

class MAT_Edge : public Standard_Transient
{

public:
  Standard_EXPORT MAT_Edge();

  Standard_EXPORT void EdgeNumber(const int anumber);

  Standard_EXPORT void FirstBisector(const occ::handle<MAT_Bisector>& abisector);

  Standard_EXPORT void SecondBisector(const occ::handle<MAT_Bisector>& abisector);

  Standard_EXPORT void Distance(const double adistance);

  Standard_EXPORT void IntersectionPoint(const int apoint);

  Standard_EXPORT int EdgeNumber() const;

  Standard_EXPORT occ::handle<MAT_Bisector> FirstBisector() const;

  Standard_EXPORT occ::handle<MAT_Bisector> SecondBisector() const;

  Standard_EXPORT double Distance() const;

  Standard_EXPORT int IntersectionPoint() const;

  Standard_EXPORT void Dump(const int ashift, const int alevel) const;

  DEFINE_STANDARD_RTTIEXT(MAT_Edge, Standard_Transient)

private:
  int                       theedgenumber;
  occ::handle<MAT_Bisector> thefirstbisector;
  occ::handle<MAT_Bisector> thesecondbisector;
  double                    thedistance;
  int                       theintersectionpoint;
};


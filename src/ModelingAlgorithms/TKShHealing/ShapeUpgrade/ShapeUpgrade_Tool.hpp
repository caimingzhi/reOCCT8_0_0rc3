#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class ShapeBuild_ReShape;

class ShapeUpgrade_Tool : public Standard_Transient
{

public:
  Standard_EXPORT ShapeUpgrade_Tool();

  Standard_EXPORT void Set(const occ::handle<ShapeUpgrade_Tool>& tool);

  void SetContext(const occ::handle<ShapeBuild_ReShape>& context);

  occ::handle<ShapeBuild_ReShape> Context() const;

  void SetPrecision(const double preci);

  double Precision() const;

  void SetMinTolerance(const double mintol);

  double MinTolerance() const;

  void SetMaxTolerance(const double maxtol);

  double MaxTolerance() const;

  double LimitTolerance(const double toler) const;

  DEFINE_STANDARD_RTTIEXT(ShapeUpgrade_Tool, Standard_Transient)

private:
  occ::handle<ShapeBuild_ReShape> myContext;
  double                          myPrecision;
  double                          myMinTol;
  double                          myMaxTol;
};

inline void ShapeUpgrade_Tool::SetContext(const occ::handle<ShapeBuild_ReShape>& context)
{
  myContext = context;
}

inline occ::handle<ShapeBuild_ReShape> ShapeUpgrade_Tool::Context() const
{
  return myContext;
}

inline void ShapeUpgrade_Tool::SetPrecision(const double preci)
{
  myPrecision = preci;
  if (myMaxTol < myPrecision)
    myMaxTol = myPrecision;
  if (myMinTol > myPrecision)
    myMinTol = myPrecision;
}

inline double ShapeUpgrade_Tool::Precision() const
{
  return myPrecision;
}

inline void ShapeUpgrade_Tool::SetMinTolerance(const double mintol)
{
  myMinTol = mintol;
}

inline double ShapeUpgrade_Tool::MinTolerance() const
{
  return myMinTol;
}

inline void ShapeUpgrade_Tool::SetMaxTolerance(const double maxtol)
{
  myMaxTol = maxtol;
}

inline double ShapeUpgrade_Tool::MaxTolerance() const
{
  return myMaxTol;
}

inline double ShapeUpgrade_Tool::LimitTolerance(const double toler) const
{

  return std::min(myMaxTol, toler);
}

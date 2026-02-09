#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Real.hpp>
#include <Standard_Boolean.hpp>
class Geom_Surface;

class TopOpeBRepDS_Surface
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopOpeBRepDS_Surface();

  Standard_EXPORT TopOpeBRepDS_Surface(const occ::handle<Geom_Surface>& P, const double T);

  Standard_EXPORT TopOpeBRepDS_Surface(const TopOpeBRepDS_Surface& Other);

  Standard_EXPORT void Assign(const TopOpeBRepDS_Surface& Other);

  void operator=(const TopOpeBRepDS_Surface& Other) { Assign(Other); }

  const occ::handle<Geom_Surface>& Surface() const { return mySurface; }

  double Tolerance() const { return myTolerance; }

  void Tolerance(double theTol) { myTolerance = theTol; }

  bool Keep() const { return myKeep; }

  void ChangeKeep(bool theToKeep) { myKeep = theToKeep; }

private:
  occ::handle<Geom_Surface> mySurface;
  double                    myTolerance;
  bool                      myKeep;
};

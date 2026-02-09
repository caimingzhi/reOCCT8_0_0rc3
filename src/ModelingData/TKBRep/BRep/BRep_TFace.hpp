#pragma once

#include <Standard.hpp>

#include <Poly_Triangulation.hpp>
#include <TopLoc_Location.hpp>
#include <Standard_Real.hpp>
#include <TopoDS_TFace.hpp>
class Geom_Surface;
class TopoDS_TShape;

class BRep_TFace : public TopoDS_TFace
{

public:
  Standard_EXPORT BRep_TFace();

  const occ::handle<Geom_Surface>& Surface() const { return mySurface; }

  void Surface(const occ::handle<Geom_Surface>& theSurface) { mySurface = theSurface; }

  const TopLoc_Location& Location() const { return myLocation; }

  void Location(const TopLoc_Location& theLocation) { myLocation = theLocation; }

  double Tolerance() const { return myTolerance; }

  void Tolerance(const double theTolerance) { myTolerance = theTolerance; }

  bool NaturalRestriction() const { return myNaturalRestriction; }

  void NaturalRestriction(const bool theRestriction) { myNaturalRestriction = theRestriction; }

  Standard_EXPORT const occ::handle<Poly_Triangulation>& Triangulation(
    const Poly_MeshPurpose thePurpose = Poly_MeshPurpose_NONE) const;

  Standard_EXPORT void Triangulation(const occ::handle<Poly_Triangulation>& theTriangulation,
                                     const bool                             theToReset = true);

  Standard_EXPORT occ::handle<TopoDS_TShape> EmptyCopy() const override;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

public:
  const NCollection_List<occ::handle<Poly_Triangulation>>& Triangulations() const
  {
    return myTriangulations;
  }

  Standard_EXPORT void Triangulations(
    const NCollection_List<occ::handle<Poly_Triangulation>>& theTriangulations,
    const occ::handle<Poly_Triangulation>&                   theActiveTriangulation);

  int NbTriangulations() const { return myTriangulations.Size(); }

  const occ::handle<Poly_Triangulation>& ActiveTriangulation() const
  {
    return myActiveTriangulation;
  }

  DEFINE_STANDARD_RTTIEXT(BRep_TFace, TopoDS_TFace)

private:
  NCollection_List<occ::handle<Poly_Triangulation>> myTriangulations;
  occ::handle<Poly_Triangulation>                   myActiveTriangulation;
  occ::handle<Geom_Surface>                         mySurface;
  TopLoc_Location                                   myLocation;
  double                                            myTolerance;
  bool                                              myNaturalRestriction;
};

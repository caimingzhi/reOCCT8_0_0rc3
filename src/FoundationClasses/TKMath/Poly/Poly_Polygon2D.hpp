#pragma once

#include <gp_Pnt2d.hpp>
#include <NCollection_Array1.hpp>
#include <Standard_Transient.hpp>

class Poly_Polygon2D : public Standard_Transient
{
public:
  Standard_EXPORT explicit Poly_Polygon2D(const int theNbNodes);

  Standard_EXPORT Poly_Polygon2D(const NCollection_Array1<gp_Pnt2d>& Nodes);

  double Deflection() const { return myDeflection; }

  void Deflection(const double theDefl) { myDeflection = theDefl; }

  int NbNodes() const { return myNodes.Length(); }

  const NCollection_Array1<gp_Pnt2d>& Nodes() const { return myNodes; }

  NCollection_Array1<gp_Pnt2d>& ChangeNodes() { return myNodes; }

  Standard_EXPORT virtual void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

  DEFINE_STANDARD_RTTIEXT(Poly_Polygon2D, Standard_Transient)

private:
  double                       myDeflection;
  NCollection_Array1<gp_Pnt2d> myNodes;
};

#pragma once

#include <Standard_Transient.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

class Poly_Polygon3D : public Standard_Transient
{
public:
  Standard_EXPORT Poly_Polygon3D(const int theNbNodes, const bool theHasParams);

  Standard_EXPORT Poly_Polygon3D(const NCollection_Array1<gp_Pnt>& Nodes);

  Standard_EXPORT Poly_Polygon3D(const NCollection_Array1<gp_Pnt>& Nodes,
                                 const NCollection_Array1<double>& Parameters);

  Standard_EXPORT virtual occ::handle<Poly_Polygon3D> Copy() const;

  double Deflection() const { return myDeflection; }

  void Deflection(const double theDefl) { myDeflection = theDefl; }

  int NbNodes() const { return myNodes.Length(); }

  const NCollection_Array1<gp_Pnt>& Nodes() const { return myNodes; }

  NCollection_Array1<gp_Pnt>& ChangeNodes() { return myNodes; }

  bool HasParameters() const { return !myParameters.IsNull(); }

  const NCollection_Array1<double>& Parameters() const { return myParameters->Array1(); }

  NCollection_Array1<double>& ChangeParameters() const { return myParameters->ChangeArray1(); }

  Standard_EXPORT virtual void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

  DEFINE_STANDARD_RTTIEXT(Poly_Polygon3D, Standard_Transient)

private:
  double                                   myDeflection;
  NCollection_Array1<gp_Pnt>               myNodes;
  occ::handle<NCollection_HArray1<double>> myParameters;
};

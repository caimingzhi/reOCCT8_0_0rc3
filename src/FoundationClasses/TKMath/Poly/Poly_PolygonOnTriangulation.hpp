#pragma once

#include <Standard_NullObject.hpp>
#include <Standard_Type.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

class Poly_PolygonOnTriangulation : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(Poly_PolygonOnTriangulation, Standard_Transient)
public:
  Standard_EXPORT Poly_PolygonOnTriangulation(const int theNbNodes, const bool theHasParams);

  Standard_EXPORT Poly_PolygonOnTriangulation(const NCollection_Array1<int>& Nodes);

  Standard_EXPORT Poly_PolygonOnTriangulation(const NCollection_Array1<int>&    Nodes,
                                              const NCollection_Array1<double>& Parameters);

  Standard_EXPORT virtual occ::handle<Poly_PolygonOnTriangulation> Copy() const;

  double Deflection() const { return myDeflection; }

  void Deflection(const double theDefl) { myDeflection = theDefl; }

  int NbNodes() const { return myNodes.Length(); }

  int Node(int theIndex) const { return myNodes.Value(theIndex); }

  void SetNode(int theIndex, int theNode) { myNodes.SetValue(theIndex, theNode); }

  bool HasParameters() const { return !myParameters.IsNull(); }

  double Parameter(int theIndex) const
  {
    Standard_NullObject_Raise_if(myParameters.IsNull(),
                                 "Poly_PolygonOnTriangulation::Parameter : parameters is NULL");
    return myParameters->Value(theIndex);
  }

  void SetParameter(int theIndex, double theValue)
  {
    Standard_NullObject_Raise_if(myParameters.IsNull(),
                                 "Poly_PolygonOnTriangulation::Parameter : parameters is NULL");
    myParameters->SetValue(theIndex, theValue);
  }

  Standard_EXPORT void SetParameters(const occ::handle<NCollection_HArray1<double>>& theParameters);

  Standard_EXPORT virtual void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

public:
  const NCollection_Array1<int>& Nodes() const { return myNodes; }

  const occ::handle<NCollection_HArray1<double>>& Parameters() const { return myParameters; }

  Standard_DEPRECATED("Deprecated method, SetNode() should be used instead")

  NCollection_Array1<int>& ChangeNodes() { return myNodes; }

  Standard_DEPRECATED("Deprecated method, SetParameter() should be used instead")

  NCollection_Array1<double>& ChangeParameters() { return myParameters->ChangeArray1(); }

private:
  double                                   myDeflection;
  NCollection_Array1<int>                  myNodes;
  occ::handle<NCollection_HArray1<double>> myParameters;
};

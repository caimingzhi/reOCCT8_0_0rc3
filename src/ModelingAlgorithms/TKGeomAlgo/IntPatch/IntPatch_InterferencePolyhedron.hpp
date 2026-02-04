#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Standard_Integer.hpp>
#include <gp_XYZ.hpp>
#include <Intf_Interference.hpp>
class IntPatch_Polyhedron;
class Intf_TangentZone;

//! Computes the interference between two polyhedra or the
//! self interference of a polyhedron. Points of intersection,
//! polylines of intersection and zones of tangence.
class IntPatch_InterferencePolyhedron : public Intf_Interference
{
public:
  DEFINE_STANDARD_ALLOC

  //! Constructs an empty interference of Polyhedron.
  Standard_EXPORT IntPatch_InterferencePolyhedron();

  //! Constructs and computes an interference between the two
  //! Polyhedra.
  Standard_EXPORT IntPatch_InterferencePolyhedron(const IntPatch_Polyhedron& Obje1,
                                                  const IntPatch_Polyhedron& Obje2);

  //! Constructs and computes the self interference of a
  //! Polyhedron.
  Standard_EXPORT IntPatch_InterferencePolyhedron(const IntPatch_Polyhedron& Obje);

  //! Computes the interference between the two Polyhedra.
  Standard_EXPORT void Perform(const IntPatch_Polyhedron& Obje1, const IntPatch_Polyhedron& Obje2);

  //! Computes the self interference of a Polyhedron.
  Standard_EXPORT void Perform(const IntPatch_Polyhedron& Obje);

private:
  Standard_EXPORT void Interference(const IntPatch_Polyhedron& Obje1);

  //! Compares the bounding volumes between the facets of <Obje1>
  //! and the facets of <Obje2> and intersects the facets when the
  //! bounding volumes have a common part.
  Standard_EXPORT void Interference(const IntPatch_Polyhedron& Obje1,
                                    const IntPatch_Polyhedron& Obje2);

  //! Computes the intersection between the facet <Tri1> of
  //! <FirstPol> and the facet <Tri2> of <SecondPol>.
  Standard_EXPORT void Intersect(const int                  TriF,
                                 const IntPatch_Polyhedron& Obje1,
                                 const int                  TriS,
                                 const IntPatch_Polyhedron& Obje2);

  //! Computes the zone of tangence between the facet <Tri1> of
  //! <FirstPol> and the facet <Tri2> of <SecondPol>.
  Standard_EXPORT bool TangentZoneValue(Intf_TangentZone&          TheTZ,
                                        const IntPatch_Polyhedron& Obje1,
                                        const int                  Tri1,
                                        const IntPatch_Polyhedron& Obje2,
                                        const int                  Tri2) const;

  Standard_EXPORT void CoupleCharacteristics(const IntPatch_Polyhedron& FirstPol,
                                             const IntPatch_Polyhedron& SeconPol);

  int    OI[3];
  int    TI[3];
  double dpOpT[3][3];
  double dpOeT[3][3];
  double deOpT[3][3];
  gp_XYZ voo[3];
  gp_XYZ vtt[3];
  double Incidence;
};


#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Standard_Integer.hpp>
#include <gp_XYZ.hpp>
#include <Intf_Interference.hpp>
class IntPatch_Polyhedron;
class Intf_TangentZone;

class IntPatch_InterferencePolyhedron : public Intf_Interference
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IntPatch_InterferencePolyhedron();

  Standard_EXPORT IntPatch_InterferencePolyhedron(const IntPatch_Polyhedron& Obje1,
                                                  const IntPatch_Polyhedron& Obje2);

  Standard_EXPORT IntPatch_InterferencePolyhedron(const IntPatch_Polyhedron& Obje);

  Standard_EXPORT void Perform(const IntPatch_Polyhedron& Obje1, const IntPatch_Polyhedron& Obje2);

  Standard_EXPORT void Perform(const IntPatch_Polyhedron& Obje);

private:
  Standard_EXPORT void Interference(const IntPatch_Polyhedron& Obje1);

  Standard_EXPORT void Interference(const IntPatch_Polyhedron& Obje1,
                                    const IntPatch_Polyhedron& Obje2);

  Standard_EXPORT void Intersect(const int                  TriF,
                                 const IntPatch_Polyhedron& Obje1,
                                 const int                  TriS,
                                 const IntPatch_Polyhedron& Obje2);

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

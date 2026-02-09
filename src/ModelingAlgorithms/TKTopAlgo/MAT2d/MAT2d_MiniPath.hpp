#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <MAT2d_Connexion.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_DataMap.hpp>
#include <Geom2d_Geometry.hpp>
class MAT2d_Connexion;

class MAT2d_MiniPath
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT MAT2d_MiniPath();

  Standard_EXPORT void Perform(
    const NCollection_Sequence<NCollection_Sequence<occ::handle<Geom2d_Geometry>>>& Figure,
    const int                                                                       IndStart,
    const bool                                                                      Sense);

  Standard_EXPORT void RunOnConnexions();

  Standard_EXPORT const NCollection_Sequence<occ::handle<MAT2d_Connexion>>& Path() const;

  Standard_EXPORT bool IsConnexionsFrom(const int Index) const;

  Standard_EXPORT NCollection_Sequence<occ::handle<MAT2d_Connexion>>& ConnexionsFrom(
    const int Index);

  Standard_EXPORT bool IsRoot(const int Index) const;

  Standard_EXPORT occ::handle<MAT2d_Connexion> Father(const int Index);

private:
  Standard_EXPORT void Append(const occ::handle<MAT2d_Connexion>& Connexion);

  Standard_EXPORT void ExploSons(NCollection_Sequence<occ::handle<MAT2d_Connexion>>& aPath,
                                 const occ::handle<MAT2d_Connexion>&                 aConnexion);

  Standard_EXPORT occ::handle<MAT2d_Connexion> MinimumL1L2(
    const NCollection_Sequence<NCollection_Sequence<occ::handle<Geom2d_Geometry>>>& Figure,
    const int                                                                       L1,
    const int                                                                       L2) const;

  NCollection_DataMap<int, NCollection_Sequence<occ::handle<MAT2d_Connexion>>> theConnexions;
  NCollection_DataMap<int, occ::handle<MAT2d_Connexion>>                       theFather;
  NCollection_Sequence<occ::handle<MAT2d_Connexion>>                           thePath;
  double                                                                       theDirection;
  int                                                                          indStart;
};

#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <MAT2d_Connexion.hpp>
#include <NCollection_DataMap.hpp>
#include <MAT2d_BiInt.hpp>
#include <NCollection_Sequence.hpp>
#include <GeomAbs_JoinType.hpp>
#include <Standard_Transient.hpp>
#include <Geom2d_Geometry.hpp>
class Geom2d_Geometry;
class MAT2d_Connexion;
class MAT2d_BiInt;
class MAT2d_MiniPath;

//! Constructs a circuit on a set of lines.
//! EquiCircuit gives a Circuit passing by all the lines
//! in a set and all the connexions of the minipath associated.
class MAT2d_Circuit : public Standard_Transient
{

public:
  Standard_EXPORT MAT2d_Circuit(const GeomAbs_JoinType aJoinType    = GeomAbs_Arc,
                                const bool             IsOpenResult = false);

  Standard_EXPORT void Perform(
    NCollection_Sequence<NCollection_Sequence<occ::handle<Geom2d_Geometry>>>& aFigure,
    const NCollection_Sequence<bool>&                                         IsClosed,
    const int                                                                 IndRefLine,
    const bool                                                                Trigo);

  //! Returns the Number of Items .
  Standard_EXPORT int NumberOfItems() const;

  //! Returns the item at position <Index> in <me>.
  Standard_EXPORT occ::handle<Geom2d_Geometry> Value(const int Index) const;

  //! Returns the number of items on the line <IndexLine>.
  Standard_EXPORT int LineLength(const int IndexLine) const;

  //! Returns the set of index of the items in <me>corresponding
  //! to the curve <IndCurve> on the line <IndLine> from the
  //! initial figure.
  Standard_EXPORT const NCollection_Sequence<int>& RefToEqui(const int IndLine,
                                                             const int IndCurve) const;

  //! Returns the Connexion on the item <Index> in me.
  Standard_EXPORT occ::handle<MAT2d_Connexion> Connexion(const int Index) const;

  //! Returns <True> is there is a connexion on the item <Index>
  //! in <me>.
  Standard_EXPORT bool ConnexionOn(const int Index) const;

  DEFINE_STANDARD_RTTIEXT(MAT2d_Circuit, Standard_Transient)

private:
  Standard_EXPORT bool IsSharpCorner(const occ::handle<Geom2d_Geometry>& Geom1,
                                     const occ::handle<Geom2d_Geometry>& Geom2,
                                     const double                        Direction) const;

  Standard_EXPORT bool PassByLast(const occ::handle<MAT2d_Connexion>& C1,
                                  const occ::handle<MAT2d_Connexion>& C2) const;

  Standard_EXPORT double Side(const occ::handle<MAT2d_Connexion>&                       C,
                              const NCollection_Sequence<occ::handle<Geom2d_Geometry>>& Line) const;

  Standard_EXPORT void UpDateLink(const int IFirst,
                                  const int ILine,
                                  const int ICurveFirst,
                                  const int ICurveLast);

  Standard_EXPORT void SortRefToEqui(const MAT2d_BiInt& aBiInt);

  Standard_EXPORT void InitOpen(NCollection_Sequence<occ::handle<Geom2d_Geometry>>& Line) const;

  Standard_EXPORT void InsertCorner(NCollection_Sequence<occ::handle<Geom2d_Geometry>>& Line) const;

  Standard_EXPORT void DoubleLine(NCollection_Sequence<occ::handle<Geom2d_Geometry>>& Line,
                                  NCollection_Sequence<occ::handle<MAT2d_Connexion>>& Connexions,
                                  const occ::handle<MAT2d_Connexion>&                 Father,
                                  const double                                        Side) const;

  Standard_EXPORT void ConstructCircuit(
    const NCollection_Sequence<NCollection_Sequence<occ::handle<Geom2d_Geometry>>>& aFigure,
    const int                                                                       IndRefLine,
    const MAT2d_MiniPath&                                                           aPath);

  double                                                      direction;
  NCollection_Sequence<occ::handle<Geom2d_Geometry>>          geomElements;
  NCollection_DataMap<int, occ::handle<MAT2d_Connexion>>      connexionMap;
  NCollection_DataMap<MAT2d_BiInt, NCollection_Sequence<int>> linkRefEqui;
  NCollection_Sequence<int>                                   linesLength;
  GeomAbs_JoinType                                            myJoinType;
  bool                                                        myIsOpenResult;
};

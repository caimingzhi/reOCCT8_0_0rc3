#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <TopOpeBRepDS_Interference.hpp>
#include <NCollection_List.hpp>
class TopoDS_Shape;
class TopOpeBRep_FaceEdgeIntersector;
class TopOpeBRepDS_HDataStructure;
class TopOpeBRepDS_Point;
class TopOpeBRepDS_DataStructure;
class TopOpeBRepDS_Interference;

class TopOpeBRep_FaceEdgeFiller
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopOpeBRep_FaceEdgeFiller();

  Standard_EXPORT void Insert(const TopoDS_Shape&                             F,
                              const TopoDS_Shape&                             E,
                              TopOpeBRep_FaceEdgeIntersector&                 FEINT,
                              const occ::handle<TopOpeBRepDS_HDataStructure>& HDS);

private:
  //! Search, among a list of interferences accessed by the iterator
  //! <IT>, a geometry <G> whose 3D point is identical to the 3D point
  //! of the TheDSPoint <DSP>.
  //! returns True if such an interference has been found, False else.
  //! if True, iterator It points (by the Value() method) on the first
  //! interference accessing an identical 3D point.
  Standard_EXPORT bool ScanInterfList(
    NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator& IT,
    const TopOpeBRepDS_Point&                                           DSP,
    const TopOpeBRepDS_DataStructure&                                   BDS) const;

  //! Search for an interference in list <IT> which 3D geometry
  //! equals 3D geometry of the current intersection of <EI>.
  //! The search is performed by ScanInterfList.
  //! if found, set <G> to the geometry of the interference found.
  //! returns found.
  Standard_EXPORT bool GetGeometry(
    NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator& IT,
    const TopOpeBRep_FaceEdgeIntersector&                               EI,
    int&                                                                G,
    const TopOpeBRepDS_DataStructure&                                   DS) const;

  Standard_EXPORT int MakeGeometry(TopOpeBRep_FaceEdgeIntersector& EI,
                                   TopOpeBRepDS_DataStructure&     DS) const;

  //! Get the geometry of a DS point <DSP>.
  //! First, search it with ScanInterfList (previous method).
  //! if found, set <G> to the geometry of the interference found.
  //! else, add the point <DSP> in the <DS> and set <G> to the
  //! value of the new geometry such created.
  //!
  //! returns the value of ScanInterfList().
  Standard_EXPORT bool GetGeometry(
    const NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& L,
    const TopOpeBRepDS_Point&                                       DSP,
    int&                                                            G,
    TopOpeBRepDS_DataStructure&                                     DS) const;

  //! Add interference <I> to list <LI>.
  //! Add <I> to the interference list of <I> geometry (via <BDS>).
  Standard_EXPORT void StoreInterference(
    const occ::handle<TopOpeBRepDS_Interference>&             I,
    NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& LI,
    TopOpeBRepDS_DataStructure&                               BDS) const;
};


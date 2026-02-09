#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <MAT_Arc.hpp>
#include <NCollection_DataMap.hpp>
#include <MAT_BasicElt.hpp>
#include <MAT_Node.hpp>
#include <Standard_Transient.hpp>
class MAT_ListOfBisector;
class MAT_Arc;
class MAT_BasicElt;
class MAT_Node;

class MAT_Graph : public Standard_Transient
{

public:
  Standard_EXPORT MAT_Graph();

  Standard_EXPORT void Perform(const bool                             SemiInfinite,
                               const occ::handle<MAT_ListOfBisector>& TheRoots,
                               const int                              NbBasicElts,
                               const int                              NbArcs);

  Standard_EXPORT occ::handle<MAT_Arc> Arc(const int Index) const;

  Standard_EXPORT occ::handle<MAT_BasicElt> BasicElt(const int Index) const;

  Standard_EXPORT occ::handle<MAT_Node> Node(const int Index) const;

  Standard_EXPORT int NumberOfArcs() const;

  Standard_EXPORT int NumberOfNodes() const;

  Standard_EXPORT int NumberOfBasicElts() const;

  Standard_EXPORT int NumberOfInfiniteNodes() const;

  Standard_EXPORT void FusionOfBasicElts(const int IndexElt1,
                                         const int IndexElt2,
                                         bool&     MergeArc1,
                                         int&      GeomIndexArc1,
                                         int&      GeomIndexArc2,
                                         bool&     MergeArc2,
                                         int&      GeomIndexArc3,
                                         int&      GeomIndexArc4);

  Standard_EXPORT void CompactArcs();

  Standard_EXPORT void CompactNodes();

  Standard_EXPORT void ChangeBasicElts(
    const NCollection_DataMap<int, occ::handle<MAT_BasicElt>>& NewMap);

  Standard_EXPORT occ::handle<MAT_BasicElt> ChangeBasicElt(const int Index);

  DEFINE_STANDARD_RTTIEXT(MAT_Graph, Standard_Transient)

private:
  Standard_EXPORT void FusionOfArcs(const occ::handle<MAT_Arc>& Arc1,
                                    const occ::handle<MAT_Arc>& Arc2);

  Standard_EXPORT void UpDateNodes(int& Index);

  NCollection_DataMap<int, occ::handle<MAT_Arc>>      theArcs;
  NCollection_DataMap<int, occ::handle<MAT_BasicElt>> theBasicElts;
  NCollection_DataMap<int, occ::handle<MAT_Node>>     theNodes;
  int                                                 numberOfArcs;
  int                                                 numberOfNodes;
  int                                                 numberOfBasicElts;
  int                                                 numberOfInfiniteNodes;
};

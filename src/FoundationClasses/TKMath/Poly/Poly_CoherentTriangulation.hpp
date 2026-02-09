#pragma once

#include <Poly_Triangulation.hpp>
#include <Poly_CoherentNode.hpp>
#include <Poly_CoherentTriangle.hpp>
#include <Poly_CoherentLink.hpp>
#include <NCollection_Vector.hpp>

class Poly_CoherentTriangulation;
template <class A>
class NCollection_List;

#include <Standard_Type.hpp>

class Poly_CoherentTriangulation : public Standard_Transient
{
public:
  class IteratorOfTriangle : public NCollection_Vector<Poly_CoherentTriangle>::Iterator
  {
  public:
    Standard_EXPORT IteratorOfTriangle(const occ::handle<Poly_CoherentTriangulation>& theTri);

    Standard_EXPORT void Next() noexcept override;
  };

  class IteratorOfNode : public NCollection_Vector<Poly_CoherentNode>::Iterator
  {
  public:
    Standard_EXPORT IteratorOfNode(const occ::handle<Poly_CoherentTriangulation>& theTri);

    Standard_EXPORT void Next() noexcept override;
  };

  class IteratorOfLink : public NCollection_Vector<Poly_CoherentLink>::Iterator
  {
  public:
    Standard_EXPORT IteratorOfLink(const occ::handle<Poly_CoherentTriangulation>& theTri);

    Standard_EXPORT void Next() noexcept override;
  };

  struct TwoIntegers
  {
    int myValue[2];

    TwoIntegers() = default;

    TwoIntegers(int i0, int i1)
    {
      myValue[0] = i0;
      myValue[1] = i1;
    }
  };

public:
  Standard_EXPORT Poly_CoherentTriangulation(
    const occ::handle<NCollection_BaseAllocator>& theAlloc = nullptr);

  Standard_EXPORT Poly_CoherentTriangulation(
    const occ::handle<Poly_Triangulation>&        theTriangulation,
    const occ::handle<NCollection_BaseAllocator>& theAlloc = nullptr);

  Standard_EXPORT ~Poly_CoherentTriangulation() override;

  Standard_EXPORT occ::handle<Poly_Triangulation> GetTriangulation() const;

  Standard_EXPORT bool RemoveDegenerated(const double                   theTol,
                                         NCollection_List<TwoIntegers>* pLstRemovedNode = nullptr);

  Standard_EXPORT bool GetFreeNodes(NCollection_List<int>& lstNodes) const;

  inline int MaxNode() const { return myNodes.Length() - 1; }

  inline int MaxTriangle() const { return myTriangles.Length() - 1; }

  inline void SetDeflection(const double theDefl) { myDeflection = theDefl; }

  inline double Deflection() const { return myDeflection; }

  Standard_EXPORT int SetNode(const gp_XYZ& thePnt, const int iN = -1);

  inline const Poly_CoherentNode& Node(const int i) const { return myNodes.Value(i); }

  inline Poly_CoherentNode& ChangeNode(const int i) { return myNodes.ChangeValue(i); }

  Standard_EXPORT int NNodes() const;

  inline const Poly_CoherentTriangle& Triangle(const int i) const { return myTriangles.Value(i); }

  Standard_EXPORT int NTriangles() const;

  Standard_EXPORT int NLinks() const;

  Standard_EXPORT bool RemoveTriangle(Poly_CoherentTriangle& theTr);

  Standard_EXPORT void RemoveLink(Poly_CoherentLink& theLink);

  Standard_EXPORT Poly_CoherentTriangle* AddTriangle(const int iNode0,
                                                     const int iNode1,
                                                     const int iNode2);

  Standard_EXPORT bool ReplaceNodes(Poly_CoherentTriangle& theTriangle,
                                    const int              iNode0,
                                    const int              iNode1,
                                    const int              iNode2);

  Standard_EXPORT Poly_CoherentLink* AddLink(const Poly_CoherentTriangle& theTri,
                                             const int                    theConn);

  Standard_EXPORT bool FindTriangle(const Poly_CoherentLink&     theLink,
                                    const Poly_CoherentTriangle* pTri[2]) const;

  Standard_EXPORT int ComputeLinks();

  Standard_EXPORT void ClearLinks();

  inline const occ::handle<NCollection_BaseAllocator>& Allocator() const { return myAlloc; }

  Standard_EXPORT occ::handle<Poly_CoherentTriangulation> Clone(
    const occ::handle<NCollection_BaseAllocator>& theAlloc) const;

  Standard_EXPORT void Dump(Standard_OStream&) const;

protected:
  NCollection_Vector<Poly_CoherentTriangle> myTriangles;
  NCollection_Vector<Poly_CoherentNode>     myNodes;
  NCollection_Vector<Poly_CoherentLink>     myLinks;
  occ::handle<NCollection_BaseAllocator>    myAlloc;
  double                                    myDeflection;

public:
  DEFINE_STANDARD_RTTIEXT(Poly_CoherentTriangulation, Standard_Transient)

  friend class IteratorOfTriangle;
  friend class IteratorOfNode;
  friend class IteratorOfLink;
};

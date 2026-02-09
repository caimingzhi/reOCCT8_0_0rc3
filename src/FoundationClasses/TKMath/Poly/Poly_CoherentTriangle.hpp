#pragma once

#include <Standard_TypeDef.hpp>

class Poly_CoherentLink;

class Poly_CoherentTriangle
{
public:
  Standard_EXPORT Poly_CoherentTriangle();

  Standard_EXPORT Poly_CoherentTriangle(const int iNode0, const int iNode1, const int iNode2);

  inline int Node(const int ind) const { return myNodes[ind]; }

  inline bool IsEmpty() const noexcept
  {
    return myNodes[0] < 0 || myNodes[1] < 0 || myNodes[2] < 0;
  }

  Standard_EXPORT bool SetConnection(const int iConn, Poly_CoherentTriangle& theTr);

  Standard_EXPORT bool SetConnection(Poly_CoherentTriangle& theTri);

  Standard_EXPORT void RemoveConnection(const int iConn);

  Standard_EXPORT bool RemoveConnection(Poly_CoherentTriangle& theTri);

  inline int NConnections() const { return myNConnections; }

  inline int GetConnectedNode(const int iConn) const { return myNodesOnConnected[iConn]; }

  inline const Poly_CoherentTriangle* GetConnectedTri(const int iConn) const
  {
    return mypConnected[iConn];
  }

  inline const Poly_CoherentLink* GetLink(const int iLink) const { return mypLink[iLink]; }

  Standard_EXPORT int FindConnection(const Poly_CoherentTriangle&) const;

private:
  int                          myNConnections;
  int                          myNodes[3]{};
  int                          myNodesOnConnected[3]{};
  const Poly_CoherentTriangle* mypConnected[3]{};
  const Poly_CoherentLink*     mypLink[3]{};

  friend class Poly_CoherentTriangulation;
};

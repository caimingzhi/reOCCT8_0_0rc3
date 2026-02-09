#include <Poly_CoherentLink.hpp>
#include <Poly_CoherentTriangle.hpp>
#include <Standard_ProgramError.hpp>

Poly_CoherentLink::Poly_CoherentLink()
    : myAttribute(nullptr)
{
  myNode[0]         = -1;
  myNode[1]         = -1;
  myOppositeNode[0] = -1;
  myOppositeNode[1] = -1;
}

Poly_CoherentLink::Poly_CoherentLink(const Poly_CoherentTriangle& theTri, int iSide)
    : myAttribute(nullptr)
{
  static const int ind[] = {1, 2, 0, 1};
  Standard_ProgramError_Raise_if(iSide < 0 || iSide > 2,
                                 "Poly_CoherentLink::Poly_CoherentLink: "
                                 "Wrong iSide parameter");
  const int aNodeInd[2] = {theTri.Node(ind[iSide + 0]), theTri.Node(ind[iSide + 1])};
  if (aNodeInd[0] < aNodeInd[1])
  {
    myNode[0]         = aNodeInd[0];
    myNode[1]         = aNodeInd[1];
    myOppositeNode[0] = theTri.Node(iSide);
    myOppositeNode[1] = theTri.GetConnectedNode(iSide);
  }
  else
  {
    myNode[0]         = aNodeInd[1];
    myNode[1]         = aNodeInd[0];
    myOppositeNode[0] = theTri.GetConnectedNode(iSide);
    myOppositeNode[1] = theTri.Node(iSide);
  }
}

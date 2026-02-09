#include <Poly_MakeLoops.hpp>
#include <NCollection_IncAllocator.hpp>
#include <NCollection_DataMap.hpp>
#include <gp_Dir.hpp>
#include <gp_Dir2d.hpp>

#ifdef OCCT_DEBUG
static int doDebug = 0;
#endif

Poly_MakeLoops::Poly_MakeLoops(const Helper*                                 theHelper,
                               const occ::handle<NCollection_BaseAllocator>& theAlloc)
    : myHelper(theHelper),
      myAlloc(theAlloc),
      myMapLink(4000, myAlloc),
      myLoops(myAlloc),
      myStartIndices(4000)
{
}

void Poly_MakeLoops::Reset(const Helper*                                 theHelper,
                           const occ::handle<NCollection_BaseAllocator>& theAlloc)
{
  myHelper = theHelper;
  myMapLink.Clear();
  myLoops.Clear(theAlloc);
  myStartIndices.Clear();
  myAlloc = theAlloc;
}

void Poly_MakeLoops::AddLink(const Link& theLink)
{
  if (theLink.node1 == theLink.node2)
    return;
  int   aInd  = myMapLink.Add(theLink);
  Link& aLink = const_cast<Link&>(myMapLink(aInd));
  aLink.flags |= theLink.flags;
#ifdef OCCT_DEBUG
  myHelper->OnAddLink(aInd, aLink);
#endif
}

void Poly_MakeLoops::ReplaceLink(const Link& theLink, const Link& theNewLink)
{
  if (theNewLink.node1 == theNewLink.node2)
    return;
  int aInd = myMapLink.Add(theLink);
  if (aInd > 0)
  {
    Link aLink;

    myMapLink.Substitute(aInd, aLink);
    aLink = theNewLink;

    myMapLink.Substitute(aInd, aLink);
#ifdef OCCT_DEBUG
    myHelper->OnAddLink(aInd, aLink);
#endif
  }
}

Poly_MakeLoops::LinkFlag Poly_MakeLoops::SetLinkOrientation(const Link&    theLink,
                                                            const LinkFlag theOrient)
{
  int      aInd = myMapLink.FindIndex(theLink);
  LinkFlag aOri = LF_None;
  if (aInd > 0)
  {
    Link& aLink = const_cast<Link&>(myMapLink(aInd));
    aOri        = (LinkFlag)(aLink.flags & LF_Both);
    aLink.flags = theOrient;
#ifdef OCCT_DEBUG
    myHelper->OnAddLink(aInd, aLink);
#endif
  }
  return aOri;
}

Poly_MakeLoops::Link Poly_MakeLoops::FindLink(const Link& theLink) const
{
  int                  aInd = myMapLink.FindIndex(theLink);
  Poly_MakeLoops::Link aLink;
  if (aInd > 0)
    aLink = myMapLink(aInd);
  return aLink;
}

int Poly_MakeLoops::Perform()
{

  myStartIndices.Clear();
  int i;
  for (i = 1; i <= myMapLink.Extent(); i++)
  {
    const Link& aLink = myMapLink(i);
    if (aLink.flags & LF_Fwd)
      myStartIndices.Add(i);
    if (aLink.flags & LF_Rev)
      myStartIndices.Add(-i);
  }

#ifdef OCCT_DEBUG
  if (doDebug)
    showBoundaryBreaks();
  int aNbLoopsOnPass2 = 0;
#endif

  int aResult = 0;

  occ::handle<NCollection_IncAllocator> aTempAlloc  = new NCollection_IncAllocator(4000);
  occ::handle<NCollection_IncAllocator> aTempAlloc1 = new NCollection_IncAllocator(4000);

  for (int aPassNum = 0; aPassNum < 2; aPassNum++)
  {
    myHangIndices.Clear();

    while (!myStartIndices.IsEmpty())
    {
      int aIndexS = myStartIndices.Top();

      aTempAlloc->Reset(false);
      NCollection_IndexedMap<int> aContour(100, aTempAlloc);
      int aStartNumber = findContour(aIndexS, aContour, aTempAlloc, aTempAlloc1);
#ifdef OCCT_DEBUG
      if (aStartNumber > 1)
        if (doDebug)
        {
          std::cout << "--- found contour with hanging links:" << std::endl;
          for (i = 1; i <= aContour.Extent(); i++)
            std::cout << " " << aContour(i);
          std::cout << std::endl;
        }
#endif
      if (aStartNumber == 0)
      {
        aResult |= RC_Failure;
        return aResult;
      }
      if (aStartNumber <= aContour.Extent())
      {

#ifdef OCCT_DEBUG
        if (aPassNum == 1)
          aNbLoopsOnPass2++;
#endif
        acceptContour(aContour, aStartNumber);
      }
      if (aStartNumber > 1)
      {

        int aNode;
        if (aStartNumber <= aContour.Extent())

          aNode = getFirstNode(aIndexS);
        else
        {

          aIndexS = aContour(aStartNumber - 1);
          aNode   = getLastNode(aIndexS);
        }
        markHangChain(aNode, aIndexS);
      }
    }

    if (aPassNum == 0)
    {

      TColStd_MapIteratorOfPackedMapOfInteger it(myHangIndices);
      for (; it.More(); it.Next())
        myStartIndices.Add(it.Key());
    }
  }
#ifdef OCCT_DEBUG
  if (doDebug && aNbLoopsOnPass2)
    std::cout << "MakeLoops: " << aNbLoopsOnPass2 << " contours accepted on the second pass"
              << std::endl;
#endif

  if (!myLoops.IsEmpty())
    aResult |= RC_LoopsDone;
  if (!myHangIndices.IsEmpty())
    aResult |= RC_HangingLinks;
  return aResult;
}

int Poly_MakeLoops::findContour(int                                           theIndexS,
                                NCollection_IndexedMap<int>&                  theContour,
                                const occ::handle<NCollection_BaseAllocator>& theTempAlloc,
                                const occ::handle<NCollection_IncAllocator>&  theTempAlloc1) const
{
  theContour.Clear();
  int                           aStartIndex = 0;
  int                           aIndexS     = theIndexS;
  NCollection_DataMap<int, int> aNodeLink(100, theTempAlloc);
  int                           aLastNode = getLastNode(aIndexS);

  for (;;)
  {
    theContour.Add(aIndexS);
    aNodeLink.Bind(getFirstNode(aIndexS), aIndexS);

    int aIndex = std::abs(aIndexS);

    theTempAlloc1->Reset(false);
    NCollection_List<int>                aLstIndS(theTempAlloc1);
    const ListOfLink&                    aLinks = myHelper->GetAdjacentLinks(aLastNode);
    Poly_MakeLoops::ListOfLink::Iterator itLinks(aLinks);
    for (; itLinks.More(); itLinks.Next())
    {
      int aInd = myMapLink.FindIndex(itLinks.Value());
      if (aInd == 0 || aInd == aIndex)
        continue;

      int aIndS  = aInd;
      int aNode1 = getFirstNode(aInd);
      if (aNode1 != aLastNode)
        aIndS = -aIndS;

      if (canLinkBeTaken(aIndS))
        aLstIndS.Append(aIndS);
    }

    if (aLstIndS.IsEmpty())
    {

      aStartIndex = theContour.Extent() + 1;
      break;
    }

    int aIndexSNext = 0;
    if (aLstIndS.First() == aLstIndS.Last())

      aIndexSNext = aLstIndS.First();
    else

      aIndexSNext = chooseLeftWay(aLastNode, aIndexS, aLstIndS);

    aIndexS = aIndexSNext;

    if (aIndexS == 0)
    {

      aStartIndex = theContour.Extent() + 1;
      break;
    }
    if (theContour.Contains(aIndexS))
    {

      aStartIndex = theContour.FindIndex(aIndexS);
      break;
    }
    if (theContour.Contains(-aIndexS))
    {

      aStartIndex = theContour.FindIndex(-aIndexS) + 1;
      break;
    }

    aLastNode = getLastNode(aIndexS);

    if (aNodeLink.IsBound(aLastNode))
    {

      theContour.Add(aIndexS);
      aStartIndex = theContour.FindIndex(aNodeLink.Find(aLastNode));
      break;
    }
  }

  return aStartIndex;
}

void Poly_MakeLoops::acceptContour(const NCollection_IndexedMap<int>& theContour,
                                   int                                theStartNumber)
{

  Loop anEmptyLoop(myAlloc);
  myLoops.Append(anEmptyLoop);
  Loop& aLoop = myLoops.ChangeValue(myLoops.Length());

  int i;
  for (i = theStartNumber; i <= theContour.Extent(); i++)
  {
    int         aIndexS       = theContour(i);
    int         aIndex        = std::abs(aIndexS);
    const Link& aLink         = myMapLink(aIndex);
    Link        aOrientedLink = aLink;
    if (aIndexS < 0)
      aOrientedLink.Reverse();
    aLoop.Append(aOrientedLink);

    myStartIndices.Remove(aIndexS);
  }
}

int Poly_MakeLoops::getFirstNode(int theIndexS) const
{
  int         aIndex = std::abs(theIndexS);
  const Link& aLink  = myMapLink(aIndex);
  if (theIndexS > 0)
    return aLink.node1;
  return aLink.node2;
}

int Poly_MakeLoops::getLastNode(int theIndexS) const
{
  int         aIndex = std::abs(theIndexS);
  const Link& aLink  = myMapLink(aIndex);
  if (theIndexS > 0)
    return aLink.node2;
  return aLink.node1;
}

void Poly_MakeLoops::markHangChain(int theNode, int theIndexS)
{
  int  aNode1  = theNode;
  int  aIndexS = theIndexS;
  int  aIndex  = std::abs(aIndexS);
  bool isOut   = (aNode1 == getFirstNode(aIndexS));
  for (;;)
  {

    const ListOfLink&                    aLinks = myHelper->GetAdjacentLinks(aNode1);
    int                                  nEdges = 0;
    Poly_MakeLoops::ListOfLink::Iterator itLinks(aLinks);
    for (; itLinks.More() && nEdges == 0; itLinks.Next())
    {
      const Link& aL   = itLinks.Value();
      int         aInd = myMapLink.FindIndex(aL);
      if (aInd == 0 || aInd == aIndex)
        continue;
      if ((isOut && aNode1 == aL.node1) || (!isOut && aNode1 == aL.node2))
        aInd = -aInd;
      if (canLinkBeTaken(aInd))
        nEdges++;
    }
    if (nEdges > 0)

      break;

    myStartIndices.Remove(aIndexS);
    myHangIndices.Add(aIndexS);

    if (isOut)
      aNode1 = getLastNode(aIndexS);
    else
      aNode1 = getFirstNode(aIndexS);
    const ListOfLink& aNextLinks  = myHelper->GetAdjacentLinks(aNode1);
    int               aNextIndexS = 0;
    for (itLinks.Init(aNextLinks); itLinks.More(); itLinks.Next())
    {
      const Link& aL   = itLinks.Value();
      int         aInd = myMapLink.FindIndex(aL);
      if (aInd == 0 || aInd == aIndex)
        continue;
      if ((isOut && aNode1 == aL.node2) || (!isOut && aNode1 == aL.node1))
        aInd = -aInd;
      if (canLinkBeTaken(aInd))
      {
        if (aNextIndexS == 0)
          aNextIndexS = aInd;
        else
        {

          aNextIndexS = 0;
          break;
        }
      }
    }
    if (aNextIndexS == 0)
      break;
    aIndexS = aNextIndexS;
    aIndex  = std::abs(aIndexS);
  }
}

bool Poly_MakeLoops::canLinkBeTaken(int theIndexS) const
{
  return myStartIndices.Contains(theIndexS);
}

#ifdef OCCT_DEBUG
void Poly_MakeLoops::showBoundaryBreaks() const
{

  TColStd_PackedMapOfInteger aNodesMap;
  int                        i;
  for (i = 1; i <= myMapLink.Extent(); i++)
  {
    const Link& aLink  = myMapLink(i);
    int         aFlags = aLink.flags & LF_Both;
    if (aFlags && aFlags != LF_Both)
    {

      aNodesMap.Add(aLink.node1);
      aNodesMap.Add(aLink.node2);
    }
  }

  bool                                    isFirst = true;
  TColStd_MapIteratorOfPackedMapOfInteger it(aNodesMap);
  for (; it.More(); it.Next())
  {
    int                                  aNode  = it.Key();
    int                                  nb     = 0;
    const ListOfLink&                    aLinks = myHelper->GetAdjacentLinks(aNode);
    Poly_MakeLoops::ListOfLink::Iterator itLinks(aLinks);
    for (; itLinks.More(); itLinks.Next())
    {
      const Poly_MakeLoops::Link& aLink = itLinks.Value();
      if (myMapLink.FindIndex(aLink) == 0)
        continue;
      int aFlags = aLink.flags & LF_Both;
      if (aFlags && aFlags != LF_Both)
      {
        if (aNode == aLink.node1)
        {
          if (aFlags & LF_Fwd)
            nb++;
          else
            nb--;
        }
        else if (aNode == aLink.node2)
        {
          if (aFlags & LF_Fwd)
            nb--;
          else
            nb++;
        }
        else

          nb += 100;
      }
    }
    if (nb != 0)
    {

      if (isFirst)
      {
        isFirst = false;
        std::cout << "boundary breaks are found in the following nodes:" << std::endl;
      }
      std::cout << aNode << " ";
    }
  }
  if (!isFirst)
    std::cout << std::endl;
}
#endif

void Poly_MakeLoops::GetHangingLinks(ListOfLink& theLinks) const
{
  TColStd_MapIteratorOfPackedMapOfInteger it(myHangIndices);
  for (; it.More(); it.Next())
  {
    int  aIndexS = it.Key();
    Link aLink   = myMapLink(std::abs(aIndexS));
    if (aIndexS < 0)
      aLink.Reverse();
    theLinks.Append(aLink);
  }
}

Poly_MakeLoops3D::Poly_MakeLoops3D(const Helper*                                 theHelper,
                                   const occ::handle<NCollection_BaseAllocator>& theAlloc)
    : Poly_MakeLoops(theHelper, theAlloc)
{
}

int Poly_MakeLoops3D::chooseLeftWay(const int                    theNode,
                                    const int                    theSegIndex,
                                    const NCollection_List<int>& theLstIndS) const
{
  double        aAngleMin = M_PI * 2;
  gp_Dir        aNormal;
  const Helper* aHelper = getHelper();
  if (!aHelper->GetNormal(theNode, aNormal))
    return theLstIndS.First();

  Link   aLink = getLink(theSegIndex);
  gp_Dir aTgtRef;
  if (!aHelper->GetLastTangent(aLink, aTgtRef))
    return theLstIndS.First();

  gp_XYZ aTgtRefXYZ = aNormal.XYZ().CrossCrossed(aTgtRef.XYZ(), aNormal.XYZ());
  if (aTgtRefXYZ.SquareModulus() < 1e-14)

    return theLstIndS.First();
  aTgtRef = aTgtRefXYZ;

  int                             aResIndex = 0;
  NCollection_List<int>::Iterator aItI(theLstIndS);
  for (; aItI.More(); aItI.Next())
  {
    int aIndS = aItI.Value();

    aLink = getLink(aIndS);
    gp_Dir aTgt;
    if (!aHelper->GetFirstTangent(aLink, aTgt))
      continue;

    gp_XYZ aTgtXYZ = aNormal.XYZ().CrossCrossed(aTgt.XYZ(), aNormal.XYZ());
    if (aTgtXYZ.SquareModulus() < 1e-14)

      continue;
    aTgt = aTgtXYZ;

    double aAngle = aTgt.AngleWithRef(aTgtRef, aNormal);
    if (aAngle < 1e-4 - M_PI)
      aAngle = M_PI;
    if (aAngle < aAngleMin)
    {
      aAngleMin = aAngle;
      aResIndex = aIndS;
    }
  }
  return aResIndex == 0 ? theLstIndS.First() : aResIndex;
}

Poly_MakeLoops2D::Poly_MakeLoops2D(const bool                                    theLeftWay,
                                   const Helper*                                 theHelper,
                                   const occ::handle<NCollection_BaseAllocator>& theAlloc)
    : Poly_MakeLoops(theHelper, theAlloc),
      myRightWay(!theLeftWay)
{
}

int Poly_MakeLoops2D::chooseLeftWay(const int,
                                    const int                    theSegIndex,
                                    const NCollection_List<int>& theLstIndS) const
{
  double        aAngleMin = M_PI * 2;
  const Helper* aHelper   = getHelper();
  Link          aLink     = getLink(theSegIndex);
  gp_Dir2d      aTgtRef;
  if (!aHelper->GetLastTangent(aLink, aTgtRef))

    return theLstIndS.First();

  int                             aResIndex = 0;
  NCollection_List<int>::Iterator aItI(theLstIndS);
  for (; aItI.More(); aItI.Next())
  {
    int aIndS = aItI.Value();

    aLink = getLink(aIndS);
    gp_Dir2d aTgt;
    if (!aHelper->GetFirstTangent(aLink, aTgt))

      continue;

    double aAngle = aTgt.Angle(aTgtRef);
    if (myRightWay)
      aAngle = -aAngle;
    if (aAngle < 1e-4 - M_PI)
      aAngle = M_PI;
    if (aAngle < aAngleMin)
    {
      aAngleMin = aAngle;
      aResIndex = aIndS;
    }
  }
  return aResIndex == 0 ? theLstIndS.First() : aResIndex;
}

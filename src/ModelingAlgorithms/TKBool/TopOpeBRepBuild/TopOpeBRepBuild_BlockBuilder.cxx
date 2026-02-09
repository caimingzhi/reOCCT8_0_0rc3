#include <TopOpeBRepBuild_BlockBuilder.hpp>
#include <TopOpeBRepBuild_BlockIterator.hpp>
#include <TopOpeBRepBuild_ShapeSet.hpp>

TopOpeBRepBuild_BlockBuilder::TopOpeBRepBuild_BlockBuilder()
    : myIsDone(false)
{
}

TopOpeBRepBuild_BlockBuilder::TopOpeBRepBuild_BlockBuilder(TopOpeBRepBuild_ShapeSet& SS)
    : myIsDone(false)
{
  MakeBlock(SS);
}

void TopOpeBRepBuild_BlockBuilder::MakeBlock(TopOpeBRepBuild_ShapeSet& SS)
{

  myOrientedShapeMap.Clear();
  myOrientedShapeMapIsValid.Clear();
  myBlocks.Clear();
  myBlocksIsRegular.Clear();

  bool IsRegular;
  int  CurNei;
  int  Mextent;
  int  Eindex;

  for (SS.InitStartElements(); SS.MoreStartElements(); SS.NextStartElement())
  {

    const TopoDS_Shape& E = SS.StartElement();
    Mextent               = myOrientedShapeMap.Extent();
    Eindex                = AddElement(E);

    bool EnewinM = (Eindex > Mextent);
    if (EnewinM)
    {

      myBlocks.Append(Eindex);
      IsRegular = true;
      CurNei    = 0;

      Mextent               = myOrientedShapeMap.Extent();
      bool searchneighbours = (Eindex <= Mextent);
      while (searchneighbours)
      {

        const TopoDS_Shape& E1 = myOrientedShapeMap(Eindex);
        CurNei                 = SS.MaxNumberSubShape(E1);
        bool condregu          = true;
        if (CurNei > 2)
          condregu = false;
        IsRegular = IsRegular && condregu;

        SS.InitNeighbours(E1);

        for (; SS.MoreNeighbours(); SS.NextNeighbour())
        {
          const TopoDS_Shape& N = SS.Neighbour();
          AddElement(N);
        }

        Eindex++;
        Mextent          = myOrientedShapeMap.Extent();
        searchneighbours = (Eindex <= Mextent);
      }
      int iiregu = IsRegular ? 1 : 0;
      myBlocksIsRegular.Append(iiregu);
    }
  }

  Mextent = myOrientedShapeMap.Extent();
  myBlocks.Append(Mextent + 1);
  myIsDone = true;
}

void TopOpeBRepBuild_BlockBuilder::InitBlock()
{
  myBlockIndex = 1;
}

bool TopOpeBRepBuild_BlockBuilder::MoreBlock() const
{

  int  l = myBlocks.Length();
  bool b = (myBlockIndex < l);
  return b;
}

void TopOpeBRepBuild_BlockBuilder::NextBlock()
{
  myBlockIndex++;
}

TopOpeBRepBuild_BlockIterator TopOpeBRepBuild_BlockBuilder::BlockIterator() const
{
  int lower = myBlocks(myBlockIndex);
  int upper = myBlocks(myBlockIndex + 1) - 1;
  return TopOpeBRepBuild_BlockIterator(lower, upper);
}

const TopoDS_Shape& TopOpeBRepBuild_BlockBuilder::Element(
  const TopOpeBRepBuild_BlockIterator& BI) const
{
  bool isbound = BI.More();
  if (!isbound)
    throw Standard_Failure("OutOfRange");

  int                 index = BI.Value();
  const TopoDS_Shape& E     = myOrientedShapeMap(index);
  return E;
}

const TopoDS_Shape& TopOpeBRepBuild_BlockBuilder::Element(const int index) const
{
  bool isbound = myOrientedShapeMapIsValid.IsBound(index);
  if (!isbound)
    throw Standard_Failure("OutOfRange");

  const TopoDS_Shape& E = myOrientedShapeMap(index);
  return E;
}

int TopOpeBRepBuild_BlockBuilder::Element(const TopoDS_Shape& E) const
{
  bool isbound = myOrientedShapeMap.Contains(E);
  if (!isbound)
    throw Standard_Failure("OutOfRange");

  int I = myOrientedShapeMap.FindIndex(E);
  return I;
}

bool TopOpeBRepBuild_BlockBuilder::ElementIsValid(const TopOpeBRepBuild_BlockIterator& BI) const
{
  bool isbound = BI.More();
  if (!isbound)
    return false;

  int  Sindex  = BI.Value();
  int  isb     = myOrientedShapeMapIsValid.Find(Sindex);
  bool isvalid = isb == 1;

  return isvalid;
}

bool TopOpeBRepBuild_BlockBuilder::ElementIsValid(const int Sindex) const
{
  bool isbound = myOrientedShapeMapIsValid.IsBound(Sindex);
  if (!isbound)
    return false;

  int  isb     = myOrientedShapeMapIsValid.Find(Sindex);
  bool isvalid = isb == 1;

  return isvalid;
}

int TopOpeBRepBuild_BlockBuilder::AddElement(const TopoDS_Shape& S)
{
  int Sindex = myOrientedShapeMap.Add(S);
  myOrientedShapeMapIsValid.Bind(Sindex, 1);

  return Sindex;
}

void TopOpeBRepBuild_BlockBuilder::SetValid(const TopOpeBRepBuild_BlockIterator& BI,
                                            const bool                           isvalid)
{
  bool isbound = BI.More();
  if (!isbound)
    return;

  int Sindex = BI.Value();
  int i      = (isvalid) ? 1 : 0;
  myOrientedShapeMapIsValid.Bind(Sindex, i);
}

void TopOpeBRepBuild_BlockBuilder::SetValid(const int Sindex, const bool isvalid)
{
  bool isbound = myOrientedShapeMapIsValid.IsBound(Sindex);
  if (!isbound)
    return;

  int i = (isvalid) ? 1 : 0;
  myOrientedShapeMapIsValid.Bind(Sindex, i);
}

bool TopOpeBRepBuild_BlockBuilder::CurrentBlockIsRegular()
{
  bool b = false;
  int  i = myBlocksIsRegular.Value(myBlockIndex);
  if (i == 1)
    b = true;
  return b;
}

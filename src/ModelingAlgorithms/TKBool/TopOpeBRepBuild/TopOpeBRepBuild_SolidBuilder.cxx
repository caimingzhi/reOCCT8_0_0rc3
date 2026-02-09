#include <TopoDS_Shape.hpp>
#include <TopOpeBRepBuild_ShellFaceClassifier.hpp>
#include <TopOpeBRepBuild_ShellFaceSet.hpp>
#include <TopOpeBRepBuild_SolidBuilder.hpp>

TopOpeBRepBuild_SolidBuilder::TopOpeBRepBuild_SolidBuilder() = default;

TopOpeBRepBuild_SolidBuilder::TopOpeBRepBuild_SolidBuilder(TopOpeBRepBuild_ShellFaceSet& SFS,
                                                           const bool                    ForceClass)
{
  InitSolidBuilder(SFS, ForceClass);
}

void TopOpeBRepBuild_SolidBuilder::InitSolidBuilder(TopOpeBRepBuild_ShellFaceSet& SFS,
                                                    const bool                    ForceClass)
{
  MakeLoops(SFS);
  TopOpeBRepBuild_BlockBuilder&       BB = myBlockBuilder;
  TopOpeBRepBuild_LoopSet&            LS = myLoopSet;
  TopOpeBRepBuild_ShellFaceClassifier SFC(BB);
  mySolidAreaBuilder.InitSolidAreaBuilder(LS, SFC, ForceClass);
}

int TopOpeBRepBuild_SolidBuilder::InitSolid()
{
  int n = mySolidAreaBuilder.InitArea();
  return n;
}

bool TopOpeBRepBuild_SolidBuilder::MoreSolid() const
{
  bool b = mySolidAreaBuilder.MoreArea();
  return b;
}

void TopOpeBRepBuild_SolidBuilder::NextSolid()
{
  mySolidAreaBuilder.NextArea();
}

int TopOpeBRepBuild_SolidBuilder::InitShell()
{
  int n = mySolidAreaBuilder.InitLoop();
  return n;
}

bool TopOpeBRepBuild_SolidBuilder::MoreShell() const
{
  bool b = mySolidAreaBuilder.MoreLoop();
  return b;
}

void TopOpeBRepBuild_SolidBuilder::NextShell()
{
  mySolidAreaBuilder.NextLoop();
}

bool TopOpeBRepBuild_SolidBuilder::IsOldShell() const
{
  const occ::handle<TopOpeBRepBuild_Loop>& L = mySolidAreaBuilder.Loop();
  bool                                     b = L->IsShape();
  return b;
}

const TopoDS_Shape& TopOpeBRepBuild_SolidBuilder::OldShell() const
{
  const occ::handle<TopOpeBRepBuild_Loop>& L = mySolidAreaBuilder.Loop();
  const TopoDS_Shape&                      B = L->Shape();
  return B;
}

int TopOpeBRepBuild_SolidBuilder::InitFace()
{
  const occ::handle<TopOpeBRepBuild_Loop>& L = mySolidAreaBuilder.Loop();
  if (L->IsShape())
    throw Standard_DomainError("TopOpeBRepBuild_SolidBuilder:InitFace");
  else
  {
    myBlockIterator = L->BlockIterator();
    myBlockIterator.Initialize();
  }
  int n = myBlockIterator.Extent();
  return n;
}

bool TopOpeBRepBuild_SolidBuilder::MoreFace() const
{
  bool b = myBlockIterator.More();
  return b;
}

void TopOpeBRepBuild_SolidBuilder::NextFace()
{
  myBlockIterator.Next();
}

const TopoDS_Shape& TopOpeBRepBuild_SolidBuilder::Face() const
{
#ifdef OCCT_DEBUG

#endif
  const TopoDS_Shape& F = myBlockBuilder.Element(myBlockIterator);
  return F;
}

void TopOpeBRepBuild_SolidBuilder::MakeLoops(TopOpeBRepBuild_ShapeSet& SS)
{
  TopOpeBRepBuild_BlockBuilder&                        BB = myBlockBuilder;
  NCollection_List<occ::handle<TopOpeBRepBuild_Loop>>& LL = myLoopSet.ChangeListOfLoop();

  BB.MakeBlock(SS);

  LL.Clear();

  for (SS.InitShapes(); SS.MoreShapes(); SS.NextShape())
  {
    const TopoDS_Shape&               S         = SS.Shape();
    occ::handle<TopOpeBRepBuild_Loop> ShapeLoop = new TopOpeBRepBuild_Loop(S);
    LL.Append(ShapeLoop);
  }

  for (BB.InitBlock(); BB.MoreBlock(); BB.NextBlock())
  {
    TopOpeBRepBuild_BlockIterator     BI        = BB.BlockIterator();
    occ::handle<TopOpeBRepBuild_Loop> BlockLoop = new TopOpeBRepBuild_Loop(BI);
    LL.Append(BlockLoop);
  }
}

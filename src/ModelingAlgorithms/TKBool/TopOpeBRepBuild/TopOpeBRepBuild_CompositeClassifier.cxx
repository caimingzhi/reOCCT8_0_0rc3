#include <BRepTools.hpp>
#include <TopoDS_Shape.hpp>
#include <TopOpeBRepBuild_BlockBuilder.hpp>
#include <TopOpeBRepBuild_CompositeClassifier.hpp>
#include <TopOpeBRepBuild_Loop.hpp>

#define MYBB ((TopOpeBRepBuild_BlockBuilder*)myBlockBuilder)

// reminder of a raise on FrozenShape during Add(myShell,aFace)
// with a shell that has already been placed in the internal solid of
// TopOpeBRepTool_SolidClassifier by LoadShell.

#ifdef OCCT_DEBUG
// static int dddjyl = 0;
// static int dddebi = 0;
// static int dddebi2 = 0;
// static void SAVSS(const TopoDS_Shape& S1,const TopoDS_Shape& S2)
//{
//   TCollection_AsciiString aname_1("cc_1"), aname_2("cc_2");
//   const char* name_1 = aname_1.ToCString(), name_2 = aname_2.ToCString();
//   std::cout<<"compositeclassifier : "<<name_1<<","<<name_2<<std::endl;
//   BRepTools::Write(S1,name_1); BRepTools::Write(S2,name_2);
// }
#endif

//=================================================================================================

TopOpeBRepBuild_CompositeClassifier::TopOpeBRepBuild_CompositeClassifier(
  const TopOpeBRepBuild_BlockBuilder& BB)
    : myBlockBuilder((void*)&BB)
{
}

//=================================================================================================

TopAbs_State TopOpeBRepBuild_CompositeClassifier::Compare(
  const occ::handle<TopOpeBRepBuild_Loop>& L1,
  const occ::handle<TopOpeBRepBuild_Loop>& L2)
{
  TopAbs_State state = TopAbs_UNKNOWN;

  bool isshape1 = L1->IsShape();
  bool isshape2 = L2->IsShape();

  if (isshape2 && isshape1)
  { // L1 is Shape , L2 is Shape
    const TopoDS_Shape& s1 = L1->Shape();
    const TopoDS_Shape& s2 = L2->Shape();
    state                  = CompareShapes(s1, s2);
  }
  else if (isshape2 && !isshape1)
  { // L1 is Block , L2 is Shape
    TopOpeBRepBuild_BlockIterator Bit1 = L1->BlockIterator();
    Bit1.Initialize();
    bool yena1 = Bit1.More();
    while (yena1)
    {
      const TopoDS_Shape& s1 = MYBB->Element(Bit1);
      const TopoDS_Shape& s2 = L2->Shape();
      state                  = CompareElementToShape(s1, s2);
      yena1                  = false;
      if (state == TopAbs_UNKNOWN)
      {
        if (Bit1.More())
          Bit1.Next();
        yena1 = Bit1.More();
      }
    }
  }
  else if (!isshape2 && isshape1)
  { // L1 is Shape , L2 is Block
    const TopoDS_Shape& s1 = L1->Shape();
    ResetShape(s1);
    TopOpeBRepBuild_BlockIterator Bit2 = L2->BlockIterator();
    for (Bit2.Initialize(); Bit2.More(); Bit2.Next())
    {
      const TopoDS_Shape& s2 = MYBB->Element(Bit2);
      if (!CompareElement(s2))
        break;
    }
    state = State();
  }
  else if (!isshape2 && !isshape1)
  { // L1 is Block , L2 is Block
    TopOpeBRepBuild_BlockIterator Bit1 = L1->BlockIterator();
    Bit1.Initialize();
    bool yena1 = Bit1.More();
    while (yena1)
    {
      const TopoDS_Shape& s1 = MYBB->Element(Bit1);
      ResetElement(s1);
      TopOpeBRepBuild_BlockIterator Bit2 = L2->BlockIterator();
      for (Bit2.Initialize(); Bit2.More(); Bit2.Next())
      {
        const TopoDS_Shape& s2 = MYBB->Element(Bit2);
        CompareElement(s2);
      }
      state = State();
      yena1 = false;
      if (state == TopAbs_UNKNOWN)
      {
        if (Bit1.More())
          Bit1.Next();
        yena1 = Bit1.More();
      }
    }
  }

  return state;
}

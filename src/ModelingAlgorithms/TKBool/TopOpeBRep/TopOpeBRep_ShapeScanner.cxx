#include <TopOpeBRep_ShapeScanner.hpp>
#include <TopOpeBRepTool_BoxSort.hpp>
#include <TopAbs_ShapeEnum.hpp>
#include <TopAbs_Orientation.hpp>
#include <TopAbs_State.hpp>
#include <TopoDS_Shape.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_Map.hpp>
#include <NCollection_List.hpp>
#include <NCollection_IndexedMap.hpp>
#include <NCollection_DataMap.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Vertex.hpp>
#include <TCollection_AsciiString.hpp>
#include <TopOpeBRepTool_ShapeExplorer.hpp>

//=================================================================================================

TopOpeBRep_ShapeScanner::TopOpeBRep_ShapeScanner() = default;

//=================================================================================================

void TopOpeBRep_ShapeScanner::Clear()
{
  myBoxSort.Clear();
}

//=================================================================================================

void TopOpeBRep_ShapeScanner::AddBoxesMakeCOB(const TopoDS_Shape&    S,
                                              const TopAbs_ShapeEnum TS,
                                              const TopAbs_ShapeEnum TA)
{
  myBoxSort.AddBoxesMakeCOB(S, TS, TA);
}

//=================================================================================================

void TopOpeBRep_ShapeScanner::Init(TopOpeBRepTool_ShapeExplorer& E)
{
  NCollection_List<int> anEmptyList;

  myListIterator.Initialize(anEmptyList);

  for (; E.More(); E.Next())
  {
    const TopoDS_Shape& cur = E.Current();
    //    TopAbs_ShapeEnum t = cur.ShapeType();
    Init(cur);
    bool b = More();
    if (b)
      break;
  }
}

//=================================================================================================

void TopOpeBRep_ShapeScanner::Init(const TopoDS_Shape& E)
{
  myListIterator = myBoxSort.Compare(E);
}

//=================================================================================================

bool TopOpeBRep_ShapeScanner::More() const
{
  bool b = myListIterator.More();
  return b;
}

//=================================================================================================

void TopOpeBRep_ShapeScanner::Next()
{
  myListIterator.Next();
}

//=================================================================================================

const TopoDS_Shape& TopOpeBRep_ShapeScanner::Current() const
{
  const TopoDS_Shape& E = myBoxSort.TouchedShape(myListIterator);
  return E;
}

//=================================================================================================

const TopOpeBRepTool_BoxSort& TopOpeBRep_ShapeScanner::BoxSort() const
{
  return myBoxSort;
}

//=================================================================================================

TopOpeBRepTool_BoxSort& TopOpeBRep_ShapeScanner::ChangeBoxSort()
{
  return myBoxSort;
}

//=================================================================================================

int TopOpeBRep_ShapeScanner::Index() const
{
  int n = 0;
  if (myListIterator.More())
    n = myListIterator.Value();
  return n;
}

//=================================================================================================

Standard_OStream& TopOpeBRep_ShapeScanner::DumpCurrent(Standard_OStream& OS) const
{
#ifdef OCCT_DEBUG
  if (More())
  {
    const TopoDS_Shape& S = Current();
    TopAbs_ShapeEnum    T = S.ShapeType();
    TopAbs_Orientation  O = S.Orientation();
    int                 I = Index();
    TopAbs::Print(T, std::cout);
    std::cout << "(" << I << ",";
    TopAbs::Print(O, std::cout);
    std::cout << ") ";
  }
#endif
  return OS;
}

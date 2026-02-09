#pragma once

#include <TopExp_Explorer.hpp>
#include <TopAbs.hpp>

class TopOpeBRepTool_ShapeExplorer : public TopExp_Explorer
{
public:
  TopOpeBRepTool_ShapeExplorer()
      : myIndex(0)
  {
  }

  TopOpeBRepTool_ShapeExplorer(const TopoDS_Shape&    S,
                               const TopAbs_ShapeEnum ToFind,
                               const TopAbs_ShapeEnum ToAvoid = TopAbs_SHAPE)
      : TopExp_Explorer(S, ToFind, ToAvoid),
        myIndex(More() ? 1 : 0)
  {
  }

  void Init(const TopoDS_Shape&    S,
            const TopAbs_ShapeEnum ToFind,
            const TopAbs_ShapeEnum ToAvoid = TopAbs_SHAPE)
  {
    TopExp_Explorer::Init(S, ToFind, ToAvoid);
    myIndex = (More() ? 1 : 0);
  }

  void Next()
  {
    if (More())
      myIndex++;
    TopExp_Explorer::Next();
  }

  int Index() const { return myIndex; }

  Standard_OStream& DumpCurrent(Standard_OStream& OS) const
  {
    if (More())
    {
      TopAbs::Print(Current().ShapeType(), OS);
      OS << "(" << Index() << ",";
      TopAbs::Print(Current().Orientation(), OS);
      OS << ") ";
    }
    return OS;
  }

private:
  int myIndex;
};

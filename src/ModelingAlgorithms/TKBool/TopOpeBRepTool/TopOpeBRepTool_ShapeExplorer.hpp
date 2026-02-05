#pragma once

#include <TopExp_Explorer.hpp>
#include <TopAbs.hpp>

//! Extends TopExp_Explorer by counting index of current item
//! (for tracing and debug)

class TopOpeBRepTool_ShapeExplorer : public TopExp_Explorer
{
public:
  //! Creates an empty explorer, becomes useful after Init.
  TopOpeBRepTool_ShapeExplorer()
      : myIndex(0)
  {
  }

  //! Creates an Explorer on the Shape <S>.
  //!
  //! <ToFind> is the type of shapes to search.
  //! TopAbs_VERTEX, TopAbs_EDGE, ...
  //!
  //! <ToAvoid> is the type of shape to skip in the
  //! exploration. If <ToAvoid> is equal or less
  //! complex than <ToFind> or if <ToAVoid> is SHAPE it
  //! has no effect on the exploration.
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

  //! Moves to the next Shape in the exploration.
  void Next()
  {
    if (More())
      myIndex++;
    TopExp_Explorer::Next();
  }

  //! Index of current sub-shape
  int Index() const { return myIndex; }

  //! Dump info on current shape to stream
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

#ifndef No_Exception
  #define No_Exception
#endif

#include <Intrv_Intervals.hpp>

Intrv_Intervals::Intrv_Intervals() = default;

Intrv_Intervals::Intrv_Intervals(const Intrv_Interval& Int)
{
  myInter.Append(Int);
}

void Intrv_Intervals::Intersect(const Intrv_Interval& Tool)
{
  Intrv_Intervals Inter(Tool);
  Intersect(Inter);
}

void Intrv_Intervals::Intersect(const Intrv_Intervals& Tool)
{
  Intrv_Intervals XUni(*this);
  XUni.XUnite(Tool);
  Unite(Tool);
  Subtract(XUni);
}

void Intrv_Intervals::Subtract(const Intrv_Interval& Tool)
{
  int index = 1;

  while (index <= myInter.Length())
  {

    switch (Tool.Position(myInter(index)))
    {

      case Intrv_Before:
        index = myInter.Length();
        break;

      case Intrv_JustBefore:
        myInter(index).CutAtStart(Tool.End(), Tool.TolEnd());
        index = myInter.Length();
        break;

      case Intrv_OverlappingAtStart:
      case Intrv_JustOverlappingAtStart:
        myInter(index).SetStart(Tool.End(), Tool.TolEnd());
        index = myInter.Length();
        break;

      case Intrv_JustEnclosingAtEnd:
      case Intrv_Enclosing:
      case Intrv_Similar:
      case Intrv_JustEnclosingAtStart:
        myInter.Remove(index);
        index--;
        break;

      case Intrv_Inside:
        myInter.InsertAfter(index, myInter(index));
        myInter(index).SetEnd(Tool.Start(), Tool.TolStart());
        myInter(index + 1).SetStart(Tool.End(), Tool.TolEnd());
        index = myInter.Length();
        break;

      case Intrv_JustOverlappingAtEnd:
      case Intrv_OverlappingAtEnd:
        myInter(index).SetEnd(Tool.Start(), Tool.TolStart());
        break;

      case Intrv_JustAfter:
        myInter(index).CutAtEnd(Tool.Start(), Tool.TolStart());
        break;

      case Intrv_After:
        break;
    }
    index++;
  }
}

void Intrv_Intervals::Subtract(const Intrv_Intervals& Tool)
{
  int index;
  for (index = 1; index <= Tool.myInter.Length(); index++)
    Subtract(Tool.myInter(index));
}

void Intrv_Intervals::Unite(const Intrv_Interval& Tool)
{
  bool           Inserted = false;
  Intrv_Interval Tins(Tool);
  int            index = 1;

  while (index <= myInter.Length())
  {

    switch (Tins.Position(myInter(index)))
    {

      case Intrv_Before:
        Inserted = true;
        myInter.InsertBefore(index, Tins);
        index = myInter.Length();
        break;

      case Intrv_JustBefore:
      case Intrv_OverlappingAtStart:
        Inserted = true;
        myInter(index).SetStart(Tins.Start(), Tins.TolStart());
        index = myInter.Length();
        break;

      case Intrv_Similar:
        Tins.FuseAtStart(myInter(index).Start(), myInter(index).TolStart());
        [[fallthrough]];
      case Intrv_JustEnclosingAtEnd:
        Tins.FuseAtEnd(myInter(index).End(), myInter(index).TolEnd());
        [[fallthrough]];
      case Intrv_Enclosing:
        myInter.Remove(index);
        index--;
        break;

      case Intrv_JustOverlappingAtEnd:
        Tins.SetStart(myInter(index).Start(), myInter(index).TolStart());
        Tins.FuseAtEnd(myInter(index).End(), myInter(index).TolEnd());
        myInter.Remove(index);
        index--;
        break;

      case Intrv_JustOverlappingAtStart:
        Inserted = true;
        myInter(index).FuseAtStart(Tins.Start(), Tins.TolStart());
        index = myInter.Length();
        break;

      case Intrv_JustEnclosingAtStart:
        Tins.FuseAtStart(myInter(index).Start(), myInter(index).TolStart());
        myInter.Remove(index);
        index--;
        break;

      case Intrv_Inside:
        Inserted = true;
        index    = myInter.Length();
        break;

      case Intrv_OverlappingAtEnd:
      case Intrv_JustAfter:
        Tins.SetStart(myInter(index).Start(), myInter(index).TolStart());
        myInter.Remove(index);
        index--;
        break;

      case Intrv_After:
        break;
    }
    index++;
  }
  if (!Inserted)
    myInter.Append(Tins);
}

void Intrv_Intervals::Unite(const Intrv_Intervals& Tool)
{
  int index;
  for (index = 1; index <= Tool.myInter.Length(); index++)
    Unite(Tool.myInter(index));
}

void Intrv_Intervals::XUnite(const Intrv_Interval& Tool)
{
  Intrv_Intervals Inter(Tool);
  XUnite(Inter);
}

void Intrv_Intervals::XUnite(const Intrv_Intervals& Tool)
{
  Intrv_Intervals Sub2(Tool);
  Sub2.Subtract(*this);
  Subtract(Tool);
  Unite(Sub2);
}

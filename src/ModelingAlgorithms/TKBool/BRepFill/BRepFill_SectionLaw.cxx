#include <BRep_Tool.hpp>
#include <BRepAdaptor_Curve.hpp>
#include <BRepFill_SectionLaw.hpp>
#include <BRepLProp.hpp>
#include <BRepTools_WireExplorer.hpp>
#include <GeomFill_SectionLaw.hpp>
#include <Standard_Type.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDS_Wire.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BRepFill_SectionLaw, Standard_Transient)

int BRepFill_SectionLaw::NbLaw() const
{
  return myLaws->Length();
}

const occ::handle<GeomFill_SectionLaw>& BRepFill_SectionLaw::Law(const int Index) const
{
  return myLaws->Value(Index);
}

int BRepFill_SectionLaw::IndexOfEdge(const TopoDS_Shape& anEdge) const
{
  return myIndices(anEdge);
}

bool BRepFill_SectionLaw::IsUClosed() const
{
  return uclosed;
}

bool BRepFill_SectionLaw::IsVClosed() const
{
  return vclosed;
}

bool BRepFill_SectionLaw::IsDone() const
{
  return myDone;
}

void BRepFill_SectionLaw::Init(const TopoDS_Wire& W)
{
  myIterator.Init(W);
}

TopoDS_Edge BRepFill_SectionLaw::CurrentEdge()
{
  TopoDS_Edge E;

  bool Suivant = false;
  if (myIterator.More())
  {
    E = myIterator.Current();

    Suivant = (BRep_Tool::Degenerated(E));
  }

  while (Suivant)
  {
    myIterator.Next();
    E = myIterator.Current();

    Suivant = (BRep_Tool::Degenerated(E) && myIterator.More());
  }

  if (myIterator.More())
    myIterator.Next();
  return E;
}

#include <Poly_CoherentNode.hpp>
#include <Poly_CoherentTriangle.hpp>

void Poly_CoherentNode::Clear(const occ::handle<NCollection_BaseAllocator>& theAlloc)
{
  Poly_CoherentTriPtr::RemoveList(myTriangles, theAlloc);
  myUV[0]     = Precision::Infinite();
  myUV[1]     = Precision::Infinite();
  myNormal[0] = 0.f;
  myNormal[1] = 0.f;
  myNormal[2] = 0.f;
  SetCoord(0., 0., 0.);
}

void Poly_CoherentNode::SetNormal(const gp_XYZ& theVector)
{
  myNormal[0] = static_cast<float>(theVector.X());
  myNormal[1] = static_cast<float>(theVector.Y());
  myNormal[2] = static_cast<float>(theVector.Z());
}

void Poly_CoherentNode::AddTriangle(const Poly_CoherentTriangle&                  theTri,
                                    const occ::handle<NCollection_BaseAllocator>& theAlloc)
{
  if (myTriangles == nullptr)
    myTriangles = new (theAlloc) Poly_CoherentTriPtr(theTri);
  else
    myTriangles->Prepend(&theTri, theAlloc);
}

bool Poly_CoherentNode::RemoveTriangle(const Poly_CoherentTriangle&                  theTri,
                                       const occ::handle<NCollection_BaseAllocator>& theAlloc)
{
  bool aResult(false);
  if (&myTriangles->GetTriangle() == &theTri)
  {
    Poly_CoherentTriPtr* aLostPtr = myTriangles;
    if (myTriangles == &myTriangles->Next())
      myTriangles = nullptr;
    else
      myTriangles = &myTriangles->Next();
    Poly_CoherentTriPtr::Remove(aLostPtr, theAlloc);
    aResult = true;
  }
  else
  {
    Poly_CoherentTriPtr::Iterator anIter(*myTriangles);
    for (anIter.Next(); anIter.More(); anIter.Next())
      if (&anIter.Value() == &theTri)
      {
        Poly_CoherentTriPtr::Remove(const_cast<Poly_CoherentTriPtr*>(&anIter.PtrValue()), theAlloc);
        aResult = true;
        break;
      }
  }
  return aResult;
}

void Poly_CoherentNode::Dump(Standard_OStream& theStream) const
{
  char buf[256];
  Sprintf(buf, "  X =%9.4f; Y =%9.4f; Z =%9.4f", X(), Y(), Z());
  theStream << buf << std::endl;
  Poly_CoherentTriPtr::Iterator anIter(*myTriangles);
  for (; anIter.More(); anIter.Next())
  {
    const Poly_CoherentTriangle& aTri = anIter.Value();
    Sprintf(buf, "      %5d %5d %5d", aTri.Node(0), aTri.Node(1), aTri.Node(2));
    theStream << buf << std::endl;
  }
}

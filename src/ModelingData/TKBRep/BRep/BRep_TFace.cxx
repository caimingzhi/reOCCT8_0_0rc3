#include <BRep_TFace.hpp>
#include <Geom_Surface.hpp>
#include <Poly_Triangulation.hpp>
#include <Standard_Type.hpp>
#include <TopLoc_Location.hpp>
#include <TopoDS_Shape.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BRep_TFace, TopoDS_TFace)

//=================================================================================================

BRep_TFace::BRep_TFace()
    : myTolerance(RealEpsilon()),
      myNaturalRestriction(false)
{
}

//=================================================================================================

occ::handle<TopoDS_TShape> BRep_TFace::EmptyCopy() const
{
  occ::handle<BRep_TFace> TF = new BRep_TFace();
  TF->Surface(mySurface);
  TF->Location(myLocation);
  TF->Tolerance(myTolerance);
  return TF;
}

//=================================================================================================

const occ::handle<Poly_Triangulation>& BRep_TFace::Triangulation(
  const Poly_MeshPurpose thePurpose) const
{
  if (thePurpose == Poly_MeshPurpose_NONE)
  {
    return ActiveTriangulation();
  }
  for (NCollection_List<occ::handle<Poly_Triangulation>>::Iterator anIter(myTriangulations);
       anIter.More();
       anIter.Next())
  {
    const occ::handle<Poly_Triangulation>& aTriangulation = anIter.Value();
    if ((aTriangulation->MeshPurpose() & thePurpose) != 0)
    {
      return aTriangulation;
    }
  }
  if ((thePurpose & Poly_MeshPurpose_AnyFallback) != 0 && !myTriangulations.IsEmpty())
  {
    // if none matching other criteria was found return the first defined triangulation
    return myTriangulations.First();
  }
  static const occ::handle<Poly_Triangulation> anEmptyTriangulation;
  return anEmptyTriangulation;
}

//=================================================================================================

void BRep_TFace::Triangulation(const occ::handle<Poly_Triangulation>& theTriangulation,
                               const bool                             theToReset)
{
  if (theToReset || theTriangulation.IsNull())
  {
    if (!myActiveTriangulation.IsNull())
    {
      // Reset Active bit
      myActiveTriangulation->SetMeshPurpose(myActiveTriangulation->MeshPurpose()
                                            & ~Poly_MeshPurpose_Active);
      myActiveTriangulation.Nullify();
    }
    myTriangulations.Clear();
    if (!theTriangulation.IsNull())
    {
      // Reset list of triangulations to new list with only one input triangulation that will be
      // active
      myTriangulations.Append(theTriangulation);
      myActiveTriangulation = theTriangulation;
      // Set Active bit
      theTriangulation->SetMeshPurpose(theTriangulation->MeshPurpose() | Poly_MeshPurpose_Active);
    }
    return;
  }
  for (NCollection_List<occ::handle<Poly_Triangulation>>::Iterator anIter(myTriangulations);
       anIter.More();
       anIter.Next())
  {
    // Make input triangulation active if it is already contained in list of triangulations
    if (anIter.Value() == theTriangulation)
    {
      if (!myActiveTriangulation.IsNull())
      {
        // Reset Active bit
        myActiveTriangulation->SetMeshPurpose(myActiveTriangulation->MeshPurpose()
                                              & ~Poly_MeshPurpose_Active);
      }
      myActiveTriangulation = theTriangulation;
      // Set Active bit
      theTriangulation->SetMeshPurpose(theTriangulation->MeshPurpose() | Poly_MeshPurpose_Active);
      return;
    }
  }
  for (NCollection_List<occ::handle<Poly_Triangulation>>::Iterator anIter(myTriangulations);
       anIter.More();
       anIter.Next())
  {
    // Replace active triangulation to input one
    if (anIter.Value() == myActiveTriangulation)
    {
      // Reset Active bit
      myActiveTriangulation->SetMeshPurpose(myActiveTriangulation->MeshPurpose()
                                            & ~Poly_MeshPurpose_Active);
      anIter.ChangeValue()  = theTriangulation;
      myActiveTriangulation = theTriangulation;
      // Set Active bit
      theTriangulation->SetMeshPurpose(theTriangulation->MeshPurpose() | Poly_MeshPurpose_Active);
      return;
    }
  }
}

//=================================================================================================

void BRep_TFace::Triangulations(
  const NCollection_List<occ::handle<Poly_Triangulation>>& theTriangulations,
  const occ::handle<Poly_Triangulation>&                   theActiveTriangulation)
{
  if (theTriangulations.IsEmpty())
  {
    myActiveTriangulation.Nullify();
    myTriangulations.Clear();
    return;
  }
  bool anActiveInList = false;
  for (NCollection_List<occ::handle<Poly_Triangulation>>::Iterator anIter(theTriangulations);
       anIter.More();
       anIter.Next())
  {
    const occ::handle<Poly_Triangulation>& aTriangulation = anIter.Value();
    Standard_ASSERT_RAISE(!aTriangulation.IsNull(),
                          "Try to set list with NULL triangulation to the face");
    if (aTriangulation == theActiveTriangulation)
    {
      anActiveInList = true;
    }
    // Reset Active bit
    aTriangulation->SetMeshPurpose(aTriangulation->MeshPurpose() & ~Poly_MeshPurpose_Active);
  }
  Standard_ASSERT_RAISE(theActiveTriangulation.IsNull() || anActiveInList,
                        "Active triangulation isn't part of triangulations list");
  myTriangulations = theTriangulations;
  if (theActiveTriangulation.IsNull())
  {
    // Save the first one as active
    myActiveTriangulation = myTriangulations.First();
  }
  else
  {
    myActiveTriangulation = theActiveTriangulation;
  }
  myActiveTriangulation->SetMeshPurpose(myActiveTriangulation->MeshPurpose()
                                        | Poly_MeshPurpose_Active);
}

//=================================================================================================

void BRep_TFace::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)

  OCCT_DUMP_BASE_CLASS(theOStream, theDepth, TopoDS_TFace)

  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, myActiveTriangulation.get())
  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, mySurface.get())
  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, &myLocation)

  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myTolerance)
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myNaturalRestriction)

  for (NCollection_List<occ::handle<Poly_Triangulation>>::Iterator anIter(myTriangulations);
       anIter.More();
       anIter.Next())
  {
    const occ::handle<Poly_Triangulation>& aTriangulation = anIter.Value();
    OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, aTriangulation.get())
  }
}

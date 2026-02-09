

#include "RWStepVisual_RWTriangulatedFace.hpp"
#include <StepVisual_TriangulatedFace.hpp>
#include <Interface_EntityIterator.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <TCollection_HAsciiString.hpp>
#include <StepVisual_CoordinatesList.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Array2.hpp>
#include <NCollection_HArray2.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Real.hpp>
#include <StepVisual_FaceOrSurface.hpp>

RWStepVisual_RWTriangulatedFace::RWStepVisual_RWTriangulatedFace() = default;

void RWStepVisual_RWTriangulatedFace::ReadStep(
  const occ::handle<StepData_StepReaderData>&     theData,
  const int                                       theNum,
  occ::handle<Interface_Check>&                   theCheck,
  const occ::handle<StepVisual_TriangulatedFace>& theEnt) const
{

  if (!theData->CheckNbParams(theNum, 7, theCheck, "triangulated_face"))
  {
    return;
  }

  occ::handle<TCollection_HAsciiString> aRepresentationItem_Name;
  theData->ReadString(theNum, 1, "representation_item.name", theCheck, aRepresentationItem_Name);

  occ::handle<StepVisual_CoordinatesList> aTessellatedFace_Coordinates;
  theData->ReadEntity(theNum,
                      2,
                      "tessellated_face.coordinates",
                      theCheck,
                      STANDARD_TYPE(StepVisual_CoordinatesList),
                      aTessellatedFace_Coordinates);

  int aTessellatedFace_Pnmax;
  theData->ReadInteger(theNum, 3, "tessellated_face.pnmax", theCheck, aTessellatedFace_Pnmax);

  occ::handle<NCollection_HArray2<double>> aTessellatedFace_Normals;
  int                                      sub4 = 0;
  if (theData->ReadSubList(theNum, 4, "tessellated_face.normals", theCheck, sub4))
  {
    int nb0                  = theData->NbParams(sub4);
    int nbj0                 = theData->NbParams(theData->ParamNumber(sub4, 1));
    aTessellatedFace_Normals = new NCollection_HArray2<double>(1, nb0, 1, nbj0);
    for (int i0 = 1; i0 <= nb0; i0++)
    {
      int subj4 = 0;
      if (theData->ReadSubList(sub4, i0, "sub-part(tessellated_face.normals)", theCheck, subj4))
      {
        int num4 = subj4;
        for (int j0 = 1; j0 <= nbj0; j0++)
        {
          double anIt0;
          theData->ReadReal(num4, j0, "real", theCheck, anIt0);
          aTessellatedFace_Normals->SetValue(i0, j0, anIt0);
        }
      }
    }
  }

  StepVisual_FaceOrSurface aTessellatedFace_GeometricLink;
  bool                     hasTessellatedFace_GeometricLink = true;
  if (theData->IsParamDefined(theNum, 5))
  {
    theData->ReadEntity(theNum,
                        5,
                        "tessellated_face.geometric_link",
                        theCheck,
                        aTessellatedFace_GeometricLink);
  }
  else
  {
    hasTessellatedFace_GeometricLink = false;
    aTessellatedFace_GeometricLink   = StepVisual_FaceOrSurface();
  }

  occ::handle<NCollection_HArray1<int>> aPnindex;
  int                                   sub6 = 0;
  if (theData->ReadSubList(theNum, 6, "pnindex", theCheck, sub6))
  {
    int nb0  = theData->NbParams(sub6);
    aPnindex = new NCollection_HArray1<int>(1, nb0);
    int num2 = sub6;
    for (int i0 = 1; i0 <= nb0; i0++)
    {
      int anIt0;
      theData->ReadInteger(num2, i0, "integer", theCheck, anIt0);
      aPnindex->SetValue(i0, anIt0);
    }
  }

  occ::handle<NCollection_HArray2<int>> aTriangles;
  int                                   sub7 = 0;
  if (theData->ReadSubList(theNum, 7, "triangles", theCheck, sub7))
  {
    int nb0    = theData->NbParams(sub7);
    int nbj0   = theData->NbParams(theData->ParamNumber(sub7, 1));
    aTriangles = new NCollection_HArray2<int>(1, nb0, 1, nbj0);
    for (int i0 = 1; i0 <= nb0; i0++)
    {
      int subj7 = 0;
      if (theData->ReadSubList(sub7, i0, "sub-part(triangles)", theCheck, subj7))
      {
        int num4 = subj7;
        for (int j0 = 1; j0 <= nbj0; j0++)
        {
          int anIt0;
          theData->ReadInteger(num4, j0, "integer", theCheck, anIt0);
          aTriangles->SetValue(i0, j0, anIt0);
        }
      }
    }
  }

  theEnt->Init(aRepresentationItem_Name,
               aTessellatedFace_Coordinates,
               aTessellatedFace_Pnmax,
               aTessellatedFace_Normals,
               hasTessellatedFace_GeometricLink,
               aTessellatedFace_GeometricLink,
               aPnindex,
               aTriangles);

#ifdef OCCT_DEBUG
  std::cout << aTessellatedFace_Pnmax << " " << (aTriangles.IsNull() ? 0 : aTriangles->NbRows())
            << std::endl;
#endif
}

void RWStepVisual_RWTriangulatedFace::WriteStep(
  StepData_StepWriter&                            theSW,
  const occ::handle<StepVisual_TriangulatedFace>& theEnt) const
{

  theSW.Send(theEnt->Name());

  theSW.Send(theEnt->Coordinates());

  theSW.Send(theEnt->Pnmax());

  theSW.OpenSub();
  for (int i3 = 1; i3 <= theEnt->Normals()->NbRows(); i3++)
  {
    theSW.NewLine(false);
    theSW.OpenSub();
    for (int j3 = 1; j3 <= theEnt->Normals()->NbColumns(); j3++)
    {
      double Var0 = theEnt->Normals()->Value(i3, j3);
      theSW.Send(Var0);
    }
    theSW.CloseSub();
  }
  theSW.CloseSub();

  if (theEnt->HasGeometricLink())
  {
    theSW.Send(theEnt->GeometricLink().Value());
  }
  else
  {
    theSW.SendUndef();
  }

  theSW.OpenSub();
  for (int i5 = 1; i5 <= theEnt->Pnindex()->Length(); i5++)
  {
    int Var0 = theEnt->Pnindex()->Value(i5);
    theSW.Send(Var0);
  }
  theSW.CloseSub();

  theSW.OpenSub();
  for (int i6 = 1; i6 <= theEnt->Triangles()->NbRows(); i6++)
  {
    theSW.NewLine(false);
    theSW.OpenSub();
    for (int j6 = 1; j6 <= theEnt->Triangles()->NbColumns(); j6++)
    {
      int Var0 = theEnt->Triangles()->Value(i6, j6);
      theSW.Send(Var0);
    }
    theSW.CloseSub();
  }
  theSW.CloseSub();
}

void RWStepVisual_RWTriangulatedFace::Share(const occ::handle<StepVisual_TriangulatedFace>& theEnt,
                                            Interface_EntityIterator& theIter) const
{

  theIter.AddItem(theEnt->StepVisual_TessellatedFace::Coordinates());

  if (theEnt->StepVisual_TessellatedFace::HasGeometricLink())
  {
    theIter.AddItem(theEnt->StepVisual_TessellatedFace::GeometricLink().Value());
  }
}

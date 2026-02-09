

#include <Interface_EntityIterator.hpp>
#include <Interface_ShareTool.hpp>
#include "RWStepShape_RWFaceBound.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepShape_EdgeLoop.hpp>
#include <StepShape_FaceBound.hpp>
#include <StepShape_Loop.hpp>
#include <StepShape_OrientedEdge.hpp>

RWStepShape_RWFaceBound::RWStepShape_RWFaceBound() = default;

void RWStepShape_RWFaceBound::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                       const int                                   num,
                                       occ::handle<Interface_Check>&               ach,
                                       const occ::handle<StepShape_FaceBound>&     ent) const
{

  if (!data->CheckNbParams(num, 3, ach, "face_bound"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<StepShape_Loop> aBound;

  data->ReadEntity(num, 2, "bound", ach, STANDARD_TYPE(StepShape_Loop), aBound);

  bool aOrientation;

  data->ReadBoolean(num, 3, "orientation", ach, aOrientation);

  ent->Init(aName, aBound, aOrientation);
}

void RWStepShape_RWFaceBound::WriteStep(StepData_StepWriter&                    SW,
                                        const occ::handle<StepShape_FaceBound>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->Bound());

  SW.SendBoolean(ent->Orientation());
}

void RWStepShape_RWFaceBound::Share(const occ::handle<StepShape_FaceBound>& ent,
                                    Interface_EntityIterator&               iter) const
{

  iter.GetOneItem(ent->Bound());
}

void RWStepShape_RWFaceBound::Check(const occ::handle<StepShape_FaceBound>& ent,
                                    const Interface_ShareTool&              aShto,
                                    occ::handle<Interface_Check>&           ach) const
{
  bool                            theFBOri2 = true;
  bool                            theFBOri1 = ent->Orientation();
  occ::handle<StepShape_EdgeLoop> theEL1    = occ::down_cast<StepShape_EdgeLoop>(ent->Bound());
  if (!theEL1.IsNull())
  {
    int nbEdg = theEL1->NbEdgeList();
    for (int i = 1; i <= nbEdg; i++)
    {
      occ::handle<StepShape_OrientedEdge> theOE1  = theEL1->EdgeListValue(i);
      occ::handle<StepShape_Edge>         theEdg1 = theOE1->EdgeElement();
      Interface_EntityIterator            myShRef = aShto.Sharings(theEdg1);
      myShRef.SelectType(STANDARD_TYPE(StepShape_OrientedEdge), true);
      int nbRef = myShRef.NbEntities();
      if (nbRef == 1)
      {
      }
      else if (nbRef == 2)
      {
        occ::handle<StepShape_OrientedEdge> theOE2;
        occ::handle<StepShape_OrientedEdge> refOE1 =
          occ::down_cast<StepShape_OrientedEdge>(myShRef.Value());
        myShRef.Next();
        occ::handle<StepShape_OrientedEdge> refOE2 =
          occ::down_cast<StepShape_OrientedEdge>(myShRef.Value());
        if (theOE1 == refOE1)
          theOE2 = refOE2;
        else if (theOE1 == refOE2)
          theOE2 = refOE1;

        bool sharOE2 = aShto.IsShared(theOE2);
        if (!sharOE2)
        {
#ifdef OCCT_DEBUG
          std::cout << "OrientedEdge2 not shared" << std::endl;
#endif
        }
        else
        {
          myShRef = aShto.Sharings(theOE2);
          myShRef.SelectType(STANDARD_TYPE(StepShape_EdgeLoop), true);
          myShRef.Start();
          occ::handle<StepShape_EdgeLoop> theEL2 =
            occ::down_cast<StepShape_EdgeLoop>(myShRef.Value());
          bool sharEL2 = aShto.IsShared(theEL2);
          if (!sharEL2)
          {
#ifdef OCCT_DEBUG
            std::cout << "EdgeLoop2 not shared" << std::endl;
#endif
          }
          else
          {
            myShRef = aShto.Sharings(theEL2);
            myShRef.SelectType(STANDARD_TYPE(StepShape_FaceBound), true);
            myShRef.Start();
            occ::handle<StepShape_FaceBound> theFB2 =
              occ::down_cast<StepShape_FaceBound>(myShRef.Value());
            if (!theFB2.IsNull())
            {
              theFBOri2 = theFB2->Orientation();
            }
            else
            {
#ifdef OCCT_DEBUG
              std::cout << "EdgeLoop not referenced by FaceBound" << std::endl;
#endif
            }
          }
        }

        bool theOEOri1 = theFBOri1 ? theOE1->Orientation() : !(theOE1->Orientation());
        bool theOEOri2 = theFBOri2 ? theOE2->Orientation() : !(theOE2->Orientation());

        if (theOEOri1 == theOEOri2)
        {
          ach->AddFail("ERROR: non 2-manifold topology");
        }
      }
    }
  }
  else
  {
#ifdef OCCT_DEBUG
    std::cout << "no EdgeLoop in FaceBound" << std::endl;
#endif
  }
}

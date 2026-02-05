#include <TopOpeBRepDS_Filter.hpp>
#include <TopOpeBRepDS_ProcessInterferencesTool.hpp>

//=================================================================================================

void TopOpeBRepDS_Filter::ProcessCurveInterferences(const int CIX)
{
  TopOpeBRepDS_DataStructure&                               BDS = myHDS->ChangeDS();
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& LI  = BDS.ChangeCurveInterferences(CIX);
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator it1(LI);

  // process interferences of LI with VERTEX geometry
  while (it1.More())
  {
    const occ::handle<TopOpeBRepDS_Interference>& I1  = it1.Value();
    int                                           G1  = I1->Geometry();
    TopOpeBRepDS_Kind                             GT1 = I1->GeometryType();
    TopAbs_Orientation                            O1  = I1->Transition().Orientation(TopAbs_IN);

    if (GT1 == TopOpeBRepDS_VERTEX)
    {

      NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator it2(it1);
      it2.Next();

      while (it2.More())
      {
        const occ::handle<TopOpeBRepDS_Interference>& I2  = it2.Value();
        int                                           G2  = I2->Geometry();
        TopOpeBRepDS_Kind                             GT2 = I2->GeometryType();
        TopAbs_Orientation                            O2  = I2->Transition().Orientation(TopAbs_IN);

        //	bool remove = (GT2 == GT1) && (G2 == G1);
        // xpu140898 : USA60111 : CPI(FORWARD,v10,C1) + CPIREV(REVERSED,v10,C1)
        //             do NOT delete CPIREV!!
        bool remove = (GT2 == GT1) && (G2 == G1) && (O1 == O2);
        if (remove)
        {
          LI.Remove(it2);
        }
        else
          it2.Next();
      }
    }
    it1.Next();
  }
}

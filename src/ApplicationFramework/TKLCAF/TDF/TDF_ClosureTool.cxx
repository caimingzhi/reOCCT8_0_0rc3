#include <Standard_TypeMismatch.hpp>
#include <TDF_AttributeIterator.hpp>
#include <TDF_ChildIterator.hpp>
#include <TDF_ClosureMode.hpp>
#include <TDF_ClosureTool.hpp>
#include <TDF_DataSet.hpp>
#include <TDF_IDFilter.hpp>
#include <TDF_Label.hpp>
#include <NCollection_Map.hpp>
#include <NCollection_List.hpp>

void TDF_ClosureTool::Closure(const occ::handle<TDF_DataSet>& aDataSet)
{
  TDF_IDFilter    Filter(false);
  TDF_ClosureMode Mode;
  TDF_ClosureTool::Closure(aDataSet, Filter, Mode);
}

void TDF_ClosureTool::Closure(const occ::handle<TDF_DataSet>& aDataSet,
                              const TDF_IDFilter&             aFilter,
                              const TDF_ClosureMode&          aMode)
{
  NCollection_Map<TDF_Label>&                  labMap  = aDataSet->Labels();
  NCollection_Map<occ::handle<TDF_Attribute>>& attMap  = aDataSet->Attributes();
  NCollection_List<TDF_Label>&                 rootLst = aDataSet->Roots();

  rootLst.Clear();
  NCollection_Map<TDF_Label>::Iterator labMItr(labMap);
  for (; labMItr.More(); labMItr.Next())
    rootLst.Append(labMItr.Key());

  NCollection_List<TDF_Label>::Iterator labLItr(rootLst);
  for (; labLItr.More(); labLItr.Next())
  {
    const TDF_Label& lab = labLItr.Value();
    if (lab.HasAttribute())
      TDF_ClosureTool::LabelAttributes(lab, labMap, attMap, aFilter, aMode);
    if (aMode.Descendants())
      TDF_ClosureTool::Closure(lab, labMap, attMap, aFilter, aMode);
  }
}

void TDF_ClosureTool::Closure(const TDF_Label&                             aLabel,
                              NCollection_Map<TDF_Label>&                  aLabMap,
                              NCollection_Map<occ::handle<TDF_Attribute>>& anAttMap,
                              const TDF_IDFilter&                          aFilter,
                              const TDF_ClosureMode&                       aMode)
{
  TDF_Label upLab;
  for (TDF_ChildIterator childItr(aLabel, true); childItr.More(); childItr.Next())
  {
    const TDF_Label& locLab = childItr.Value();

    if (locLab.HasAttribute())
    {
      aLabMap.Add(locLab);
      upLab = locLab.Father();
      while (aLabMap.Add(upLab))
        upLab = upLab.Father();
      TDF_ClosureTool::LabelAttributes(locLab, aLabMap, anAttMap, aFilter, aMode);
    }
  }
}

void TDF_ClosureTool::LabelAttributes(const TDF_Label&                             aLabel,
                                      NCollection_Map<TDF_Label>&                  aLabMap,
                                      NCollection_Map<occ::handle<TDF_Attribute>>& anAttMap,
                                      const TDF_IDFilter&                          aFilter,
                                      const TDF_ClosureMode&                       aMode)
{
  occ::handle<TDF_DataSet>                              tmpDataSet;
  bool                                                  BindLabel;
  NCollection_Map<occ::handle<TDF_Attribute>>::Iterator attMItr;
  NCollection_Map<TDF_Label>::Iterator                  labMItr;

  for (TDF_AttributeIterator attItr(aLabel); attItr.More(); attItr.Next())
  {
    const occ::handle<TDF_Attribute> locAtt1 = attItr.Value();
    if (aFilter.IsKept(locAtt1))
    {
      if (anAttMap.Add(locAtt1))
      {

        tmpDataSet = new TDF_DataSet();
        if (aMode.References())
        {

          locAtt1->References(tmpDataSet);

          const NCollection_Map<occ::handle<TDF_Attribute>>& tmpAttMap = tmpDataSet->Attributes();
          for (attMItr.Initialize(tmpAttMap); attMItr.More(); attMItr.Next())
          {
            const occ::handle<TDF_Attribute>& locAtt2 = attMItr.Key();
            BindLabel                                 = false;
            if (!locAtt2.IsNull())
            {
              const TDF_Label& locLab2 = locAtt2->Label();
              BindLabel                = !locLab2.IsNull();
              if (BindLabel)
              {

                if (aLabMap.Add(locLab2))
                  TDF_ClosureTool::Closure(locLab2, aLabMap, anAttMap, aFilter, aMode);
              }
              else
              {

                anAttMap.Add(locAtt2);
              }
            }
          }

          const NCollection_Map<TDF_Label>& tmpLabMap = tmpDataSet->Labels();
          for (labMItr.Initialize(tmpLabMap); labMItr.More(); labMItr.Next())
          {
            const TDF_Label& locLab1 = labMItr.Key();
            if (aLabMap.Add(locLab1))
              TDF_ClosureTool::Closure(locLab1, aLabMap, anAttMap, aFilter, aMode);
          }
        }
      }
    }
  }
}

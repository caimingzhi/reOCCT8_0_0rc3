#pragma once


#include <Standard.hpp>

#include <TopOpeBRepDS_Interference.hpp>
#include <NCollection_List.hpp>
#include <NCollection_DataMap.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Boolean.hpp>
class TopOpeBRepDS_Interference;

class TopOpeBRepDS_Association : public Standard_Transient
{

public:
  Standard_EXPORT TopOpeBRepDS_Association();

  Standard_EXPORT void Associate(const occ::handle<TopOpeBRepDS_Interference>& I,
                                 const occ::handle<TopOpeBRepDS_Interference>& K);

  Standard_EXPORT void Associate(
    const occ::handle<TopOpeBRepDS_Interference>&                   I,
    const NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& LI);

  Standard_EXPORT bool HasAssociation(const occ::handle<TopOpeBRepDS_Interference>& I) const;

  Standard_EXPORT NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& Associated(
    const occ::handle<TopOpeBRepDS_Interference>& I);

  Standard_EXPORT bool AreAssociated(const occ::handle<TopOpeBRepDS_Interference>& I,
                                     const occ::handle<TopOpeBRepDS_Interference>& K) const;

  DEFINE_STANDARD_RTTIEXT(TopOpeBRepDS_Association, Standard_Transient)

private:
  NCollection_DataMap<occ::handle<TopOpeBRepDS_Interference>,
                      NCollection_List<occ::handle<TopOpeBRepDS_Interference>>>
    myMap;
};


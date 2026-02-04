#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
#include <NCollection_DataMap.hpp>

class Transfer_MapContainer : public Standard_Transient
{

public:
  Standard_EXPORT Transfer_MapContainer();

  //! Set map already translated geometry objects.
  Standard_EXPORT void SetMapObjects(
    NCollection_DataMap<occ::handle<Standard_Transient>, occ::handle<Standard_Transient>>&
      theMapObjects);

  //! Get map already translated geometry objects.
  Standard_EXPORT NCollection_DataMap<occ::handle<Standard_Transient>,
                                      occ::handle<Standard_Transient>>&
                  GetMapObjects();

  DEFINE_STANDARD_RTTIEXT(Transfer_MapContainer, Standard_Transient)

private:
  NCollection_DataMap<occ::handle<Standard_Transient>, occ::handle<Standard_Transient>> myMapObj;
};


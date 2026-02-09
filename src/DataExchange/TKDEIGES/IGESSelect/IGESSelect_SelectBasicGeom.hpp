#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <IFSelect_SelectExplore.hpp>
class Standard_Transient;
class Interface_Graph;
class Interface_EntityIterator;
class TCollection_AsciiString;
class IGESData_IGESEntity;

class IGESSelect_SelectBasicGeom : public IFSelect_SelectExplore
{

public:
  Standard_EXPORT IGESSelect_SelectBasicGeom(const int mode);

  Standard_EXPORT bool CurvesOnly() const;

  Standard_EXPORT bool Explore(const int                              level,
                               const occ::handle<Standard_Transient>& ent,
                               const Interface_Graph&                 G,
                               Interface_EntityIterator&              explored) const override;

  Standard_EXPORT TCollection_AsciiString ExploreLabel() const override;

  Standard_EXPORT static bool SubCurves(const occ::handle<IGESData_IGESEntity>& ent,
                                        Interface_EntityIterator&               explored);

  DEFINE_STANDARD_RTTIEXT(IGESSelect_SelectBasicGeom, IFSelect_SelectExplore)

private:
  int thegeom;
};

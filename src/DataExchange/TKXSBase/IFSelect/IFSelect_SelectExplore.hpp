#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <IFSelect_SelectDeduct.hpp>
class Interface_EntityIterator;
class Interface_Graph;
class Standard_Transient;
class TCollection_AsciiString;

class IFSelect_SelectExplore : public IFSelect_SelectDeduct
{

public:
  Standard_EXPORT int Level() const;

  Standard_EXPORT Interface_EntityIterator RootResult(const Interface_Graph& G) const override;

  Standard_EXPORT virtual bool Explore(const int                              level,
                                       const occ::handle<Standard_Transient>& ent,
                                       const Interface_Graph&                 G,
                                       Interface_EntityIterator&              explored) const = 0;

  Standard_EXPORT TCollection_AsciiString Label() const override;

  Standard_EXPORT virtual TCollection_AsciiString ExploreLabel() const = 0;

  DEFINE_STANDARD_RTTIEXT(IFSelect_SelectExplore, IFSelect_SelectDeduct)

protected:
  Standard_EXPORT IFSelect_SelectExplore(const int level);

private:
  int thelevel;
};

#include <TopOpeBRepDS_Surface.hpp>

#include <Geom_Surface.hpp>

//=================================================================================================

TopOpeBRepDS_Surface::TopOpeBRepDS_Surface()
    : myTolerance(0.0),
      myKeep(false)
{
}

//=================================================================================================

TopOpeBRepDS_Surface::TopOpeBRepDS_Surface(const occ::handle<Geom_Surface>& theSurface,
                                           const double                     theTolerance)
    : mySurface(theSurface),
      myTolerance(theTolerance),
      myKeep(false)
{
}

//=================================================================================================

TopOpeBRepDS_Surface::TopOpeBRepDS_Surface(const TopOpeBRepDS_Surface& theOther)

  = default;

//=================================================================================================

void TopOpeBRepDS_Surface::Assign(const TopOpeBRepDS_Surface& Other)
{
  mySurface   = Other.mySurface;
  myTolerance = Other.myTolerance;
  myKeep      = Other.myKeep;
}

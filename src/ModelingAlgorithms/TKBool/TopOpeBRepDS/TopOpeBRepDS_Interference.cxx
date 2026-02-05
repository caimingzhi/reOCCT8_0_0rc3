#include <TopOpeBRepDS.hpp>
#include <TopOpeBRepDS_Interference.hpp>
#include <TopOpeBRepDS_Transition.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TopOpeBRepDS_Interference, Standard_Transient)

//=================================================================================================

TopOpeBRepDS_Interference::TopOpeBRepDS_Interference() = default;

//=================================================================================================

TopOpeBRepDS_Interference::TopOpeBRepDS_Interference(const TopOpeBRepDS_Transition& T,
                                                     const TopOpeBRepDS_Kind        ST,
                                                     const int                      S,
                                                     const TopOpeBRepDS_Kind        GT,
                                                     const int                      G)
    : myTransition(T),
      mySupport(S),
      myGeometry(G),
      mySupportType(ST),
      myGeometryType(GT)
{
}

//=================================================================================================

TopOpeBRepDS_Interference::TopOpeBRepDS_Interference(
  const occ::handle<TopOpeBRepDS_Interference>& I)
    : myTransition(I->Transition()),
      mySupport(I->Support()),
      myGeometry(I->Geometry()),
      mySupportType(I->SupportType()),
      myGeometryType(I->GeometryType())
{
}

//=================================================================================================

const TopOpeBRepDS_Transition& TopOpeBRepDS_Interference::Transition() const
{
  return myTransition;
}

//=================================================================================================

TopOpeBRepDS_Transition& TopOpeBRepDS_Interference::ChangeTransition()
{
  return myTransition;
}

//=================================================================================================

void TopOpeBRepDS_Interference::Transition(const TopOpeBRepDS_Transition& T)
{
  myTransition = T;
}

//=================================================================================================

void TopOpeBRepDS_Interference::GKGSKS(TopOpeBRepDS_Kind& GK,
                                       int&               G,
                                       TopOpeBRepDS_Kind& SK,
                                       int&               S) const
{
  GK = myGeometryType;
  G  = myGeometry;
  SK = mySupportType;
  S  = mySupport;
}

//=================================================================================================

TopOpeBRepDS_Kind TopOpeBRepDS_Interference::SupportType() const
{
  return mySupportType;
}

//=================================================================================================

int TopOpeBRepDS_Interference::Support() const
{
  return mySupport;
}

//=================================================================================================

TopOpeBRepDS_Kind TopOpeBRepDS_Interference::GeometryType() const
{
  return myGeometryType;
}

//=================================================================================================

int TopOpeBRepDS_Interference::Geometry() const
{
  return myGeometry;
}

//=================================================================================================

void TopOpeBRepDS_Interference::SetGeometry(const int GI)
{
  myGeometry = GI;
}

//=================================================================================================

void TopOpeBRepDS_Interference::SupportType(const TopOpeBRepDS_Kind ST)
{
  mySupportType = ST;
}

//=================================================================================================

void TopOpeBRepDS_Interference::Support(const int S)
{
  mySupport = S;
}

//=================================================================================================

void TopOpeBRepDS_Interference::GeometryType(const TopOpeBRepDS_Kind GT)
{
  myGeometryType = GT;
}

//=================================================================================================

void TopOpeBRepDS_Interference::Geometry(const int G)
{
  myGeometry = G;
}

//=================================================================================================

bool TopOpeBRepDS_Interference::HasSameSupport(
  const occ::handle<TopOpeBRepDS_Interference>& I) const
{
  return (mySupportType == I->mySupportType && mySupport == I->mySupport);
}

//=================================================================================================

bool TopOpeBRepDS_Interference::HasSameGeometry(
  const occ::handle<TopOpeBRepDS_Interference>& I) const
{
  return (myGeometryType == I->myGeometryType && myGeometry == I->myGeometry);
}

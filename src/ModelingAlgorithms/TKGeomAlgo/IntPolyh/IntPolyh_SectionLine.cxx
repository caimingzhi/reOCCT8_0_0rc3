#include <IntPolyh_SectionLine.hpp>
#include <IntPolyh_StartPoint.hpp>
#include <IntPolyh_Triangle.hpp>

#include <cstdio>

//=================================================================================================

IntPolyh_SectionLine::IntPolyh_SectionLine() /*: n(0),nbstartpoints(0),ptr(0)*/ = default;

//=================================================================================================

IntPolyh_SectionLine::IntPolyh_SectionLine(const int N) /* : nbstartpoints(0)*/
{
  Init(N);
}

//=================================================================================================

void IntPolyh_SectionLine::Init(const int /*N*/)
{
  //   ptr = (void*) (new IntPolyh_StartPoint [N]);
  //   n=N;
  if (!mySeqOfSPoints.Length())
    IncrementNbStartPoints();
}

//=================================================================================================

int IntPolyh_SectionLine::GetN() const
{
  // return(n);
  return mySeqOfSPoints.Length();
}

//=================================================================================================

int IntPolyh_SectionLine::NbStartPoints() const
{
  //  return(nbstartpoints);
  return mySeqOfSPoints.Length() - 1;
}

//=================================================================================================

void IntPolyh_SectionLine::IncrementNbStartPoints()
{
  //  nbstartpoints++;
  IntPolyh_StartPoint aSP;
  mySeqOfSPoints.Append(aSP);
}

//=================================================================================================

const IntPolyh_StartPoint& IntPolyh_SectionLine::Value(const int Index) const
{
  return mySeqOfSPoints(Index + 1);
}

//=================================================================================================

IntPolyh_StartPoint& IntPolyh_SectionLine::ChangeValue(const int Index)
{
  return mySeqOfSPoints(Index + 1);
}

//=================================================================================================

void IntPolyh_SectionLine::Destroy()
{
  //   if(n) {
  //     if(ptr) {
  //       IntPolyh_StartPoint *ptrstpoint = (IntPolyh_StartPoint *)ptr;
  //       delete [] ptrstpoint;
  //       ptr=0;
  //       n=0;
  //     }
  //   }
}

//=================================================================================================

IntPolyh_SectionLine& IntPolyh_SectionLine::Copy(const IntPolyh_SectionLine& Other)
{
  //   if(ptr==Other.ptr) return(*this);
  //   Destroy();
  //   n=Other.n;
  //   ptr = (void *) (new IntPolyh_StartPoint[n]);
  //   for(int i=0;i<=n;i++) {
  //     (*this)[i]=Other[i];
  //   }
  mySeqOfSPoints = Other.mySeqOfSPoints;
  return (*this);
}

//=================================================================================================

void IntPolyh_SectionLine::Dump() const
{
  printf("\n SectionLine 0-> %d", /*nbstartpoints*/ NbStartPoints() - 1);
  for (int i = 0; i < NbStartPoints(); i++)
  {
    //(*this)[i].Dump(i);
    Value(i).Dump(i);
    //     const IntPolyh_StartPoint& SP = Value(i);
    //     std::cout << "point P" << i << " " << SP.X() << " " << SP.Y() << " " << SP.Z() <<
    //     std::endl;
  }
  printf("\n");
}

//=================================================================================================

void IntPolyh_SectionLine::Prepend(const IntPolyh_StartPoint& SP)
{
  mySeqOfSPoints.Prepend(SP);
}

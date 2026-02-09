#include <Intf_Interference.hpp>
#include <Intf_SectionLine.hpp>
#include <Intf_SectionPoint.hpp>
#include <Intf_TangentZone.hpp>

Intf_Interference::Intf_Interference(const bool Self)
    : SelfIntf(Self),
      Tolerance(0.0)
{
}

void Intf_Interference::SelfInterference(const bool Self)
{
  SelfIntf = Self;
  mySPoins.Clear();
  mySLines.Clear();
  myTZones.Clear();
}

bool Intf_Interference::Insert(const Intf_TangentZone& LaZone)
{
  if (myTZones.Length() <= 0)
    return false;
  int  lzin     = 0;
  int  lunp     = 0;
  int  lotp     = 0;
  int  lunl     = 0;
  int  lotl     = 0;
  bool same     = false;
  bool Inserted = true;
  int  npcz     = -1;
  int  nplz     = LaZone.NumberOfPoints();

  for (int Iz = 1; Iz <= myTZones.Length(); Iz++)
  {

    npcz = myTZones(Iz).NumberOfPoints();
    int Ipz0, Ipz1, Ipz2;
    for (Ipz1 = 1; Ipz1 <= npcz; Ipz1++)
    {
      Ipz0 = Ipz1 - 1;
      if (Ipz0 <= 0)
        Ipz0 = npcz;
      Ipz2 = (Ipz1 % npcz) + 1;

      int Ilz1, Ilz2;
      for (Ilz1 = 1; Ilz1 <= nplz; Ilz1++)
      {
        Ilz2 = (Ilz1 % nplz) + 1;

        if ((myTZones(Iz).GetPoint(Ipz1)).IsEqual(LaZone.GetPoint(Ilz1)))
        {
          if ((myTZones(Iz).GetPoint(Ipz0)).IsEqual(LaZone.GetPoint(Ilz2)))
          {
            lzin = Iz;
            lunp = Ipz0;
            lotp = Ipz1;
            lunl = Ilz1;
            lotl = Ilz2;
            same = false;
            break;
          }
          else if ((myTZones(Iz).GetPoint(Ipz2)).IsEqual(LaZone.GetPoint(Ilz2)))
          {
            lzin = Iz;
            lunp = Ipz1;
            lotp = Ipz2;
            lunl = Ilz1;
            lotl = Ilz2;
            same = true;
            break;
          }
          else
          {
            lzin = Iz;
            lunp = Ipz1;
            lunl = Ilz1;
          }
        }
      }
      if (lotp != 0)
        break;
    }
    if (lotp != 0)
      break;
  }

  int Ilc;
  if (lotp != 0)
  {
    for (Ilc = lotl + 1; (((Ilc - 1) % nplz) + 1) != lunl; Ilc++)
    {
      myTZones(lzin).InsertBefore(lotp, LaZone.GetPoint(((Ilc - 1) % nplz) + 1));
      if (!same)
        lotp++;
    }
  }

  else if (lunp > 0)
  {
    bool loop = false;
    for (Ilc = lunl;; Ilc++)
    {
      myTZones(lzin).InsertBefore(lunp, LaZone.GetPoint((((Ilc - 1) % nplz) + 1)));
      lunp++;
      if (loop && (((Ilc - 1) % nplz) + 1) == lunl)
        break;
      loop = true;
    }
  }

  else
  {
    Inserted = false;
  }

  if (Inserted)
  {
    Intf_TangentZone theNew = myTZones(lzin);
    myTZones.Remove(lzin);
    if (!Insert(theNew))
      myTZones.Append(theNew);
  }
  return Inserted;
}

void Intf_Interference::Insert(const Intf_SectionPoint& pdeb, const Intf_SectionPoint& pfin)
{
  bool              Inserted = false;
  int               TheLS    = 0;
  bool              Begin    = false;
  Intf_SectionPoint TheBout(pfin);
  int               ils, nd, nf;

  for (ils = 1; ils <= mySLines.Length(); ils++)
  {
    Intf_SectionLine& SL = mySLines(ils);
    nd                   = SL.IsEnd(pdeb);
    nf                   = SL.IsEnd(pfin);
    if (nd == 1)
    {
      if (nf > 1)
        SL.Close();
      Inserted = true;
      TheLS    = ils;
      Begin    = true;
      break;
    }
    else if (nd > 1)
    {
      if (nf == 1)
        SL.Close();
      Inserted = true;
      TheLS    = ils;
      Begin    = false;
      break;
    }
    else if (nf == 1)
    {
      Inserted = true;
      TheLS    = ils;
      Begin    = true;
      TheBout  = pdeb;
      break;
    }
    else if (nf > 1)
    {
      Inserted = true;
      TheLS    = ils;
      Begin    = false;
      TheBout  = pdeb;
      break;
    }
  }

  if (!Inserted)
  {
    Intf_SectionLine LaLS;
    LaLS.Append(pdeb);
    LaLS.Append(pfin);
    mySLines.Append(LaLS);
  }
  else
  {
    nd = 0;
    for (ils = 1; ils <= mySLines.Length(); ils++)
    {
      if (ils != TheLS)
      {
        nd = mySLines(ils).IsEnd(TheBout);
        if (nd == 1)
        {
          if (Begin)
          {
            mySLines(TheLS).Reverse();
          }
          mySLines(ils).Prepend(mySLines(TheLS));
          break;
        }
        else if (nd > 1)
        {
          if (!Begin)
          {
            mySLines(TheLS).Reverse();
          }
          mySLines(ils).Append(mySLines(TheLS));
          break;
        }
      }
    }
    if (nd > 0)
    {
      mySLines.Remove(TheLS);
    }
    else
    {
      if (Begin)
        mySLines(TheLS).Prepend(TheBout);
      else
        mySLines(TheLS).Append(TheBout);
    }
  }
}

bool Intf_Interference::Contains(const Intf_SectionPoint& LePnt) const
{

  for (int l = 1; l <= mySLines.Length(); l++)
  {
    if (mySLines(l).Contains(LePnt))
      return true;
  }
  for (int t = 1; t <= myTZones.Length(); t++)
  {

    if (myTZones(t).Contains(LePnt))
      return true;
  }
  return false;
}

void Intf_Interference::Dump() const
{
  std::cout << "Mes SectionPoint :" << std::endl;
  for (int p = 1; p <= mySPoins.Length(); p++)
  {
    mySPoins(p).Dump(2);
  }
  std::cout << "Mes SectionLine :" << std::endl;
  for (int l = 1; l <= mySLines.Length(); l++)
  {
    mySLines(l).Dump(2);
  }
  std::cout << "Mes TangentZone :" << std::endl;
  for (int t = 1; t <= myTZones.Length(); t++)
  {
    myTZones(t).Dump(2);
  }
}

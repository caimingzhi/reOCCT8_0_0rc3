#include <Standard_GUID.hpp>
#include <Standard_Type.hpp>
#include <TCollection_ExtendedString.hpp>
#include <TDF.hpp>
#include <TFunction_Driver.hpp>
#include <NCollection_DataMap.hpp>
#include <TFunction_DriverTable.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TFunction_DriverTable, Standard_Transient)

static occ::handle<TFunction_DriverTable> DT;

occ::handle<TFunction_DriverTable> TFunction_DriverTable::Get()
{
  if (DT.IsNull())
    DT = new TFunction_DriverTable;
  return DT;
}

TFunction_DriverTable::TFunction_DriverTable() = default;

bool TFunction_DriverTable::AddDriver(const Standard_GUID&                 guid,
                                      const occ::handle<TFunction_Driver>& driver,
                                      const int                            thread)
{
  if (thread == 0)
    return myDrivers.Bind(guid, driver);
  else if (thread > 0)
  {
    if (myThreadDrivers.IsNull())
    {

      myThreadDrivers =
        new NCollection_HArray1<NCollection_DataMap<Standard_GUID, occ::handle<TFunction_Driver>>>(
          1,
          thread);
    }
    else if (myThreadDrivers->Upper() < thread)
    {

      occ::handle<
        NCollection_HArray1<NCollection_DataMap<Standard_GUID, occ::handle<TFunction_Driver>>>>
        new_dt = new NCollection_HArray1<
          NCollection_DataMap<Standard_GUID, occ::handle<TFunction_Driver>>>(1, thread);

      int i = 1, old_upper = myThreadDrivers->Upper();
      for (; i <= old_upper; i++)
      {
        const NCollection_DataMap<Standard_GUID, occ::handle<TFunction_Driver>>& t =
          myThreadDrivers->Value(i);
        NCollection_DataMap<Standard_GUID, occ::handle<TFunction_Driver>>::Iterator itrt(t);
        for (; itrt.More(); itrt.Next())
        {
          new_dt->ChangeValue(i).Bind(itrt.Key(), itrt.Value());
        }
      }
      myThreadDrivers = new_dt;
    }
    return myThreadDrivers->ChangeValue(thread).Bind(guid, driver);
  }
  return false;
}

bool TFunction_DriverTable::HasDriver(const Standard_GUID& guid, const int thread) const
{
  if (thread == 0)
    return myDrivers.IsBound(guid);
  else if (thread > 0 && !myThreadDrivers.IsNull() && myThreadDrivers->Upper() >= thread)
    return myThreadDrivers->Value(thread).IsBound(guid);
  return false;
}

bool TFunction_DriverTable::FindDriver(const Standard_GUID&           guid,
                                       occ::handle<TFunction_Driver>& driver,
                                       const int                      thread) const
{
  if (thread == 0)
  {
    if (myDrivers.IsBound(guid))
    {
      driver = myDrivers.Find(guid);
      return true;
    }
  }
  else if (thread > 0 && !myThreadDrivers.IsNull() && myThreadDrivers->Upper() >= thread)
  {
    if (myThreadDrivers->Value(thread).IsBound(guid))
    {
      driver = myThreadDrivers->Value(thread).Find(guid);
      return true;
    }
  }
  return false;
}

Standard_OStream& TFunction_DriverTable::Dump(Standard_OStream& anOS) const
{
  NCollection_DataMap<Standard_GUID, occ::handle<TFunction_Driver>>::Iterator itr(myDrivers);
  for (; itr.More(); itr.Next())
  {
    itr.Key().ShallowDump(anOS);
    anOS << "\t";
    TCollection_ExtendedString es;
    TDF::ProgIDFromGUID(itr.Key(), es);
    anOS << es << "\n";
  }
  return anOS;
}

bool TFunction_DriverTable::RemoveDriver(const Standard_GUID& guid, const int thread)
{
  if (thread == 0)
    return myDrivers.UnBind(guid);
  else if (thread > 0 && !myThreadDrivers.IsNull() && myThreadDrivers->Upper() >= thread)
    myThreadDrivers->ChangeValue(thread).UnBind(guid);
  return false;
}

void TFunction_DriverTable::Clear()
{
  myDrivers.Clear();
  if (!myThreadDrivers.IsNull())
    myThreadDrivers.Nullify();
}

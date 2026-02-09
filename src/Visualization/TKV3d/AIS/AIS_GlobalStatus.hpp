#pragma once

#include <Standard.hpp>

#include <Prs3d_Drawer.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_List.hpp>
#include <Standard_Transient.hpp>

class AIS_GlobalStatus : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(AIS_GlobalStatus, Standard_Transient)
public:
  Standard_EXPORT AIS_GlobalStatus();

  int DisplayMode() const { return myDispMode; }

  void SetDisplayMode(const int theMode) { myDispMode = theMode; }

  bool IsHilighted() const { return myIsHilit; }

  void SetHilightStatus(const bool theStatus) { myIsHilit = theStatus; }

  void SetHilightStyle(const occ::handle<Prs3d_Drawer>& theStyle) { myHiStyle = theStyle; }

  const occ::handle<Prs3d_Drawer>& HilightStyle() const { return myHiStyle; }

  const NCollection_List<int>& SelectionModes() const { return mySelModes; }

  bool IsSModeIn(int theMode) const { return mySelModes.Contains(theMode); }

  bool AddSelectionMode(const int theMode)
  {
    if (!mySelModes.Contains(theMode))
    {
      mySelModes.Append(theMode);
      return true;
    }
    return false;
  }

  bool RemoveSelectionMode(const int theMode) { return mySelModes.Remove(theMode); }

  void ClearSelectionModes() { mySelModes.Clear(); }

  bool IsSubIntensityOn() const { return mySubInt; }

  void SetSubIntensity(bool theIsOn) { mySubInt = theIsOn; }

private:
  NCollection_List<int>     mySelModes;
  occ::handle<Prs3d_Drawer> myHiStyle;
  int                       myDispMode;
  bool                      myIsHilit;
  bool                      mySubInt;
};

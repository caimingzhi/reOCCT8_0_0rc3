#pragma once


#include <Standard.hpp>

#include <Prs3d_Drawer.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_List.hpp>
#include <Standard_Transient.hpp>

//! Stores information about objects in graphic context:
class AIS_GlobalStatus : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(AIS_GlobalStatus, Standard_Transient)
public:
  //! Default constructor.
  Standard_EXPORT AIS_GlobalStatus();

  //! Returns the display mode.
  int DisplayMode() const { return myDispMode; }

  //! Sets display mode.
  void SetDisplayMode(const int theMode) { myDispMode = theMode; }

  //! Returns TRUE if object is highlighted
  bool IsHilighted() const { return myIsHilit; }

  //! Sets highlighted state.
  void SetHilightStatus(const bool theStatus) { myIsHilit = theStatus; }

  //! Changes applied highlight style for a particular object
  void SetHilightStyle(const occ::handle<Prs3d_Drawer>& theStyle) { myHiStyle = theStyle; }

  //! Returns applied highlight style for a particular object
  const occ::handle<Prs3d_Drawer>& HilightStyle() const { return myHiStyle; }

  //! Returns active selection modes of the object.
  const NCollection_List<int>& SelectionModes() const { return mySelModes; }

  //! Return TRUE if selection mode was registered.
  bool IsSModeIn(int theMode) const { return mySelModes.Contains(theMode); }

  //! Add selection mode.
  bool AddSelectionMode(const int theMode)
  {
    if (!mySelModes.Contains(theMode))
    {
      mySelModes.Append(theMode);
      return true;
    }
    return false;
  }

  //! Remove selection mode.
  bool RemoveSelectionMode(const int theMode) { return mySelModes.Remove(theMode); }

  //! Remove all selection modes.
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


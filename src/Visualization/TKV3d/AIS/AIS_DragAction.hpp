#pragma once


//! Dragging action.
enum AIS_DragAction
{
  AIS_DragAction_Start,     //!< (try) start dragging object
  AIS_DragAction_Confirmed, //!< dragging interaction is confirmed.
  AIS_DragAction_Update,    //!< perform dragging (update position)
  AIS_DragAction_Stop,      //!< stop dragging (save position)
  AIS_DragAction_Abort,     //!< abort dragging (restore initial position)
};


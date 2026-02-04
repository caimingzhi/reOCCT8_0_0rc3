#pragma once


//! Some fields of an IGES entity may be
//! - Undefined
//! - Defined as a single item
//! - Defined as a list of items.
//! A typical example, which presents this kind of variation,
//! is a level number.
//! This enumeration allows you to identify which of the above is the case.
//! The semantics of the terms is as follows:
//! - DefNone indicates that the list is empty (there is not
//! even a single item).
//! - DefOne indicates that the list contains a single item.
//! - DefSeveral indicates that the list contains several items.
//! - ErrorOne indicates that the list contains one item, but
//! that this item is incorrect
//! - ErrorSeveral indicates that the list contains several
//! items, but that at least one of them is incorrect.
enum IGESData_DefList
{
  IGESData_DefNone,
  IGESData_DefOne,
  IGESData_DefSeveral,
  IGESData_ErrorOne,
  IGESData_ErrorSeveral
};


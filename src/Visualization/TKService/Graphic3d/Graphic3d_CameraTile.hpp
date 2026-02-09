#pragma once

#include <NCollection_Vec2.hpp>
#include <Standard_TypeDef.hpp>
#include <Standard_Integer.hpp>
#include <Standard_OStream.hpp>

class Graphic3d_CameraTile
{
public:
  NCollection_Vec2<int> TotalSize;
  NCollection_Vec2<int> TileSize;

  NCollection_Vec2<int> Offset;
  bool                  IsTopDown;

public:
  Graphic3d_CameraTile()
      : IsTopDown(false)
  {
  }

  bool IsValid() const
  {
    return TotalSize.x() > 0 && TotalSize.y() > 0 && TileSize.x() > 0 && TileSize.y() > 0;
  }

  NCollection_Vec2<int> OffsetLowerLeft() const
  {
    return NCollection_Vec2<int>(Offset.x(),
                                 !IsTopDown ? Offset.y() : TotalSize.y() - Offset.y() - 1);
  }

  Graphic3d_CameraTile Cropped() const
  {
    Graphic3d_CameraTile aTile = *this;
    if (!IsValid())
    {
      return aTile;
    }

    aTile.Offset.x() = (std::max)(Offset.x(), 0);
    aTile.Offset.y() = (std::max)(Offset.y(), 0);

    const int anX      = (std::min)(Offset.x() + TileSize.x(), TotalSize.x());
    const int anY      = (std::min)(Offset.y() + TileSize.y(), TotalSize.y());
    aTile.TileSize.x() = anX - Offset.x();
    aTile.TileSize.y() = anY - Offset.y();
    return aTile;
  }

  bool operator==(const Graphic3d_CameraTile& theOther) const
  {
    const NCollection_Vec2<int> anOffset1 = OffsetLowerLeft();
    const NCollection_Vec2<int> anOffset2 = theOther.OffsetLowerLeft();
    return TotalSize.x() == theOther.TotalSize.x() && TotalSize.y() == theOther.TotalSize.y()
           && TileSize.x() == theOther.TileSize.x() && TileSize.y() == theOther.TileSize.y()
           && anOffset1.x() == anOffset2.x() && anOffset1.y() == anOffset2.y();
  }

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;
};

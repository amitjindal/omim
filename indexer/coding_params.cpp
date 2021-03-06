#include "indexer/coding_params.hpp"
#include "indexer/point_to_int64.hpp"

#include "geometry/pointu_to_uint64.hpp"


namespace serial
{
  CodingParams::CodingParams()
    : m_BasePointUint64(0), m_CoordBits(POINT_COORD_BITS)
  {
     m_BasePoint = m2::Uint64ToPointU(m_BasePointUint64);
  }

  CodingParams::CodingParams(uint8_t coordBits, m2::PointD const & pt)
    : m_CoordBits(coordBits)
  {
    SetBasePoint(pt);
  }

  CodingParams::CodingParams(uint8_t coordBits, uint64_t basePointUint64)
    : m_BasePointUint64(basePointUint64), m_CoordBits(coordBits)
  {
    m_BasePoint = m2::Uint64ToPointU(m_BasePointUint64);
  }

  void CodingParams::SetBasePoint(m2::PointD const & pt)
  {
    m_BasePoint = PointD2PointU(pt, m_CoordBits);
    m_BasePointUint64 = m2::PointUToUint64(m_BasePoint);
  }
}

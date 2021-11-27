#include "camera.h"

Camera::Camera()
{}

Vec2f Camera::worldPosToScreenPos(const Vec2f& worldPos) const
{
  Vec2f dPos = worldPos - m_position;

  // TOOD rotate dPos

  Vec2f scaled = dPos * m_scale;

  Vec2f offset = Vec2f(m_screenCenter.x + scaled.x,
		       m_screenCenter.y - scaled.y);

  return offset;
}

#ifndef camera_h
#define camera_h

#include "bdg_math.h"

class Camera {
 public:
  Camera();

  // in pixels
  void setScreenSize(Vec2f ss) { m_screenSize = ss; m_screenCenter = ss * 0.5f ; }

  const Vec2f& getPosition() const { return m_position; };
  void setPosition(Vec2f inPos) { m_position = inPos; }

  // scale is measured in pixels/meter
  float getScale() const { return m_scale; } ;
  void setScale(float s) { m_scale = fclamp(s, m_minScale, m_maxScale); }

  float getRotation() const { return m_rotation; };
  void setRotation(float r) { m_rotation = r; }

  Vec2f worldPosToScreenPos(const Vec2f& worldPos) const;

  float worldAngleToScreenAngle(float worldAngle) const;

 private:
  Vec2f m_position = Vec2f(0, 0);

  // in pixels/meter
  float m_scale;
  const float m_maxScale = 50.0f;
  const float m_minScale = 0.01f;

  // in radians that we rotate the world ccw around us (or us cw in the world)
  float m_rotation;

  Vec2f m_screenSize = Vec2f(0, 0);
  Vec2f m_screenCenter = Vec2f(0, 0);
};

#endif // camera_h

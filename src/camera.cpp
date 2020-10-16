#include "../include/camera.hpp"

#include "../include/globals.hpp"
void Camera::Move(const float& dt, sf::Vector2f& mouse){

  sf::Vector2f dist = mouse - m_origin;

  if(!m_io.WantCaptureMouse&& !m_moveBoundary.contains(mouse) && mouse.x >= 0 && mouse.x < m_widht && mouse.y >= 0 && mouse.y < m_height){
    // vertical
    // e: y = m_moveBoundary.top + m_moveBoundary.height
    // f: - dist.y * x + dist.x * y = -dist.y * m_origin.x + dist.x * m_origin.y;
    // f: - dist.y * x + dist.x * (m_moveBoundary.top + m_moveBoundary.height) = -dist.y * m_origin.x + dist.x * m_origin.y;
    // f: - dist.y * x = -dist.y * m_origin.x + dist.x * ( m_origin.y - m_moveBoundary.top - m_moveBoundary.height) ;
    // f: x = m_origin.x - dist.x * ( m_origin.y - m_moveBoundary.top - m_moveBoundary.height)/dist.y ;

    int x = m_origin.x - dist.x * (m_origin.y - m_moveBoundary.top - m_moveBoundary.height)/dist.y;
    int y = m_moveBoundary.top + m_moveBoundary.height;
    if(x >= m_moveBoundary.left && x < m_moveBoundary.left + m_moveBoundary.width){

      // g: y = m_height
      // f: - dist.y * x + dist.x * y = -dist.y * m_origin.x + dist.x * m_origin.y;
      // f: - dist.y * x + dist.x * m_height = -dist.y * m_origin.x + dist.x * m_origin.y;
      // f: - dist.y * x = -dist.y * m_origin.x + dist.x * ( m_origin.y - m_height)
      // f: x = m_origin.x - dist.x * ( m_origin.y - m_height) / dist.y
      int x2 = m_origin.x - dist.x * ( m_origin.y - m_height) / dist.y;
      int y2 = m_height;

      if(mouse.y < m_moveBoundary.top){
        x = m_widht - x;
        y = m_height - y;
        x2 = m_widht - x2;
        y2 = m_height - y2;
      }

      dist = mouse - sf::Vector2f(x, y);

#if CAMERA_DEBUG
      m_window.setView(m_window.getDefaultView());
      sf::VertexArray line(sf::PrimitiveType::Lines, 2);
      line[0].position = sf::Vector2f(x, y);
      line[0].color = sf::Color::Green;
      line[1].position = sf::Vector2f(x, y) + dist;
      line[1].color = sf::Color::Green;
      m_window.draw(line);
      m_window.setView(m_view);
#endif // CAMERA_DEBUG
      float innerLen = sqrt((x-x2) * (x-x2) + (y-y2) * (y-y2));

      dist /= innerLen;

      dist *= m_maxCameraSpeed * dt;
      m_view.move(dist);
      m_window.setView(m_view);

    }else{

      // horizontal
      // e: x = m_moveBoundary.left
      // f: - dist.y * x + dist.x * y = -dist.y * m_origin.x + dist.x * m_origin.y
      // f: - dist.y * m_moveBoundary.left + dist.x * y = -dist.y * m_origin.x + dist.x * m_origin.y
      // f: dist.x * y = -dist.y * m_origin.x + dist.x * m_origin.y + dist.y * m_moveBoundary.left
      // f: y = -dist.y * m_origin.x / dist.x + m_origin.y + dist.y * m_moveBoundary.left / dist.x
      // f: y = m_origin.y - dist.y( m_origin.x / dist.x - m_moveBoundary.left / dist.x)
      // f: y = m_origin.y - dist.y( m_origin.x - m_moveBoundary.left)/ dist.x
      y = m_origin.y - dist.y * ( m_origin.x - m_moveBoundary.left) / dist.x;
      x = m_moveBoundary.left;

      if(y < m_moveBoundary.top + m_moveBoundary.height && y >= m_moveBoundary.top){

        // e: x = 0
        // f: - dist.y * x + dist.x * y = -dist.y * m_origin.x + dist.x * m_origin.y
        // f: dist.x * y = -dist.y * m_origin.x + dist.x * m_origin.y
        // f:
        int y2 = m_origin.y - dist.y * m_origin.x / dist.x;
        int x2 = 0;

        if(mouse.x > m_moveBoundary.left + m_moveBoundary.width){
          x = m_widht - x;
          y = m_height - y;
          x2 = m_widht - x2;
          y2 = m_height - y2;
        }

        dist = mouse - sf::Vector2f(x, y);

#if CAMERA_DEBUG
        m_window.setView(m_window.getDefaultView());
        sf::VertexArray line(sf::PrimitiveType::Lines, 2);
        line[0].position = sf::Vector2f(x, y);
        line[0].color = sf::Color::Green;
        line[1].position = sf::Vector2f(x, y) + dist;
        line[1].color = sf::Color::Green;
        m_window.draw(line);
        m_window.setView(m_view);
#endif // CAMERA_DEBUG

        float innerLen = sqrt((x-x2) * (x-x2) + (y-y2) * (y-y2));

        dist /= innerLen;

        dist *= m_maxCameraSpeed * dt;
        m_view.move(dist);
        m_window.setView(m_view);
      }
    }
  }

#if CAMERA_DEBUG
  m_window.setView(m_window.getDefaultView());
  static bool moveInside_init = true;
  static sf::RectangleShape moveInside({m_moveBoundary.width, m_moveBoundary.height});
  if(moveInside_init){
    moveInside.setPosition(m_moveBoundary.left, m_moveBoundary.top);
    sf::Color moveInside_color(10, 201, 50, 85);
    moveInside.setFillColor(moveInside_color);
    puts("init");
    moveInside_init = false;
  }
  m_window.draw(moveInside);
  m_window.setView(m_view);
#endif // CAMERA_DEBUG

}




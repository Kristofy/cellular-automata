#ifndef CAMERA_HPP_INCLUDED
#define CAMERA_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include "../Imgui/imgui.h"

#define CAMERA_DEBUG 0

class Camera{
  public:
    Camera(float width, float height, sf::Vector2f& origin, sf::RenderWindow& window, ImGuiIO& io)
    :m_widht(width), m_height(height), m_origin(origin), m_window(window), m_io(io),
    m_view(m_origin, sf::Vector2f(m_widht, m_height)),
    m_moveBoundary(m_view.getCenter() - sf::Vector2f(m_widht * 0.75f, m_height * 0.75f)/2.0f, sf::Vector2f(m_widht * 0.75f, m_height * 0.75f))
    {
      m_window.setView(m_view);
      m_maxCameraSpeed = 400.0f;
    }

    void Move(const float& dt, sf::Vector2f& mouse);
    const sf::Vector2f& getCenter(){
      return m_view.getCenter();
    }

  private:
    float m_widht, m_height;
    sf::Vector2f m_origin;
    sf::RenderWindow& m_window;
    ImGuiIO& m_io;
    sf::View m_view;
    sf::FloatRect m_moveBoundary;
    float m_maxCameraSpeed;
};

#endif // CAMERA_HPP_INCLUDED

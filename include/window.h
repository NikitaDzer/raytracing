#ifndef WINDOW_H
#define WINDOW_H


#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>


static const     char     WINDOW_NAME[] = "Raytracing app";
static constexpr unsigned WINDOW_WIDTH  = 1920 / 2;
static constexpr unsigned WINDOW_HEIGHT = 1080;

static constexpr sf::Keyboard::Key KEY_EXIT        = sf::Keyboard::Key::Q;
static const     sf::Color         COLOR_BG        = sf::Color::Black;
static constexpr unsigned          FRAMERATE_LIMIT = 120;


void init_window( sf::RenderWindow &window);


#endif // WINDOW_H

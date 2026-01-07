#include "Level.h"

Level::Level(sf::RenderWindow& hwnd, Input& in) :
	BaseLevel(hwnd, in)
{
	// initialise game objects
	m_snake.setRadius(20.f);
	m_snake.setFillColor(sf::Color::Green);

	// put the snake in the middle of the screen.
	sf::Vector2u window_size = m_window.getSize();
	m_snake.setPosition({ 
		window_size.x / 2.f - m_snake.getRadius(), 
		window_size.y / 2.f - m_snake.getRadius()
	});
}

// handle user input
void Level::handleInput(float dt)
{
	// move the snake.
	if (m_input.isKeyDown(sf::Keyboard::Scancode::W))
	{
		m_direction = SnakeDirection::UP;
	}
	if (m_input.isKeyDown(sf::Keyboard::Scancode::S))
	{
		m_direction = SnakeDirection::DOWN;
	}
	if (m_input.isKeyDown(sf::Keyboard::Scancode::A))
	{
		m_direction = SnakeDirection::LEFT;
	}
	if (m_input.isKeyDown(sf::Keyboard::Scancode::D))
	{
		m_direction = SnakeDirection::RIGHT;
	}

}

// Update game objects
void Level::update(float dt)
{
	// move the snake.
	switch (m_direction)
	{
	case SnakeDirection::UP:
		m_snake.move({ 0, -m_snakeSpeed * dt });
		break;
	case SnakeDirection::DOWN:
		m_snake.move({ 0, m_snakeSpeed * dt });
		break;
	case SnakeDirection::LEFT:
		m_snake.move({ -m_snakeSpeed * dt, 0 });
		break;
	case SnakeDirection::RIGHT:
		m_snake.move({ m_snakeSpeed * dt, 0 });
		break;
	}

	// check for wall collision
	sf::Vector2u window_size = m_window.getSize();
	sf::Vector2f snake_pos = m_snake.getPosition();
	if (snake_pos.x < 0 || snake_pos.y < 0 ||
		snake_pos.x + 2 * m_snake.getRadius() > window_size.x ||
		snake_pos.y + 2 * m_snake.getRadius() > window_size.y)
	{
		// reset to middle
		m_snake.setPosition({
		window_size.x / 2.f - m_snake.getRadius(),
		window_size.y / 2.f - m_snake.getRadius()
			});
	}

}

// Render level
void Level::render()
{
	beginDraw();
	m_window.draw(m_snake);
	endDraw();
}


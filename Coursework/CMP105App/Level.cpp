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

	// initialise the food
	m_food.setRadius(5.f);
	m_food.setFillColor(sf::Color::Yellow);
	spawnFood();
}

void Level::spawnFood()
{
	sf::Vector2u window_size = m_window.getSize();
	float x = rand() % window_size.x;
	float y = rand() % window_size.y;
	m_food.setPosition({x, y});
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
	if (m_isGameOver) return;


	m_timeTaken += dt;

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
		m_isGameOver = true;

		std::cout << "Unlucky! Game Over\nPoints: " << m_foodEaten;
		std::cout << "\nTime taken: " << m_timeTaken;

		// OLD:
		//// reset to middle
		//m_snake.setPosition({
		//window_size.x / 2.f - m_snake.getRadius(),
		//window_size.y / 2.f - m_snake.getRadius()
		//	});
	}

	// check for food collision
	float radii_sum = m_snake.getRadius() + m_food.getRadius();
	sf::Vector2f snake_center = m_snake.getPosition() + sf::Vector2f(m_snake.getRadius(), m_snake.getRadius());
	sf::Vector2f food_center = m_food.getPosition() + sf::Vector2f(m_food.getRadius(), m_food.getRadius());
	float x_diff = snake_center.x - food_center.x;
	float y_diff = snake_center.y - food_center.y;

	if (radii_sum * radii_sum > (x_diff * x_diff) + (y_diff * y_diff))
	{
		// they are colliding
		m_snakeSpeed *= 1.2f;
		spawnFood();
		std::cout << "yum\n";
		m_foodEaten++;
	}


}

// Render level
void Level::render()
{
	beginDraw();
	m_window.draw(m_food);
	m_window.draw(m_snake);

	endDraw();
}


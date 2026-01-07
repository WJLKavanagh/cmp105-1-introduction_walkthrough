#pragma once

#include "Framework/BaseLevel.h"

class Level : BaseLevel{
public:
	Level(sf::RenderWindow& window, Input& input);
	~Level() override = default;

	void handleInput(float dt) override;
	void update(float dt);
	void render();

private:
	// Default functions for rendering to the screen.
	void spawnFood();


	// Default variables for level class.
	enum class SnakeDirection { UP, DOWN, LEFT, RIGHT};

	sf::CircleShape m_snake;
	sf::CircleShape m_food;
	float m_snakeSpeed = 300.0f;
	SnakeDirection m_direction;
	int m_foodEaten = 0;
	float m_timeTaken = 0.f;
	bool m_isGameOver = false;

};
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <stdlib.h>
#include <math.h>

#include <iostream>
#include <sstream>

const int MAP_WIDTH = 32;
const int MAP_HEIGHT = 24;
const int CELL = 32;
const int WIDTH = MAP_WIDTH * CELL;
const int HEIGHT = MAP_HEIGHT * CELL;

int Map[MAP_HEIGHT][MAP_WIDTH] =
{
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,1},
		{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,0,0,0,0,0,2,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,0,0,0,0,0,2,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,1},
		{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,0,0,0,0,0,2,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1},
		{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,1},
		{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1},
		{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,1},
		{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1},
		{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,1},
		{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,1},
		{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

sf::Vector2f rotate(sf::Vector2f vec, float value) {
	return sf::Vector2f(
		vec.x * std::cos(value) - vec.y * std::sin(value),
		vec.x * std::sin(value) + vec.y * std::cos(value)
	);
}

bool check(const sf::Vector2f pos, const sf::Vector2f block);

int main()
{

	sf::Vector2f position(22.f, 12.f);
	sf::Vector2f direction(-1.f, 0.f);
	sf::Vector2f cameraPlane(0.f, 0.66f);
	sf::Vector2f block(0.375, 0.375);
	float moveSpeed = 5.f;
	float rotateSpeed = 3.f;

	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML", sf::Style::Default);

	window.setFramerateLimit(60);
	sf::Clock clock = sf::Clock();
	float dt = 0.f;

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			// Escape key: exit
			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
				window.close();
		}

		window.clear();

		dt = clock.restart().asSeconds();

		float moveForward = 0.f;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) moveForward = 1.f;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) moveForward = -1.f;

		if (moveForward != 0.f)
		{
			sf::Vector2f veclocity = direction * moveSpeed * moveForward * dt;
			if (check(sf::Vector2f(position.x + veclocity.x, position.y), block)) position.x += veclocity.x;
			if (check(sf::Vector2f(position.x, position.y + veclocity.y), block)) position.y += veclocity.y;
		}

		float rotateDir = 0.f;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) rotateDir = 1.f;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) rotateDir = -1.f;

		if (rotateDir != 0.f)
		{
			float rotateAngle = rotateSpeed * rotateDir * dt;
			direction = rotate(direction, rotateAngle);
			cameraPlane = rotate(cameraPlane, rotateAngle);
		}

		for (int x = 0; x < WIDTH; x++)
		{
			float cameraX = 2 * x / float(WIDTH) - 1.f;
			sf::Vector2f rayPos = position;
			sf::Vector2f rayDir = direction + cameraPlane * cameraX;

			sf::Vector2i mapPos = sf::Vector2i(position);

			
			sf::Vector2f sideDist;
			/*sf::Vector2f deltaDist(
				sqrt(1.0f + (rayDir.y * rayDir.y) / (rayDir.x * rayDir.x)),
				sqrt(1.0f + (rayDir.x * rayDir.x) / (rayDir.y * rayDir.y))
			);*/

			sf::Vector2f deltaDist(abs(1.f / rayDir.x), abs(1.f / rayDir.y));
			float perpWallDist = 0.f;

			sf::Vector2i step;

			int hit = 0; 
			int side; 

			if (rayDir.x < 0.0f) {
				step.x = -1;
				sideDist.x = (rayPos.x - mapPos.x) * deltaDist.x;
			}
			else {
				step.x = 1;
				sideDist.x = (mapPos.x + 1.0f - rayPos.x) * deltaDist.x;
			}
			if (rayDir.y < 0.0f) {
				step.y = -1;
				sideDist.y = (rayPos.y - mapPos.y) * deltaDist.y;
			}
			else {
				step.y = 1;
				sideDist.y = (mapPos.y + 1.0f - rayPos.y) * deltaDist.y;
			}

			while (hit == 0)
			{
				if (sideDist.x < sideDist.y)
				{
					sideDist.x += deltaDist.x;
					mapPos.x += step.x;
					side = 0;
				}
				else
				{
					sideDist.y += deltaDist.y;
					mapPos.y += step.y;
					side = 1;
				}
				//Check if ray has hit a wall
				if (Map[mapPos.x][mapPos.y] > 0) hit = 1;
			}

			//Calculate distance projected on camera direction (oblique distance will give fisheye effect!)
			if (side == 0)
				perpWallDist = fabs((mapPos.x - rayPos.x + (1 - step.x) / 2) / rayDir.x);
			else
				perpWallDist = fabs((mapPos.y - rayPos.y + (1 - step.y) / 2) / rayDir.y);

			//Calculate height of line to draw on screen
			int lineHeight = abs(int(WIDTH / perpWallDist));

			//calculate lowest and highest pixel to fill in current stripe
			int drawStart = -lineHeight / 2 + WIDTH / 2;
			if (drawStart < 0)drawStart = 0;
			int drawEnd = lineHeight / 2 + WIDTH / 2;
			if (drawEnd >= WIDTH)drawEnd = WIDTH - 1;

			//choose wall color
			sf::Color color;
			switch (Map[mapPos.x][mapPos.y])
			{
			case 1:  color = sf::Color::Red;  break; //red
			case 2:  color = sf::Color::Green;  break; //green
			case 3:  color = sf::Color::Blue;   break; //blue
			case 4:  color = sf::Color::White;  break; //white
			default: color = sf::Color::Yellow; break; //yellow
			}

			//give x and y sides different brightness
			if (side == 1) {
				color = sf::Color(color.r / 2, color.g / 2, color.b / 2);
			}

			//draw the pixels of the stripe as a vertical line
			//verLine(x, drawStart, drawEnd, color);

			sf::Vertex line[2] =
			{
					sf::Vertex(sf::Vector2f(x, drawStart), color),
					sf::Vertex(sf::Vector2f(x, drawEnd), color)
			};
			window.draw(line, 2, sf::Lines);

		}


		window.display();
		window.clear();
	}
	return EXIT_SUCCESS;
}

bool check(const sf::Vector2f pos, const sf::Vector2f block)
{
	sf::Vector2i front = sf::Vector2i(pos - block);
	sf::Vector2i back = sf::Vector2i(pos + block);
	if (front.x < 0 || front.y < 0 || back.x > MAP_WIDTH || back.y > MAP_HEIGHT) return false;

	for (int i = front.y; i <= back.y; ++i)
	{
		for (int j = front.x; j <= back.x; ++j)
		{
			if (Map[j][i] != 0)
				return false;
		}
	}
	return true;
}

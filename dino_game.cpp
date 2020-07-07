#include "dino_game.h"

void dino_game::set_window()
{
	this->window = nullptr;
	this->videoMode.height = 600;
	this->videoMode.width = 800;
	this->window = new RenderWindow(this->videoMode, "Dino Game", Style::Default);
	this->window->setFramerateLimit(60);
}

void dino_game::set_text()
{
	this->font.loadFromFile("arial.ttf");
	this->points_text.setCharacterSize(15);
	this->points_text.setFillColor(Color::Color(73, 73, 73));
	this->points_text.setFont(this->font);
	this->points_text.setString("Sample points text");
	this->points_text.setPosition(Vector2f(this->window->getSize().x - 100.f, 15.f));
}

void dino_game::load_textures()
{
	this->playerTex.loadFromFile("dino.png");
	this->player.setTexture(this->playerTex);

	this->cloudTex.loadFromFile("cloud.png");
	this->cloud.setTexture(this->cloudTex);

	this->cactusTex.loadFromFile("cactus.png");
	this->cactus.setTexture(this->cactusTex);
}

void dino_game::set_floor()
{
	this->outline.setSize(Vector2f(this->window->getSize().x, 2.5f));
	this->outline.setFillColor(Color::Color(73, 73, 73));
	this->outline.setPosition(0.f, this->window->getSize().y - 200.f);
}

void dino_game::set_player()
{
	this->verticalV = 0.f;
	this->jumpDelay = 0;
	this->points = 0;
	this->is_space = false;
	this->player.setScale(0.5, 0.5);
	this->player.setPosition(this->window->getSize().x / 3 - this->player.getGlobalBounds().width, 400.f - this->player.getGlobalBounds().height);
}

void dino_game::up()
{
	if (this->jumpDelay < 35)
		this->jumpDelay++;
	if (this->jumpDelay >= 35)
	{
		if (Keyboard::isKeyPressed(Keyboard::Space))
		{
			this->verticalV = -16.f;
			this->jumpDelay = 0;
		}
	}
}

void dino_game::jump()
{
	this->player.move(0.f, this->verticalV);
	if (this->verticalV < 0.f)
		this->verticalV += 0.3f;
	this->verticalV++;
	if (this->player.getPosition().y < 200.f)
		this->verticalV += 0.2f;
	if (this->player.getPosition().y + this->player.getGlobalBounds().height >= 400.f)
	{
		this->player.setPosition(this->player.getPosition().x, 400.f - this->player.getGlobalBounds().height);
	}
}

void dino_game::set_cloud()
{
	this->cloudDelay = 0;
	this->cloud.setPosition(this->player.getPosition().x - 100.f, this->player.getPosition().y - 100.f);
}

void dino_game::spawn_cloud()
{
	this->cloud.setPosition(this->window->getSize().x + this->cloud.getGlobalBounds().width,
		rand() % int(this->outline.getPosition().y - this->cloud.getGlobalBounds().height));
	this->clouds.push_back(this->cloud);
}

void dino_game::move_clouds()
{
	for (size_t i = 0; i < this->clouds.size(); i++)
	{
		this->clouds[i].move(-5.f, 0.f);
		if (this->clouds[i].getPosition().x + this->clouds[i].getGlobalBounds().width <= 0.f)
			this->clouds.erase(this->clouds.begin() + i);
	}
}

void dino_game::add_cloud()
{
	if (this->cloudDelay < 60)
		this->cloudDelay++;
	if (this->cloudDelay >= 60)
	{
		this->spawn_cloud();
		this->cloudDelay = 0;
	}
}

void dino_game::set_cactus()
{
	this->maxCactusDelay = 180;
	this->cactusDelay = this->maxCactusDelay;
	this->cactus.setScale(0.2, 0.2);
	this->cactus.setPosition(this->window->getSize().x, 400.f - this->cactus.getGlobalBounds().height);
}

void dino_game::add_cactus()
{
	if (this->cactusDelay < this->maxCactusDelay)
		this->cactusDelay++;
	if (this->cactusDelay >= this->maxCactusDelay)
	{
		this->cactusDelay = 0;
		this->spawn_cactus();
	}
}

void dino_game::move_cactuses()
{
	for (size_t i = 0; i < this->cactuses.size(); i++)
	{
		this->cactuses[i].move(-10.f, 0.f);
		if (this->cactuses[i].getPosition().x + this->cactuses[i].getGlobalBounds().width <= 0.f)
			this->cactuses.erase(this->cactuses.begin() + i);
	}
}

void dino_game::collisions()
{
	for (size_t i = 0; i < this->cactuses.size(); i++)
	{
		if (this->player.getGlobalBounds().intersects(this->cactuses[i].getGlobalBounds()))
			this->window->close();
	}
}

void dino_game::movables()
{
	this->up();
	this->jump();
	this->add_cactus();
	this->move_cactuses();
	this->add_cloud();
	this->move_clouds();
	this->collisions();
	this->update_text();
	this->manage_points();
	this->points++;
}

void dino_game::events()
{
	while (this->window->pollEvent(this->e))
	{
		if (this->e.type == Event::Closed)
			this->window->close();
		if (Keyboard::isKeyPressed(Keyboard::Escape))
			this->window->close();
	}
}

void dino_game::render()
{
	this->window->clear(Color::White);
	this->render_window();
	this->render_clouds(*this->window);
	this->render_player(*this->window);
	this->render_cactuses(*this->window);
	this->render_text(*this->window);
	this->window->display();
}

dino_game::dino_game()
{
	this->load_textures();
	this->set_window();
	this->set_text();
	this->set_player();
	this->set_cactus();
	this->set_cloud();
	this->set_floor();
}

void dino_game::update()
{
	this->movables();
	this->events();
	this->render();
}
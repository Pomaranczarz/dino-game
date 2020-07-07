#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include<iostream>

using namespace sf;

class dino_game
{
	private:
		RenderWindow* window;
		VideoMode videoMode;
		Event e;
		RectangleShape outline;
		bool is_space;

		Sprite player;
		Texture playerTex;
		float verticalV;
		int jumpDelay;
		int points;

		Sprite cloud;
		Texture cloudTex;
		int cloudDelay;
		std::vector<Sprite> clouds;

		Sprite cactus;
		Texture cactusTex;
		int cactusDelay;
		int maxCactusDelay;
		std::vector<Sprite> cactuses;

		Text points_text;
		Font font;

		///================ Basics ================

		void set_window();

		void set_text();

		void load_textures();

		void set_floor();

		///================ Player ================
		void set_player();

		void up();

		void jump();

		///================ Clouds ================
		void set_cloud();

		void spawn_cloud();

		void move_clouds();

		void add_cloud();

		///================ Cactuses ================
		void set_cactus();

		void spawn_cactus() { this->cactuses.push_back(this->cactus); }

		void add_cactus();

		void move_cactuses();

		///================ Moving and respawning ================

		void collisions();

		void manage_points() { if (this->points % 100 == 0) this->maxCactusDelay -= 5; }

		void movables();

		void events();

		//================ Update and render ================

		void update_text() { this->points_text.setString("Points: " + std::to_string(this->points)); }

		void render_text(RenderTarget& window) { window.draw(this->points_text); }

		void render_window() { this->window->draw(this->outline); }

		void render_clouds(RenderTarget& window) { for (auto i : this->clouds) window.draw(i); }

		void render_cactuses(RenderTarget& window) { for (auto i : this->cactuses) window.draw(i); }

		void render_player(RenderTarget& window) { window.draw(this->player); }

		void render();
	public:
		dino_game();

		void update();

		const bool is_good() const { return this->window->isOpen(); }

		~dino_game() { delete this->window; }
};


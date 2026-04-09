#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <vector>
#include <GL/glu.h>
#include <cmath>
#include "display.h"
#include "obj_manage.h"
#include "objects.h"
std::vector<Object*> objects;
extern int WIDTH, HEIGHT;
int pick_id=1;
sf::Font font;
sf::ContextSettings settings(24,8,0,2,1);//depthBits,stencilBits,,majorVersion,minorVersion
sf::RenderWindow window(
    sf::VideoMode(WIDTH, HEIGHT),
    "3D Geometric SketchPad",
    sf::Style::Default,
    settings
);
extern sf::Text angleText;

int main() {

	font.loadFromFile("C:\\Windows\\Fonts\\simsun.ttc");

	angleText.setFont(font);
	angleText.setCharacterSize(14);
	angleText.setFillColor(sf::Color::White);
	angleText.setPosition(5, HEIGHT-50);

	window.setFramerateLimit(60);

	initGL();
	init_obj();

	bool isRotating = false,isDragging=false;
	sf::Vector2i lastMousePos;
	render_scene();

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::Resized) {
				resize_window(event.size.width,event.size.height);
			}
			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					isDragging = false;
					isRotating = true;
					lastMousePos = sf::Mouse::getPosition(window);
				} else if (event.mouseButton.button == sf::Mouse::Right) {
					isDragging = true;
					isRotating = false;
					lastMousePos = sf::Mouse::getPosition(window);
				}
			}
			if (event.type == sf::Event::MouseButtonReleased) {
				if (event.mouseButton.button == sf::Mouse::Left)
					isRotating = false;
				else if (event.mouseButton.button == sf::Mouse::Right)
					isDragging = false;
			}
			if (event.type == sf::Event::MouseWheelScrolled) {
				if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
					zoom_cam(event.mouseWheelScroll.delta);
					render_scene();
				}
			}
			if (event.type == sf::Event::MouseMoved) {
				if (isRotating) {
					sf::Vector2i currentPos = sf::Mouse::getPosition(window);
					sf::Vector2i delta = currentPos - lastMousePos;
					rotate_obj(delta);
					lastMousePos = currentPos;
					render_scene();
				} else if (isDragging) {
					sf::Vector2i currentPos = sf::Mouse::getPosition(window);
					sf::Vector2i delta = currentPos - lastMousePos;
					drag_cam(delta);
					lastMousePos = currentPos;
					render_scene();
				}
			}
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape) {
					window.close();
				} else if (event.key.code == sf::Keyboard::Space) {
					reset_cam();
				}
			}
		}
	}
	return 0;
}

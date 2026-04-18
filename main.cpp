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
extern std::vector<Object*> objects;
extern int WIDTH, HEIGHT;
bool pickDebug=false;
sf::Vector2i lastMousePos,currentPos;
sf::ContextSettings settings(24,8,0,2,1);//depthBits,stencilBits,,majorVersion,minorVersion
sf::RenderWindow window(
    sf::VideoMode(WIDTH, HEIGHT),
    "3D Geometric SketchPad",
    sf::Style::Default,
    settings
);
int main() {
	window.setFramerateLimit(60);
	initScreen();
	initGL();
	init_obj();
	bool isRotating = false,isDragging=false;
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
				currentPos = sf::Mouse::getPosition(window);
				if (isRotating) {
					sf::Vector2i delta = currentPos - lastMousePos;
					rotate_obj(delta);
					lastMousePos = currentPos;
				} else if (isDragging) {
					sf::Vector2i delta = currentPos - lastMousePos;
					drag_cam(delta);
					lastMousePos = currentPos;
				}
				render_scene();
			}
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape) {
					window.close();
				} else if (event.key.code == sf::Keyboard::Space) {
					reset_cam();
				} else if (event.key.code == sf::Keyboard::D) {
					pickDebug^=1;
					render_scene();
				}
			}
		}
	}
	return 0;
}

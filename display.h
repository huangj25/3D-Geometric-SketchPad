#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/vec3.hpp>
#include <glm/geometric.hpp>
#include <GL/glu.h>
#include <sstream>
#include <iomanip>
sf::String chn_encode(std::string a);

void initScreen();

void initGL();

void render_scene();

void resize_window(int w,int h);

void zoom_cam(float delta);

void drag_cam(sf::Vector2i delta);

void rotate_obj(sf::Vector2i delta);

void reset_cam();

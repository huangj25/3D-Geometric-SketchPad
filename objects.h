#include <glm/vec3.hpp>
#include <GL/glu.h>
class Object {
	public:
		bool visible=true;
		bool selected=false;
		int id;
		virtual void render();
		virtual void renderForPicking();
};
class Point: public Object {
	public:
		glm::vec3 pos;
		Point(glm::vec3 pos);
		Point(float x,float y,float z);
		void render();
};
class Axis: public Object {
	public:
		float range=6;
		float width=3;
		float arrowsize=0.25;
		Point* origin=new Point(glm::vec3(0,0,0));
		Axis(int axisrange=6);
		void render();
		void renderForPicking();
};
class Line: public Object {
	public:
		Point* begin;
		Point* end;
		float width=3;
		float color[3]= {1.0f,1.0f,1.0f};
		Line(Point* s1, Point* s2);
		void render();
};
class Plane: public Object {
	public:
		int type;
		Point* startp;
		float normal[3];
		Plane(Point* s1,Point* s2,Point* s3);
};
class tPolygon: public Object {
	public:
		Plane* plane;
		Point** points;
		int point_num;
		tPolygon(Point* points[],int num);
		void render();
};

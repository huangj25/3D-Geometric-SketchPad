#include "objects.h"
#include <cstring>
#include <cstdio>
extern int pick_id;
extern Object* pickmap[100000];
Object::Object() {
	id=pick_id++;
	pickmap[id]=this;
}
void Object::render() {}
void Object::renderForPicking() {}
void Object::pointAtRender() {}
//Point
Point::Point(glm::vec3 pos) {
	this->pos=pos;
	strcpy(name,"Point");
}
Point::Point(float x,float y,float z) {
	this->pos=glm::vec3(x,y,z);
	strcpy(name,"Point");
}
void Point::render() {
	if (visible) {
		glPushMatrix(); // 保存当前矩阵（避免影响其他物体）
		glTranslatef(pos.x, pos.y, pos.z); // 移动到目标位置
		glColor3ub(255,255,0);    // 设置球体颜色
		GLUquadric* quad = gluNewQuadric(); // 创建二次曲面对象
		gluQuadricNormals(quad, GLU_SMOOTH); // 生成平滑法线（光照更自然）
		gluSphere(quad, 0.1f, 10, 10);
		gluDeleteQuadric(quad); // 释放对象（避免内存泄漏）

		glPopMatrix();
	}
}
void Point::pointAtRender() {
	glPushMatrix(); // 保存当前矩阵（避免影响其他物体）
	glTranslatef(pos.x, pos.y, pos.z); // 移动到目标位置
	glColor3ub(0,255,0);    // 设置球体颜色
	GLUquadric* quad = gluNewQuadric(); // 创建二次曲面对象
	gluQuadricNormals(quad, GLU_SMOOTH); // 生成平滑法线（光照更自然）
	gluSphere(quad, 0.1f, 10, 10);
	gluDeleteQuadric(quad); // 释放对象（避免内存泄漏）

	glPopMatrix();
}
void Point::renderForPicking() {
	if (visible) {
		glPushMatrix(); // 保存当前矩阵（避免影响其他物体）
		glTranslatef(pos.x, pos.y, pos.z); // 移动到目标位置
		glColor3ub(id/65536, id/256, id%256);    // 设置球体颜色
		GLUquadric* quad = gluNewQuadric(); // 创建二次曲面对象
		gluQuadricNormals(quad, GLU_SMOOTH); // 生成平滑法线（光照更自然）
		gluSphere(quad, 0.1f, 10, 10);
		gluDeleteQuadric(quad); // 释放对象（避免内存泄漏）
		glPopMatrix();
	}
}
//Axis
Axis::Axis(int axisrange) {
	this->range=axisrange;
	strcpy(name,"Axis");
}
void Axis::render() {
	if (visible) {
		origin->render();
		glLineWidth(width);
		glEnable(GL_LINE_SMOOTH);
		glBegin(GL_LINES);
		glColor3ub(255, 0, 0);
		glVertex3f(-range, 0, 0);
		glVertex3f(range, 0, 0);
		glVertex3f(range, 0, 0);
		glVertex3f(range-arrowsize, arrowsize, 0);
		glVertex3f(range, 0, 0);
		glVertex3f(range-arrowsize, -arrowsize, 0);
		glColor3ub(0, 255, 0);
		glVertex3f(0, -range, 0);
		glVertex3f(0, range, 0);
		glVertex3f(0, range, 0);
		glVertex3f(arrowsize, range-arrowsize, 0);
		glVertex3f(0, range, 0);
		glVertex3f(-arrowsize, range-arrowsize, 0);
		glColor3ub(0, 0, 255);
		glVertex3f(0, 0, -range);
		glVertex3f(0, 0, range);
		glVertex3f(0, 0, range);
		glVertex3f(0, arrowsize, range-arrowsize);
		glVertex3f(0, 0, range);
		glVertex3f(0, -arrowsize, range-arrowsize);

		glEnd();
	}
}
void Axis::pointAtRender() {
	origin->pointAtRender();
	glLineWidth(width);
	glEnable(GL_LINE_SMOOTH);
	glBegin(GL_LINES);
	glColor3ub(255, 128, 128);
	glVertex3f(-range, 0, 0);
	glVertex3f(range, 0, 0);
	glVertex3f(range, 0, 0);
	glVertex3f(range-arrowsize, arrowsize, 0);
	glVertex3f(range, 0, 0);
	glVertex3f(range-arrowsize, -arrowsize, 0);
	glColor3ub(128, 255, 128);
	glVertex3f(0, -range, 0);
	glVertex3f(0, range, 0);
	glVertex3f(0, range, 0);
	glVertex3f(arrowsize, range-arrowsize, 0);
	glVertex3f(0, range, 0);
	glVertex3f(-arrowsize, range-arrowsize, 0);
	glColor3ub(128, 128, 255);
	glVertex3f(0, 0, -range);
	glVertex3f(0, 0, range);
	glVertex3f(0, 0, range);
	glVertex3f(0, arrowsize, range-arrowsize);
	glVertex3f(0, 0, range);
	glVertex3f(0, -arrowsize, range-arrowsize);
	glEnd();
}
void Axis::renderForPicking() {
	if (visible) {
		origin->renderForPicking();
		glLineWidth(width+5);
		glEnable(GL_LINE);
		glDisable(GL_LINE_SMOOTH);
		glColor3ub(id/65536, id/256, id%256);
		glBegin(GL_LINES);
		glVertex3f(-range, 0, 0);
		glVertex3f(range, 0, 0);
		glVertex3f(0, -range, 0);
		glVertex3f(0, range, 0);
		glVertex3f(0, 0, -range);
		glVertex3f(0, 0, range);
		glEnd();
	}
}

//line
Line::Line(Point* s1, Point* s2) {
	begin=s1;
	end=s2;
	strcpy(name,"Line");
}
void Line::render() {
	if (visible) {
		glLineWidth(width);
		glEnable(GL_LINE_SMOOTH);
		glBegin(GL_LINES);
		glColor3ub(255,255,255);
		glVertex3f(begin->pos.x,begin->pos.y,begin->pos.z);
		glVertex3f(end->pos.x,end->pos.y,end->pos.z);
		glEnd();
	}
}
void Line::pointAtRender(){
	glLineWidth(width);
		glEnable(GL_LINE_SMOOTH);
		glBegin(GL_LINES);
		glColor3ub(255,128,128);
		glVertex3f(begin->pos.x,begin->pos.y,begin->pos.z);
		glVertex3f(end->pos.x,end->pos.y,end->pos.z);
		glEnd();
}
void Line::renderForPicking() {
	if (visible) {
		glLineWidth(width+5);
		glDisable(GL_LINE_SMOOTH);
		glBegin(GL_LINES);
		glColor3ub(id/65536, id/256, id%256);
		glVertex3f(begin->pos.x,begin->pos.y,begin->pos.z);
		glVertex3f(end->pos.x,end->pos.y,end->pos.z);
		glEnd();
	}
}
//plane


//polygon
tPolygon::tPolygon(Point* in_points[],int num) {
	//plane=new Plane(points[0],points[1],points[2]);
	point_num=num;
	this->points=new Point*[10];
	for (int i=0; i<num; i++) points[i]=in_points[i];
	strcpy(name,"Polygon");
}
void tPolygon::render() {
	glDisable(GL_CULL_FACE); // 确保平面双面都能显示透明效果
	glDepthMask(GL_FALSE);
	glColor4ub(0,255,255,64);
	glBegin(GL_POLYGON);

	for (int i=0; i<point_num; i++) {
		glVertex3f(points[i]->pos.x,points[i]->pos.y,points[i]->pos.z);
	}

	glEnd();
	glDepthMask(GL_TRUE);
	glEnable(GL_CULL_FACE);
}
void tPolygon::pointAtRender(){
	glDisable(GL_CULL_FACE);
	glDepthMask(GL_FALSE);
	glColor4ub(128,255,255,64);
	glBegin(GL_POLYGON);
	for (int i=0; i<point_num; i++) {
		glVertex3f(points[i]->pos.x,points[i]->pos.y,points[i]->pos.z);
	}
	glEnd();
	glLineWidth(3);
	glColor3ub(255, 255, 255);
	glBegin(GL_LINE_LOOP);
	for (int i=0; i<point_num; i++) {
		glVertex3f(points[i]->pos.x,points[i]->pos.y,points[i]->pos.z);
	}
	glEnd();
	glDepthMask(GL_TRUE);
	glEnable(GL_CULL_FACE);
}
void tPolygon::renderForPicking() {
	glDisable(GL_CULL_FACE);
	glColor3ub(id/65536, id/256, id%256);
	glBegin(GL_POLYGON);
	for (int i=0; i<point_num; i++) {
		glVertex3f(points[i]->pos.x,points[i]->pos.y,points[i]->pos.z);
	}
	glEnd();
	glEnable(GL_CULL_FACE);
}


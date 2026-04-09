#include "objects.h"
#include <cstdio>
void Object::render(){}
void Object::renderForPicking(){}

//Point
Point::Point(glm::vec3 pos) {
	this->pos=pos;
}
Point::Point(float x,float y,float z) {
	this->pos=glm::vec3(x,y,z);
}
void Point::render() {
	if (visible) {
		glPushMatrix(); // 保存当前矩阵（避免影响其他物体）
		glTranslatef(pos.x, pos.y, pos.z); // 移动到目标位置
		glColor3f(1.f, 1.f, 0.f);    // 设置球体颜色
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
}
void Axis::render() {
	if (visible) {
		origin->render();
		glLineWidth(width);
		glEnable(GL_LINE_SMOOTH);
		glBegin(GL_LINES);
		glColor3f(1.0f, 0, 0);
		glVertex3f(-range, 0, 0);
		glVertex3f(range, 0, 0);
		glVertex3f(range, 0, 0);
		glVertex3f(range-arrowsize, arrowsize, 0);
		glVertex3f(range, 0, 0);
		glVertex3f(range-arrowsize, -arrowsize, 0);
		glColor3f(0, 1.0f, 0);
		glVertex3f(0, -range, 0);
		glVertex3f(0, range, 0);
		glVertex3f(0, range, 0);
		glVertex3f(arrowsize, range-arrowsize, 0);
		glVertex3f(0, range, 0);
		glVertex3f(-arrowsize, range-arrowsize, 0);
		glColor3f(0, 0, 1.0f);
		glVertex3f(0, 0, -range);
		glVertex3f(0, 0, range);
		glVertex3f(0, 0, range);
		glVertex3f(0, arrowsize, range-arrowsize);
		glVertex3f(0, 0, range);
		glVertex3f(0, -arrowsize, range-arrowsize);

		glEnd();
	}
}
void Axis::renderForPicking() {
	if (visible) {
		origin->render();
		glLineWidth(width);
		glEnable(GL_LINE);
		//gl
		glBegin(GL_LINES);
		glVertex3f(-range, 0, 0);
		glVertex3f(range, 0, 0);
		glVertex3f(range, 0, 0);
		glVertex3f(range-arrowsize, arrowsize, 0);
		glVertex3f(range, 0, 0);
		glVertex3f(range-arrowsize, -arrowsize, 0);
		glVertex3f(0, -range, 0);
		glVertex3f(0, range, 0);
		glVertex3f(0, range, 0);
		glVertex3f(arrowsize, range-arrowsize, 0);
		glVertex3f(0, range, 0);
		glVertex3f(-arrowsize, range-arrowsize, 0);
		glVertex3f(0, 0, -range);
		glVertex3f(0, 0, range);
		glVertex3f(0, 0, range);
		glVertex3f(0, arrowsize, range-arrowsize);
		glVertex3f(0, 0, range);
		glVertex3f(0, -arrowsize, range-arrowsize);
		glEnd();
	}
}

//line
Line::Line(Point* s1, Point* s2) {
	begin=s1;
	end=s2;
}
void Line::render() {
	if (visible) {
		glLineWidth(width);
		glEnable(GL_LINE_SMOOTH);
		glBegin(GL_LINES);
		glColor3f(color[0],color[1],color[2]);
		glVertex3f(begin->pos.x,begin->pos.y,begin->pos.z);
		glVertex3f(end->pos.x,end->pos.y,end->pos.z);
		glEnd();
	}
}

//plane
Plane::Plane(Point* s1,Point* s2,Point* s3) {
	startp=s1;
	/*
	float dx1,dy1,dz1,dx2,dy2,dz2;

	dx1=s2->x-s1->x;
	dy1=s2->y-s1->y;
	dz1=s2->z-s1->z;
	dx2=s3->x-s1->x;
	dy2=s3->y-s1->y;
	dz2=s3->z-s1->z;
	normal[0]=dy1*dz2-dy2*dz1;
	normal[1]=dz1*dx2-dz2*dx1;
	normal[2]=dx1*dy2-dx2*dy1;*/

}

//polygon
tPolygon::tPolygon(Point* in_points[],int num) {
	//plane=new Plane(points[0],points[1],points[2]);
	point_num=num;
	this->points=new Point*[10];
	for (int i=0;i<num;i++) points[i]=in_points[i];
}
void tPolygon::render() {
	glDisable(GL_CULL_FACE); // 确保平面双面都能显示透明效果
	glDepthMask(GL_FALSE);
	glColor4f(0.0f,1.0f,1.0f,0.5f);
	glBegin(GL_POLYGON);
	
	for (int i=0; i<point_num; i++) {
		glVertex3f(points[i]->pos.x,points[i]->pos.y,points[i]->pos.z);
	}

	glEnd();
	glDepthMask(GL_TRUE);
	glEnable(GL_CULL_FACE);
}


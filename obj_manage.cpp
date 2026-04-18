#include "obj_manage.h"
#include "objects.h"
std::vector<Object*> objects;
std::vector<int> selected;
Object* pickmap[100000];
int pick_id=100;
void init_obj(){
	Axis* new_axis=new Axis();
	objects.push_back(new_axis);

	Point* s1=new Point(1,1,-1);
	Point* s2=new Point(2,2,1);
	Line* ll=new Line(s1,s2);
	objects.push_back(s1);
	objects.push_back(s2);
	objects.push_back(ll);
	Point* s3=new Point(1,-1,-1);
	Point* s4=new Point(1,-1,1);
	Point* s5=new Point(-1,-1,1);
	Point* s6=new Point(-1,-1,-1);
	
	Point* ss[4]={s3,s4,s5,s6};
	tPolygon* p1=new tPolygon(ss,4);
	objects.push_back(p1);
}

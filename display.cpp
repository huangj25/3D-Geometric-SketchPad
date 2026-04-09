#include "display.h"
#include "objects.h"
float rotX = -45.0f,rotZ = -135.0f;
float camX=0.0f,camY=0.0f;
float cam_dist=16.0;
int WIDTH=800, HEIGHT=600;
sf::Text angleText;
extern std::vector<Object*> objects;
extern sf::RenderWindow window;
sf::String chn_encode(std::string a) {
	return sf::String::fromUtf8(
	           reinterpret_cast<const std::uint8_t*>(a.data()),
	           reinterpret_cast<const std::uint8_t*>(a.data() + a.size())
	       );
}
// 初始化OpenGL状态
void initGL() {
	// 启用深度测试（处理3D遮挡）
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	//用混合（透明度核心）
	glEnable(GL_BLEND);                      // 开启混合
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // 设置混合因子
	glEnable(GL_ALPHA_TEST);                 // 可选：过滤完全透明的像素
	glAlphaFunc(GL_GREATER, 0.01f);          // 只绘制Alpha>0.01的像素

	// 设置背景色
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	glViewport(0, 0, WIDTH, HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (float)WIDTH / HEIGHT, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
}
void render_scene() {
	// 清除颜色缓冲区和深度缓冲区
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// 重置模型视图矩阵
	glLoadIdentity();
	// 设置视角（摄像机位置）
	glTranslatef(camX, camY, -cam_dist);

	glRotatef(rotX, 1.0f, 0.0f, 0.0f);  // X轴旋转
	glRotatef(rotZ, 0.0f, 0.0f, 1.0f);  // Z轴旋转
	for (int i=0; (unsigned)i<objects.size(); i++) {
		objects[i]->render();
	}
	window.pushGLStates();  // 保存OpenGL状态并切换到SFML渲染
	window.resetGLStates();
	std::stringstream ss;
	ss << std::fixed << std::setprecision(1);
	ss << "rotation: " << rotX << ','<<rotZ<<"\n";
	ss << "camera: " <<camX<<','<<camY<<','<<cam_dist;
	angleText.setString(chn_encode(ss.str()));
	window.draw(angleText);
	window.popGLStates();
	window.display();
}
void resize_window(int w,int h) {
	WIDTH=w;
	HEIGHT=h;
	glViewport(0, 0, WIDTH, HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (float)WIDTH / HEIGHT, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	window.setView(sf::View(sf::FloatRect(0, 0, WIDTH, HEIGHT)));
	angleText.setPosition(5, HEIGHT-50);
	render_scene();
}
void zoom_cam(float delta) {
	cam_dist-=delta;
	if (cam_dist < 3.0f) cam_dist = 3.0f;
	if (cam_dist > 50.0f) cam_dist = 50.0f;
	
}
void drag_cam(sf::Vector2i delta) {
	camX += delta.x*0.02f;
	camY -= delta.y*0.02f;
}
void rotate_obj(sf::Vector2i delta) {
	rotX += delta.y * 0.5f;
	rotZ += delta.x * 0.5f;
	if (rotX<-180.f) rotX=-180.f;
	if (rotX>0.f) rotX=0.f;
}
void reset_cam() {
	float o_camX=camX,o_camY=camY,o_rotX=rotX,o_rotZ=rotZ;
	int frames=30;
	for (int i=0; i<frames; i++) {
		camX=((frames-i)*o_camX)/frames;
		camY=((frames-i)*o_camY)/frames;
		rotX=((frames-i)*o_rotX+i*(-45.0f))/frames;
		rotZ=((frames-i)*o_rotZ+i*(-135.0f))/frames;
		render_scene();
	}
}

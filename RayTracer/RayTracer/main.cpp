#include "scene.h"
#include "sphere.h"

const int screenWidth = 640;
const int screenHieght = 480;

int main()
{
	Scene scene(
		new Camera(Vec3f(0, 10, 10), Vec3f(0, 0, -1), Vec3f(0, 1, 0), 90, (float)screenWidth / screenHieght),
		screenWidth,
		screenHieght,
		Color::black);
	scene.addEntity(new Sphere(Vec3f(0, 10, -20), 10, new Material(new Shader_Lit(Color::white, Color::red, Color::white, 16))));
	scene.render();
	return 0;
}
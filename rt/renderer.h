#ifndef CG1RAYTRACER_RENDERER_HEADER
#define CG1RAYTRACER_RENDERER_HEADER

#include <core/scalar.h>
#include <rt\cameras\camera.h>
#include <core\image.h>

#include <main\a_julia.h>
#include <main\a_cameras.h>
#include <rt\integrators\integrator.h>
#include <core\random.h>

#include "guiConsole.h"
#include <mutex>

namespace rt {

class Image;
class Camera;
class Integrator;

class Renderer {
public:
    Renderer(Camera* cam, Integrator* integrator) : cam(cam), integrator(integrator) {}
    void setSamples(uint samples);
	void renderRG(Image& img); //rotatedGrid
    void render(Image& img);
    void test_render1(Image& img);
    void test_render2(Image& img);
private:
    Camera* cam;
    Integrator* integrator;
    uint samples = 1;
	bool init;
};

}

#endif


#include <core/assert.h>
#include <core/scalar.h>
#include <core/image.h>

#include <rt/world.h>
#include <rt/renderer.h>

#include <rt/loaders/obj.h>

#include <rt/groups/bvh.h>
#include <rt/groups/kdtree.h>

#include <rt/solids/sphere.h>
#include <rt\solids\triangle.h>
#include <rt\solids\quad.h>
#include <rt\solids\infiniteplane.h>
#include <rt\solids\aabox.h>
#include <rt\solids\disc.h>

#include <rt/cameras/perspective.h>
#include <rt\cameras\orthographic.h>

#include <rt/integrators/casting.h>
#include <rt\integrators\recraytrace.h>
#include <rt\integrators\raytrace.h>

#include <rt\lights\pointlight.h>
#include <rt\lights\spotlight.h>
#include <rt\lights\directional.h>
#include <rt\lights\ambient.h>
#include <rt\lights\projectivelight.h>

#include <rt\coordmappers\plane.h>
#include <rt\coordmappers\spherical.h>

#include <rt\textures\texture.h>
#include <rt\textures\constant.h>
#include <rt\textures\imagetex.h>
#include <rt\textures\perlin.h>
#include <rt\textures\checkerboard.h>

#include <rt\materials\lambertian.h>
#include <rt\materials\mirror.h>
#include <rt\materials\flatmaterial.h>
#include <rt\materials\dummy.h>
#include <rt\materials\fuzzymirror.h>
#include <rt\materials\mirror.h>
#include <rt\materials\combine.h>
#include <rt\materials\glass.h>

#include <rt\primmod\instance.h>

using namespace rt;

void renderProcess(World* world) {
	Image img(1280, 960);
	Image img2(320, 240); //thumbnail 320,240
	Image img3(1350, 800); //website

	float scale = 1.5f;
	/*main*/
	PerspectiveCamera mainCam(Point(15, 3, 0), Vector(-1, 0, 0), Vector(0, 1, 0), 0.686f*scale, 0.686f*scale);

	RecursiveRayTracingIntegrator integrator(world);
	Renderer engine1(&mainCam, &integrator);
	engine1.setSamples(400); //200 are approx. 3.5hrs.
	//engine1.render(img);
	//img.writePNG("final.png");
	engine1.renderRG(img);
	img.writePNG("final.png");
	engine1.renderRG(img2);
	img2.writePNG("thumbnail.png");
	engine1.renderRG(img3);
	img3.writePNG("final_website.png");
}

void addLights(World* world) {
	float ceiling_scale = 25;

	/*ambient light*/
	world->light.push_back(new AmbientLight(RGBColor().rep(0.875f)));

	/*main source*/
	world->light.push_back(new PointLight(Point(7, 3, 1), RGBColor(1,1,1) *ceiling_scale )); // main frame
	
}

void loadObjects(Group* scene) {

	MatLib* m = new MatLib;

	loadOBJMat(m, "models/", "rc.mtl");
	loadOBJ(scene, "models/", "rc.obj", m);
}

void rc() {

	BVH* scene = new BVH();
	World* world = new World;
	world->scene = scene;

	MatLib* m = new MatLib;

	Vector up(0, 1, 0);
	Vector right(0, 0, -1);


	Texture* blacktex = new ConstantTexture(RGBColor::rep(0.0f));
	Texture* whitetex = new ConstantTexture(RGBColor::rep(25.0f));
	Texture* smallWhiteTex = new ConstantTexture(RGBColor::rep(1.0f));

	Texture* brownTex = new ConstantTexture(RGBColor(0.5f,0.25f,0.1f));

	Texture* greentex = new ConstantTexture(RGBColor(0, 1, 0));
	Texture* redtex = new ConstantTexture(RGBColor(1, 0.3f, 0.1f));
	Texture* bluetex = new ConstantTexture(RGBColor(0, 0, 1));
	Texture* yellowtex = new ConstantTexture(RGBColor(1, 1, 0));
	Texture* smallBlackTex = new ConstantTexture(RGBColor().rep(0.05f));
	Texture* greyTex = new ConstantTexture(RGBColor(0.5f, 0.5f, 0.5f));

	ConstantTexture* lightsrctex = new ConstantTexture(RGBColor::rep(25.0f));
	Material* lightsource = new LambertianMaterial(lightsrctex, blacktex);

	/*Primary colors*/
	Material* greenMaterial = new LambertianMaterial(blacktex, greentex);
	Material* redMaterial = new LambertianMaterial(blacktex, redtex);
	Material* blueMaterial = new LambertianMaterial(blacktex, bluetex);
	Material* yellowMaterial = new LambertianMaterial(blacktex, whitetex);
	Material* whiteMaterial = new LambertianMaterial(smallBlackTex, smallWhiteTex);
	Material* greyMaterial = new LambertianMaterial(blacktex, greyTex);
	Material* blackMaterial = new LambertianMaterial(blacktex, smallBlackTex);
	Material* brownMaterial = new LambertianMaterial(brownTex, smallBlackTex);

	/*Advanced colors*/
	CombineMaterial* combineOneWayMirror = new CombineMaterial();
	Material* mirrorMaterial = new MirrorMaterial(2.485, 3.433);
	Material* glassMaterial = new GlassMaterial(1);

	//combineOneWayMirror->add(mirrorMaterial, 0.00001f);
	combineOneWayMirror->add(glassMaterial, 2);

	//Mirror 
	scene->add(new Quad(Point(12.6f, 0, 2), up*5, right*4, nullptr, combineOneWayMirror));

	//frame
	//scene->add(new Quad(Point(12.8f, 0, 2), up * 5, right, nullptr, whiteMaterial)); //left
	scene->add(new Quad(Point(12.8f, 0, -1), up * 5, right, nullptr, blackMaterial)); //right

	scene->add(new Quad(Point(12.8f, 4, 3), up, right *5, nullptr, blackMaterial)); //top
	scene->add(new Quad(Point(12.8f, 1, 3), up, right*5, nullptr, blackMaterial)); //bottom



	loadObjects(scene);
	addLights(world);
	scene->rebuildIndex();
	renderProcess(world);
}
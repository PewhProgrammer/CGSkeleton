#include "renderer.h"

namespace rt {

	std::mutex mtx;

	void Renderer::setSamples(uint samples) {
		this->samples = samples; 
		init = true;
	}

	/*rotated Grid*/
	void Renderer::renderRG(Image& img) {

		
		uint resX = img.width(), resY = img.height();
		float r1, r2;
		float scaleX, scaleY;

		if (!init) samples = 1;
		#pragma omp parallel for
		for (int i = 0; i < resX; i++) {
			//#pragma omp parallel for
			for (int j = 0; j < resY; j++) {

				RGBColor computedColor(0.0f, 0.0f, 0.0f);
				uint rotation = 0;
				float theta = 0;
				float u = 1, v = 1; 
				//#pragma omp parallel for
				for (int k = 0; k < samples; k++) {
					// Normalized device coordinates [0,1]

					if (init) {
						float x, y; 
						if (rotation == 0) {
							theta = random(0, pi * 0.5f);
						}

						x = cos(theta) * u; //u and v handles sign management
						y = sin(theta) * v;

						v = pow(-1,rotation); 
						u = v * u; 

						scaleX = (i + x) / resX; //instead of middle, we take surrounding area
						scaleY = (j + y) / resY;

						rotation++;
						if (rotation == 4) {
							rotation = 0;
						}
					}
					else {
						scaleX = (i + 0.5f) / resX;
						scaleY = (j + 0.5f) / resY;
					}

					// Screen space coordinates [-1,1]
					scaleX = (scaleX - 0.5f) * 2;
					scaleY = (scaleY - 0.5f) * 2;

					//mtx.lock();
					computedColor = computedColor + this->integrator->getRadiance(
						this->cam->getPrimaryRay(scaleX, scaleY));
					//mtx.unlock();

				}

				computedColor = computedColor / samples;
				img(i, j) = computedColor;

				mtx.lock();
				updateScreen(i, j, computedColor);
				mtx.unlock();
			}
		}

	}

	void Renderer::render(Image& img) {
		
		uint resX = img.width(), resY = img.height();
		float r1, r2;
		float scaleX, scaleY; 

		if (!init) samples = 1; 
		//#pragma omp parallel for
		for (int i = 0; i < resX; i++) {
			//#pragma omp parallel for
			//#pragma omp parallel for
			for (int j = 0; j < resY; j++) {

				RGBColor computedColor(0.0f, 0.0f, 0.0f);
				//#pragma omp parallel for
				for (int k = 0; k < samples; k++) {
					// Normalized device coordinates [0,1]
					
					if (init) {
						scaleX = (i + random()) / resX; //instead of middle, we take surrounding area
						scaleY = (j + random()) / resY;
					}
					else {
						scaleX = (i + 0.5f) / resX;
						scaleY = (j + 0.5f) / resY;
					}

					// Screen space coordinates [-1,1]
					scaleX = (scaleX - 0.5f) * 2;
					scaleY = (scaleY - 0.5f) * 2;

					computedColor = computedColor + this->integrator->getRadiance(
						this->cam->getPrimaryRay(scaleX, scaleY));

				}

				computedColor = computedColor / samples;
				img(i, j) = computedColor;

				updateScreen(i, j, computedColor);

			}
		}

	}

	void Renderer::test_render1(Image& img) {

		uint width = img.width(), height = img.height();

		for (uint i = 0; i < width; i++) {
			for (uint j = 0; j < height; j++) {

				RGBColor computedColor = a1computeColor(i, j, width, height);
				img(i, j) = computedColor;
				updateScreen(i, j, computedColor);
			}
		}

	}

	void Renderer::test_render2(Image& img) {

		uint resX = img.width(), resY = img.height();

		for (uint i = 0; i < resX; i++) {
			for (uint j = 0; j < resY; j++) {


				// Normalized device coordinates [0,1]
				float scaleX = (i + 0.5f) / resX ;
				float scaleY = (j + 0.5f) / resY ;

				// Screen space coordinates [-1,1]
				scaleX = (scaleX - 0.5f) * 2;
				scaleY = (scaleY - 0.5f) * 2; 

				RGBColor computedColor = a2computeColor(this->cam->getPrimaryRay(scaleX,scaleY));
				img(i, j) = computedColor;
				updateScreen(i, j, computedColor);


			}
		}
	}
}
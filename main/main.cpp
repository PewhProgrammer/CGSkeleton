
void a_julia();
void a_cameras();
void a_solids();
void a_indexing();
void a_instancing();
void a_lighting();
void a_materials();
void a_distributed();
void oldassignment3();
void light();
void a_textures();
void a_smooth();
void a_mappers();
void a_bumpmappers();
void objTextured();
void rc();

#include <rt\guiConsole.h>
#include <time.h>
#include <fstream>
using namespace std;

int main(int argc, char* argv[])
{
	//rt::GUImain();
	//a_smooth();
    //a_bumpmappers();
	//a_mappers();
	clock_t t1, t2;
	t1 = clock();
	rc();
	t2 = clock();
	float diff( ((float)t2 - (float)t1) / (double)CLOCKS_PER_SEC) ;
	cout << diff << endl;
	ofstream myfile;
	myfile.open("Running_time.txt");
	myfile << "Raytracer ran in: " << diff/60 << " min.";
	myfile.close();

	return 0;
}

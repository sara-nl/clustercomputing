#include <iostream>
#include <cstdlib>
#include <string>
#include "pngio.h"
#include "util.h"

using namespace std;

int main(int argc, char* argv[])
{
	int rc;
	readpng_version_info();

	FILE* infile;
	FILE* outfile;
	Image image;
	Image processed_1;
	Image processed_2;
	//Image processed;
	string input;
	string output;
	if(argc == 2)
		input = argv[1];
	else
		input = "lena.png";
	output = "result_" + input; 

	infile = fopen(input.c_str(), "rb");
	if(infile == NULL)
	{
		cout << "Failed to open file " << input << " ..." << endl;
		return EXIT_FAILURE;
	}
	outfile = fopen(output.c_str(), "wb");


	// read lena.png
	rc = read_png(infile, image);
	if(rc == EXIT_SUCCESS)
		cout << "Successfully loaded " << input << " ..." << endl;
	else
	{
		cout << "Failed to load " << input << " ..." << endl;
		return EXIT_FAILURE;
	}

	// process the image
  processed_1 = gsmoothing(image);
	processed_2 = edge(processed_1);

	// write processed image to result.png
	rc = write_png(outfile, processed_2);
	if(rc == EXIT_SUCCESS)
		cout << "Successfully saved " << output << " ..." << endl;
	else
	{
		cout << "Failed to save " << output << " ..." << endl;
		return EXIT_FAILURE;
	}

	fclose(infile);
	fclose(outfile);
	
	return EXIT_SUCCESS;
}

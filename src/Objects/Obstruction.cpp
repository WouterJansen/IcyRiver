/*
 * Obstructor.cpp
 *
 *  Created on: 12-mrt.-2016
 *      Author: Wouter
 */

#include "Obstruction.h"

using namespace GAME;

//abstract obstruction object. Its the object that will be floating on the water.
Obstruction::Obstruction() {
	x = 100;
	y = 100;
	w = 0;
	h = 0;
}

Obstruction::~Obstruction() {
	// TODO Auto-generated destructor stub
}


// Sets the texture variation random.
void Obstruction::setVariation(int type){
	// go through the folder of possible textures and make a list of all possible ones.
	std::vector<std::string> names;
	std::string folder = "textures";
	char search_path[200];
	sprintf(search_path, "%s/*.*", folder.c_str());
	WIN32_FIND_DATA fd;
	HANDLE hFind = ::FindFirstFile(search_path, &fd);
	if(hFind != INVALID_HANDLE_VALUE) {
		do {

			if(! (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) ) {
				std::string result = fd.cFileName;
				if(type == 1){ // if the line belongs to the floater type.
					if(result.find("floater",0) != std::string::npos)
						names.push_back("./textures/" + result);
				}else{ // if the line belongs to the obstruction type.
					if(result.find("obstructor",0) != std::string::npos)
						names.push_back("./textures/" + result);
				}
			}
		}while(::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}
	int randIndex = rand() % names.size(); // pick a random texture out of the possible ones.
	variant = names[randIndex];
}

/*
 * Obstructor.cpp
 *
 *  Created on: 12-mrt.-2016
 *      Author: Wouter
 */

#include "Obstruction.h"

Obstruction::Obstruction() {
	x = 100;
	y = 100;
	w = 0;
	h = 0;
}

Obstruction::~Obstruction() {
	// TODO Auto-generated destructor stub
}

void Obstruction::setVariation(int type){
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
				if(type == 1){
					if(result.find("floater",0) != std::string::npos)
						names.push_back("./textures/" + result);
				}else{
					if(result.find("obstructor",0) != std::string::npos)
						names.push_back("./textures/" + result);
				}
			}
		}while(::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}
	int randIndex = rand() % names.size();
	variant = names[randIndex];
}

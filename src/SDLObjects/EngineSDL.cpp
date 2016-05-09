/*
 * WindowSDL.cpp
 *
 *  Created on: Feb 26, 2016
 *      Author: wouter
 */

//engine object that takes care of all rendering.
#include "EngineSDL.h"

using namespace SDLGAME;


EngineSDL::EngineSDL(){
	ren = 0;
	win  = 0;
	fontSmall = 0;
	fontLarge = 0;
}

EngineSDL::~EngineSDL() {
	SDL_DestroyRenderer(ren); // destroy the rendering context for a window and free associated textures.
	SDL_DestroyWindow(win); // destroy a window.
	TTF_Quit(); // quit the TTF library
	IMG_Quit(); // quit the Image library
	Mix_CloseAudio(); //quit the Mixer library
	SDL_Quit(); // clean up all initialized subsystems.
}

//create a new SDL window. Parameters are for it's size.
int EngineSDL::newWindow(int iwidth, int iheight){
	std::cout << "Icy River - Event Log" << std::endl;
	std::cout << "---------------------" << std::endl;
	width = iwidth; 	//set resolution
	height = iheight;
	if (SDL_Init(SDL_INIT_VIDEO) != 0){ //Verify that SDL has been loaded.
		logError(std::cout, "SDL Init:");
		SDL_Quit();
		return 1;
	}
	else{
		std::cout << "ENGINE:" << getMillis() << " SDL Engine initiated." << std::endl;
	}

	if (TTF_Init() != 0){//Verify that SDL TTF Library for fonts has been loaded.
		logError(std::cout, "TTF_Init");
		SDL_Quit();
		return 1;
	}else{
		std::cout << "ENGINE:" << getMillis() << " SDL TTF Font Library initiated." << std::endl;
	}

	if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 ){
		logError(std::cout, "SDL Mixer:");
		SDL_Quit();
		return 1;
	}else{
		std::cout << "ENGINE:" << getMillis() << " Mixer Sound library initiated." << std::endl;
	}

	//create a SDL Window.
	win = SDL_CreateWindow("IcyRiver - by Wouter Jansen", 320, 30, width, height, SDL_WINDOW_SHOWN);
	if (win == 0){ // Verify.
		logError(std::cout, "CreateWindow:");
		SDL_Quit();
		return 1;
	}else{
		std::cout << "ENGINE:" << getMillis() << " Created Window with resolution " << width << "x" << height << "." << std::endl;
	}

	//set the program icon.
	SDL_Surface *loadedImage = IMG_Load("./textures/penguin_right.png");
	SDL_SetWindowIcon(win, loadedImage);
	SDL_FreeSurface(loadedImage);

	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED); // create SDL Renderer
	if (ren == 0){ // Verify
		logError(std::cout, "CreateRenderer:");
		SDL_DestroyWindow(win);
		SDL_Quit();
		return 1;
	}else{
		std::cout << "ENGINE:" << getMillis() << " Created Renderer." << std::endl;
	}

	loadFonts();

	//draw loadingscreen
	Uint8 color[] = {255,255,255,255};
	renderText("Loading Textures & Sounds...",width/2,height/2,color,0,"centre");
	renderFrame();

	preloadSounds(); //search for all sounds in the Sounds folder and load them into memory ready to be used.
	preloadTextures(); //search for all textures in the Textures folder and load them into memory ready to be used.

	return 0;
}

void EngineSDL::loadFonts(){
	std::string fontName="./fonts/Minecraft.ttf";
	fontSmall = TTF_OpenFont(fontName.c_str(), height/16);

	if (fontSmall == 0){
		logError(std::cout, "TTF_OpenFont");
	}

	fontLarge = TTF_OpenFont(fontName.c_str(), height/10);
	if (fontLarge == 0){
		logError(std::cout, "TTF_OpenFont");
	}
}

//search for all sounds in the Sounds folder and load them into memory ready to be used.
void EngineSDL::preloadSounds(){
	std::cout << "ENGINE:" << getMillis() << " Preloading Sounds..." << std::endl;

	std::string folder = "music"; //folder in which to search.
	char search_path[200];
	sprintf(search_path, "%s/*.*", folder.c_str()); // place foldername into search_path string
	// windows function to go through all files.
	WIN32_FIND_DATA fd;
	HANDLE hFind = ::FindFirstFile(search_path, &fd);
	if(hFind != INVALID_HANDLE_VALUE) {
		do {
			if(! (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) ) {
				std::string result = fd.cFileName; //if file is found get the name
				std::string combined = "./music/" + result; //combine this with the foldername to get full name.
				Mix_Music *music = 0;
				music = Mix_LoadMUS(combined.c_str());
				if( music == NULL )
				{
					std::cout << "ENGINE:" << getMillis() << " Error: music file '" << combined << "' couldn't be loaded." << std::endl;
				}else{
					musicBuf[combined.c_str()] = music; // add texture to memory map and use filename as key
					std::cout << "ENGINE:" << getMillis() << " Preloaded music file: " << combined.c_str() << std::endl;
				}
			}
		}while(::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}

	folder = "sounds"; //folder in which to search.
	sprintf(search_path, "%s/*.*", folder.c_str()); // place foldername into search_path string
	// windows function to go through all files.
	hFind = ::FindFirstFile(search_path, &fd);
	if(hFind != INVALID_HANDLE_VALUE) {
		do {
			if(! (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) ) {
				std::string result = fd.cFileName; //if file is found get the name
				std::string combined = "./sounds/" + result; //combine this with the foldername to get full name.
				Mix_Chunk *chunk = 0;
				chunk = Mix_LoadWAV(combined.c_str());
				if( chunk == NULL )
				{
					std::cout << "ENGINE:" << getMillis() << " Error: sound effect '" << combined << "' couldn't be loaded." << std::endl;
				}else{
					chunkBuf[combined.c_str()] = chunk; // add texture to memory map and use filename as key
					std::cout << "ENGINE:" << getMillis() << " Preloaded sound effect: " << combined.c_str() << std::endl;
				}
			}
		}while(::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}
	std::cout << "ENGINE:" << getMillis() << " Preloaded " << musicBuf.size() + chunkBuf.size() << " sounds." << std::endl;
}


//search for all textures in the Textures folder and load them into memory ready to be used.
void EngineSDL::preloadTextures(){
	std::cout << "ENGINE:" << getMillis() << " Preloading Textures..." << std::endl;

	std::string folder = "textures"; //folder in which to search.
	char search_path[200];
	sprintf(search_path, "%s/*.*", folder.c_str()); // place foldername into search_path string
	// windows function to go through all files.
	WIN32_FIND_DATA fd;
	HANDLE hFind = ::FindFirstFile(search_path, &fd);
	if(hFind != INVALID_HANDLE_VALUE) {
		do {
			if(! (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) ) {
				std::string result = fd.cFileName; //if file is found get the name
				std::string combined = "./textures/" + result; //combine this with the foldername to get full name.
				SDL_Texture *texture = 0;
				//Load the image
				SDL_Surface *loadedImage = IMG_Load(combined.c_str()); //load in image using SDL_Image library into a SDL_Surface(pixel data)
				//If the loading went ok, convert to texture and return the texture
				if(loadedImage != 0){
					texture = SDL_CreateTextureFromSurface(ren, loadedImage); // turn pixel data into texture.
					SDL_FreeSurface(loadedImage); // now the surface can be cleared again.
					if (texture == 0){ // Verify
						logError(std::cout, "CreateTextureFromSurface:");
					}
				}else {
					logError(std::cout, "Load File:");
				}
				texBuf[combined.c_str()] = texture; // add texture to memory map and use filename as key
				std::cout << "ENGINE:" << getMillis() << " Preloaded texture: " << combined.c_str() << std::endl;
			}
		}while(::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}
	std::cout << "ENGINE:" << getMillis() << " Preloaded " << texBuf.size() << " textures. Engine setup completed." << std::endl;
}

//get current time since start of SDL initialization.
Uint32 EngineSDL::getMillis(){
	return SDL_GetTicks(); //Returns an unsigned 32-bit value representing the number of milliseconds since the SDL library initialized.
}

//Console print function to print out SDL errors.
void EngineSDL::logError(std::ostream &os, const std::string &msg){
	os << "ENGINE:" << getMillis() << " Error: " << msg << SDL_GetError() << std::endl;
}

void EngineSDL::increaseResolution(){
	RECT desktop;
	GetWindowRect(GetDesktopWindow(), &desktop);
	if(width + 12 < desktop.right && height + 10 < desktop.bottom - 50){
		width += 12;
		height += 10;
		SDL_SetWindowSize(win,width,height);
		loadFonts();
		std::cout << "ENGINE:" << getMillis() << " Increasing resolution to " << width << "x" << height << "." << std::endl;
	}else{
		std::cout << "ENGINE:" << getMillis() << " Maximum resolution is " << width << "x" << height << "." << std::endl;
	}
}

void EngineSDL::decreaseResolution(){
	if(width > 128){
		width -= 12;
		height -= 10;
		SDL_SetWindowSize(win,width,height);
		loadFonts();
		std::cout << "ENGINE:" << getMillis() << " Decreasing resolution to " << width << "x" << height << "." << std::endl;
	}else{
		std::cout << "ENGINE:" << getMillis() << " Minimum resolution is " << width << "x" << height << "." << std::endl;
	}
}

//search the buffer for what key is possibly being pressed and return it.
std::string EngineSDL::Poll(){
	SDL_Event e; // create event from buffer
	SDL_PollEvent(&e); //search that event
	if (e.type == SDL_KEYDOWN){ // if the the type is a key being pressed
		const char* c = SDL_GetKeyName(e.key.keysym.sym); // return the name of the key
		if(std::string(c) == "PageUp"){
			increaseResolution();
		}if(std::string(c) == "PageDown"){
			decreaseResolution();
		}
		return c;
	}else if (e.type == SDL_QUIT){ // if the type is the exit button of the window being pressed
		stop = true;
		std::cout << "ENGINE:" << getMillis() << " Close button pressed. Closing..." << std::endl;
		return "";
	}
	return "";
}



//load a music sound from the memory and play it.
void EngineSDL::playMusic(const std::string &file, int times){
	std::map<std::string,Mix_Music*>::iterator it;
	it = musicBuf.find(file.c_str());
	if(it != musicBuf.end()){
		Mix_PlayMusic( it->second, times ); // play the sound.
	}else{
		std::cout << "ENGINE:" << getMillis() << " Error: Music sound '" << file << "' not found." << std::endl;
	}
}

//load a  sound effect from the memory and play it.
void EngineSDL::playSound(const std::string &file, int times){
	std::map<std::string,Mix_Chunk*>::iterator it;
	it = chunkBuf.find(file.c_str());
	if(it != chunkBuf.end()){
		if(Mix_PlayChannel( -1, it->second, times )==-1)
		{
			std::cout << "ENGINE:" << getMillis() << " Error: Sound effect '" << file << "' Couldn't be played." << std::endl;
		}
	}else{
		std::cout << "ENGINE:" << getMillis() << " Error: Sound effect '" << file << "' not found." << std::endl;
	}
}

void EngineSDL::renderText(const std::string &message, float x, float y, Uint8 color[], int size, std::string outline){
	SDL_Surface *surf = 0;
	SDL_Color colorSDL = { color[0], color[1], color[2], color[3] };
	if(size == 0){
		surf = TTF_RenderText_Solid(fontSmall, message.c_str(), colorSDL);
		if (surf == 0){
			logError(std::cout, "TTF_RenderText");
		}
	}else{
		surf = TTF_RenderText_Solid(fontLarge, message.c_str(), colorSDL);
		if (surf == 0){
			logError(std::cout, "TTF_RenderText");
		}
	}
	SDL_Texture *texture = SDL_CreateTextureFromSurface(ren, surf);
	if (texture == 0){
		logError(std::cout, "CreateTextureFromSurface:");
	}
	SDL_FreeSurface(surf);
	int w, h;
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
	SDL_Rect dst;
	std::vector<float> array = transform(x,y,0,0);
	if(outline == "centre"){
		dst.x = array[0] - w/2; //set x coordinate
		dst.y = array[1]; //set y coordinate
	}else if(outline == "left"){
		dst.x = array[0]; //set x coordinate
		dst.y = array[1]; //set y coordinate
	}else{
		dst.x = array[0] - w; //set x coordinate
		dst.y = array[1]; //set y coordinate
	}
	dst.w = w; //set width
	dst.h = h; //set height
	SDL_RenderCopy(ren,texture, NULL, &dst);
	SDL_DestroyTexture(texture);
}

//load a texture from the memory and render it.
void EngineSDL::renderTexture(const std::string &file, float x, float y,float w, float h,bool flip){
	SDL_Rect dst;
	std::vector<float> array = transform(x,y,w,h);
	dst.x = array[0]; //set x coordinate
	dst.y = array[1]; //set y coordinate
	dst.w = array[2]; //set width
	dst.h = array[3]; //set height
	std::map<std::string,SDL_Texture*>::iterator it;
	it = texBuf.find(file.c_str());
	if(it != texBuf.end()){
		if(flip)
			SDL_RenderCopyEx(ren, it->second, NULL, &dst, NULL, NULL, SDL_FLIP_HORIZONTAL);// copy the texture to the renderer
		else
			SDL_RenderCopy(ren,it->second, NULL, &dst); // copy the texture to the renderer
	}else{
		std::cout << "ENGINE:" << getMillis() << " Error: Texture '" << file << "' not found." << std::endl;
	}
}

//Similar to function above we can use this function to render animated images.
//Using the partial filename, the extention, the coordinates,
//width and height of the image. We also pass the last time the background was rendered and what state it was in.
//to make sure the animation goes at the right speed we pass the framerate and speed as well.
Uint32 EngineSDL::renderTextureAnimated(const std::string &file,const std::string &ext, float x, float y, float w, float h, Uint32 lastTime, int *i,int rate, int max, int speed){
	SDL_Rect dst;
	std::vector<float> array = transform(x,y,w,h);
	dst.x = array[0]; //set x coordinate
	dst.y = array[1]; //set y coordinate
	dst.w = array[2]; //set width
	dst.h = array[3]; //set height
	std::string StringInt = static_cast<std::ostringstream*>( &(std::ostringstream() << *i) )->str(); // turn the intiger into a string
	std::string result =  file.c_str() + StringInt + ext.c_str(); //combine the filename with the animation-index and the extention.


	std::map<std::string,SDL_Texture*>::iterator it;
	it = texBuf.find(result);
	if(it != texBuf.end()){
		SDL_RenderCopy(ren,it->second, NULL, &dst); // copy the texture to the renderer
		Uint32 t = getMillis(); // get current time
		if( (t - lastTime) >= ((1000/rate)*speed)){ // if the time since last render of the animation isn't long enouph, then wait until it's time to render next animation image.
			if(*i == max) // once all images of animation as been rendered, start over
				*i = 1; // set the given state pointer back to 1.
			else
				*i = *i + 1;// set the given state pointer to one higher for next render.
			return t; // return the current time as it's the new last time the image was rendered
		}
		return lastTime; // if not enouph time has past then don't increase counter and simply return the last time again.
	}else{
		std::cout << "ENGINE:" << getMillis() << " Error: Texture '" << file << "' not found." << std::endl;
		return 0;
	}
}

//Similar to function above we can use this function to render animated images in tiles in a given rectangle.
//Using the partial filename, the extention, the limit-coordinates of the rectangle,
//width and height of the image. We also pass the last time the background was rendered and what state it was in.
//to make sure the animation goes at the right speed we pass the framerate and speed as well.
Uint32 EngineSDL::renderTextureAnimatedTiled(const std::string &file,const std::string &ext, float x, float y, float totalw, float totalh, float w, float h, Uint32 lastTime, int *i,int rate, int max, int speed){

	std::string StringInt = static_cast<std::ostringstream*>( &(std::ostringstream() << *i) )->str(); // turn the intiger into a string
	std::string result =  file.c_str() + StringInt + ext.c_str(); //combine the filename with the animation-index and the extention.

	std::vector<float> array = transform(x,y,w,h);
	std::vector<float> totalarray = transform(totalw,totalh,0,0);
	std::map<std::string,SDL_Texture*>::iterator it;
	it = texBuf.find(result);
	if(it != texBuf.end()){
		for(int k = 0; k <= totalarray[0]; k = k + array[2]){ // render it from 0 to the x-coordinate limit for each tile-width.
			for(int j = 0;j <= totalarray[1]; j = j + array[3]){ // render it from 0 to the y-coordinate limit for each tile-height.
				SDL_Rect dst;
				dst.w = array[2]; //set width
				dst.h = array[3]; //set height
				dst.x = array[0] + k; // set x coordinate
				dst.y = array[1] + j; // set y coordinate
				SDL_RenderCopy(ren,it->second, NULL, &dst); // copy the texture to the renderer
			}
		}
		Uint32 t = getMillis(); // get current time
		if( (t - lastTime) >= ((1000/rate)*speed)){ // if the time since last render of the animation isn't long enouph, then wait until it's time to render next animation image.
			if(*i == max) // once all images of animation as been rendered, start over
				*i = 1; // set the given state pointer back to 1.
			else
				*i = *i + 1;// set the given state pointer to one higher for next render.
			return t; // return the current time as it's the new last time the image was rendered
		}
		return lastTime; // if not enouph time has past then don't increase counter and simply return the last time again.
	}else{
		std::cout << "ENGINE:" << getMillis() << " Error: Texture '" << file << "' not found." << std::endl;
		return 0;
	}
}

//get the size(width and height) of a image and save it in the w and h pointers of the object.
void EngineSDL::getSize(const std::string &file, float x, float y, float *w, float *h){
	SDL_Rect dst;
	dst.x = x; // set the x coordinate.
	dst.y = y; // set the y coordinate.
	bool found = false;

	//iterate the texture buffer map.
	for (std::map<std::string,SDL_Texture*>::iterator it = texBuf.begin() ; it != texBuf.end(); ++it){
		if(it->first == file.c_str()){ // if the filename is found in the map using the key
			SDL_QueryTexture(it->second, NULL, NULL, &dst.w, &dst.h); //  this function queries the attributes of a texture.
			found = true;
			std::vector<float> arraysize = transformSize((float)dst.w,(float)dst.h);
			*w = arraysize[0];
			*h = arraysize[1];
		}
	}
	if(!found){
		logError(std::cout, "CreateTextureFromSurface");
		std::cout << "ENGINE:" << getMillis() << " Error: Texture '" + file << "' not found when requesting size." << std::endl;
	}
}

// clear the renderer.
void EngineSDL::clearFrame(){
	SDL_RenderClear(ren); //clear the current rendering.

}

// render the rendered textures out.
void EngineSDL::renderFrame(){
	SDL_RenderPresent(ren); //update the screen with any rendering performed since the previous call.
}

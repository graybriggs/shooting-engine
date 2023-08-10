

#include <iostream>

#include <string>
#include <vector>

#include <SDL.h>

struct SomeGameClass {

	std::string s;

};

Uint32 one(Uint32 interval, void* params) {
	//SomeGameClass* sgc = reinterpret_cast<SomeGameClass*>(params);
	SomeGameClass* sgc = static_cast<SomeGameClass*>(params);
	std::cout << sgc->s << std::endl;

	SDL_RemoveTimer((SDL_TimerID)params);

	//return interval;
	return 0;
}

Uint32 two(Uint32 interval, void* params) {
	SomeGameClass* sgc = static_cast<SomeGameClass*>(params);
	std::cout << sgc->s << std::endl;

	return interval;
}

Uint32 three(Uint32 interval, void* params) {
	SomeGameClass* sgc = static_cast<SomeGameClass*>(params);
	std::cout << sgc->s << std::endl;

	return 0;
}





int main(int argc, char* args[]) {

	SDL_Init(SDL_INIT_TIMER);
	std::vector<SDL_TimerID> timers;

	SomeGameClass sgc1;
	sgc1.s = "sgc one";
	SomeGameClass sgc2;
	sgc2.s = "sgc two";
	SomeGameClass sgc3;
	sgc3.s = "sgc three";
	timers.push_back(SDL_AddTimer(500, one, &sgc1));
	timers.push_back(SDL_AddTimer(1200, two, &sgc2));
	timers.push_back(SDL_AddTimer(5000, three, &sgc3));

	SDL_Event event;
	bool done = false;

	while (!done) {
		if (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				done = true;
			}
		}

	}

	SDL_Quit();

	return 0;
}
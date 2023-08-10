

#include <iostream>

#include <string>
#include <vector>

#include <SDL.h>

struct Entity {

	SDL_Rect r;
};

struct GameBase {

	std::string s;
	virtual void set_active() = 0;
	virtual void pattern() = 0;
	virtual void update() = 0;

	bool active = false;
};

struct SomeGameClass : public GameBase {

	void set_active() override {
		active = true;
	};
	void pattern() override {}
	void update() override {
		std::cout << "updating SomeGameClass" << std::endl;
	};

};

struct SineWave : public GameBase {

	void set_active() override {
		active = true;
	};

	void pattern() override {}
	void update() override {
		if (active) {
			std::cout << "updating SineWave" << std::endl;
		}
	};
};

struct StraightLine : public SomeGameClass {

	void set_active() override {
		active = true;
	};

	void pattern() override {}
	void update() override {
		if (active) {
			std::cout << "updating Straight Line" << std::endl;
		}
	};
};

struct LoopBack : public SomeGameClass {
	
	void set_active() override {
		active = true;
	};

	void pattern() override {}
	void update() override {
		if (active) {
			std::cout << "updating Loopback" << std::endl;
		}
	};
};



Uint32 one(Uint32 interval, void* params) {
	//SomeGameClass* sgc = reinterpret_cast<SomeGameClass*>(params);
	SomeGameClass* sgc = static_cast<SomeGameClass*>(params);
	std::cout << sgc->s << " set active" << std::endl;
	sgc->set_active();
	SDL_RemoveTimer((SDL_TimerID)params);

	//return interval;
	return 0;
}

Uint32 two(Uint32 interval, void* params) {
	SomeGameClass* sgc = static_cast<SomeGameClass*>(params);
	std::cout << sgc->s << " set active" << std::endl;
	sgc->set_active();
	return 0;
}

Uint32 three(Uint32 interval, void* params) {
	SomeGameClass* sgc = static_cast<SomeGameClass*>(params);
	std::cout << sgc->s << " set active" << std::endl;
	sgc->set_active();

	return 0;
}


void cleanup_timers(std::vector<SDL_TimerID>& timers) {
	
	for (int i = 0; i < timers.size(); ++i) {
		SDL_RemoveTimer(timers[i]);
	}
}


int main(int argc, char* args[]) {

	SDL_Init(SDL_INIT_TIMER);
	std::vector<SDL_TimerID> timers;
	std::vector<GameBase*> gb;

	SineWave sine;
	sine.s = "sine";
	StraightLine straight;
	straight.s = "straight";
	LoopBack loop;
	loop.s = "loop";
	timers.push_back(SDL_AddTimer(2000, one, &sine));
	timers.push_back(SDL_AddTimer(3000, two, &straight));
	timers.push_back(SDL_AddTimer(5000, three, &loop));

	gb.push_back(&sine);
	gb.push_back(&straight);
	gb.push_back(&loop);


	SDL_Event event;
	bool done = false;

	while (!done) {
		if (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				done = true;
			}
		}

		for (auto& b : gb) {
			b->update();
			SDL_Delay(500);
		}

	}

	cleanup_timers(timers);
	SDL_Quit();

	return 0;
}
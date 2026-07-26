#include "RMI/rmi.h"
#include <SDL3/SDL_thread.h>
#include <SDL3/SDL_timer.h>

void shi1(){

};

void shi2(){
	
};

void shi3(){
	Uint64 ticks = SDL_GetTicks();
	RMI_Log("Tick was %u",ticks);
	SDL_Delay(1000u);
	RMI_StopRunning();
	ticks = SDL_GetTicks();
	RMI_Log("Tick was %u",ticks);
};

int main(){
	RMI_Result initResult = RMI_Init(360,360,60,&shi1,&shi2,&shi3);
	if (initResult == RMI_RESULT_FAILURE){
		RMI_Log("Init failed :(\n");
		return 1;
	}

	//do the updating on a new thread with a tickrate
	//function();

	// do the drawing on the main thread with a framerate
	while(RMI_KeepRunning()){
		RMI_HandleEvents();
		RMI_Draw();
	}

	RMI_Result deinitResult = RMI_Deinit();
	if (deinitResult == RMI_RESULT_FAILURE){
		RMI_Log("Deinit failed :P\n");
	}

	return 0;
}

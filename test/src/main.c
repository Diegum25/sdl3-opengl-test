#include "RMI/rmi.h"
#include "glad/gl.h"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_timer.h>

Uint64 updates = 0;
Uint64 draws = 0;

void gameEvent(SDL_Event* event){
	if(event->type == SDL_EVENT_QUIT || event->type == SDL_EVENT_TERMINATING) RMI_Stop();
};

void gameUpdate(){
	updates++;
	RMI_Log("[UPDATE]\n");
};

void gameDraw(){
	draws++;
	RMI_Log("[DRAW]\n");
	glClearColor(SDL_randf(),SDL_randf(),SDL_randf(),1.0f);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
};

int main(){
	RMI_Result initResult = RMI_Init(360,360,&gameEvent,&gameUpdate,&gameDraw);
	if (initResult == RMI_RESULT_FAILURE){
		RMI_Log("Init failed :(\n");
		return 1;
	}

	RMI_Result runResult = RMI_Run();
	if(runResult == RMI_RESULT_FAILURE){
		RMI_Log("Could not run\n");
	}

	RMI_Log("Updates [%lu]\n",updates);
	RMI_Log("Draws [%lu]\n",draws);

	RMI_Deinit();

	RMI_Log("End of progarm\n");
	return 0;
}

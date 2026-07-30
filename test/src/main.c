#include "RMI/rmi.h"

void gameEvent(){

};

void gameUpdate(){
	RMI_Log("[UPDATE]\n");
};

void gameDraw(){
	RMI_Log("[DRAW]\n");
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

	RMI_Deinit();

	RMI_Log("End of progarm\n");
	return 0;
}

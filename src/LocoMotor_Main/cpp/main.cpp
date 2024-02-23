#include <iostream>


// Para que no salga la consola hay que cambiar una propiedad en vinculador->sistema, y utilizar la funcion main de windows (WinMain)
// Como solo queremos que pase en release, hacemos este #ifdef
#ifdef _DEBUG
#define LocoMotor_Main	main
#define Main_Args		
#else
#include "windows.h"
#define LocoMotor_Main	WinMain
#define Main_Args		HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow
#endif

int LocoMotor_Main(Main_Args) {
	std::cout << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAa" << std::endl;
}
#include <iostream>
#include "Engine.h"

// Para que no salga la consola hay que cambiar una propiedad en vinculador->sistema, y utilizar la funcion main de windows (WinMain)
// Como solo queremos que pase en release, hacemos este #ifdef
#ifdef _DEBUG
#include "CheckML.h"
#define LocoMotor_Main	main
#define Main_Args
#else
#include "windows.h"
#define LocoMotor_Main	WinMain
#define Main_Args		HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow
#endif

int LocoMotor_Main(Main_Args) {

#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	LocoMotor::Engine* i = new LocoMotor::Engine();

	if (!i->Init()) {
		delete i;
		std::cerr << "\033[1;31m" << "Algo no se inicializó correctamente" << "\033[0m" << std::endl;
		return -1;
	}

	//Esto se llamaría desde el código del juego
	if (!i->StartGameWindow("hola ventana de ogre")) {
		delete i;
		std::cerr << "\033[1;31m" << "Algo salió mal en el método de crear la ventana" << "\033[0m" << std::endl;
		return -1;
	}

	if (!i->MainLoop()) {
		delete i;
		std::cerr << "\033[1;31m" << "Algo salió mal en el bucle principal" << "\033[0m" << std::endl;
		return -1;
	}

	std::cout 
		<< "\033[1;31m" << "F" 
		<< "\033[1;33m" << "U" 
		<< "\033[1;32m" << "N" 
		<< "\033[1;36m" << "C" 
		<< "\033[1;34m" << "I" 
		<< "\033[1;35m" << "O" 
		<< "\033[1;31m" << "N" 
		<< "\033[1;33m" << "A" << "\033[0m" << std::endl;
	std::cout 
		<< "\033[1;33m" << "F" 
		<< "\033[1;32m" << "U" 
		<< "\033[1;36m" << "N" 
		<< "\033[1;34m" << "C" 
		<< "\033[1;35m" << "I" 
		<< "\033[1;31m" << "O" 
		<< "\033[1;33m" << "N" 
		<< "\033[1;32m" << "A" << "\033[0m" << std::endl;
	std::cout 
		<< "\033[1;32m" << "F" 
		<< "\033[1;36m" << "U" 
		<< "\033[1;34m" << "N" 
		<< "\033[1;35m" << "C" 
		<< "\033[1;31m" << "I" 
		<< "\033[1;33m" << "O" 
		<< "\033[1;32m" << "N" 
		<< "\033[1;36m" << "A" << "\033[0m" << std::endl;

	delete i;

	return 0;
}

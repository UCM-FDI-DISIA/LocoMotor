#include <iostream>
#include "Engine.h"

#include "windows.h"

// Para que no salga la consola hay que cambiar una propiedad en vinculador->sistema, y utilizar la funcion main de windows (WinMain)
// Como solo queremos que pase en release, hacemos este #ifdef
#ifdef _DEBUG
#include "CheckML.h"
#define LocoMotor_Main	main
#define Main_Args       //HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow
#else

#define LocoMotor_Main	WinMain
#define Main_Args		HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow
#endif

// typedef de los metodos que vamos a encontrar en la dll del Juego
typedef const char* (CALLBACK* InitJuegoFunc)(LocoMotor::Engine* m);

int LocoMotor_Main(Main_Args) {

#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
			
#endif

	bool dllLoaded = false;

	LocoMotor::Engine* motor = new LocoMotor::Engine();

	if (!motor->Init()) {
		delete motor;
		std::cerr << "\033[1;31m" << "Algo no se inicializó correctamente" << "\033[0m" << std::endl;
		return -1;
	}

	//Esto se llamaría desde el código del juego
	motor->setWindowName("hola ventana de ogre");

#pragma region Explicit dll loading
	LPCWSTR dllName;
	HINSTANCE g6Game;
	InitJuegoFunc initJuego;

#ifdef _DEBUG
	dllName = L"G7_JuegoDePistolas_d";
#else
	dllName = L"g6Game";
#endif // _DEBUG

	g6Game = LoadLibrary(dllName);
	if (g6Game != NULL) {

		// Buscamos la funcion, notese que no hace falta hacer lo de Wide Char
		LPCSTR functionName = LPCSTR("InitJuego");
		initJuego = (InitJuegoFunc) GetProcAddress(g6Game, functionName);

		if (initJuego != NULL) {
			// La ejecutamoss
			auto result = initJuego(motor);
			std::cout << result << std::endl;
		}
		else {
			std::cerr << "DLL EXPLICIT LOADING ERROR: '" << functionName << "' function couldn't be executed" << std::endl;
		}

		dllLoaded = true;
	}
	else {
		std::cerr << "DLL EXPLICIT LOADING ERROR: '" << dllName << "' wasn't found" << std::endl;
	}
#pragma endregion

	if (!motor->MainLoop()) {
		delete motor;
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

	delete motor;
	if (dllLoaded) {
		FreeLibrary(g6Game);
	}

	return 0;
}

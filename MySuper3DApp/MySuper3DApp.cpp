#include <iostream>
#include "KatamariDamacyGame.h"
#include "Transform.h"
#include "SimpleMath.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

int main()
{
	KatamariDamacyGame* game = new KatamariDamacyGame(L" Katamari Damacy ", 1200, 1200);
	game->Run();

	//Assimp::Importer importer;

	return EXIT_SUCCESS;
}
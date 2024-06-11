#include <string>

#include "MazeGen.h"

int main(int argc, char* argv[]) 
{
	if (argc < 2)
	{
		return 1;
	}

	MazeGen::MazeInfo maze;

	if (std::stoi(argv[1]) == -1)
	{
		maze = MazeGen::LoadMazeFromFile("matrix.txt");
	}
	else
	{
		size_t N = std::stoull(argv[1]);
		size_t M = N;
		bool giveTrue = false;

		if (argc > 2)
		{
			M = std::stoull(argv[2]);
		}
		if (argc > 3)
		{
			giveTrue = static_cast<bool>(std::stoi(argv[3]));
		}

		maze = MazeGen::GenerateMaze(N, M, giveTrue);
	}

	MazeGen::PrintExitPath(maze);
}
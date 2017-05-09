#pragma once
#include <vector>

class Ground
{
public:
	void InitializeGround();
	void Draw();
    void Fill();

	std::vector<int> ground;
};

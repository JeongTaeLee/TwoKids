#pragma once
class cMainGame
{
private:
public:
	cMainGame();
	~cMainGame();

	void Init();
	void Release();
	void Update();
	void Render();

	void LostDevice();
	void ResetDevice();
};


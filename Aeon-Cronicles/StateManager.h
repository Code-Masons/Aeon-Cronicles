#pragma once
#include <vector>

class State;
class StateManager
{
private:
	static std::vector<State*> s_states;

public:
	static void Update(float deltaTime);
	static void Render();
	static void PushState(State* pState);
	static void popState();
	static void ChangeState(State* pState);
	static void Quit();
	static std::vector<State*>& GetStates();

private:
	StateManager() {}
};


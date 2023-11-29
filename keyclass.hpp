#pragma once
#include <SDL2/SDL.h>
#include <vector>

enum KeyEventType
{
	PRESSED,
	RELEASED
};

struct Key
{
	unsigned int key;
	KeyEventType type;
};

class KeyClass
{
private:
	std::vector<Key> keys{};
public:
	bool isDown(SDL_KeyCode keycode);
	bool isUp(SDL_KeyCode keycode);
};
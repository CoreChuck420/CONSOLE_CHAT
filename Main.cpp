#include "Chat.h"

using namespace std;


auto main() -> int
{
	system("chcp 1251");
	Chat chat;
	chat.Start();
	while (chat.isOnline())
	{
		chat.showLoginMenu();
		while (chat.getCurrentUser())
		{
			chat.showUserMenu();
		}

	}
	return 0;
}
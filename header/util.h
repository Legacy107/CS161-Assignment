#pragma once
#include <iostream>
#include <chrono>
#include <string.h>
#include <thread>
#include <windows.h>

// Get duration from start to now in ms
int get_duration(std::chrono::steady_clock::time_point start);

// Format duration in ms to Am Bs Cms
std::string format_duration(int duration);

void set_cursor(int x = 0, int y = 0);

void show_cursor(bool show);

void util();

/**
 * Copyright 2025 University of Michigan EECS183
 *
 * test.cpp
 * Project UID 8885f2d9f10d2f99bc099aa9c3fc0543
 *
 * Project 4: Battleship
 *
 * Contains functions for testing classes in the project. 
 */

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

#include "Position.h"
#include "Ship.h"
#include "Player.h"
#include "Game.h"
#include "utility.h"

using namespace std;

void test_position();
void test_ship();
void test_player();
void test_game();
void test_project_setup();

void startTests() {
    test_project_setup();
    test_position();
    test_ship();
    test_player();
    
    return;
}

void test_position() {
    // Write your tests here
    return;
}

void test_ship() {
    // Write your tests here
    return;
}

void test_player() {
    // Write your tests here
    return;
}

void test_project_setup() {
    // open file to verify setup
    ifstream ins;
    ins.open("grid1.txt");

    // check for fail state
    if (ins.fail()) {
        cout << "Project was not created correctly." << endl;
        cout << "Text files are not in the correct folder." << endl;
        cout << "Check the project specification "
            << "for how to set up your project." << endl;
    }
    else {
        cout << "Project set up correctly, file opened." << endl;
    }

    return;
}

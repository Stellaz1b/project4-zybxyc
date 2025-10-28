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
    cout << "==== POSITION TESTS ====\n";

    // POSITION_DEFAULT_CONSTRUCTOR
    Position pos_p0;
    cout << "POSITION_DEFAULT_CONSTRUCTOR\n";
    cout << "  Expected row=0 col=0; write=(1,A)\n";
    cout << "  Actual   row=" << pos_p0.get_row() << " col=" << pos_p0.get_col()
         << "; write=" << pos_p0 << "\n";

    // POSITION_NON_DEFAULT_CONSTRUCTOR_1 (int,int)
    Position pos_p1(3, 4);
    Position pos_bad1(99, 99);
    cout << "POSITION_NON_DEFAULT_CONSTRUCTOR_1\n";
    cout << "  p(3,4) Expected (row=3,col=4; write=(4,E))\n";
    cout << "  p(3,4) Actual   (row=" << pos_p1.get_row() << ",col=" << pos_p1.get_col()
         << "; write=" << pos_p1 << ")\n";
    cout << "  p(99,99) range-fix Expected row=0 col=0\n";
    cout << "  p(99,99) Actual     row=" << pos_bad1.get_row()
         << " col=" << pos_bad1.get_col() << "\n";

    // POSITION_NON_DEFAULT_CONSTRUCTOR_2 (char,char)
    Position pos_p2('8','h');
    Position pos_p3('1','a');
    cout << "POSITION_NON_DEFAULT_CONSTRUCTOR_2\n";
    cout << "  ('8','h') Expected row=7 col=7; write=(8,H)\n";
    cout << "  ('8','h') Actual   row=" << pos_p2.get_row() << " col=" << pos_p2.get_col()
         << "; write=" << pos_p2 << "\n";
    cout << "  ('1','a') Expected write=(1,A)\n";
    cout << "  ('1','a') Actual   write=" << pos_p3 << "\n";

    // POSITION_READ
    Position pos_r;
    istringstream iss;
    iss.str("1A"); iss.clear();
    iss >> pos_r;
    cout << "POSITION_READ (compact '1A')\n";
    cout << "  Expected row=0 col=0; write=(1,A)\n";
    cout << "  Actual   row=" << pos_r.get_row() << " col=" << pos_r.get_col()
         << "; write=" << pos_r << "\n";
    iss.str("(1,a)"); iss.clear();
    iss >> pos_r;
    cout << "POSITION_READ (tuple '(1,a)')\n";
    cout << "  Expected row=0 col=0; write=(1,A)\n";
    cout << "  Actual   row=" << pos_r.get_row() << " col=" << pos_r.get_col()
         << "; write=" << pos_r << "\n";
    iss.str("(0,Z)"); iss.clear();
    iss >> pos_r;
    cout << "POSITION_READ (invalid '(0,Z)')\n";
    cout << "  Expected row fixed to 0; col fixed to 0\n";
    cout << "  Actual   row=" << pos_r.get_row() << " col=" << pos_r.get_col() << "\n";
    return;
}

void test_ship() {
    cout << "\n==== SHIP TESTS ====\n";
    // SHIP_DEFAULT_CONSTRUCTOR
    Ship ship_s0;
    cout << "SHIP_DEFAULT_CONSTRUCTOR\n";
    cout << "  Expected size=0; start=(1,A); end=(1,A)\n";
    cout << "  Actual   size=" << ship_s0.get_size()
         << "; start=" << ship_s0.get_start()
         << "; end="   << ship_s0.get_end() << "\n";

    // SHIP_NON_DEFAULT_CONSTRUCTOR
    Ship ship_h(Position(0,0), Position(0,3));
    Ship ship_v(Position(2,5), Position(5,5));
    cout << "SHIP_NON_DEFAULT_CONSTRUCTOR\n";
    cout << "  Horizontal Expected size=4; is_horizontal=1\n";
    cout << "  Actual      size=" << ship_h.get_size()
         << "; is_horizontal=" << (ship_h.is_horizontal()?1:0) << "\n";
    cout << "  Vertical   Expected size=4; is_horizontal=0\n";
    cout << "  Actual      size=" << ship_v.get_size()
         << "; is_horizontal=" << (ship_v.is_horizontal()?1:0) << "\n";

    // SHIP_HAS_POSITION
    Ship ship_c(Position(3,2), Position(3,5));
    Ship ship_c2(Position(6,6), Position(2,6));
    cout << "SHIP_HAS_POSITION\n";
    cout << "  Contains (3,4) Expected 1; Actual " << (ship_c.has_position(Position(3,4))?1:0) << "\n";
    cout << "  Contains (3,5) Expected 1; Actual " << (ship_c.has_position(Position(3,5))?1:0) << "\n";
    cout << "  Contains (3,1) Expected 0; Actual " << (ship_c.has_position(Position(3,1))?1:0) << "\n";
    cout << "  Reverse contains (3,6) Expected 1; Actual " << (ship_c2.has_position(Position(3,6))?1:0) << "\n";
    cout << "  Reverse contains (1,6) Expected 0; Actual " << (ship_c2.has_position(Position(1,6))?1:0) << "\n";

    // SHIP_HIT
    Ship ship_hit(Position(1,1), Position(1,3));
    cout << "SHIP_HIT\n";
    cout << "  has_sunk() initially Expected 0; Actual " << (ship_hit.has_sunk()?1:0) << "\n";
    ship_hit.hit(); ship_hit.hit();
    cout << "  After 2 hits Expected 0; Actual " << (ship_hit.has_sunk()?1:0) << "\n";
    ship_hit.hit();
    cout << "  After 3 hits Expected 1; Actual " << (ship_hit.has_sunk()?1:0) << "\n";
    ship_hit.hit(); ship_hit.hit();
    cout << "  After extra hits Expected 1; Actual " << (ship_hit.has_sunk()?1:0) << "\n";
    return;
}

void test_player() {
    cout << "\n==== PLAYER TESTS ====\n";
    // PLAYER_DEFAULT_CONSTRUCTOR
    Player ply_d;
    cout << "PLAYER_DEFAULT_CONSTRUCTOR\n";
    cout << "  Expected name=\"\"; num_ships=0; remaining=0; grid empty\n";
    cout << "  Actual   name=\"" << ply_d.get_name() << "\"; num_ships=" << ply_d.get_num_ships()
         << "; remaining=" << ply_d.get_remaining_ships()
         << "; grid(0,0)='" << ply_d.get_grid_at(0,0)
         << "' guess(7,7)='" << ply_d.get_guess_grid_at(7,7) << "'\n";

    // PLAYER_NON_DEFAULT_CONSTRUCTOR
    Player ply_n("Alice");
    cout << "PLAYER_NON_DEFAULT_CONSTRUCTOR\n";
    cout << "  Expected name=Alice; grid(2,2)=EMPTY('" << EMPTY_LETTER << "')\n";
    cout << "  Actual   name=" << ply_n.get_name()
         << "; grid(2,2)='" << ply_n.get_grid_at(2,2) << "'\n";

    // PLAYER_ADD_SHIP_1/2/3
    Player ply_a("P");
    cout << "PLAYER_ADD_SHIP_1\n";
    ply_a.add_ship(Ship(Position(0,0), Position(0,1)));
    cout << "  Expected num=1 remaining=1; marks at (0,0),(0,1)=SHIP('" << SHIP_LETTER << "')\n";
    cout << "  Actual   num=" << ply_a.get_num_ships() << " remaining=" << ply_a.get_remaining_ships()
         << "; grid(0,0)='" << ply_a.get_grid_at(0,0)
         << "' grid(0,1)='" << ply_a.get_grid_at(0,1) << "'\n";

    cout << "PLAYER_ADD_SHIP_2\n";
    ply_a.add_ship(Ship(Position(2,2), Position(4,2)));
    cout << "  Expected num=2 remaining=2; marks at (2,2),(4,2)=SHIP\n";
    cout << "  Actual   num=" << ply_a.get_num_ships() << " remaining=" << ply_a.get_remaining_ships()
         << "; grid(2,2)='" << ply_a.get_grid_at(2,2)
         << "' grid(4,2)='" << ply_a.get_grid_at(4,2) << "'\n";

    cout << "PLAYER_ADD_SHIP_3 (cap at MAX_SHIPS)\n";
    ply_a.add_ship(Ship(Position(6,0), Position(6,3)));
    ply_a.add_ship(Ship(Position(7,7), Position(7,3)));
    ply_a.add_ship(Ship(Position(5,5), Position(5,7)));
    int ply_before = ply_a.get_num_ships();
    ply_a.add_ship(Ship(Position(0,7), Position(0,7))); // 第6艘，应该被忽略
    cout << "  Expected num stays=" << ply_before << "\n";
    cout << "  Actual   num=" << ply_a.get_num_ships() << "\n";

    // PLAYER_LOAD_GRID_FILE + PLAYER_ATTACK_1/2
    Player A("A"), B("B");
    bool ok1 = B.load_grid_file("grid1.txt");
    bool ok2 = A.load_grid_file("grid2.txt");
    cout << "PLAYER_LOAD_GRID_FILE\n";
    cout << "  Expected true true; Actual " << (ok1 ? "true" : "false")
         << " " << (ok2 ? "true" : "false") << "\n";

    ostringstream cap;
    std::streambuf* old_buf = cout.rdbuf();

    cout.rdbuf(cap.rdbuf());
    A.attack(B, Position(0,0));            //hit
    cout.rdbuf(old_buf);
    cout << "PLAYER_ATTACK_1 (hit at (1,A))\n";
    cout << "  Captured: " << cap.str();
    cap.str(""); cap.clear();

    cout.rdbuf(cap.rdbuf());
    A.attack(B, Position(0,0));            // repeat -> miss
    cout.rdbuf(old_buf);
    cout << "PLAYER_ATTACK_2 (repeat same cell -> miss)\n";
    cout << "  Captured: " << cap.str();
    cap.str(""); cap.clear();

    cout.rdbuf(cap.rdbuf());
    A.attack(B, Position(0,7));            // 多半为空 -> miss
    cout.rdbuf(old_buf);
    cout << "PLAYER_ATTACK_2 (miss at (1,H))\n";
    cout << "  Captured: " << cap.str();
    cap.str(""); cap.clear();
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

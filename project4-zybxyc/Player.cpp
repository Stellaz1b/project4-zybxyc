/**
 * Copyright 2025 University of Michigan EECS183
 *
 * Player.cpp
 * Project UID 95f0d1fcee98fd521df7bce6625c2263
 *
 * Yancheng Xiang/Yibei Zhai
 * ericxyc/yibei
 *
 * Project 4: Battleship
 *
 * EECS 183 Project 4 Player
 */

#include <fstream>

#include "Player.h"


Player::Player() {
    name = "";
    num_ships = 0;
    remaining_ships = 0;
    init_grid();
}

Player::Player(string name_val) {
    name = name_val;
    num_ships = 0;
    remaining_ships = 0;
    init_grid();
}

void Player::init_grid() {
    for (int i = 0; i < MAX_GRID_SIZE; i++) {
        for (int j = 0; j < MAX_GRID_SIZE; j++) {
            grid[i][j] = EMPTY_LETTER;
            guess_grid[i][j] = EMPTY_LETTER;
        }
    }
    return;
}

string Player::get_name() {
    return name;
}

int Player::get_num_ships() {
    return num_ships;
}

int Player::get_remaining_ships() {
    return remaining_ships;
}

char Player::get_grid_at(int row, int col) {
    return grid[row][col];
}

char Player::get_guess_grid_at(int row, int col) {
    return guess_grid[row][col];
}

void Player::add_ship(Ship ship) {
    if (num_ships >= MAX_NUM_SHIPS) {
        return;
    }
    ships[num_ships] = ship;
    num_ships += 1;
    remaining_ships += 1;
    
    Position ship_start = ship.get_start();
    Position ship_end = ship.get_end();
    if (ship.is_horizontal()) {
        int row = ship_start.get_row();
        int from_col = 0;
        int to_col = 0;
        if (ship_start.get_col() < ship_end.get_col()) {
            from_col = ship_start.get_col();
            to_col = ship_end.get_col();
        }
        else {
            from_col = ship_end.get_col();
            to_col = ship_start.get_col();
        }
        for (int col = from_col; col <= to_col; col++) {
            grid[row][col] = SHIP_LETTER;
        }
    }
    else {
        int col = ship_start.get_col();
        int from_row = 0;
        int to_row = 0;
        if (ship_start.get_row() < ship_end.get_row()) {
            from_row = ship_start.get_row();
            to_row = ship_end.get_row();
        }
        else {
            from_row = ship_end.get_row();
            to_row = ship_start.get_row();
        }
        for (int row = from_row; row <= to_row; row++) {
            grid[row][col] = SHIP_LETTER;
        }
    }
    return;
}

void Player::attack(Player &opponent, Position pos) {
    int row = pos.get_row();
    int col = pos.get_col();
    if (opponent.grid[row][col] == HIT_LETTER || opponent.grid[row][col] == MISS_LETTER) {
        guess_grid[row][col] = MISS_LETTER;
        opponent.grid[row][col] = MISS_LETTER;
        cout << name << " " << pos << " miss" << endl;
        return;
    }
    bool hit_ship = false;
    for (int i = 0; i < opponent.num_ships; i++) {
        if (opponent.ships[i].has_position(pos)) {
            hit_ship = true;
            guess_grid[row][col] = HIT_LETTER;
            opponent.grid[row][col] = HIT_LETTER;
            cout << name << " " << pos << " hit" << endl;
            opponent.ships[i].hit();
            if (opponent.ships[i].has_sunk()) {
                opponent.remaining_ships -= 1;
                announce_ship_sunk(opponent.ships[i].get_size());
            }
            break;
        }
    }
    if (!hit_ship) {
        guess_grid[row][col] = MISS_LETTER;
        opponent.grid[row][col] = MISS_LETTER;
        cout << name << " " << pos << " miss" << endl;
    }
    return;
}

void Player::announce_ship_sunk(int size) {
    string ship_type;
    if (size == 2) {
        ship_type = "Destroyer";
    }
    else if (size == 3) {
        ship_type = "Submarine";
    }
    else if (size == 4) {
        ship_type = "Battleship";
    }
    else {
        ship_type = "Carrier";
    }
    cout << "Congratulations " << name << "! You sunk a " << ship_type << endl;
    return;
}

bool Player::load_grid_file(string filename) {
    ifstream input;
    input.open(filename);
    if (!input.is_open()) {
        return false;
    }
    while (input.good() && num_ships < MAX_NUM_SHIPS) {
        Position new_start;
        Position new_end;
        input >> new_start >> new_end;
        if (input.good()) {
            Ship new_ship(new_start, new_end);
            add_ship(new_ship);
        }
    }
    input.close();
    return true;
}

bool Player::destroyed() {
    if (remaining_ships == 0) {
        return true;
    }
    else {
        return false;
    }
}

// Your code goes above this line.
// Don't change the implementations below!

void Player::print_grid() {
    ::print_grid(grid);
}

void Player::print_guess_grid() {
    ::print_grid(guess_grid);
}

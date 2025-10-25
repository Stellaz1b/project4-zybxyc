/**
 * Copyright 2025 University of Michigan EECS183
 *
 * Position.cpp
 * Project UID 95f0d1fcee98fd521df7bce6625c2263
 *
 * Yancheng Xiang/Yibei Zhai
 * ericxyc
 *
 * Project 4: Battleship
 *
 * EECS 183 Project 4 Position
 */

#include "Position.h"
#include "utility.h"


Position::Position() {
    row = 0;
    col = 0;
}

Position::Position(int row_in, int col_in) {
    //row
    row = check_range(row_in);
    //col
    col = check_range(col_in);
}

Position::Position(char row_in, char col_in) {
    //row
    row = check_range((row_in - '0') - 1);
    //col
    col = check_range(toupper(col_in) - 'A');
}

int Position::get_row() {
    return row;
    return -1;
}

void Position::set_row(int row_in) {
    row = check_range(row_in);
    return;
}

int Position::get_col() {
    return col;
    return -1;
}

void Position::set_col(int col_in) {
    col = check_range(col_in);
    return;
}

void Position::write(ostream &os) {
    int rowOut;
    char colOut;
    rowOut = static_cast<char>(row + 1);    // 0-based → 1-based
    colOut = 'A' + col; // 0→'A', 1→'B', …
    os << '(' << rowOut << ',' << colOut << ')';
    return;
}

int Position::check_range(int val) {
    if (val >= 0 && val < MAX_GRID_SIZE){
        return val;
    }
    else {
        if (val < 0) {
            return 0;
        }
        else {
            return MAX_GRID_SIZE - 1;
        }
    }
}

void Position::read(istream& is) {
    // This function is **partially** implemented for you
    // add your code below after the TODO comment
    char trash = 't';
    int row_in = 0;
    char col_in = 'c';

    // read format 1A
    is >> row_in >> col_in;

    // if stream failed, must read format (1,A)
    if (is.fail()) {
        is.clear();
        is >> trash >> row_in >> trash >> col_in >> trash;
    }
    //row
    row = check_range(row_in - 1);
    //col
    col = check_range(toupper(col_in) - 'A');

    return;
}

// Your code goes above this line.
// Don't change the implementations below!

istream &operator>>(istream &is,  Position &pos) {
    pos.read(is);
    return is;
}

ostream &operator<<(ostream &os, Position pos) {
    pos.write(os);
    return os;
}


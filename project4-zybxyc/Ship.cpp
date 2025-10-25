/**
 * Copyright 2025 University of Michigan EECS183
 *
 * Ship.cpp
 * Project UID 95f0d1fcee98fd521df7bce6625c2263
 *
 * Yancheng Xiang/Yibei Zhai
 * ericxyc/yibei
 *
 * Project 4: Battleship
 *
 * EECS 183 Project 4 Ship
 */

#include <cmath>

#include "Ship.h"


Ship::Ship() {
    size = 0;
    num_hits = 0;
    Position start(0, 0);
    Position end(0, 0);
    size = 0;
}

Ship::Ship(Position start_in, Position end_in) {
    start = start_in;
    end = end_in;
    num_hits = 0;
    if(is_horizontal()){
        size = abs(end.get_col() - start.get_col()) + 1;
    }
    else{
        size = abs(end.get_row() - start.get_row()) + 1;
    }
}

Position Ship::get_start() {
    return start;
}

Position Ship::get_end() {
    return end;
}

int Ship::get_size() {
    return size;
}

bool Ship::is_horizontal() {
    if(start.get_row() == end.get_row()){
        return true;
    }
    else{
        return false;
    }
}

bool Ship::has_position(Position pos) {
    if(is_horizontal()){
        if(pos.get_row() != start.get_row()){
            return false;
        }
        else{
            if(start.get_col() < end.get_col()){
                if(pos.get_col() >= start.get_col() && pos.get_col() <= end.get_col()){
                    return true;
                }
                else{
                    return false;
                }
            }
            else{
                if(pos.get_col() >= end.get_col() && pos.get_col() <= start.get_col()){
                    return true;
                }
                else{
                    return false;
                }
            }
        }
    }
    else{
        if(pos.get_col() != start.get_col()){
            return false;
        }
        else{
            if(start.get_row() < end.get_row()){
                if(pos.get_row() >= start.get_row() && pos.get_row() <= end.get_row()){
                    return true;
                }
                else{
                    return false;
                }
            }
            else{
                if(pos.get_row() >= end.get_row() && pos.get_row() <= start.get_row()){
                    return true;
                }
                else{
                    return false;
                }
            }
        }
    }
}

void Ship::hit() {
    if(num_hits < size){
        num_hits++;
    }
    return;
}

bool Ship::has_sunk() {
    if(num_hits == size){
        return true;
    }
    else{
        return false;
    }
}


#include <iostream>
#include <cmath>
#include "Position.h"

using namespace std;

float Position::operator-(const Position that) const {
    float diff_x = this->x - that.x;
    float diff_y = this->y - that.y;
    return sqrt(diff_x * diff_x + diff_y * diff_y);
}
Position Position::operator+(Position that) const {
    float diff_x = this->x + that.x;
    float diff_y = this->y + that.y;
    Position pos = Position(diff_x,diff_y);
    return pos;
}
Position Position::operator/(float denominator) const {
    float diff_x = this->x / denominator;
    float diff_y = this->y / denominator;
    Position pos = Position(diff_x,diff_y);
    return pos;
}
float Position::GetX() const{
    return this->x;
}
float Position::GetY() const{
    return this->y;
}

void Position::Read(istream& s) {
    cin >> x >> y;
}


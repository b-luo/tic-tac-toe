#include "cell.h"

std::ostream &operator<<(std::ostream &out, const Position &p) {
	out << "(" << p.x << ", " << p.y << ")";
	return out;
}

std::ostream &operator<<(std::ostream &out, const Cell &c) {
	out << c.getSym();
	return out;
}

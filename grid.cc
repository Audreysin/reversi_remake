#include "cell.h"
#include "state.h"
#include "info.h"
#include "textdisplay.h"
#include "grid.h"
#include <iostream>

using namespace std;

Grid::~Grid() {
	delete td;
	delete ob;
}


void Grid::setObserver(Observer<Info, State> *ob) {
	this->ob = ob;
}

bool Grid::isFull() const {
	for (unsigned int i = 0; i < theGrid.size(); i++) {
		for (unsigned int j = 0; j < theGrid[i].size(); j++) {
			if (theGrid[i][j].getInfo().colour == Colour::NoColour) {
				return false;
			}
		}
	}
	return true;
}

Colour Grid::whoWon() const{
	int blackCount = 0;
	int whiteCount = 0;
	
	for (unsigned int i = 0; i < theGrid.size(); i++) {
                for (unsigned int j = 0; j < theGrid[i].size(); j++) {
			if (theGrid[i][j].getInfo().colour == Colour::Black) blackCount++;
			if (theGrid[i][j].getInfo().colour == Colour::White) whiteCount++;
		}
	}

	if (blackCount > whiteCount) {
		cout << "Black wins!" << endl;
		return Colour::Black;
	} else if (whiteCount > blackCount) {
	        cout << "White wins!" << endl;
		return Colour::White;
	} else {
		cout << "Tie!" << endl;
		return Colour::NoColour;
	}
}

void Grid::init(size_t n) {
	theGrid.clear();
	delete td;
	
	int num = (int) n;
	td = new TextDisplay {num};


	for (unsigned int r = 0; r < n; r++) {
		vector<Cell> row;
		for (unsigned int c = 0; c < n; c++) {
			row.emplace_back(Cell {r, c});
		}
		theGrid.emplace_back(row);
	}
	int _n = (int) n;
	for (int r = 0; r < _n; r++) {
		for (int c = 0; c < _n; c++) {
			theGrid[r][c].attach(td);

			if ((r - 1) >= 0) {
				if ((c - 1) >= 0) {
					theGrid[r][c].attach(&theGrid[r - 1][c - 1]);
				}
				theGrid[r][c].attach(&theGrid[r - 1][c]);
				if ((c + 1) < _n) {
					theGrid[r][c].attach(&theGrid[r - 1][c + 1]);
				}
			}
			if ((r + 1) < _n) {
				if ((c - 1) >= 0) {
					theGrid[r][c].attach(&theGrid[r + 1][c - 1]);
				}
				theGrid[r][c].attach(&theGrid[r + 1][c]);
				if ((c + 1) < _n) {
					theGrid[r][c].attach(&theGrid[r + 1][c + 1]);
				}
			}
			if ((c - 1) >= 0) {
				theGrid[r][c].attach(&theGrid[r][c - 1]);
			}
			if (c + 1 < _n) {
				theGrid[r][c].attach(&theGrid[r][c + 1]);
			}


			/*
			for (int i = r - 1; i <= r + 1; i++) {
				if (i < 0 || i >= _n) continue;
				for (int j = c - 1; j <= c + 1; c++) {
					if (j < 0 || j >= _n) continue;
					if (i == r && j == c) continue;
					#ifdef DEBUG
                                        cerr << "Attached cell (" << i << "," << j << ")"  << endl;
#endif
					theGrid[r][c].attach(&theGrid[i][j]);
				}
			}*/
		}
	}	


	int TLinit = (n /2) - 1;

	setPiece(TLinit, TLinit, Colour::Black);
	setPiece(TLinit + 1, TLinit, Colour::White);
	setPiece(TLinit, TLinit + 1, Colour::White);
	setPiece(TLinit + 1, TLinit + 1, Colour::Black);
	
}

void Grid::setPiece(size_t r, size_t c, Colour colour) {
	if (theGrid[r][c].getInfo().colour != Colour::NoColour) {
	       throw InvalidMove{};
	}	       
	theGrid[r][c].setPiece(colour);
}

void Grid::toggle(size_t r, size_t c) {
	theGrid[r][c].toggle();
}

ostream &operator<<(ostream &out, const Grid &g) {
	out << *(g.td);
	return out;
}


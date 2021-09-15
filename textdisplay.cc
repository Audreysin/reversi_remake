#include "textdisplay.h"
#include "cell.h"

#include <iostream>
#include <vector>
using namespace std;

TextDisplay::TextDisplay(int n) :
	gridSize {n}{
		for (int i = 0; i < n; i++) {
			vector<char> row;
			for (int j = 0; j < n; j++) {
				row.emplace_back('-');
			}
			theDisplay.emplace_back(row); 
		}
	}


void TextDisplay::notify(Subject<Info, State> &whoNotified) {
	State subjectState = whoNotified.getState();
	if ((subjectState.type == StateType::NewPiece) ||
		(subjectState.type == StateType::Reply)){
		Info sInfo = whoNotified.getInfo();
		if (sInfo.colour == Colour::Black) {
			theDisplay[sInfo.row][sInfo.col] = 'B';
		} else if (sInfo.colour == Colour::White) {
			theDisplay[sInfo.row][sInfo.col] = 'W';
		}
	} 	

}

ostream &operator<<(ostream &out, const TextDisplay &td) {
	for (unsigned int i = 0; i < td.theDisplay.size(); i++) {
		for (unsigned int j = 0; j < td.theDisplay[i].size(); j++) {
			out << td.theDisplay[i][j];
		}
		out << endl;
	}
	return out;
}

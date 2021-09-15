#include "cell.h"

Cell::Cell(size_t r, size_t c) :
	r {r}, c {c}, colour {Colour::NoColour} {
		setState(State{StateType::Reply, Colour::NoColour});
	}

void Cell::setPiece(Colour colour) {
	this->colour = colour;
	setState(State {StateType::NewPiece,colour});
	notifyObservers();
}

void Cell::toggle() {
	if (this->colour == Colour::Black) {
		this->colour = Colour::White;
	} else if (this->colour == Colour::White) {
		this->colour = Colour::Black;
	}
}

Direction Cell::setDirection(Subject<Info, State> &s) {
	Info myInfo = getInfo();
	Info subjectInfo = s.getInfo();

	if (subjectInfo.row < myInfo.row) {
		if (subjectInfo.col < myInfo.col) {
			return Direction::NW;
		} else if (subjectInfo.col > myInfo.col) {
			return Direction::NE;
		} else {
			return Direction::N;
		}
	} else if (subjectInfo.row > myInfo.row) {
		if (subjectInfo.col < myInfo.col) {
			return Direction::SW;
		} else if (subjectInfo.col > myInfo.col) {
			return Direction::SE;
		} else {
			return Direction::S;
		}
	} else {
		if (subjectInfo.col < myInfo.col) {
			return Direction::W;
		} else {
			return Direction::E;
		}
	}
}


void Cell::notify(Subject<Info, State> &whoFrom) {
	if (getInfo().colour != Colour::NoColour) {

		State whoState = whoFrom.getState();
		if (whoState.type == StateType::NewPiece) {
			if (whoState.colour == this->colour) {
				setState({StateType::Reply, whoState.colour, setDirection(whoFrom)});
			} else {
				setState({StateType::Relay, whoState.colour, setDirection(whoFrom)});
			}
			notifyObservers();
		} else if (whoState.type == StateType::Relay) {
			if (setDirection(whoFrom) == whoState.direction) {
				if (whoState.colour == this->colour) {
					setState({StateType::Reply, whoState.colour, whoState.direction});
				} else {
					setState({StateType::Relay, whoState.colour, whoState.direction});
				}
				notifyObservers();
			}
		} else /*(whoState.type == StateType::Reply)*/ {
			State myState = getState();
			if ((myState.type == StateType::Relay) &&
			    (myState.colour == whoState.colour) &&
			    (myState.direction == whoState.direction)) {
				setState({StateType::Reply,myState.colour, myState.direction});
				if (getInfo().colour != myState.colour) toggle();
				notifyObservers();
				//
			} //else if (myState.type == StateType::NewPiece) {
				//setState({StateType::Reply, getInfo().colour});
			//}

		}
	}
}	





Info Cell::getInfo() const {
	return Info {r, c, colour};
}


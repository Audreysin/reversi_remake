#include <iostream>
#include <string>
// You may include other allowed headers, as needed
#include "grid.h"
#include "state.h"
using namespace std;

// Do not remove any code; do not add code other than where indicated.

int main(int argc, char *argv[]) {
#ifdef DEBUG
	cerr << "Here" << endl;
#endif
  cin.exceptions(ios::eofbit|ios::failbit);
  string cmd;
  Grid g;
  int gridSize;
  Colour currentPlayer = Colour::Black;
  // Add code here

  try {
  while (true) {
#ifdef DEBUG
	  cerr << "Reached here" << endl;
#endif
    cin >> cmd;
    if (cmd == "new") {
      int n;
      cin >> n;
#ifdef DEBUG 
      cerr << "call init" << endl;
#endif
      if ((n >= 4) && (n % 2 == 0)) {
	      gridSize = n;
	      g.init(n);
#ifdef DEBUG
	      cerr << "1" << endl;
#endif

	      cout << g;
      }
      // Add code here
    }
    else if (cmd == "play") {
      int r = 0, c = 0;
      cin >> r >> c;
      
      try {
	      if ((r < 0) || (r >= gridSize) || (c < 0) || (c >= gridSize)) {
		      throw InvalidMove {};
	      }
	      g.setPiece(r, c, currentPlayer);
	      
	      currentPlayer = (currentPlayer == Colour::Black)? Colour::White : Colour::Black;
	      cout << g;
      } catch ( InvalidMove &i) {}
      // Add code here
    }
    if (g.isFull()) {
	    g.whoWon();
	    break;
    }
  }
  }
  catch (ios::failure &)  {}  // Any I/O failure quits
  
}

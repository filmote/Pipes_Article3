
#define MENU_ITEM_3            3
#define MENU_ITEM_3_X          19
#define MENU_ITEM_3_1_Y        19
#define MENU_ITEM_3_2_Y        29
#define MENU_ITEM_3_3_Y        39
#define MENU_ITEM_3_WIDTH      92   
#define MENU_ITEM_3_HEIGHT     9

#define MENU_ITEM_2            2
#define MENU_ITEM_2_X          17
#define MENU_ITEM_2_1_Y        23
#define MENU_ITEM_2_2_Y        35
#define MENU_ITEM_2_WIDTH      98   
#define MENU_ITEM_2_HEIGHT     11


byte levelSelect_selectedItem = 0;
byte levelSelect_topItem = 0;

byte puzzleSelect_selectedItem = 0;


/* ----------------------------------------------------------------------------
 *   Handle the scolling and selection of the levels.  
 */
void levelSelect() {

  clearHighlightAndSelection();

  arduboy.clear();

  if (arduboy.justPressed(UP_BUTTON) && levelSelect_selectedItem > 0) 					            { levelSelect_selectedItem--; }
  if (arduboy.justPressed(DOWN_BUTTON) && levelSelect_selectedItem < sizeof(levels) - 1) 	  { levelSelect_selectedItem++; }
  if (arduboy.justPressed(B_BUTTON)) 												                                { gameState = STATE_INTRO; }
  
  if (arduboy.justPressed(A_BUTTON)) { 
	  
	  puzzle.level = levels[levelSelect_selectedItem];
	  puzzle.index = 0;


    // If the player has completed some puzzles, give them the option to restart  
    // the level or puzzle.  Otherwise simply start the puzzle ..
    
    if (readEEPROM(puzzle.level) > 0) {
      
  	  gameState = STATE_PUZZLE_SELECT;
      prevState = STATE_LEVEL_SELECT;
      puzzleSelect_selectedItem = 0;
     
    }
    else {
      
      gameState = STATE_INIT_GAME;
      
    }
	  
  }
  
  
  // Adjust the top menu item based on selected item ..
  
  if (levelSelect_selectedItem < MENU_ITEM_3 - 1) {

	  levelSelect_topItem = 0;

  }
  else {

    if (levelSelect_selectedItem > sizeof(levels) - MENU_ITEM_3 + 1) {

      levelSelect_topItem = sizeof(levels) - MENU_ITEM_3;

  	}
  	else {
   
      levelSelect_topItem = levelSelect_selectedItem - 1;
          
  	}

  }
	
  
  // Render menu ..
  
  renderLevelDetail(MENU_ITEM_3_X, MENU_ITEM_3_1_Y, levels[levelSelect_topItem], (levelSelect_topItem == levelSelect_selectedItem));
  renderLevelDetail(MENU_ITEM_3_X, MENU_ITEM_3_2_Y, levels[levelSelect_topItem + 1], (levelSelect_topItem + 1 == levelSelect_selectedItem));
  renderLevelDetail(MENU_ITEM_3_X, MENU_ITEM_3_3_Y, levels[levelSelect_topItem + 2], (levelSelect_topItem + 2 == levelSelect_selectedItem));

}


/* ----------------------------------------------------------------------------
 *   Render a single level menu item.  
 */
void renderLevelDetail(byte x, byte y, byte level, byte highlight) {

  if (highlight) {
	  
  	arduboy.setTextColor(BLACK);
  	arduboy.setTextBackground(WHITE);
  	arduboy.fillRect(x - 1, y - 1, MENU_ITEM_3_WIDTH, MENU_ITEM_3_HEIGHT, WHITE);
	  
  }
	
  arduboy.setCursor(x, y);
  
  switch (level) {
  
  	case PUZZLE_5X5:
  		arduboy.print("Practice  ");
      arduboy.print(readEEPROM(PUZZLE_5X5) < 10 ? " " : "");
      arduboy.print(readEEPROM(PUZZLE_5X5));
  		arduboy.print("/");
  		arduboy.print(puzzles_5x5_count);
  		break;
  	  
  	case PUZZLE_6X6:
  		arduboy.print("Easy      ");
      arduboy.print(readEEPROM(PUZZLE_6X6) < 10 ? " " : "");
  		arduboy.print(readEEPROM(PUZZLE_6X6));
      arduboy.print("/");
  		arduboy.print(puzzles_6x6_count);
  		break;
  	  
  	case PUZZLE_7X7:
  		arduboy.print("Medium    ");
      arduboy.print(readEEPROM(PUZZLE_7X7) < 10 ? " " : "");
  		arduboy.print(readEEPROM(PUZZLE_7X7));
      arduboy.print("/");
  		arduboy.print(puzzles_7x7_count);
  		break;
  	  
  	case PUZZLE_8X8:
  		arduboy.print("Hard      ");
      arduboy.print(readEEPROM(PUZZLE_8X8) < 10 ? " " : "");
  		arduboy.print(readEEPROM(PUZZLE_8X8));
      arduboy.print("/");
  		arduboy.print(puzzles_8x8_count);
  		break;
  	  
  	case PUZZLE_9X9:
  		arduboy.print("Extreme   ");
      arduboy.print(readEEPROM(PUZZLE_9X9) < 10 ? " " : "");
  		arduboy.print(readEEPROM(PUZZLE_9X9));
  		arduboy.print("/");
  		arduboy.print(puzzles_9x9_count);
  		break;  		
  }
  
  arduboy.setTextColor(WHITE);
  arduboy.setTextBackground(BLACK);
  
}


/* ----------------------------------------------------------------------------
 *   Handle the puzzle select menu.  
 *   
 *   Users can simply restart the level or continue playing.  If this screen
 *   was accessed via the 'level select' screen the "Continue Playing" message  
 *   is shown otherwise the "Restart Puzzle" message is displayed.
 */
void puzzleSelect() {

  clearHighlightAndSelection();

  arduboy.clear();
   
  if (arduboy.justPressed(UP_BUTTON) && puzzleSelect_selectedItem > 0)         { puzzleSelect_selectedItem--; }
  if (arduboy.justPressed(DOWN_BUTTON) && puzzleSelect_selectedItem < 1)       { puzzleSelect_selectedItem++; }
  if (arduboy.justPressed(B_BUTTON))                                           { gameState = STATE_LEVEL_SELECT; }
  
  if (arduboy.justPressed(A_BUTTON)) { 
	  
	  if (puzzleSelect_selectedItem == 1) {
		  
		  puzzle.index = 0;
      updateEEPROM(puzzle.level, puzzle.index);
           
	  }
	  
	  if (puzzleSelect_selectedItem == 0) {


      // If all puzzles in the current level are completed, simply re-show the last puzzle ..
      
		  puzzle.index = (readEEPROM(puzzle.level) == getNumberOfPuzzles(puzzle.level) ? readEEPROM(puzzle.level) -1 : readEEPROM(puzzle.level));
		  
	  }
	  
	  gameState = STATE_INIT_GAME;
	  
  }
  
	
  
  // Render menu ..
  
  renderPuzzleOption(MENU_ITEM_2_X, MENU_ITEM_2_1_Y, (prevState == STATE_LEVEL_SELECT ? "Continue Playing" : " Restart Puzzle "), (puzzleSelect_selectedItem == 0));
  renderPuzzleOption(MENU_ITEM_2_X, MENU_ITEM_2_2_Y, "  Reset Level", (puzzleSelect_selectedItem == 1));
    
}


/* ----------------------------------------------------------------------------
 *   Render a single puzzle menu item.  
 */
void renderPuzzleOption(byte x, byte y, String message, byte highlight) {

  if (highlight) {
	  
	  arduboy.setTextColor(BLACK);
	  arduboy.setTextBackground(WHITE);
	  arduboy.fillRect(x - 1, y - 2, MENU_ITEM_2_WIDTH, MENU_ITEM_2_HEIGHT, WHITE);
	  
  }
	
  arduboy.setCursor(x, y);
  arduboy.print(message);
  
  arduboy.setTextColor(WHITE);
  arduboy.setTextBackground(BLACK);
  
}

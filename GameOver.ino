/* ----------------------------------------------------------------------------
 *   Render the Game Over screen.
 *   
 *   If this is the last puzzle in the level, the message 'Level Finished' is
 *   displayed otherwise a simple 'Congratulations' is shown.
 */
void gameOver() { 
  
  arduboy.delayShort(1000);
  arduboy.clear();


  
  // Play 'puzzle solved' tune before the message is shown ..

  arduboy.delayShort(1000);

  arduboy.setTextColor(BLACK);
  arduboy.setTextBackground(WHITE);

  arduboy.fillRect(12, 23, 104, 18, WHITE);
  
  if (puzzle.index == getNumberOfPuzzles(puzzle.level) - 1) {
  
    arduboy.setCursor(21, 28);
    arduboy.print("Level Finished!");
    gameState = STATE_LEVEL_SELECT;
  
  }
  else {
   
    arduboy.setCursor(18, 28);
    arduboy.print("Congratulations!");
    gameState = STATE_INIT_GAME;

  }

  puzzle.index++;
  updateEEPROM(puzzle.level, puzzle.index);
  
  arduboy.display();
  arduboy.setTextColor(WHITE);
  arduboy.setTextBackground(BLACK);

  gameOverDelay(1000);
  
}


/* ----------------------------------------------------------------------------
 *   Delay the screen for a period of time.  
 *   
 *   The delay can be cancelled by clicking either the A or B button.
 */
void gameOverDelay(int delayLength) {

  arduboy.pollButtons();

  while (delayLength >= 0) {

    if (arduboy.justPressed(A_BUTTON) || arduboy.justPressed(B_BUTTON)) { break; /* return true;*/ }
    
    arduboy.delayShort(5);  
    delayLength--;

  }
  
}


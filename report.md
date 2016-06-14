## Jamie Maher
## CSE 20211
## Final Lab

##### Summary

For this lab, I decided to recreate the classic computer game, Minesweeper. The rules are the same as any usual Minesweeper game. The user selects blocks to clear, and flags blocks to avoid using the numerical clues on the cleared blocks. The user is alerted to a win or a loss and can play again or quit the program. 

##### Internal Program

Internally, the program relies heavily on the use of structures. Each block in the array of structures has information attached to it, like if the block is covered or uncovered, if a flag has been placed on the block, whether or not a mine is located in the block, and the x and y position of the upper left corner of the block on the display window. 

##### Logic

First, the board is generated. This is done by randomly choosing integers, and if it is less than  a certain value (which could be changed internally to change the difficulty of the board), a mine is placed there and the information inside that block’s structure is updated accordingly. After all the mines have been placed, the find_count function is used to go through each block and look at all its neighboring blocks. It counts how many mines are in the neighbors, and changes the  block’s count in the structure. Then the program continues by obtaining the next of the user’s  events. If it is a mouse click, the location of the click and corresponding block is found and if it is a mine, the game is over. If not, the block is uncovered. If it is a block with no count, in  other words none of its neighbors contain a bomb, then all of its neighbors are uncovered. This process is then repeated if any of the uncovered blocks happened to also have no mines in its neighbors. If the user presses ‘f’ over one of the blocks, a flag is placed there, and this block will not be automatically uncovered if something like the previous case happens. 

##### Final Logic

When a mine has been clicked on, the user loses and the program displays a screen saying so. To find out if the user has won the game, there is a function that checks the location of all the mines and all the uncovered blocks. If the only uncovered blocks contain mines, and no mines are showing, then the user has won the game and will be alerted. 

##### Testing

To ascertain the accuracy of this program, I tested it with varying levels of difficulty, situations, and  outcomes. I would purposely misplace flags or lose to see what would happen. Since it was  working like the traditional Minesweeper game, I was able to conclude that the functions and  program were working properly. As a final test, I let some of my friends who knew how to play Minesweeper play the game and took some of their suggestions. Some wanted the fonts and  colors to be more readable, so I adjusted those. I also added some animation to the welcome screen to create a more aesthetically pleasing game. 

##### Future Improvements

To improve upon the game, I could consider adding other levels of difficulty. This could be  achieved by changing the amount of mines placed, or changing the size or the board. I could also have given the user to put a ‘?’ on the blocks as well. 

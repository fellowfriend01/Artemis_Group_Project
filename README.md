# Artemis_Group_Project
Notes:
Remove int main from clue.cpp, replace with function to load clues from clues.txt.
Remove loadClues from TreasureHunt.cpp? Assign vector "clues" to return from clues.cpp?

Compilation:
This project uses a modular structure, meaning the code is split across multiple files. To run the program, you must compile all .cpp files together in a 
single command so the linker can connect the class definitions.

Using g++, run the following in your terminal: g++ main.cpp TreasureHunt.cpp Clue.cpp -o TreasureHunt

When you run this, g++ compiles each .cpp file into hidden temporary object files. g++ then calls the Linker. The Linker looks at those temporary files, connects the function calls, and stitches them together. The Linker saves that final combined program using the name you provided after the -o flag.

Team Roles:
Each person was assigned a file to complete. This included the Clue.cpp (Shruti), Clue.h (Tanvi), Map.txt (Bhavini), TreasureHunt.cpp (Jeslyn), 
TreasureHunt.h (Hana), clues.txt (Noah), main.cpp (Thomas). Because some parts of the code were easier than others (ie. clues.txt and main.cpp), these 
members worked on any additional tasks. Noah completed most of the debugging and integration, while Jeslyn and Thomas wrote the ReadMe and included the 
bonus point opportunities.

AI Tools:
AI assistance was minimal. By primarily limiting its use to learning and finalizing bug fixes, we ensured that group members contributed the majority of 
the work and progress.

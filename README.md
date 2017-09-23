***Krishna Dwypayan Kota***
***20172076***

***OS assignment 1 Text Editor***

*Kindly execute small files, might be the case that the data structure used would not be able to handle large files*

The editor runs in 3 modes
-> Normal mode
	- Open an existing file.
	- Navigation : Allows scrolling (both horizontal and vertical) using h, j, k, l character keys
     - Go to first line of file : Pressing ‘gg’ takes the cursor to the first line of the file.
     -	 Go to last line of file : Pressing ‘G’ takes the cursor to the last line of the file.

-> Command mode
	- Implementation using fork/exec system calls to display the various shell commands.
	- Quit and force quit.
	- Partial implementation of saving the data.

-> Insert mode
	- Implementation of Data Structure to store the data from an existing file.
	- Appending to the file.
	- insertion and deletion at a particular position.
	- Bugs while insertion in empty lines
	- Backspace functionality

-> Switching between modes
     	- Normal to Insert/Edit mode - on pressing key ‘i’.
	- Insert/Edit to Normal mode OR Command Line to Normal mode - on pressing key “esc”.
     	- Normal to command-line mode - by prefixing “:” in front of your command.

-> Display Characteristics
	- Status bar displaying the current mode and the current cursor positions
	- Added text scrolling up/down
	- Dynamic window sizing 

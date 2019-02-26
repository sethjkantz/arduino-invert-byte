
# invertByte.ino
#### -Seth Kantz

This program is used to determine the inverse of an 8 byte array through a serial connection to a Moteino board.

## Setup 
To push the code to the board simply connect the board to your computer through a serial connection, open invertByte.ino in the Arduino IDE, and click upload.

## Use
In order to communicate with the board, first open up the Serial Monitor (ctrl + shift + m in the Arduino IDE) and begin typing.  The program will ignore all information typed until it comes across "0x".  The program will then consider the next two valid hex characters (works with both upper and lowercase) to be the information for that byte. It will print the byte you inputted into serial.  This will be repeated until 8 bytes have been read in.  Once this happens, the program will print the inverted output array.  It will then loop through again and wait for the next 8 bytes.

## Example

input: 		
		0xAB 0xBA 0xB1 0xBE 0xBC 0xB6 0xAB 0xA6 <br/>
		[0x 0 1 0x--23. 0x:45, 0x6 7 0x89, 0xab, 0xcd, 0xef] <br/>
		0xfe 0xdc 0xba 0x98 0x76 0x54 0x32 0x10 <br/>

output:
		Input  (HEX) :  [0xAB,0xBA,0xB1,0xBE,0xBC,0xB6,0xAB,0xA6] <br/>
		Output (HEX) :  [0x54,0x45,0x4E,0x41,0x43,0x49,0x54,0x59] <br/>
		Input  (HEX) :  [0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef] <br/>
		Output (HEX) :  [0xFE,0xDC,0xBA,0x98,0x76,0x54,0x32,0x10] <br/>
		Input  (HEX) :  [0xfe,0xdc,0xba,0x98,0x76,0x54,0x32,0x10] <br/>
		Output (HEX) :  [0x01,0x23,0x45,0x67,0x89,0xAB,0xCD,0xEF] <br/>

				

## Notes
- If you wish to change the size of the array read in, simply change the #define ARRSIZE statement.
- If your serial connection is using a different BPS, change the #define BPS statement.
- Compiled and tested on Arduino Uno board.
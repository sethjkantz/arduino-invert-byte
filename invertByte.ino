/* NAME:      Seth Kantz
 * PROJECT:   Hardware Intern Coding Problem
 * PURPOSE:   Read in 8 bytes from serial, invert, and output to serial.
 *            For use with the MonteinoCore Board
 * 
 * Ex:       Input  0xAB 0xBA 0xB1 0xBE 0xBC 0xB6 0xAB 0xA6
 *           Output 0x54 0x45 0x4E 0x41 0x43 0x49 0x54 0x59
 */
 
#define ARRSIZE 8
#define BPS 9600


int i, j,currByte = 0;
unsigned char c1,c2,byteOut[ARRSIZE][2],num[2];


void setup() {
  // opens up  serial connection 
  Serial.begin(BPS);
}

void loop() {
  
  // read in new byte when available
  if(Serial.available() > 0 && currByte < ARRSIZE){
    // skips information to read in until a leading 0x appears
    skipToHex(0);
    if(currByte == 0){
      Serial.print("Input  (HEX) :  [");  
    }
    Serial.print("0x");
    for(i=0;i<2;i++){
      //gets next character to be read in
      num[i] = getNextChar();
      Serial.print((char)num[i]); 
      // converts it into a hex value 
      num[i] = ATOH(num[i]);   
      //inverts the hex value and subtract 240 (because it will lead with 1111 xxxx) 
      byteOut[currByte][i] = (~num[i])-240;
    }
    currByte++;

    // prints for formatting in Serial
    if(currByte >=ARRSIZE){
      Serial.println("]");  
    }else{
      Serial.print(",");
    }   
  }
  

  // write to output when all 8 bytes have been read in
  if(currByte>=ARRSIZE){
    Serial.print("Output (HEX) :  [");
    for(i=0;i<ARRSIZE;i++){
      Serial.print("0x");
      Serial.print(HTOA(byteOut[i][0]));
      Serial.print(HTOA(byteOut[i][1]));
      if(i!=(ARRSIZE-1)){
        Serial.print(",");  
      }
    }
    Serial.println("]");    
    currByte=0;
  }
}



/*  FUNCTION:     skipToHex(int start)
 *  INPUT:        int start - is zero if has not found 0 yet, otherwise
 *                is checking for x.
 *  PURPOSE:      recurse through itself until a 0x is read in through serial
 * 
 */
void skipToHex(int start){
  char c;
  // waits for a character from Serial
  while(Serial.available()==0){}
  c = Serial.read();

  if(c == '0'){
    // if 0 is found, search for x
    skipToHex(1);
  } else if(c=='x' && start != 0){
    //if already found a 0
      return;
  }else{
    // keeps looking until 0x is found
    skipToHex(0);
  }
}


/*  FUNCTION:     getNextChar()
 *  INPUT:        VOID
 *  PURPOSE:      wait until a character in hex available in serial
 *                and returns it (0-9, a-f, or A-F)
 */
char getNextChar(){
  char c;
  //waits for a character from Serial
  while(Serial.available() == 0){}
  c = Serial.read();  
  
  // return said value if it is an acceptable hex value
  if((c >= '0' && c<='9')||(c>='a'&&c<='f')||(c>='A'&&c<='F')){
    return c;
  }else{
    //else wait until an acceptable one is sent
    return getNextChar();
  }
}


/*  FUNCTION:         ATOH()
 *  INPUT:            char c  - character to be manipulated
 *  PURPOSE:          convert a char in ascii to a byte in hex
 */
char ATOH(char c){
  if(c > 47 && c < 58){
    // if number
    return (c - 48); 
  }else if(c > 64 && c < 71){
    // if  uppercase letter 
    return (c-55);
  }else if(c > 96 && c <103){
    // if lowercase letter
    return (c-87);
  }else{
    // if error occured 
    return 0;
  }   
}




/*  FUNCTION:     HTOA()
 *  INPUT:        char c  - character to be manipulated 
 *  PURPOSE:      convert a hex value into its ASCII value
 *                (automatically prints in caps)
 */
char HTOA(char c){
  if(c >= 0 && c < 10){
     // if number
    return (c + 48);
  }else if(c >= 10 && c < 17){
    // if  uppercase letter 
    return (c+55);
  }else{
    // if error occurred
    return 0;
  } 
}


/*
 * http://www.clounce.com
 *
 * With this code, Clounce will show you how you use variables to manipulate your data.
 * Of course, you would not use the current code in real scenarios, but these are created
 * to help you understand the concepts.
 *
 */


// we define a function to print a number (integer) via Serial port
// with leading zeros.
String toBinary(int number) 
{
  String output = "";
  for (unsigned int i = (1 << (sizeof(number)*8)-1); i; i >>= 1) 
    output.concat(number & i ? '1' : '0');
  return output;
}

bool isOdd(int number)
{
  return (number % 2) == 1;
}

void setup()
{
  // initialise serial communication
  //  we will use 9600 baud rate 
  //  and default config = 8N1 (8-buts for data, no parity, and 1 stop bit)
  Serial.begin(9600);

  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // send an intro message
  // this is a must for learning a new language!
  Serial.println("\nHello World!");
  Serial.println(); // like adding a \n at the end of the previous string
}

void loop()
{
  //----------------------------------------------------------------------------------------------
  // let's experiment a bit with C variables
  
  // The size of an int, unsigned int, short, and a word are the same on Arduino UNO (On Due, int has different size)
  String message = String("byte sizes:\n");
  message.concat("\t int = " + String(sizeof(int)) + "bytes\n");
  message.concat("\t word = " + String(sizeof(word)) + "bytes\n");
  message.concat("\t short = " + String(sizeof(short)) + "bytes\n");
  message.concat("\t unsigned int = " + String(sizeof(unsigned int)) + "bytes\n");

  message.concat("\t long = " + String(sizeof(long)) + "bytes\n");
  message.concat("\t unsigned long = " + String(sizeof(unsigned long)) + "bytes\n");
  message.concat("\t float = " + String(sizeof(float)) + "bytes\n");
  message.concat("\t double = " + String(sizeof(double)) + "bytes\n");
  
  Serial.println(message);
  Serial.println("\n\n----------------------------------------------\n\n"); // pretty dividers!

  // Hexadecimal and binary representations are frequently used for representing flags and switches
  // Displaying them is easy with Arduino's String library
  int value = 175; // 175 base 10
  String hexValue = String(value, HEX);
  hexValue.toUpperCase();
  message = String(String(value) + " = 0x" + hexValue);
  Serial.println(message);
  
  String binaryValue = String(value, BIN);
  Serial.println(String(value) + " = " + binaryValue + " in binary format");

  Serial.println("\n\n----------------------------------------------\n\n"); // pretty dividers!

  // Let's talk arrays
  char msg[] = "This is a c string";
  int len = sizeof(msg) / sizeof(char);
  Serial.println("Our c string has a length of " + String(len));
  // print the message but make it funny
  for (int i = 0; i < len; i++) {
    String letter = String(msg[i]) + " ";    
    if (isOdd(i))
      letter.toUpperCase();
    else
      letter.toLowerCase();
    Serial.print(letter);
  }  

  Serial.println("\n\n----------------------------------------------\n\n"); // pretty dividers!

  // array of string
  char* names[] = {"Clounce", "Arduino", "C"};
  Serial.println("There are " + String(sizeof(names)/sizeof(names[0])) + " elements in names array!");

  Serial.println("\n\n----------------------------------------------\n\n"); // pretty dividers!

  // sometimes we need to store data in arrays and then get some statistics
  // here we fill up an array of 24 floating point numbers, representing the temperature 
  // in degrees Celsius on the hour for 1 day. Then we find the average temperature for that day
  float temperature[] = {10.0, 9.9, 9.8, 9.7, 9.9, 10.1, 10.5, 11.1, 
                         12.7, 13.0, 13.5, 14.2, 13.7, 14.5, 14.7, 14.0, 
                         14.2, 14.0, 13.7, 13.8, 13.2, 12.7, 12.3, 11.9};
  float total = 0.0;
  // we can either assume that we have 24 entries in 1 day, or else compute it. The latter is a 
  // better choice, as we do not have to change our code if we decide to sample temperature every 
  // 30mins instead every hour.
  len = sizeof(temperature) / sizeof(float);
  for(int i = 0; i < len; i++) 
    total += temperature[i];

  Serial.println("Average temperature is " + String(total / len) + " degrees Celsius.");

  Serial.println("\n\n----------------------------------------------\n\n"); // pretty dividers!
  
  // Bit manipulation is also important.  Here we show how to do basic operations.
  for(int i = 0; i < 5; i++) {
    int x = random(3, 1000);
    Serial.println("Random value: " + String(x));
    Serial.println("            : " + String(x, BIN));
    Serial.println("       bit 0: " + String(bitRead(x, 0)));
    Serial.println("       bit 1: " + String(bitRead(x, 1)));
    if (bitRead(x, 2))
      Serial.println("       bit 2: is set!");
    else
      Serial.println("       bit 2: is NOT set!");
  }

  Serial.println("\n\n----------------------------------------------\n\n"); // pretty dividers!
  
  // binary fun 
  int x = 0;
  for (int i = 0; i < 8; i++) {
    int j = x | 1 << i;
    Serial.println(toBinary(j));
  }

  Serial.println("\n\n----------------------------------------------\n\n"); // pretty dividers!
  Serial.println("Bye bye!");
    
  while (true); // block here
}

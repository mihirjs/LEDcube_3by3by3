/*
** Arduino sketch for powering an LED cube.
** Loops through each pin in each row for the
** designated time DELAY (in usec). The current 
** pattern switches on the ith column of the ith 
** plane waits for the designated delay and then turns 
** it off and goes to the next column.
*/

const int CUBESIZE = 3;
const int PLANESIZE = 9;
const int DELAY_ON = 10;



/*
** Defining pins in array makes it easier to rearrange how cube is wired
** Adjust numbers here until LEDs flash in the right order
*/
int LEDPin[] = {5,4,6,7,8,9,10,11,12};  //order of columns (+)
int PlanePin[] = {3,2,1}; //order of planes (-)
int initial=0;
// initialization
void setup()
{
	int pin; 
	// set up LED pins as output (active HIGH)
	for (pin=0; pin<PLANESIZE; pin++)
        {
		pinMode( LEDPin[pin], OUTPUT );
                digitalWrite( LEDPin[pin], 0 );
        }
	// set up plane pins as outputs (active LOW)
	for (pin=0; pin<CUBESIZE; pin++)
        {
		pinMode( PlanePin[pin], OUTPUT );
                digitalWrite( PlanePin[pin], 1);
        }
}

void loop()
{
        int input[][9] = {{1,1,1,0,0,0,0,0,0},{0,0,0,1,1,1,0,0,0},{0,0,0,0,0,0,1,1,1}}; 
        int oldcube[3][9] = {{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0}};
        int newcube[3][9]= {{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0}};
       
        for (int i=0;i<CUBESIZE;i++)
        {
          for (int l=0; l<PLANESIZE; l++)
          {
            newcube[0][l]=input[i][l];
          }
          for (int j=1;j<CUBESIZE;j++)
          {
            for (int l=0; l<PLANESIZE; l++)
            {
              newcube[j][l]=oldcube[j-1][l];
            }
          }
          for (int m=0;m<500;m++)
          {
            planecontrol(newcube);      
          }
          delay(50);
          
          for (int j=0;j<CUBESIZE;j++)
          {
            for (int l=0; l<PLANESIZE; l++)
            {
              oldcube[j][l]=newcube[j][l];
            }
          }
          
     }   
}

void planecontrol(int in[][9])
{
  int ledrow, ledpin, ledcol;
      for (ledrow = 0; ledrow<CUBESIZE; ledrow++)
             {        
                digitalWrite(PlanePin[ledrow],0);
      		for (ledpin = 0; ledpin<PLANESIZE;ledpin ++)
      		{
                     digitalWrite(LEDPin[ledpin],in[ledrow][ledpin]); 
                     delayMicroseconds (DELAY_ON);
                     digitalWrite(LEDPin[ledpin],0);
                }
              digitalWrite(PlanePin[ledrow],1);  
             }
}



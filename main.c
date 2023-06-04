#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define NUMBER_OF_COLORS 500 //please enter the number of declared colors in the file - less than 4 294 967 295
#define DEFAULT_VALUE 128

typedef struct
{
    uint8_t min;
    uint8_t max;


    char hex[10];       //^([0-9a-f]{8})$ 
    uint8_t red;        //in range between 0 and 255
    uint8_t green;      //in range between 0 and 255
    uint8_t blue;       //in range between 0 and 255
    uint8_t alpha;      //in range between 0 and 255
    int16_t hue;       //in range between 0 and 360
    double saturation;   //in range between 0 and 1
    double lightness;    //in range between 0 and 1


}Color_t;



void mix();
int mix2();
void lowest();
void highest();
void mix_saturate();

void intToHex();

///////***FUNCTION ONLY FOR HSL***///////
void lightness();
void saturation();
void hue();
///////***PARSER FUNCTION***/////////////
int HexToDec1b1();
void intParser();
void hexParser();
void Parser();

/////////***USER FUNCTION***/////////////

void HSL();
void RGBAchooser();
void printer();
void CommandListPrinter();
void SaveColor();





int main()
{

    Color_t Color;

   // highest("colors.txt",&Color);

    char text[20];
    char *ParseCommand;
    int Flag=0;

    do
    {
   
        printf("\nEnter command (or -commands) : ");
        fgets(text,20,stdin);

        ParseCommand=strtok(text, "\n"); 
            
        if( 0 == (strcmp(ParseCommand,"-commands")))
        {
            CommandListPrinter();

            printf("\nEnter command (or -commands) : ");
            fgets(text,20,stdin);

            ParseCommand=strtok(text, " "); 
            
        }
        else
        {
            ParseCommand=strtok(text, " "); 
        }


        if(0 == (strcmp(ParseCommand,"-m")) || 0 == (strcmp(ParseCommand,"--mode")) )
        {
            ParseCommand=strtok(NULL, "\n");

            if(0 == strcmp(ParseCommand,"mix"))
            {
                mix2(&Color);
                printer(&Color);
                SaveColor("colors.txt", &Color);
                Flag = 1;
            }
            else if(0 == strcmp(ParseCommand,"lowest"))
            {
                RGBAchooser(lowest,"colors.txt", &Color);
                printer(&Color);
                SaveColor("colors.txt", &Color);
                Flag = 1;

            }
            else if(0 == strcmp(ParseCommand,"highest"))
            {
                RGBAchooser(highest,"colors.txt", &Color);
                printer(&Color);
                SaveColor("colors.txt", &Color);
                Flag = 1;
            }
            else if(0 == strcmp(ParseCommand,"mix-saturate"))
            {
                mix_saturate("colors.txt",&Color);
                printer(&Color);
                SaveColor("colors.txt", &Color);
                Flag = 1;
            }
            else
            {
                printf("\n\nWrong command!\n\n");
                CommandListPrinter();

            }

        }
        else
        {
            printf("\n\nWrong command!\n\n");
            CommandListPrinter();
        }

    } while (Flag == 0);

}


void mix(Color_t *Color)
{
    int value;

    printf("Create your RGBA color! Please enter value betwen 0-255 for RGBA\n\r");
    printf("Red(0-255) : ");
    scanf("%d", &value);

    if(value >= 0 && value <= 255)
    {
        Color->red = value;
    }
    else
    {
        printf("Wrong value! Deafult set(R=0)\n");
        Color->red = 0;
    }

    printf("Green(0-255) : ");
    scanf("%d", &value);

    if(value >= 0 && value <= 255)
    {
        Color->green = value;
    }
    else
    {
        printf("Wrong value! Deafult set(G=0)\n");
        Color->green = 0;
    }

    printf("Blue(0-255) : ");
    scanf("%d", &value);

    if(value >= 0 && value <= 255)
    {
        Color->blue = value;
    }
    else
    {
        printf("Wrong value! Deafult set(B=0)\n");
        Color->blue = 0;
    }

    printf("Alpha(0-255) : ");
    scanf("%d", &value);

    if(value >= 0 && value <= 255)
    {
        Color->alpha = value;
    }
    else
    {
        printf("Wrong value! Deafult set(A=0)\n");
        Color->alpha = 0;
    }

    HSL(Color);

}

int mix2(Color_t *Color)
{
    char buff[20];
    char *Ptr;
    


    int NumberOfColors,x;
    int16_t i,counter, redTmp, blueTmp, greenTmp, alphaTmp;
    uint16_t redBin=0,greenBin=0,blueBin=0,alphaBin=0;

    printf("How many color do You want to mix? (max 127) :");
    scanf("%d", &NumberOfColors);
    


    if(NumberOfColors<0 || NumberOfColors>127)
    {
        NumberOfColors = 0;
        printf("wrong value! default answer = 0\n");

        return 1;
    }
    
    

    printf("\nRGBA Format : /^([0-9]{1,3},){3}[0-9]{1,3}$/ - for example: 255,0,0,255\n");
    printf("or /^[0-9a-f]{3}|[0-9a-f]{6}|[0-9a-f]{8})$/ - for example: fff v ff00ff v ff0000ff\n\n");



    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}

    for(i=1; i<=NumberOfColors; i++, counter++)
    {
        printf("Color %d : \n", i);

        if( ((strncmp(Ptr = fgets(buff,20,stdin),"\n",1)) == 0) || (0>=strlen(buff) ))
        {
            
            printf("Wrong all Value! RGBA = Default = %d\n", DEFAULT_VALUE);
            redTmp = DEFAULT_VALUE;
            greenTmp = DEFAULT_VALUE;
            blueTmp = DEFAULT_VALUE;
            alphaTmp = DEFAULT_VALUE;

            redBin+=redTmp;
            greenBin+=greenTmp;
            blueBin+=blueTmp;
            alphaBin+=alphaTmp;

            continue;
            
        }

        //printf("buff:%s\n", buff);


        if((strpbrk(buff,",")==NULL))
        {     
            if( (strlen(buff)==4) || (strlen(buff)==7) || (strlen(buff)==9) )
            {

            Color_t TmpColor;
            Parser(&TmpColor,buff);
            redTmp = TmpColor.red;
            greenTmp = TmpColor.green;
            blueTmp = TmpColor.blue;
            alphaTmp = TmpColor.alpha;

                /*
                printf("red: %d\n", redTmp);
                printf("green: %d\n", greenTmp);
                printf("blue: %d\n", blueTmp);
                printf("alpha: %d\n", alphaTmp);
                */

            }
            else 
            {

            printf("Wrong all Value! RGBA = 0\n");
            //redTmp = DEFAULT_VALUE;
            //greenTmp = DEFAULT_VALUE;
            //blueTmp = DEFAULT_VALUE;
           //alphaTmp = DEFAULT_VALUE;

            //redBin+=redTmp;
            //greenBin+=greenTmp;
           // blueBin+=blueTmp;
           // alphaBin+=alphaTmp;

            }
        }
        else
        {

            if((((Ptr = strtok(buff,",")) != NULL) && (strlen(Ptr)>=0) && (strspn(Ptr,"0123456789")==strlen(Ptr))))
            {
                redTmp = atoi(Ptr);
                


                if(!((redTmp >= 0) && (redTmp <= 255)))
                {
                    redTmp=DEFAULT_VALUE;
                    printf("Wrong value! R value = Deafult = %d\n", redTmp);
                }
            } 
            else 
            {   
                redTmp=DEFAULT_VALUE;
                printf("Wrong input! R value = Deafult = %d\n", redTmp);
            }


            if((((Ptr = strtok(NULL,",")) != NULL) && (strlen(Ptr)>=0) && (strspn(Ptr,"0123456789")==strlen(Ptr))))
            {
                greenTmp = atoi(Ptr);

                if(!((greenTmp >= 0) && (greenTmp <= 255)))
                {
                    greenTmp=DEFAULT_VALUE;
                    printf("Wrong value! G value = Deafult = %d\n", greenTmp);
                }
            } 
            else 
            {   
                
                greenTmp=DEFAULT_VALUE;
                printf("Wrong input! G value = Deafult = %d\n", greenTmp);
            }


            if((((Ptr = strtok(NULL,",")) != NULL) && (strlen(Ptr)>=0) && (strspn(Ptr,"0123456789")==strlen(Ptr))))
            {
                blueTmp = atoi(Ptr);

                if(!((blueTmp >= 0) && (blueTmp <= 255)))
                {
                    blueTmp=DEFAULT_VALUE;
                    printf("Wrong value! B value = Deafult = %d\n", blueTmp);
                }
            } 
            else 
            {   
                blueTmp=DEFAULT_VALUE;
                printf("Wrong input! B value = Deafult = %d\n", blueTmp);
            }


            if((((Ptr = strtok(NULL,"\n")) != NULL) && (strlen(Ptr)>=0) && (strspn(Ptr,"0123456789")==strlen(Ptr))))
            {
                alphaTmp = atoi(Ptr);

                if(!((alphaTmp >= 0) && (alphaTmp <= 255)))
                {
                    alphaTmp=DEFAULT_VALUE;
                    printf("Wrong value! A value = Deafult = %d\n", alphaTmp);
                }
            } 
            else 
            {   
                alphaTmp=DEFAULT_VALUE;
                printf("Wrong input! A value = Deafult = %d\n", alphaTmp);
            }
            
        }


    redBin+=redTmp;
    greenBin+=greenTmp;
    blueBin+=blueTmp;
    alphaBin+=alphaTmp;   

    }

    Color->red = redBin/counter;
    Color->green = greenBin/counter;
    Color->blue = blueBin/counter;
    Color->alpha = alphaBin/counter;

    HSL(Color);

}

void lowest(const char * __restrict__ File, Color_t *Color)
{
    FILE *colorsF;   

    if((colorsF=fopen(File,"r")) == NULL)
    {
        printf("file cannot be opened\n\r"); 
    } 

    char buff[20];
    char *Ptr;
    uint8_t minRed,minGreen,minBlue,minAlpha;
    uint8_t Flag = 0;
    uint32_t RealCounter = 0;

    for(uint32_t i=0; i<NUMBER_OF_COLORS && !feof(colorsF); i++)
    {

        if(fgets(buff,20,colorsF)==NULL)
        {
            continue;
        }


       Parser(Color,buff);

        if(Flag == 0)
        {
            minRed   =  Color->red;
            minGreen =  Color->green;
            minBlue  =  Color->blue;
            minAlpha =  Color->alpha;
            Flag++;
            continue;
        }

        if (minRed>Color->red)
        {
            minRed = Color->red;
        }

        if (minGreen>Color->green)
        {
            minGreen = Color->green;
        }

         if (minBlue>Color->blue)
        {
            minBlue = Color->blue;
        }

         if (minAlpha>Color->alpha)
        {
            minAlpha = Color->alpha;
        }        
    }

Color->red = minRed;
Color->green = minGreen;
Color->blue = minBlue;
Color->alpha = minAlpha;

intToHex(Color);
HSL(Color);

/*
    printf("R:%d\n",Color->red);
    printf("G:%d\n",Color->green);
    printf("B:%d\n",Color->blue);
    printf("A:%d\n",Color->alpha);
    printf("Hex:%s\n",Color->hex);
*/


    if((fclose(colorsF)) != 0)
    {
        printf("file cannot be closed\n\r");
    }

}

void highest(const char * __restrict__ File, Color_t *Color)
{
    FILE *colorsF;   

    if((colorsF=fopen(File,"r")) == NULL)
    {
        printf("file cannot be opened\n\r"); 
    } 

    char buff[20];
    char *Ptr;
    uint8_t maxRed,maxGreen,maxBlue,maxAlpha;
    uint8_t Flag = 0;
    

    for(uint32_t i=0; i<NUMBER_OF_COLORS, !feof(colorsF); i++)
    {

        if(fgets(buff,20,colorsF)==NULL)
        {
            continue;
        }

        Parser(Color,buff);

        if(Flag == 0)
        {
            maxRed   =  Color->red;
            maxGreen =  Color->green;
            maxBlue  =  Color->blue;
            maxAlpha =  Color->alpha;
            Flag++;
            continue;
        }

        if (maxRed<Color->red)
        {
            maxRed = Color->red;
        }

        if (maxGreen<Color->green)
        {
            maxGreen = Color->green;
        }

         if (maxBlue<Color->blue)
        {
            maxBlue = Color->blue;
        }

         if (maxAlpha<Color->alpha)
        {
            maxAlpha = Color->alpha;
        }        
    }

Color->red = maxRed;
Color->green = maxGreen;
Color->blue = maxBlue;
Color->alpha = maxAlpha;

intToHex(Color);
HSL(Color);

/*
    printf("R:%d\n",Color->red);
    printf("G:%d\n",Color->green);
    printf("B:%d\n",Color->blue);
    printf("A:%d\n",Color->alpha);
    printf("Hex:%s\n",Color->hex);
*/


    if((fclose(colorsF)) != 0)
    {
        printf("file cannot be closed\n\r"); 
    }

}

void mix_saturate(const char * __restrict__ File, Color_t *Color)
{
    FILE *colorsF;

    uint8_t redTmp,greenTmp,blueTmp,alphaTmp;
    double saturationTmp=0;
    char buff[20];
    char *Ptr;
    uint32_t RealCounter = 0;

    redTmp = Color->red;
    greenTmp = Color->green;
    blueTmp = Color->blue;
  

    if((colorsF=fopen(File,"r")) == NULL)
    {
        printf("file cannot be opened\n\r"); 
    } 

    for(int i=0; i<NUMBER_OF_COLORS, !feof(colorsF); i++)
    {

        if(fgets(buff,20,colorsF)==NULL)
        {
            continue;
        }
     
        Parser(Color,buff);

        RealCounter++;

        HSL(Color);

        saturationTmp+=Color->saturation;


    }


    Color->red = redTmp;
    Color->green = greenTmp;
    Color->blue = blueTmp;
    Color->saturation = (saturationTmp/RealCounter);

    

/*
    printf("R:%d\n",Color->red);
    printf("G:%d\n",Color->green);
    printf("B:%d\n",Color->blue);
    printf("A:%d\n",Color->alpha);
*/

    if((fclose(colorsF)) != 0)
    {
        printf("file cannot be closed\n\r"); //return?
    }

}

void intToHex(Color_t *Color)
{
    sprintf(Color->hex,"#%.2x%.2x%.2x%.2x", Color->red,Color->green,Color->blue,Color->alpha);
}



///////***FUNCTION ONLY FOR HSL***///////

void lightness(Color_t *Color)
{
    uint8_t R,G,B;
    float tmpMin, tmpMax;

    R = Color->red;
    G = Color->green;
    B = Color->blue;

   if (R>G)
   {
        if(R>B)
        {   
            Color->max = R;
            
            if(B>G)
            {
                Color->min = G;
            } 
            else
            {
                Color->min = B;
            }
        } 
        else 
        {
            Color->min = G;
            Color->max = B;
        }
   }
   else if (R>B)
   {
    Color->max = G;
    Color->min = B;
   }
   else
   {
    Color->min = R;
    if(B>G)
    {
        Color->max = B;
    }
    else
    {
        Color->max = G;
    }
   }
   
//  printf("%d\n",Color->max);
//  printf("%d\n",Color->min);

tmpMin =(double)Color->min/255;
tmpMax =(double)Color->max/255;

Color->lightness = ((tmpMax + tmpMin)/2);

//  printf("%.2f\n", Color->lightness);

}

void saturation(Color_t *Color)
{
    double tmpMin = (double) ((Color->min)/255.0);
    double tmpMax = (double) ((Color->max)/255.0);

    if(Color->max == Color->min)
    {
        Color->saturation=0;
        Color->hue=0;
    }
    else if(Color->lightness <= 0.5)
    {
        Color->saturation = ((tmpMax - tmpMin)/(tmpMax + tmpMin));
    }
    else if(Color->lightness > 0.5 ) 
    {
      //  printf("tmpMin:%f\n,%f\n",tmpMin,tmpMax);
        Color->saturation = ((tmpMax - tmpMin)/(2.0 - tmpMax - tmpMin));
    }
    else
    {
        printf("Error saturation");
    }

//   printf("%f\n", Color->lightness);
//   printf("%f\n", Color->saturation);
}

void hue(Color_t *Color)
{
    double r = (double)(Color->red)/255.0;
    double g = (double)(Color->green)/255.0;
    double b = (double)(Color->blue)/255.0;
    double tmpMin = (double) ((Color->min)/255.0);
    double tmpMax = (double) ((Color->max)/255.0);

    if(Color->red == Color->max)
    {
        Color->hue = (int16_t) (((g-b)/(tmpMax-tmpMin))*60);
    }
    else if (Color->green == Color->max)
    {
        Color->hue = (int16_t) (( 2.0 + ((b-r)/(tmpMax - tmpMin)))*60);
    }
    else if (Color->blue == Color->max)
    {    
        Color->hue = (int16_t) (( 4.0 + ((r-g)/(tmpMax - tmpMin)))*60);
    }
    else
    {
        printf("Error\n");   //return?
    }

    if(Color->hue < 0)
    {
        Color->hue += 360;
    }

 //   printf("%d", Color->hue);
}

/////////***PARSER FUNCTION***///////////

void intParser(Color_t *Color, char *buffToParse)
{
    char *Ptr;

    Ptr = strtok(buffToParse,",");
    Color->red = atoi(Ptr);

    Ptr = strtok(NULL,",");
    Color->green = atoi(Ptr);

    Ptr = strtok(NULL,",");
    Color->blue = atoi(Ptr);

    Ptr = strtok(NULL,"\0");
    Color->alpha = atoi(Ptr);
}

void hexParser(Color_t *Color, char *buffToParse)
{
    int len,x=1;

    char* end = strchr(buffToParse, '\n');
    
    len = strlen(buffToParse);
   // printf("%s\n", buffToParse);

    if(len > 0 && buffToParse[len-1] == '\n')
    {
        x=1;
    }
    else
    {
        x=0;
    }



    int dec[len];

   // printf("len : %d\n", len);

    for(int i=0; i<=len; i++)
    {
        dec[i]=HexToDec1b1(buffToParse,i);
       // printf("i%d = %d : ", i,dec[i]);
    }


 // printf("x=%d\n",x);

    if((len-x) == 3)
    {
        Color->red = dec[0];
        Color->green = dec[1];
        Color->blue = dec[2];
        Color->alpha = 0;
    }
    else if((len-x) == 6)
    {
        Color->red = ((dec[0]*16)+dec[1]);
        Color->green = ((dec[2]*16)+dec[3]);
        Color->blue = ((dec[4]*16)+dec[5]);
        Color->alpha = 0;
    }
    else if ((len-x) == 8)
    {
        Color->red = ((dec[0]*16)+dec[1]);
        Color->green = ((dec[2]*16)+dec[3]);
        Color->blue = ((dec[4]*16)+dec[5]);
        Color->alpha = ((dec[6]*16)+dec[7]);
    }

    
    /*
    printf("red: %d\n", Color->red);
    printf("green: %d\n", Color->green);
    printf("blue: %d\n", Color->blue);
    printf("alpha: %d\n", Color->alpha);
    */


}

int HexToDec1b1(char *ParseBuf, int WhichChar)
{
    
    int x = (int)ParseBuf[WhichChar];

    switch (x)
    {
    case 48:
        x=0;
        break;
    case 49:
        x=1;
        break;
    case 50:
        x=2;
        break;
    case 51:
        x=3;
        break;
    case 52:
        x=4;
        break;
    case 53:
        x=5;
        break;
    case 54:
        x=6;
        break;
    case 55:
        x=7;
        break;
    case 56:
        x=7;
        break;
    case 57:
        x=8;
        break;
    case 58:
        x=9;
        break;
    case 97:
        x=10;
        break;
    case 98:
        x=11;
        break;
    case 99:
        x=12;
        break;
    case 100:
        x=13;
        break;
    case 101:
        x=14;
        break;
    case 102:
        x=15;
        break;
    case 103:
        x=16;
        break;
    default:
        break;
    }

    return x;
}

void Parser(Color_t *Color, char *buffToParse)
{
    
    if(((strspn(buffToParse,",0123456789abcdef\n\0"))==strlen(buffToParse)))
    {
        if(((strpbrk(buffToParse,","))==NULL))
        {
            hexParser(Color,buffToParse);
        }
        else
        {
            intParser(Color,buffToParse);
        }
    }
    else
    {
        printf("Wrong chars!\n");
        printf("Wrong all Value! RGBA = Default = %d\n", DEFAULT_VALUE);
        Color->red = DEFAULT_VALUE;
        Color->green = DEFAULT_VALUE;
        Color->blue = DEFAULT_VALUE;
        Color->alpha = DEFAULT_VALUE;

    }
/*
    printf("red: %d\n", Color->red);
    printf("green: %d\n", Color->green);
    printf("blue: %d\n", Color->blue);
    printf("alpha: %d\n", Color->alpha);
*/
}


/////////***USER FUNCTION***/////////////


void HSL(Color_t *Color)
{
    lightness(Color);
    saturation(Color);
    hue(Color);
}

void RGBAchooser(void (*FunPtr)(const char * __restrict__ , Color_t * ),const char * __restrict__ File, Color_t *Color)
{
    int R,G,B,A,x;
    uint8_t tmpRed,tmpGreen,tmpBlue,tmpAlpha;

    printf("R? (0-No / 1-Yes) :");
    scanf("%d", &R);
    x = (R<0 || R>1)? printf("wrong value! default answer = 0\n"), R = 0 :0;

    printf("G? (0-No / 1-Yes) :");
    scanf("%d", &G);
    x = (G<0 || G>1)? printf("wrong value! default answer = 0\n"), G = 0 :0;

    printf("B? (0-No / 1-Yes) :");
    scanf("%d", &B);
    x = (B<0 || B>1)? printf("wrong value! default answer = 0\n"), B = 0 :0;
    
    printf("A? (0-No / 1-Yes) :");
    scanf("%d", &A);
    x = (A<0 || A>1)? printf("wrong value! default answer = 0\n"), A = 0 :0;


    tmpRed = (R==0)? Color->red : 0;
    tmpGreen = (G==0)? Color->green : 0;
    tmpBlue = (B==0)? Color->blue : 0;
    tmpAlpha = (A==0)? Color->alpha : 0;

        FunPtr(File, Color);  // "lowest"/"highest" or another similar

    Color->red = (R == 0)? tmpRed : Color->red;
    Color->green = (G == 0)? tmpGreen : Color->green;
    Color->blue = (B == 0)? tmpBlue : Color->blue;
    Color->alpha = (A == 0)? tmpAlpha : Color->alpha;

    HSL(Color);
}

void printer(Color_t *Color)
{
    intToHex(Color);
    printf("\nred value : %d\n", Color->red);
    printf("green value : %d\n", Color->green);
    printf("blue value : %d\n", Color->blue);
    printf("alpha value : %d\n", Color->alpha);
    printf("hex : %s\n", Color->hex);
    printf("hue : %d\n", Color->hue);
    printf("saturation : %.2f\n", Color->saturation);
    printf("lightness: %.2f\n", Color->lightness);

}

void CommandListPrinter()
{
    printf("Command list:\nbegin from '--mode MODE' or '-m MODE' \n");
    printf("Modes:\n");
    printf("'mix' - create new color\n");
    printf("'lowest' - find the smallest value selected from  RGBA and use in current color\n");
    printf("'highest' - find the bigest value selected from RGBA and use in current color \n");
    printf("'mix-saturate' - set new saturation eqal to average of other clors\n");
}

void SaveColor(const char * __restrict__ File, Color_t *Color)
{   
    FILE *colorsF;
    int x;
    printf("Save(0-no, 1-yes) ?\n");
    scanf("%d", &x);

    if( (x==1) )
    {
        if((colorsF=fopen(File,"a")) == NULL)
        {
            printf("file cannot be opened\n\r"); 
        } 

        
        char hex[9];
        sprintf(hex,"\n%.2x%.2x%.2x%.2x\n", Color->red, Color->green, Color->blue, Color->alpha);
        fputs(hex,colorsF);


        if((fclose(colorsF)) != 0)
        {
            printf("file cannot be closed\n\r"); //return?
        }
        else
        {
            printf("saved succesfully!\n");
        }
    }
    
}
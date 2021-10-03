/*
Name: James Lee

Class Account: cssc3719

CS520-01 Spring 2021

Assignment#1, Hex/Binary Dump Source Code
*/

//Include lines
#include<stdio.h>
#include<stdlib.h>
#include<string.h>



//Hex Printer
void _hexPrinter(const char *g){
    FILE *fp;
    unsigned char buffers[17];
    int address = 0;
    int incCounter = 0;
    int hexChecker = 0;
    unsigned char c;

    //Opening the file and seeing if it is a valid file. This function will print an error otherwise.
    fp = fopen(g, "r");
    if(fp == NULL){
        printf("Error in opening file");
        return;
    }

    //This do while loop will loop through each character in the file to calculate and print the address, hex values, and readable print.
    do{
        c = (unsigned char) fgetc(fp);

        //Checks to see if the end of the file is reached, and if so it will either finish the output line if needed, or just break if 
        //there is no leftover characters.
        if(feof(fp)){
            if(incCounter == 0){
                break;
            }
            if(incCounter < 16){
                int times = 16 - incCounter;
                times /= 2;
                while(times !=0){
                    printf("     ");
                    times--;
                }
                printf("%s", buffers);
            }
            break;
        }

        //This will print out the correct address.
        if(incCounter == 0){
            printf("%07x:  ", address);
        }

        //This will change non-printable characters to '.' and put it into the char array
        //buffers, or it will just put it in if the character is human readable.
        if(c > 126 || c < 32){
            buffers[incCounter] = '.';
        }
        else{
            buffers[incCounter] = c;
        }

        //This will print out the hex numbers in octets. It will check that every two hex
        //numbers will create a space after in order to make the octects. 
        printf("%02x", c);
        hexChecker++;
        incCounter++;
        if(hexChecker == 2){
            printf(" ");
            hexChecker = 0;
        }

        //This checks to see that if 16 characters have been read through, we will print out 
        //the 16 as human readable characters, and then go to a new line.
        if(incCounter == 16){
            printf("%s", buffers);
            printf("\n");
            hexChecker = 0;
            incCounter = 0;
            address += 16;
        }


    } while(1);
    

}


//Binary Printer
void _binaryPrinter(const char *h){
    FILE *fp;
    unsigned char buffers[9];
    int address = 0;
    int incCounter = 0;
    int binChecker = 0;
    unsigned char c;
    int binary[8];


    //Opening the file and seeing if it is a valid file. This function will print an error otherwise.
    fp = fopen(h, "r");
    if(fp == NULL){
        printf("Error in opening file");
        return;
    }

    //This do while loop will loop through each character in the file to calculate and print the address, binary values, and readable print.
    do{
        c = (unsigned char) fgetc(fp);

        //Checks to see if the end of the file is reached, and if so it will either finish the output line if needed, or just break if 
        //there is no leftover characters.
        if(feof(fp)){
            if(incCounter == 0){
                break;
            }
            if(incCounter < 8){
                int amount = 8 - incCounter;
                while(amount !=0){
                    printf("         ");
                    amount --;
                }
                printf("%s", buffers);
            }
            break;
        }

        //This will print out the correct address.
        if(incCounter == 0){
            printf("%07x:  ", address);
        }

        //This will change non-printable characters to '.' and put it into the char array
        //buffers, or it will just put it in if the character is human readable.
        if(c > 126 || c < 32){
            buffers[incCounter] = '.';
        }
        else{
            buffers[incCounter] = c;
        }

        //This will print out the binary numbers in 8 bytes per record. It will also check that 
        //every two binary numbers will create a space after in order to make the format correct. 
        for(int n = 0; n < 8; n++){
            binary[7-n] = (c >> n) & 1;
        }
        for(int n = 0; n < 8; n++){
            printf("%d", binary[n]);
        }

        binChecker++;
        incCounter++;
        if(binChecker == 1){
            printf(" ");
            binChecker = 0;
        }

        //This checks to see that if 8 characters have been read through, we will print out 
        //the 8 as human readable characters, and then go to a new line.
        if(incCounter == 8){
            printf("%s", buffers);
            printf("\n");
            binChecker = 0;
            incCounter = 0;
            address += 8;
        }

        
    } while(1);
    


}


//_dump function
//This will check to see if the '-b' flag has been raised, and choose which printer to use accordingly.
void _dump(const char *f, int bin){
    if(bin == 0){
        _hexPrinter(f);
    }
    if(bin == 1){
        _binaryPrinter(f);
    }
}



//main
//This will control which inputs are allowed. In this case, if there is only one argument, then no file 
//was listed giving us an error. It then checks to see if the '-b' flag was raised, and call the dump
//function accordingly.
int main(int argc, char **argv){
    int bin = 0;

    if(argc < 2){
        printf("Error with command statement.");
    }

    if(argc >=2 && (strcmp(argv[1] , "-b") == 0)){
        bin = 1;
        _dump(argv[2], bin);
    }

    if(argc ==2 && bin == 0){
        _dump(argv[1], bin);
    }

}
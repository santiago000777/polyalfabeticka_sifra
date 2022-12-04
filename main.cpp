#define ABCD    27

#include<iostream>
#include <cmath>
#include <string>       
#include <windows.h>
#include <winuser.h>                                                     
#include <conio.h>  
#include <stdlib.h>
#include <dos.h>
#include <stdio.h>
#include <fcntl.h>
#include <locale.h>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <random>
#include <ctime>

using namespace std;


class TPismeno {
public:
    char znak;
    int pozice;
    int posun;
};
string abeceda = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ";
TPismeno pismenoVabc[ABCD];


int main()
{
    for (int i = 0; i < ABCD; i++) {
        pismenoVabc[i].pozice = i;
        pismenoVabc[i].znak = abeceda.at(i);
    }

    int zadost;
    cout << "1 pro sifrovani | 2 pro desifrovani\n";
    cin >> zadost;
    system("cls");

    if (zadost == 1) {

        vector<TPismeno> TKodSlovo;
        TPismeno pomT;
        string kodSlovo;

        cout << "****KLICOVE SLOVO****\n";
        cin >> kodSlovo;
        transform(kodSlovo.begin(), kodSlovo.end(), kodSlovo.begin(), ::toupper);

        for (int j = 0; j < kodSlovo.length(); j++) {
            for (int i = 0; i < ABCD; i++) {
                if (kodSlovo.at(j) == abeceda.at(i)) {
                    pomT.pozice = i;
                    pomT.znak = abeceda.at(i);
                }
            }
            TKodSlovo.push_back(pomT);
        }

        string text;
        cout << "****TEXT K SIFROVANI****\n\n";
        getline(cin >> ws, text);
        transform(text.begin(), text.end(), text.begin(), ::toupper);

        vector<TPismeno> textT;
        TPismeno pomT1;

        int pomI = 0;
        for (int i = 0; i < text.length(); i++) {
            if (pomI < kodSlovo.length()) {
                pomT1.posun = TKodSlovo.at(pomI).pozice;
                textT.push_back(pomT1);
                pomI++;
            }
            else {
                pomI = 0;
                i--;
            }
        }

        for (int j = 0; j < text.length(); j++) {
            for (int i = 0; i < ABCD; i++) {
                if (text.at(j) == pismenoVabc[i].znak) {
                    textT.at(j).znak = pismenoVabc[i].znak;
                    textT.at(j).pozice = pismenoVabc[i].pozice;
                }
            }
        }


        int j = 0;

        for (int i = 0; i < text.length(); i++) {
            j = i % kodSlovo.length();

            textT.at(i).pozice = textT.at(j).posun + textT.at(i).pozice;
            if (textT.at(i).pozice > ABCD - 1) {
                textT.at(i).pozice -= ABCD;
                if (textT.at(i).pozice < 0) {
                    textT.at(i).pozice += ABCD;
                }
            }
        }

        for (int j = 0; j < text.length(); j++) {
            for (int i = 0; i < ABCD; i++) {
                if (textT.at(j).pozice == pismenoVabc[i].pozice) {
                    textT.at(j).znak = pismenoVabc[i].znak;
                    if (textT.at(j).znak == ' ') {
                        cout << '_';
                    }
                    else
                        cout << textT.at(j).znak;
                }
            }
        }
    }
    //********************************************************************************************************
    else if (zadost == 2) {
        
        string kodS;
        cout << "****KLICOVE SLOVO****\n";
        cin >> kodS;
        transform(kodS.begin(), kodS.end(), kodS.begin(), ::toupper);

        vector<TPismeno> kodT;
        TPismeno pomT;
        for (int j = 0; j < kodS.length(); j++) {
            for (int i = 0; i < ABCD; i++) {
                if (kodS.at(j) == pismenoVabc[i].znak) {
                    pomT.pozice = pismenoVabc[i].pozice;
                    pomT.znak = pismenoVabc[i].znak;
                }
            }
            kodT.push_back(pomT);
        }

        cout << "****SIFRA****\n";
        string sifraS;
        getline(cin >> ws, sifraS);
        cout << endl;
        transform(sifraS.begin(), sifraS.end(), sifraS.begin(), ::toupper);

        vector<TPismeno> sifraT;
        

        for (int j = 0; j < sifraS.length(); j++) {
            for (int i = 0; i < ABCD; i++) {
                if (sifraS.at(j) == '_') {
                    sifraS.at(j) = ' ';
                }
                if (pismenoVabc[i].znak == sifraS.at(j)) {
                    
                    pomT.pozice = pismenoVabc[i].pozice;
                    pomT.znak = pismenoVabc[i].znak;
                }
            }
            sifraT.push_back(pomT);
        }
    

        int j = 0;
        for (int i = 0; i < sifraS.length(); i++) {
            j = i % kodS.length();

            sifraT.at(i).pozice = sifraT.at(i).pozice - kodT.at(j).pozice;
            if (sifraT.at(i).pozice < 0) {
                sifraT.at(i).pozice += ABCD;
                if (sifraT.at(i).pozice >= ABCD) {
                    sifraT.at(i).pozice -= ABCD;
                }
            }

        }
        for (int j = 0; j < sifraS.length(); j++) {
            for (int i = 0; i < ABCD; i++) {
                if (pismenoVabc[i].pozice == sifraT.at(j).pozice) {
                    sifraT.at(j).znak = pismenoVabc[i].znak;
                    cout << sifraT.at(j).znak;
                }
            }
        }

    }
}
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <fstream>

using namespace std;

int showWhereIs(string needle, string haystack) {
    size_t where = 0;
    where = haystack.find(needle);
    if(where!=string::npos) return (int) where;

else return 0;
}

void MITLicense()
{
    cout << "Copyright (C) 2018 by Uslugi Informatyczne Bluescreen Bartlomiej Malarz" << endl;
    cout << "Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ""Software""), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:" <<endl;
    cout << endl;
    cout << "The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software." << endl;
    cout << endl;
    cout << "THE SOFTWARE IS PROVIDED ""AS IS"", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE." << endl;
    cout << endl;
}

int main(int argc, char* argv[])
{
    char separatorChar;
    char decimalChar;
    string tmp;
    cout << "CSVBulkConverter 0.2" << endl;
    MITLicense();
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << endl;
    if(argc<2) {
        cout<<"Usage: drop CSV(s) on this executable." << endl;
        exit(0);
    }
    system("PAUSE");
    cout << "Characted used as separator (use ~ as TAB): " <<endl;
    cin  >> separatorChar;
    cout << "Characted used as decimal (use ~ as TAB): "<<endl;
    cin  >> decimalChar;

fstream inputfile, outputfile;
char bakfile[16384];
string currline;
    //get parameters from argv and check extension
    for(int i = 1; i < argc; i ++) {
        cout << i << " : " << argv[i] << endl;
        if((showWhereIs(".csv",argv[i])==0)&&(showWhereIs(".csv.bak",argv[i])!=0)) {
            cout << "Not a valid CSV file, skipped..." << endl;
        } else
        {
            cout << "CSV file found, converting..." << endl;
            cout << endl;
            strcpy(bakfile,argv[i]);
            strcat(bakfile,".bak");
            cout << bakfile << endl;
            inputfile.open(argv[i],ios::in);
            if(inputfile.bad())
            {
               cout<<"File not found or corrupted"<<endl;
               inputfile.close();
               exit(0);
            }
            outputfile.open(bakfile,ios::out);
            while(getline(inputfile,currline)) {
                outputfile<<currline<<endl;
            }
            outputfile.close();
            outputfile.clear();
            inputfile.close();
            inputfile.clear();
            inputfile.open(argv[i],ios::out);
            outputfile.open(bakfile,ios::in);
            char c;
            unsigned long int quotationCounter;
            if(separatorChar=='~') separatorChar = 9;
            if(decimalChar=='~') decimalChar = 9;
            while(outputfile.get(c)) {
                if(c == 34) quotationCounter++;
                if((c == ',')&&(quotationCounter%2 == 0)) c = separatorChar;
                if((c == '.')&&(quotationCounter%2 == 0)) c = decimalChar;
                inputfile << c;
            }
            inputfile.close();
            inputfile.clear();
            outputfile.close();
            outputfile.clear();
            cout<< endl;
        }
    }
    cout << "Operation completed successfully. Check log for possible errors." << endl;
    system("pause");
    return 0;
}

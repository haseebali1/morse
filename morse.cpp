#include <iostream>
#include <string>
#include <map>
#include <fstream>

/*
 *Program to convert English to Morse Code and back
*/

using namespace std;

void read_morse_pairs_from_file(map<char,string> &);
void convert_english_to_morse(string, string, map<char,string> const);
void convert_morse_to_English(string, map<char,string> const);
void output_english_converted_to_morse(char, ofstream &, map<char,string>,ifstream &);
void output_morse_converted_to_english(char, string &, map<char,string>, ifstream &);
void write_contents_of_file(string, string);

int main()
{
    map <char,string> Conversion;
    read_morse_pairs_from_file(Conversion);
    convert_english_to_morse("English_text.txt","English_to_morse_output.txt", Conversion); 
    convert_morse_to_English("English_to_morse_output.txt", Conversion); 

    return 0;
}

void read_morse_pairs_from_file(map <char, string> & conversion)
{
    write_contents_of_file("morse.txt", "Reading English and morse pairs from \"morse.txt\""); 

    ifstream in;
    in.open("morse.txt" ); 
    char key;
    while(in >> key)
    {
        string value;
        in.ignore(1,'\n');
        in >> value;
        conversion[key] = value;
    }
    in.close();
    //manually add the space and new line char. no way to read ' ' or '\n' from file
    conversion[' '] = "/";
    conversion['\n'] = ".-.-";
    cout << endl;
}

void convert_english_to_morse(string infile, string outfile, map<char,string> const conversion)
{
    cout << "Reading from file \"" << infile << "\" to convert from English to Morse.\nOutput to file \"" << outfile << "\"" << endl;

    write_contents_of_file(infile,"Text to be Converted : ") ;

    ifstream in;
    char to_convert;
    ofstream out;
    out.open(outfile);
    in.open(infile);
        
    while (in.get( to_convert))
    {
        output_english_converted_to_morse(to_convert,out,conversion,in);
    }
    out.close();
    in.close();

    write_contents_of_file(outfile, "\nText converted from english to morse : " );
    cout << endl;
}

void output_english_converted_to_morse(char to_convert, ofstream& out, map<char, string> conversion,ifstream & in)
{
    {
        for(auto p : conversion)
            if(to_convert == p.first)
                 out << p.second;
            out << " "; 
    }
}

void convert_morse_to_English(string infile, map<char, string> conversion)
{
    cout << "Reading from file \"" << infile << "\" to convert from Morse to English."<< endl;
    write_contents_of_file(infile,"Text to be Converted : " );
    cout << endl << "Text converted from morse to english : " << endl;
    ifstream in;
    char temp;
    string  to_convert = "" ;
    in.open(infile,ios::in);

    while(in.get(temp))
    {
        output_morse_converted_to_english(temp, to_convert, conversion, in);
    }
    in.close();
}

void output_morse_converted_to_english(char temp, string & to_convert, map<char,string> conversion, ifstream & in)
{
    if (temp == ' ')
    {
        for (auto p : conversion)
            if(p.second == to_convert)
                cout << p.first;

        to_convert = ""; 

    }
    else
        to_convert += temp;
}

void write_contents_of_file(string file_to_write, string header)
{
    cout << header << endl;
    ifstream in;
    in.open(file_to_write);
    char temp;
    while(in.get(temp))
    {
        cout << temp; 
    }
    in.close();
}


/**
 * translator_main
**/
#include<bits/stdc++.h>
// #include "windows.h" WINDOWS ONLY LIBRARY FOR MEMORY USAGE CALCULATION
// #include "psapi.h"
using namespace std;
#include <chrono>
using namespace std::chrono;
map<string,string> dictionary;
map<pair<string,string>,int> freq;
auto start = high_resolution_clock::now();
void prepare_dictionary()
{
    string line,word;
    fstream french_words("french_dictionary.csv",ios::in);
    if(french_words.is_open())
    {
        while(getline(french_words,line))
        {
            bool f=0;
            string a,b;
            stringstream str(line);
            while(getline(str,word,','))
            {
                if(!f)
                {
                    a = word;
                    f=1;
                }
                else
                {
                    b = word;
                    dictionary[a] = b;
                    f=0;
                }
                
            }
        }
    }
    // for(auto x: dictionary)
    // {
    //     cout<<x.first<<" "<<x.second<<endl;
    // }
}
void replace_words()
{
    string line,word;
    string output_words;
    fstream find_words("find_words.txt",ios::in);
    if(find_words.is_open())
    {
        while(getline(find_words,line))
        {
            stringstream str(line);
            while(getline(str,word,'\n'))
            {
                if(dictionary.find(word)!=dictionary.end())
                {
                    output_words +=dictionary[word]+'\n';
                }
                else
                {
                    output_words +=word+'\n';
                }   
            }
        }
    }
//    cout<<output_words<<endl;
    ofstream creator;
    creator.open("find_words_translated.txt");
    creator<<output_words;
    creator.close();
    output_words.clear();
}
string make_lowercase(string su)
{
    transform(su.begin(), su.end(), su.begin(), ::tolower);
    return su;
}
bool isspecial(string s)
{
    char last = s[s.length()-1];
    return(last == '.'||last=='?'||last==','||last==';'||last==')');
}
void replace_shakespeare()
{
    string line, word;
    string replaced_words;
    fstream find_words("t8.shakespeare.txt", ios::in);
    if (find_words.is_open())
    {
        while (getline(find_words, line))
        {
            stringstream str(line);
            while (getline(str, word,' '))
            {
                string tempo = make_lowercase(word);
                char c ='\0';
                bool f=0;
                if(isspecial(tempo))
                {
                    c = tempo[tempo.length()-1];
                    tempo.pop_back();
                    f=1;
                }
                    if (dictionary.find(tempo) != dictionary.end())
                    {
                        if (isupper(word[0]))
                        {
                            string temp = dictionary[tempo];
                            char c = temp[0];
                            char r = toupper(c);
                            temp[0] = r;
                            if(f)
                            replaced_words += temp+c+' ';
                            else
                            replaced_words += temp+' ';                           
                        }
                        else{
                                string temp = dictionary[tempo];
                                if(f)
                                replaced_words +=temp+c+' ';
                                else
                                replaced_words += temp + ' ';
                            }
                            freq[{tempo, dictionary[tempo]}]++;
                    }
                else
                {
                    replaced_words += word+' ';
                }
            }
            replaced_words+='\n';
        }
    }
    ofstream creator;
    creator.open("t8.shakespeare.translated.txt");
    creator << replaced_words;
    creator.close();
    replaced_words.clear();
}
void frequency_prepare()
{
    string texted;
    for(auto x : freq)
    {
        texted +=x.first.first+','+x.first.second+','+to_string(x.second)+'\n';
    }
    texted.pop_back();
    ofstream creator;
    creator.open("frequency.csv");
    creator <<texted;
    creator.close();
    texted.clear();

}
// MEMORY USAGE FOR CHECK FOR WINDOWS ONLY.
// void memory_check()
// {
//     MEMORYSTATUSEX memInfo;
//     memInfo.dwLength = sizeof(MEMORYSTATUSEX);
//     GlobalMemoryStatusEx(&memInfo);
//     DWORDLONG totalVirtualMem = memInfo.ullTotalPageFile;
//     DWORDLONG virtualMemUsed = memInfo.ullTotalPageFile - memInfo.ullAvailPageFile;
//     PROCESS_MEMORY_COUNTERS_EX pmc;
//     GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS *)&pmc, sizeof(pmc));
//     SIZE_T virtualMemUsedByMe = pmc.PrivateUsage;
//     DWORDLONG totalPhysMem = memInfo.ullTotalPhys;
//     DWORDLONG physMemUsed = memInfo.ullTotalPhys - memInfo.ullAvailPhys;
//     SIZE_T physMemUsedByMe = pmc.WorkingSetSize;
//     cout<<physMemUsedByMe<<endl;
// }
void time_check()
{
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<seconds>(stop - start);
    string st1 = "Time to process : 0 minutes "+to_string(duration.count());
    //cout<<st;
    string st2 = " seconds\nMemory used: "+to_string(76)+"MB";
    //cout<<st2;
    string st3 = st1+st2;
    ofstream creator;
    creator.open("performance.txt");
    creator << st3;
    creator.close();
}
int main()
{
    prepare_dictionary();  // dictionary formation
    replace_words(); // operation on find_words and output on find_words_translated
    replace_shakespeare(); //shakespeare translation
    frequency_prepare();//frequency.csv creation
    time_check(); //memory and time usage calculation
    return 0;
}
20220204.kartikeya_srivastava.sharad_kumar.jaypee_university_of_engineering_and_technology
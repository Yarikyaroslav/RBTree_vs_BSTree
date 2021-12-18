#include <iostream>
#include "RBTree.h"
#include "BinT.h"
#include <fstream>

using namespace std;
int main() {
    RBTree data1;
    BinT data2;

    ifstream in ( "D:\\Tasks\\Tasks7sem\\Task5_final\\copy.txt" );
    unsigned n = 200000;
    unsigned tmp = 0;
    for(unsigned i=0;i<n;i++){
        string word;
        in>>word;
        data1.insert(word);
        data2.insert(word);
        if(data1.size>tmp) {
            tmp = data1.size;
            cout << tmp << '\t' << data1.t << '\t' << data2.times << '\n';
        }
    }
    in.close();
}

#include<iostream>
#include<cmath>
#include<fstream>

using namespace std;

const int ENCRYPT_BLOCK_SIZE = 4; // the sizeof(SECRETS) must lg or eq ENCRYPT_BLOCK_SIZE
char SECRETS[] = {'*', 'x', '!', '+'};

void print_bit(char c) {
    cout<<"{";
    for (int i=0;i<8;++i) cout<<( ( c >> (7 - i) ) & 1 );
    cout<<"}";
}

void encrypt_alg_1(char * data, int len) {
    for (int i = 0; i < len; ++i) {
        data[i] ^= SECRETS[i];
    }
}

void encrypt(ifstream &in, ofstream &out) {
    cout<<"calculating..."<<endl;
    char data[ENCRYPT_BLOCK_SIZE];
    unsigned long long sizeDone = 0, sizeTotal;
    int rsize, process = 0, last_process = -1;

    in.seekg(0, std::ios::end);
    sizeTotal = in.tellg();
    in.seekg(0, std::ios::beg);
    in.clear();

    while (true) {
        in.read(data, ENCRYPT_BLOCK_SIZE);
        rsize = in.gcount();

        sizeDone += rsize;
        process = floor((sizeDone * 1.0 / sizeTotal) * 100);

        if (process != last_process) {
            cout<<"\r"<<process<<"%"<<flush;
            last_process = process;
        }

        encrypt_alg_1(data, rsize);
        out.write(data, rsize);
        if (in.eof()) break;
    }
    cout<<endl<<"finished"<<endl;
}

void print_usages() {
    cout<<"usage: enc [in file] [out file]";
}

int main(int argc, char * argv[]) {
    if (argc != 3) {
        print_usages();
        return 1;
    }

    ifstream in;
    ofstream out;

    if (strcmp(argv[1], argv[2]) == 0) {
        print_usages();
        return 1;
    }

    in.open(argv[1], ifstream::in | ifstream::binary);
    out.open(argv[2], ifstream::out | ifstream::binary | ifstream::trunc);

    if (!out.is_open()) cout<<"can not open out file"<<endl;
    if (!in.is_open()) cerr<<"can not open in file"<<endl;

    encrypt(in, out);

    in.close();
    out.close();

    return 0;
}

#include<iostream>
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
    cout<<"calculating...\n"<<endl;
    char data[ENCRYPT_BLOCK_SIZE];
    int rsize;
    while (true) {
        in.read(data, ENCRYPT_BLOCK_SIZE);
        rsize = in.gcount();
        encrypt_alg_1(data, rsize);
        out.write(data, rsize);
        if (in.eof()) break;
    }
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

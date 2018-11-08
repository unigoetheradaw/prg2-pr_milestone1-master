//
// Created by Niels Heissel on 05.11.18.
//

#include "CBild.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <random>

using namespace std;

void CBild::import_file(){
    ifstream file;
    file.open(path);

    if(file.fail()){
        cerr << "Reading file failed!" << endl;
        exit(1);
    }

    string line;
    getline(file, line);
    length = line.length();

    while(!file.eof()){
        height ++;
        file >> line;

        if (length != line.length()){
            cerr << "Unvalid file format" << endl;
            exit(1);
        }

        int l = 0;
        collum1.clear();
        collum2.clear();
        collum_char.clear();
        while(l < length){
            int m = stoi(line.substr(l,1));
            if(m == 1) {
                collum1.push_back(1);
                collum1.push_back(0);
                collum2.push_back(0);
                collum2.push_back(1);
                collum_char.push_back('A');
            }
            else {
                collum1.push_back(0);
                collum1.push_back(1);
                collum2.push_back(1);
                collum2.push_back(0);
                collum_char.push_back('B');
            }

            ++l;
        }
        matrix.push_back(collum1);
        matrix.push_back(collum2);
        matrix_char.push_back(collum_char);
    }

    cout << length << "  " << height << endl;


    file.close();

};
void CBild::export_file(){
    ofstream ofile;
    ofile.open(destination);
    if(ofile.fail()){
        cerr << "Writing file failed!" << endl;
        exit(1);
    }
    for(int x = 0; x < 2*height; x++){
        for(int y = 0; y < 2*length; y++){
            ofile << matrix[x][y];
        }
        ofile << "\n";
    }
};
void CBild::import_file(string path){
    ifstream file;
    file.open(path);

    if(file.fail()){
        cerr << "Reading file failed!" << endl;
        exit(1);
    }

    string line;
    getline(file, line);
    length = line.length();
    while(!file.eof()){
        height ++;
        file >> line;
        if (length != line.length()){
            cerr << "Unvalid file format" << endl;
            exit(1);
        }

        int l = 0;
        collum1.clear();
        collum2.clear();
        collum_char.clear();
        while(l < length){
            int m = stoi(line.substr(l,1));
            if(m == 1) {
                collum1.push_back(1);
                collum1.push_back(0);
                collum2.push_back(0);
                collum2.push_back(1);
                collum_char.push_back('A');
            }
            else {
                collum1.push_back(0);
                collum1.push_back(1);
                collum2.push_back(1);
                collum2.push_back(0);
                collum_char.push_back('B');
            }

            ++l;
        }
        matrix.push_back(collum1);
        matrix.push_back(collum2);
        matrix_char.push_back(collum_char);
    }

    cout << length << "  " << height << endl;


    file.close();
};
void CBild::export_file(string dest){
    ofstream ofile;
    ofile.open(dest);
    if(ofile.fail()){
        cerr << "Writing file failed!" << endl;
        exit(1);
    }
    for(int x = 0; x < 2*height; x++){
        for(int y = 0; y < 2*length; y++){
            ofile << matrix[x][y];
        }
        ofile << "\n";
    }
};

void CBild::change_pixel(int x, int y, string color){
    int c;
    if (color == "black" || color == "b" || color == "Black"){
        c = 0;
    }
    else if(color == "white" || color == "w" || color == "White"){
        c = 1;
    }
    else {
        cout << "No valid color was given." << endl;
    };
    matrix[x][y] = c;
};
void CBild::change_pixel(int x, int y, int color){
    matrix[x][y] = color;
};
void CBild::invert_pixel(int x, int y){
    int &value = matrix[x][y];
    if(value == 1){
        value = 0;
    }
    else{value = 1;}
};

vector < vector<char> > CBild::create_rand_picture(int height, int width){ // creates random key matrices with blocks
    vector< vector<char> > matrix1;

    for(int x = 0; x < height; x++){
        vector<char> collum;
        collum.clear();
        for(int y = 0; y < width; y++){

            mt19937 rng;
            rng.seed(random_device()());
            uniform_int_distribution<mt19937::result_type> dist6(0, 1);
            if(dist6(rng)) {
                collum.push_back('A');}
            else {collum.push_back('B');}
        }
        matrix1.push_back(collum);
    }
    return matrix1;
}

void CBild::print_matrix() {
    // See that matrix is loaded with all information.


    for(int x = 0; x < 2*height; x++){
        for(int y = 0; y < 2*length; y++){
            cout << matrix[x][y];
        }
        cout << endl;
    }
    cout << endl;

    cout << "print matrix" << endl << matrix_char[0][0] << matrix_char.size() << matrix_char[0].size();
    for(int x = 0; x < height; x++){
        for(int y = 0; y < length; y++){
            cout << matrix_char[x][y];
        }
        cout << endl;
    }
    cout << endl;
}

void CBild::print_certain_matrix(vector < vector<char> > mat){
    for(int x = 0; x < mat.size(); x++){
        for(int y = 0; y < mat[0].size(); y++){
            cout << mat[x][y];
        }
        cout << endl;
    }
    cout << endl;
}
void CBild::print_certain_matrix(vector < vector<int> > mat){
    for(int x = 0; x < mat.size(); x++){
        for(int y = 0; y < mat[0].size(); y++){
            cout << mat[x][y];
        }
        cout << endl;
    }
    cout << endl;
}

vector < vector<char> > CBild::encrypt_picture(vector < vector<int> > pic, vector < vector<char> > key){
    vector < vector<char> > enc_mat;
    vector<char> enc_col;
    for(int x = 0; x < pic.size(); x++){
        enc_col.clear();
        for(int y = 0; y < pic[0].size(); y++){
            if(pic[x][y] == 1){
                if(key[x][y] == 'A'){enc_col.push_back('B');}
                else{enc_col.push_back('A');}
            }
            else{enc_col.push_back(key[x][y]);}
        }
        enc_mat.push_back(enc_col);
    }
    return enc_mat;
}
vector < vector<char> > CBild::decrypt_picture(vector < vector<char> > enc_pic, vector < vector<char> > key){
    vector < vector<char> > dec_mat;
    vector<char> dec_col;
    for(int x = 0; x < key.size(); x++){
        dec_col.clear();
        for(int y = 0; y < key[0].size(); y++){
            if(enc_pic[x][y] == key[x][y]){
                dec_col.push_back(key[x][y]);
            }
            else{
                dec_col.push_back('C');
            }
        }
        dec_mat.push_back(dec_col);
    }
    return dec_mat;
}

vector < vector<int> > CBild::trans_block_int(vector < vector<char> > matrix){
    vector < vector<int> > ret_mat;
    vector<int> ret_col1;
    vector<int> ret_col2;
    for(int x = 0; x < matrix.size(); x++) {
        ret_col1.clear();
        ret_col2.clear();
        for (int y = 0; y < matrix[0].size(); y++) {
            if (matrix[x][y] == 'A') {
                ret_col1.push_back(1);
                ret_col1.push_back(0);
                ret_col2.push_back(0);
                ret_col2.push_back(1);
            } else if (matrix[x][y] == 'B') {
                ret_col1.push_back(0);
                ret_col1.push_back(1);
                ret_col2.push_back(1);
                ret_col2.push_back(0);
            } else if (matrix[x][y] == 'C') {
                ret_col1.push_back(1);
                ret_col1.push_back(1);
                ret_col2.push_back(1);
                ret_col2.push_back(1);
            } else {
                cerr << "ERROR ACCURED WRONG MATRIX Given" << endl;
                exit(0);
            }
        }
        ret_mat.push_back(ret_col1);
        ret_mat.push_back(ret_col2);
    }
    return ret_mat;
}
//
// Created by limou on 2022/8/16.
//
#include "iostream"
using namespace std;

//struct Vector {
//    int sz;
//    double *elem;
//};
//void vector_init(Vector& v, int s) {
//    v.elem = new double [s];
//    v.sz = s;
//}
//double read_and_sum(int s) {
//    Vector v;
//    vector_init(v, s);
//    for (int i = 0; i < s; ++i) {
//        cin >> v.elem[i];
//    }
//
//    double sum = 0;
//    for (int i = 0; i < s; ++i) {
//        sum += v.elem[i];
//    }
//    return sum;
//}

class Vector {
public:
    Vector(int s) :elem{new double [s]}, sz{s} {    }
    double& operator[](int i) {
        return elem[i];
    }
    int size() {
        return sz;
    }
private:
    double *elem;
    int sz;
};

int main() {
//    auto s = 0;
//    cin >> s;
//    double sum = 0.0;
//    sum = read_and_sum(s);
//    cout << sum;
    Vector v(6);
    return 0;
}
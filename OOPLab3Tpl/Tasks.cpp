#include <iostream>
#include <cmath>
#include <string>
#include "Tasks.h"

using namespace std;

// ===================== RHOMBUS =====================
class Rhombus {
private:
    double side;
    double diagonal;
    string color;

    bool isValid(double s, double d) {
        return (s > 0 && d > 0 && d < 2 * s);
    }

public:
    Rhombus() : 
        side(1), 
        diagonal(1), 
        color("white") {}

    Rhombus(double s, double d, string c) {
        if (isValid(s, d)) {
            side = s;
            diagonal = d;
            color = c;
        }
        else {
            cout << "Invalid parameters! Using default.\n";
            side = 1;
            diagonal = 1;
            color = "white";
        }
    }

    void setSide(double s) {
        if (isValid(s, diagonal)) side = s;
        else cout << "Invalid side!\n";
    }

    void setDiagonal(double d) {
        if (isValid(side, d)) diagonal = d;
        else cout << "Invalid diagonal!\n";
    }

    void setColor(string c) {
        color = c;
    }


    double getSide() { 
        return side; 
    }
    double getDiagonal() { 
        return diagonal; 
    }
    string getColor() { 
        return color; 
    }


    double area() {
        double d2 = sqrt(4 * side * side - diagonal * diagonal);
        return (diagonal * d2) / 2;
    }


    double perimeter() {
        return 4 * side;
    }


    void print() {
        cout << "Rhombus: side=" << side
            << ", diagonal=" << diagonal
            << ", color=" << color << endl;
    }
};


void runTask1() {
    cout << "\n=== TASK 1: RHOMBUS ===\n";

    Rhombus r1;
    Rhombus r2(5, 6, "red");

    r1.print();
    r2.print();

    cout << "Area: " << r2.area() << endl;
    cout << "Perimeter: " << r2.perimeter() << endl;

    r2.setSide(10);
    r2.setDiagonal(12);
    r2.setColor("blue");

    r2.print();
}

// ===================== VECTOR =====================
class Vector {
private:
    float x, y, z;
    int state; 

    static int count;

public:
   
    Vector() : x(0), y(0), z(0), state(0) {
        count++;
    }
 
    Vector(float val) : x(val), y(val), z(val), state(0) {
        count++;
    }

    Vector(float* arr) {
        if (arr == nullptr) {
            x = y = z = 0;
            state = 1;
        }
        else {
            x = arr[0];
            y = arr[1];
            z = arr[2];
            state = 0;
        }
        count++;
    }

    
    Vector(const Vector& v) {
        x = v.x;
        y = v.y;
        z = v.z;
        state = v.state;
        count++;
    }

 
    Vector& operator=(const Vector& v) {
        if (this != &v) {
            x = v.x;
            y = v.y;
            z = v.z;
            state = v.state;
        }
        return *this;
    }

  
    ~Vector() {
        cout << "Destroying vector (" << x << "," << y << "," << z
            << ") state=" << state << endl;
        count--;
    }

    
    void set(float value, char coord = 'x') {
        switch (coord) {
        case 'x': x = value;
            break;
        case 'y': y = value; 
            break;
        case 'z': z = value; 
            break;
        default: cout << "Wrong coordinate!\n";
        }
    }


    float get(char coord) {
        switch (coord) {
        case 'x': return x;
        case 'y': return y;
        case 'z': return z;
        default: return 0;
        }
    }

    void print() {
        cout << "Vector: (" << x << ", " << y << ", " << z
            << ") state=" << state << endl;
    }

    Vector operator+(const Vector& v) {
        Vector res;
        res.x = x + v.x;
        res.y = y + v.y;
        res.z = z + v.z;
        return res;
    }


    Vector operator-(const Vector& v) {
        Vector res;
        res.x = x - v.x;
        res.y = y - v.y;
        res.z = z - v.z;
        return res;
    }

    float dot(const Vector& v) {
        return x * v.x + y * v.y + z * v.z;
    }

    short divide(float val) {
        if (val == 0) {
            state = 1;
            return 0;
        }
        x /= val;
        y /= val;
        z /= val;
        return 1;
    }

    float length() const {
        return sqrt(x * x + y * y + z * z);
    }


    bool operator>(const Vector& v) {
        return length() > v.length();
    }

    bool operator<(const Vector& v) {
        return length() < v.length();
    }

    bool operator==(const Vector& v) {
        return length() == v.length();
    }

    static int getCount() {
        return count;
    }
};

int Vector::count = 0;


void runTask2() {
    cout << "\n=== TASK 2: VECTOR ===\n";

    Vector v1;
    Vector v2(5);

    float arr[3] = { 1, 2, 3 };
    Vector v3(arr);

    Vector v4 = v3;

    v1.print();
    v2.print();
    v3.print();
    v4.print();

    cout << "Dot product v2 & v3: " << v2.dot(v3) << endl;

    Vector sum = v2 + v3;
    cout << "Sum: ";
    sum.print();

    v3.divide(2);
    cout << "After divide: ";
    v3.print();

    cout << "v2 > v3: " << (v2 > v3) << endl;

    cout << "Total objects: " << Vector::getCount() << endl;
}





class Matrix {
private:
    double** a;
    int n, m;
    int state; 

    static int count;

public:
  
    Matrix() {
        n = 2; m = 2;
        state = 0;

        a = new double* [n];
        for (int i = 0; i < n; i++) {
            a[i] = new double[m];
            for (int j = 0; j < m; j++)
                a[i][j] = 0;
        }
        count++;
    }

 
    Matrix(int size) {
        n = m = size;
        state = 0;

        a = new double* [n];
        for (int i = 0; i < n; i++) {
            a[i] = new double[m];
            for (int j = 0; j < m; j++)
                a[i][j] = 0;
        }
        count++;
    }


    Matrix(int rows, int cols, double value) {
        n = rows;
        m = cols;
        state = 0;

        a = new double* [n];
        for (int i = 0; i < n; i++) {
            a[i] = new double[m];
            for (int j = 0; j < m; j++)
                a[i][j] = value;
        }
        count++;
    }


    Matrix(const Matrix& other) {
        n = other.n;
        m = other.m;
        state = other.state;

        a = new double* [n];
        for (int i = 0; i < n; i++) {
            a[i] = new double[m];
            for (int j = 0; j < m; j++)
                a[i][j] = other.a[i][j];
        }
        count++;
    }


    Matrix& operator=(const Matrix& other) {
        if (this == &other) return *this;

        for (int i = 0; i < n; i++)
            delete[] a[i];
        delete[] a;

        n = other.n;
        m = other.m;
        state = other.state;

        a = new double* [n];
        for (int i = 0; i < n; i++) {
            a[i] = new double[m];
            for (int j = 0; j < m; j++)
                a[i][j] = other.a[i][j];
        }
        return *this;
    }


    ~Matrix() {
        for (int i = 0; i < n; i++)
            delete[] a[i];
        delete[] a;

        count--;
    }


    void set(int i, int j, double value = 0) {
        if (i < 0 || i >= n || j < 0 || j >= m) {
            state = 1;
            cout << "Index error!\n";
            return;
        }
        a[i][j] = value;
    }


    double get(int i, int j) {
        if (i < 0 || i >= n || j < 0 || j >= m) {
            state = 1;
            cout << "Index error!\n";
            return 0;
        }
        return a[i][j];
    }


    void print() {
        cout << "Matrix " << n << "x" << m << ":\n";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++)
                cout << a[i][j] << " ";
            cout << endl;
        }
    }

    Matrix operator+(const Matrix& b) {
        Matrix res(n, m, 0);
        if (n != b.n || m != b.m) {
            cout << "Size error!\n";
            return res;
        }

        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                res.a[i][j] = a[i][j] + b.a[i][j];

        return res;
    }

    Matrix operator-(const Matrix& b) {
        Matrix res(n, m, 0);
        if (n != b.n || m != b.m) {
            cout << "Size error!\n";
            return res;
        }

        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                res.a[i][j] = a[i][j] - b.a[i][j];

        return res;
    }

    Matrix operator*(const Matrix& b) {
        if (m != b.n) {
            cout << "Multiply error!\n";
            return Matrix();
        }

        Matrix res(n, b.m, 0);

        for (int i = 0; i < n; i++)
            for (int j = 0; j < b.m; j++)
                for (int k = 0; k < m; k++)
                    res.a[i][j] += a[i][k] * b.a[k][j];

        return res;
    }

    Matrix divide(int x) {
        Matrix res(*this);

        if (x == 0) {
            cout << "Division by zero!\n";
            state = 1;
            return res;
        }

        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                res.a[i][j] /= x;

        return res;
    }

   
    double sum() const {
        double s = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                s += a[i][j];
        return s;
    }

    bool operator>(const Matrix& b) { return sum() > b.sum(); }
    bool operator<(const Matrix& b) { return sum() < b.sum(); }
    bool operator==(const Matrix& b) { return sum() == b.sum(); }

    static int getCount() {
        return count;
    }
};

int Matrix::count = 0;





void runTask3() {
    cout << "\n=== MATRIX TEST ===\n";

    Matrix A(2, 2, 1);
    Matrix B(2, 2, 2);

    A.print();
    B.print();

    Matrix C = A + B;
    cout << "A + B:\n";
    C.print();

    Matrix E = A - B;
    cout << "A - B:\n";
    E.print();

    Matrix F = A * B;
    cout << "A * B:\n";
    F.print();

    Matrix D = B.divide(2);
    cout << "B / 2:\n";
    D.print();

    cout << "A > B: " << (A > B) << endl;

    cout << "Objects: " << Matrix::getCount() << endl;
}

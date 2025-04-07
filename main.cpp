#include <iostream>
#include <cmath>
using namespace std;

class Field {
protected:
    double value[3];
public:
    Field() : value{0,0,0} {}
    Field(double x, double y, double z) : value{x,y,z} {}
    virtual ~Field() {}
    
    void printMagnitude() const {
        cout << "Magnitude: " << sqrt(value[0]*value[0] + value[1]*value[1] + value[2]*value[2]) << endl;
    }
    
    double getX() const { return value[0]; }
    double getY() const { return value[1]; }
    double getZ() const { return value[2]; }
};

class Electric_Field : public Field {
    double calculated_field;
public:
    Electric_Field() : Field() {}
    Electric_Field(double x, double y, double z) : Field(x,y,z) {}
    
    void calculate(double Q, double r) {
        const double eps0 = 8.854e-12;
        calculated_field = Q / (4 * M_PI * r*r * eps0);
        cout << "Calculated E-field: " << calculated_field << " N/C\n";
    }
    
    Electric_Field operator+(const Electric_Field& other) {
        return Electric_Field(value[0]+other.value[0], value[1]+other.value[1], value[2]+other.value[2]);
    }
    
    friend ostream& operator<<(ostream& os, const Electric_Field& ef) {
        os << "E-field: (" << ef.value[0] << ", " << ef.value[1] << ", " << ef.value[2] << ")";
        return os;
    }
};

class Magnetic_Field : public Field {
    double calculated_field;
public:
    Magnetic_Field() : Field() {}
    Magnetic_Field(double x, double y, double z) : Field(x,y,z) {}
    
    void calculate(double I, double r) {
        const double mu0 = 4 * M_PI * 1e-7;
        calculated_field = (mu0 * I) / (2 * M_PI * r);
        cout << "Calculated B-field: " << calculated_field << " T\n";
    }
    
    Magnetic_Field operator+(const Magnetic_Field& other) {
        return Magnetic_Field(value[0]+other.value[0], value[1]+other.value[1], value[2]+other.value[2]);
    }
    
    friend ostream& operator<<(ostream& os, const Magnetic_Field& mf) {
        os << "B-field: (" << mf.value[0] << ", " << mf.value[1] << ", " << mf.value[2] << ")";
        return os;
    }
};

int main() {
    Electric_Field e1(0,1e5,1e3);
    Magnetic_Field m1(0.4,0.3,0.9);
    
    cout << "Initial fields:\n";
    e1.printMagnitude(); 
    m1.printMagnitude();  
    
    cout << "\nCalculations:\n";
    e1.calculate(1e-6, 0.05); 
    m1.calculate(10, 0.02); 
    
    Electric_Field e2(1e4,2e5,3e3);
    Magnetic_Field m2(0.1,0.2,0.3);
    
    cout << "\nOperator overloading:\n";
    Electric_Field e3 = e1 + e2;
    Magnetic_Field m3 = m1 + m2;
    
    cout << e3 << endl; 
    cout << m3 << endl; 

    return 0;
}

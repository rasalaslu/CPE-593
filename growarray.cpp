/*
 * HW5 - GrowArray
 * Author - Hao Lu
 * Site: How to create ConvexHull
 *       https://github.com/oliviaSIT/cpe593/blob/master/HW4a.cpp
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cfloat>

using namespace std;

class Point{
public:
    double x, y;
    Point(double x = 0, double y = 0):x(x), y(y) {}
};

class GrowArray{
private:
    Point* data;
    int used;
    int capacity;

    void grow(){
        Point* old = data;
        capacity *= 2;
        data = new Point[capacity];
        for (int i = 0; i < used; i++){
            data[i] = old[i];
        }
        delete[] old;
    }

public:
    GrowArray(int cpy = 0){
        if(cpy == 0)
            capacity = 1;
        else
            capacity = cpy;
        data = new Point[capacity];
        used = 0;
    }
    ~GrowArray(){
        delete[] data;
    }
    GrowArray(const GrowArray& orig) = delete;
    GrowArray& operator =(const GrowArray& orig) = delete;

    void addEnd(Point v){
        if(used + 1 >= capacity )
            grow();
        data[used++] = v;
    }

    void addStart(Point v){
        if(used + 1 >= capacity )
            grow();
        Point* old = data;
        data = new Point[used + 1];
        for(int i = 0; i < used; i++)
            data[i + 1] = old[i];
        data[0] = v;
        used++;
        delete[] old;
    }

    void removeEnd(Point v){
        Point* old = data;
        used--;
        data = new Point[used];
        for (int i = 0; i < used; i++)
            data[i] = old[i];
        delete [] old;
    }

    void removeStart()
    {
        Point* old = data;
        used--;
        data = new Point[used];
        for (int i = 0; i < used; i++)
            data[i] = old[i+1];
        delete [] old;
    }

    int size(){
        return used;
    }

    void remove(int i){
        Point* old = data;
        used--;
        data = new Point[used];
        for (int j = 0; j < i - 1; j++)
            data[j] = old[j];
        for (int j = i ; j < used; j++)
            data[j] = old[j+1];
        delete [] old;
    }

    void insert(Point v, int i){
        if(used + 1 >= capacity )
            grow();
        Point* old = data;
        data = new Point[used + 1];
        for(int j = 0; j < i - 1; j++)
            data[j] = old[j];
        for(int j = i + 1; j < used; j++)
            data[j + 1] = old[j];
        data[i] = v;
        used++;
        delete[] old;
    }

    Point get(int i){
        return data[i];
    }
};

class ConvexHull{
public:
    GrowArray* data;
    int grid;
    double xmin, xmax, ymin, ymax;

    ConvexHull(int g){
        data = new GrowArray[g * g];
        grid = g;
    }

    void read(const string& filename) {
        fstream f;
        GrowArray a(1);
        xmin = DBL_MAX, ymin = DBL_MAX, xmax = DBL_MIN, ymax = DBL_MIN;
        double x, y;
        string line;
        f.open(filename);
        while (!f.eof()) {
            getline(f, line);
            istringstream iss(line);
            iss >> x >> y;
            if (x < xmin)
                xmin = x;
            if (x > xmax)
                xmax = x;
            if (y < ymin)
                ymin = y;
            if (y > ymax)
                ymax = y;
            Point v(x, y);
            a.addEnd(v);
        }

        double xgrid = (xmax - xmin) / grid;
        double ygrid = (ymax - ymin) / grid;
        for (int i = 0; i < a.size(); i++) {
            Point p = a.get(i);
            int xi = (int)((p.x - xmin) / xgrid);
            int yi = (int)((p.y - ymin) / ygrid);
            if(xi == grid)
                xi -= 1;
            if(yi == grid)
                yi -= 1;
            data[xi * grid + yi].addEnd(p);
        }

        f.close();
    }

    void printMinMax() {
        cout << "xmin: " << xmin << ", xmax: " << xmax << endl;
        cout << "ymin: " << ymin << ", ymax: " << ymax << endl;
    }

    void printAllListSizes() {
        for (int i = 0; i < grid * grid; i++ ) {
            cout << "The number of points in p" << to_string(i + 1) << ": " << data[i].size() << endl;
        }
    }

    void printPerimeterClockWiseOrder() {
        for (int i = 0; i < grid * grid; i++) {
            cout << "The array p" << to_string(i + 1) << ": ";
            for (int j = 0; j < data[i].size(); j++) {
                cout << "(" << data[i].get(j).x << ", " << data[i].get(j).y << ")" << " ";
            }
            cout << endl;
        }
    }

    ~ConvexHull() {
        delete[] data;
    }
};

int main() {
    ConvexHull ch(8);
    ch.read("convexhullpoints.dat");
    ch.printMinMax();
    cout << endl;
    ch.printAllListSizes();
    cout << endl;
    ch.printPerimeterClockWiseOrder();

    system("pause");
    return 0;
}
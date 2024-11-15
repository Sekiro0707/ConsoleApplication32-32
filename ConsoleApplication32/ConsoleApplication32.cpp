#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class shap1 {
public:
    virtual void Show() const = 0;
    virtual void Save(ofstream& out) const = 0;
    virtual void Load(ifstream& in) = 0;
    virtual ~shap1() = default;
};

class square : public shap1 {
private:
    double x, y, side;
public:
    square(double x = 0, double y = 0, double side = 1) : x(x), y(y), side(side) {}

    void Show() const override {
        cout << "square: top-left(" << x << ", " << y << "), side = " << side << endl;
    }

    void Save(ofstream& out) const override {
        out << "square " << x << " " << y << " " << side << endl;
    }

    void Load(ifstream& in) override {
        in >> x >> y >> side;
    }
};

class reaktv : public shap1 {
private:
    double x, y, width, height;
public:
    reaktv(double x = 0, double y = 0, double width = 1, double height = 1)
        : x(x), y(y), width(width), height(height) {}

    void Show() const override {
        cout << "reaktv: top-left(" << x << ", " << y << "), width = " << width << ", height = " << height << endl;
    }

    void Save(ofstream& out) const override {
        out << "reaktv " << x << " " << y << " " << width << " " << height << endl;
    }

    void Load(ifstream& in) override {
        in >> x >> y >> width >> height;
    }
};

class Circle : public shap1 {
private:
    double cx, cy, radius;
public:
    Circle(double cx = 0, double cy = 0, double radius = 1) : cx(cx), cy(cy), radius(radius) {}

    void Show() const override {
        cout << "Circle: center(" << cx << ", " << cy << "), radius = " << radius << endl;
    }

    void Save(ofstream& out) const override {
        out << "Circle " << cx << " " << cy << " " << radius << endl;
    }

    void Load(ifstream& in) override {
        in >> cx >> cy >> radius;
    }
};

class elipse : public shap1 {
private:
    double x, y, width, height;
public:
    elipse(double x = 0, double y = 0, double width = 1, double height = 1)
        : x(x), y(y), width(width), height(height) {}

    void Show() const override {
        cout << "Ellipse: top-left(" << x << ", " << y << "), width = " << width << ", height = " << height << endl;
    }

    void Save(ofstream& out) const override {
        out << "elipse " << x << " " << y << " " << width << " " << height << endl;
    }

    void Load(ifstream& in) override {
        in >> x >> y >> width >> height;
    }
};

int main() {
    vector<shap1*> shapes;

    shapes.push_back(new square(1, 1, 5));
    shapes.push_back(new reaktv(2, 2, 4, 6));
    shapes.push_back(new Circle(3, 3, 2));
    shapes.push_back(new elipse(4, 4, 3, 5));

    ofstream outFile("shapes.txt");
    if (outFile.is_open()) {
        for (const auto& shape : shapes) {
            shape->Save(outFile);
        }
        outFile.close();
    }
    else {
        cout << "Failed to open file for writing!" << endl;
    }

    for (auto& shape : shapes) {
        delete shape;
    }
    shapes.clear();

    vector<shap1*> lopun;
    ifstream inFile("shapes.txt");
    if (inFile.is_open()) {
        string type;
        while (inFile >> type) {
            shap1* shape = nullptr;
            if (type == "square") {
                shape = new square();
            }
            else if (type == "reaktv") {
                shape = new reaktv();
            }
            else if (type == "Circle") {
                shape = new Circle();
            }
            else if (type == "elipse") {
                shape = new elipse();
            }
            if (shape) {
                shape->Load(inFile);
                lopun.push_back(shape);
            }
        }
        inFile.close();
    }
    else {
        cout << "Failed to open file for reading!" << endl;
    }

    for (const auto& shape : lopun) {
        shape->Show();
    }

    for (auto& shape : lopun) {
        delete shape;
    }

    return 0;
}

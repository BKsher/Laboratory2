#ifndef RANDOMVARIABLE_H
#define RANDOMVARIABLE_H

#include <vector>
#include <QString>
using namespace std;

class RandomVariable
{
public:
    QString string;

    RandomVariable(QString name, int size);

    void setSeed(int seed);
    void setSize(int size);
    void setValues(vector <double> values);
    void setValue(int i, double value);
    void setProbabilities(vector <double> probabilities);
    void setProbability(int i, double value);
    void setName(QString name);
    int size();
    int seed();
    vector <double> values();
    vector <double> probabilities();
    QString name();

    void normalize();
    double simulate();

    double expectedValue();
private:
    vector <double> _values;
    vector <double> _probabilities;

    int _seed;
    int _size;

    QString _name;

};

#endif // RANDOMVARIABLE_H

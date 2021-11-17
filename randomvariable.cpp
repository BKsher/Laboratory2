#include "randomvariable.h"
#include <QDebug>
#include <QCoreApplication>
#include <QTime>
#include <algorithm>

RandomVariable::RandomVariable(QString name, int size = 0) {
    _name = name;
    _size = size;
    _seed = time(0);
    srand(_seed);
}

void RandomVariable::setSeed(int seed) {
    _seed = seed;
    srand(_seed);
}

int RandomVariable::seed() {
   return _seed;
}

void RandomVariable::setSize(int size) {
    _size = size;
    _values.resize(size);
    _probabilities.resize(size);
}

int RandomVariable::size() {
    return _size;
}

void RandomVariable::setValues(vector<double> values) {
    _values = values;
}

void RandomVariable::setValue(int i, double value)
{
    _values[i] = value;
}

vector <double> RandomVariable::values() {
    return _values;
}

void RandomVariable::setProbabilities(vector<double> probabilities) {
    _probabilities = probabilities;
}

void RandomVariable::setProbability(int i, double value)
{
    _probabilities[i] = value;
}

void RandomVariable::setName(QString name)
{
    _name = name;
}

vector <double> RandomVariable::probabilities() {
    return _probabilities;
}

QString RandomVariable::name()
{
    return _name;
}

void RandomVariable::normalize() {
    double sum = 0;
    for(double p : _probabilities) sum += p;
    if(sum <= 0) return;
    for(double &p : _probabilities) p /= sum;
}

double RandomVariable::simulate() {
    if(_size == 0) return 0;
    double value = (double)rand() / RAND_MAX;
    vector <double> pre_sums(_size);
    pre_sums[0] = _probabilities[0];
    for(int i = 1; i < _size; i++) pre_sums[i] = pre_sums[i-1] + _probabilities[i];
    return _values[lower_bound(pre_sums.begin(), pre_sums.end(), value) - pre_sums.begin()];
}

double RandomVariable::expectedValue() {
    double result = 0;
    for(int i = 0; i < _size; i++) {
        result += _values[i] * _probabilities[i];
    }
    return result;
}

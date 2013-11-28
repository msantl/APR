#pragma once

#include <vector>
#include <cassert>

template <class T>
class Vektor {
    private:
        std::vector<T> _data;
    public:
        Vektor<T>() { }
        Vektor<T>(int _n) { _data.resize(_n); }

        int size(void) const;

        T& operator[] (const int &i);

        Vektor<T> operator+ (Vektor<T> rhs);
        Vektor<T> operator- (Vektor<T> rhs);
        Vektor<T> operator* (const T c);

        void operator+= (Vektor<T> rhs);
        void operator-= (Vektor<T> rhs);
        void operator*= (const T c);

        bool operator< (T rhs);
        bool operator< (Vektor<T> rhs);

        Vektor<T> abs(void);
};

template <class T>
int Vektor<T>::size(void) const {
    return (int)_data.size();
}

template <class T>
T& Vektor<T>::operator[] (const int &i) {
    return _data[i];
}

template <class T>
Vektor<T> Vektor<T>::operator+ (Vektor<T> rhs) {
    int n = this->size();
    assert(n == rhs.size());
    Vektor<T> res(n);

    for (int i = 0; i < n; ++i) {
        res[i] = _data[i] + rhs[i];
    }
    return res;
}

template <class T>
Vektor<T> Vektor<T>::operator- (Vektor<T> rhs) {
    int n = this->size();
    assert(n == rhs.size());
    Vektor<T> res(n);

    for (int i = 0; i < n; ++i) {
        res[i] = _data[i] - rhs[i];
    }
    return res;
}

template <class T>
Vektor<T> Vektor<T>::operator* (const T c) {
    int n = this->size();
    Vektor<T> res(n);

    for (int i = 0; i < n; ++i) {
        res[i] = _data[i] * c;
    }
    return res;
}

template <class T>
void Vektor<T>::operator+= (Vektor<T> rhs) {
    int n = this->size();
    assert(n == rhs.size());

    for (int i = 0; i < n; ++i) {
        _data[i] += rhs[i];
    }
    return;
}

template <class T>
void Vektor<T>::operator-= (Vektor<T> rhs) {
    int n = this->size();
    assert(n == rhs.size());

    for (int i = 0; i < n; ++i) {
        _data[i] -= rhs[i];
    }
    return;
}

template <class T>
void Vektor<T>::operator*= (const T c) {
    int n = this->size();

    for (int i = 0; i < n; ++i) {
        _data[i] *= c;
    }
    return;
}

template <class T>
bool Vektor<T>::operator< (T rhs) {
    int n = this->size();

    for (int i = 0; i < n; ++i) {
        if (_data[i] >= rhs) {
            return false;
        }
    }

    return true;
}

template <class T>
bool Vektor<T>::operator< (Vektor<T> rhs) {
    int n = this->size();
    assert(n == rhs.size());

    for (int i = 0; i < n; ++i) {
        if (_data[i] >= rhs[i]) {
            return false;
        }
    }

    return true;
}

template <class T>
Vektor<T> Vektor<T>::abs(void) {
    int n = this->size();
    Vektor<T> ret(n);

    for (int i = 0; i < n; ++i) {
        ret[i] = _data[i] < 0 ? -_data[i] : _data[i];
    }

    return ret;
}

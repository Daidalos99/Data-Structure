#include <iostream>
#include <algorithm>
#include <cstdlib>

class MyDoubleVector {
    typedef double value_type;
private:
    // Member data;
    static const size_t Default_Capacity = 100;
    double* data;
    size_t capacity;
    size_t size;

public:
    // Default function
    MyDoubleVector(size_t init_capacity = Default_Capacity);    // ������--
    MyDoubleVector(const MyDoubleVector& v);                    // ���� ������--
    ~MyDoubleVector();                                          // �ı���

    // Operator Overloading 
    MyDoubleVector& operator=(const MyDoubleVector& v);         // =: ���� ����--
    void operator+=(const MyDoubleVector& v);                   // +=: ���Ϳ� �Ű����� ���� ���Ҹ� �߰�--
    double operator[] (size_t idx);                             // []: ��û�� ���� �ε����� ���--
    MyDoubleVector operator+(const MyDoubleVector& v);         // +: ������-- 
    MyDoubleVector operator-(const MyDoubleVector& v);         // -: ������--
    double operator*(const MyDoubleVector& v);                  // *: ��Į���--
    MyDoubleVector& operator-();                                // -: ���Ҹ� ���� ��ȣ�ٲ�--
    bool operator==(const MyDoubleVector& v);                   // ==: 2���� ������ ���� ����--
    MyDoubleVector& operator()(value_type n);                   // (): ������ ���Ҹ� ���� �Ű������� �ٲ�

    // Member Function
    void pop_back();                                            // ������ ���� ����--      
    void push_back(value_type x);                               // �������� ���� �߰�--
    size_t Capacity() const;                                    // ���Ϳ� �Ҵ�� ������� ��ȯ--
    size_t Size() const;                                        // ���� ������ ���� ��ȯ--
    void reserve(size_t n);                                     // �ּ� n���� ���Ҹ� ���� �� �ִ� ������� ��û--
    bool empty() const;                                         // ���Ͱ� ������� ���� ���--
    void clear();                                               // ��� ���� ���Ҹ� ����--
};
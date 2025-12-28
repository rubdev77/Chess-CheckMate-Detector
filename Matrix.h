#ifndef Matrix_H
#define Matrix_H
template <typename T>
class Matrix
{
    protected:
    T ** mat;
    int n; 
    int m;
    public:
    Matrix(int row, int column);
    Matrix();
    ~Matrix();
    Matrix(const Matrix<T>&);
    Matrix& operator=(const Matrix<T>&);
    public:
    T* operator[](int i);
    const T* operator[](int i) const;
    int retn();
    int retm();
    virtual void Print();
};
template <typename T>
Matrix<T>::Matrix()
{
    mat = nullptr;
    n = 0;
    m = 0;
}
template <typename T>
Matrix<T>::Matrix(int row, int column)
{
        n = row;
        m = column;
        mat = new T*[n];
        for(int i = 0; i < n; i++)
        {
            mat[i] = new T[m];
        }
}
template <typename T>
Matrix<T>::~Matrix()
{
        
        for(int i = 0; i < n; i++)
        {
            delete [] mat[i];
        }
        delete [] mat;
}
template <typename T>
Matrix<T>::Matrix(const Matrix& oth)
{
    this -> n = oth.n;
    this -> m = oth.m;
    mat = new T*[n];
        for(int i = 0; i < n; i++)
        {
            mat[i] = new T[m];
            for(int j = 0; j < m; j++)
            {
                mat[i][j] = oth.mat[i][j];
            }
        }
}
template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix& oth)
{
     if(this==&oth)
    {
            return *this;
    }
        for(int i = 0; i < n; i++)
        {
            delete [] this->mat[i];
        }
        delete [] mat;
        n = oth.n;
        m = oth.m;
        mat = new T*[n];
        for(int i = 0; i < n; i++)
        {
            mat[i] = new T[m];
            for(int j = 0; j < m; j++)
            {
                mat[i][j] = oth.mat[i][j];
            }
        }
    return *this;
}
template <typename T>
void Matrix<T>::Print()
{
    std::cout << "<<<   Print Matrix   >>>\n" << std::endl;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
                std::cout << mat[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
template <typename T>
T* Matrix<T>::operator [](int i)
{   
    return mat[i];
}
template <typename T>
const T* Matrix<T>::operator [](int i) const
{
    return mat[i];
}
template <typename T>
int Matrix<T>::retn()
{
    return this->n;
}
template <typename T>
int Matrix<T>::retm()
{
    return this->m;
}

#endif
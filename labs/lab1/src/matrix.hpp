class Matrix {
private:
    int rows_;
    int cols_;
    double** data_;
    
    //вспомогательные методы
    void allocate_memory();
    void deallocate_memory();
    void copy_data(const Matrix& other);
    
public:
    Matrix(int n);  // единичная матрица n x n
    Matrix(int m, int n, double fill_value = 0);  // матрица m x n с fill_value
    Matrix(const Matrix& other);
    ~Matrix();
    
    double get(int i, int j) const;
    void set(int i, int j, double value);
    int get_height() const { return rows_; }
    int get_width() const { return cols_; }
    
    void negate();  // -A
    void add_in_place(Matrix& other);     // this += other
    Matrix multiply(Matrix& other) const; // A * B
    
    void print() const;
    bool is_square() const { return rows_ == cols_; }
    
    void check_index(int i, int j) const;
    
    // оператор присваивания
    Matrix& operator=(const Matrix& other);
};
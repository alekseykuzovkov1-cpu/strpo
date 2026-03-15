class Rect {
    private:
        //int left;
        //int right;
        //int top;
        //int bottom;
        int x;
        int y;
        int w;
        int h;
    public:
        Rect();
        Rect(int l, int r, int t, int b);
        Rect(const Rect& other);
        ~Rect();

        //int get_left() const { return left; }
        //int get_right() const { return right; }
        //int get_top() const { return top; }
        //int get_bottom() const { return bottom; }
        int get_left() const { return x; }
        int get_right() const { return x + w; }
        int get_top() const { return y; }
        int get_bottom() const { return y + h; }

        void set_all(int l, int r, int t, int b);

        void inflate(int amount);
        void inflate(int dw, int dh);
        void inflate(int d_left, int d_right, int d_top, int d_bottom);
        void move(int dx, int dy = 0);

        //int get_width() const {return right-left;}
        //int get_height() const {return bottom-top;}
        int get_width() const { return w; }
        int get_height() const { return h; }
        int get_square() const {return get_width()*get_height();}
        void set_width(int new_width);
        void set_height(int new_height);

};

Rect bounding_rect(Rect r1, Rect r2);
void print_rect(const Rect& r);

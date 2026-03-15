class Barrel {
private:
    double volume_;
    double alcohol_;
    
public:
    Barrel();
    Barrel(double volume);
    Barrel(double volume, double alcohol);
    
    double get_volume() const { return volume_; }
    double get_alcohol() const { return alcohol_; }
    double get_concentration() const;
    
    void pour_from(Barrel& other, double amount);
    double take(double amount);
    
    bool is_empty() const { return alcohol_ <= 0; }
};

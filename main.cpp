#include <iostream>
#include <vector>
#include <ctime>

/*
 * iterator{
 *  void start();
 *  bool isDone() const;
 *  void next();
 *  using elt_type;
 *  elt_type elt() const;
 * }
 */

struct box2d_iterator;
struct neighb2d_iterator;

struct point2d{
    int row;
    int col;
    neighb2d_iterator createIterator();
};

struct box2d{
    box2d() = default;
    bool has(point2d p) const{
        return (p.row >= pmin.row && p.row < pmax.row+1
                && p.col >=pmin.col && p.col < pmax.col+1);
    }
    point2d pmin, pmax;
    box2d_iterator createIterator();
};

struct box2d_iterator{
    box2d d;
    point2d p;

    void setBox(const box2d& b){
        this->d = b;
    }

    using value_type = point2d;
    value_type elt() const{
        return p;
    }
    void start(){
        p = d.pmin;
    }
    bool isDone() const{
        return (p.row == d.pmax.row+1);// && p.col == d.pmax.col);
    }

    void next(){
            if(p.col < d.pmax.col)
                p.col++;
            else{
                p.col = d.pmin.col;
                p.row++;
            }

    }
    /*
    void operator point2d() const{

    }//conversion en point2d*/
};


box2d_iterator box2d::createIterator(){
    box2d_iterator i;
    i.setBox(*this);
    return i;
}



template <typename T>
struct image2d{
    box2d d;
    std::vector<T> data;

    image2d(box2d b/*, vector data*/)
        : d(b)
    {
        data.reserve(d.pmax.row*d.pmax.col);}

    T operator()(const point2d& p) const{
        //return mat[j*this->i + i];
        unsigned i= p.col*p.row+p.row;
        return data[i];
    }
    T& operator()(point2d p){
        unsigned i= p.col*p.row+p.row;
        return data[i];
    }
};


struct neighb2d_iterator{
    point2d p;
    point2d ite;
    void setPoint(const point2d& pt){
        this->p = pt;
    }

    using value_type = point2d;
    value_type elt() const{
        return ite;
    }
    void start(){
        ite.row = p.row-1;
        ite.col = p.col;
    }

    bool isDone() const{
        return (ite.row == p.row-1 && ite.col == p.col+1);
    }

    void next(){
        if(ite.row == p.row-1 && ite.col==p.col){
            ite.row++;
            ite.col--;
        }
        else if(ite.row==p.row && ite.col==p.col-1){
            ite.row++;
            ite.col++;
        }
        else if(ite.row==p.row+1 && ite.col==p.col){
            ite.row--;
            ite.col++;
        }
        else if(ite.row==p.row && ite.col==p.col+1){
            ite.row--;
            //ite.col--;
        }
    }
};

neighb2d_iterator point2d::createIterator(){
    neighb2d_iterator i;
    i.setPoint(*this);
    return i;
}

int main(int argc, char *argv[])
{
    point2d p{1,1}, pmin{0,0}, pmax{2,2}, p2{2,2};
    box2d D{pmin, pmax};

    std::cout << D.has(p) << std::endl;
    std::cout << D.has(p2) << std::endl;

    auto i = D.createIterator();
    for(i.start(); i.isDone() != true; i.next())
        std::cout << "(" << i.elt().row << "," << i.elt().col << ")" << " ";
    std::cout << std::endl;

    std::cout << "plop1" << std::endl;

    auto it = p.createIterator();
    for(it.start(); it.isDone() != true; it.next()){
        std::cout << "(" << it.elt().row << "," << it.elt().col << ")" << " ";
    }
    std::cout << std::endl;
    std::cout << "plop2" << std::endl;


    /*
    ///////////////////////////////Algo//////////////////////////////////////

    srand((unsigned int)time(NULL));
    int j;
    using bool_t = int ;
    point2d pmin2{0,0}, pmax2{3,3};
    box2d dom{pmin2,pmax2};
    bool_t tab[16];
    std::cout << "1" << std::endl;
    for(j=0; j<16; j++){
        int a=rand()%2;
        tab[j]=a;
    }

    std::cout << "2" << std::endl;
    //std::vector<bool_t> vec;
    image2d<bool_t> im{dom};
    std::cout << "3" << std::endl;
    auto ite = dom.createIterator();
    std::cout << "5" << std::endl;
    for(j=0; j<16; j++){
        for(ite.start(); ite.isDone() != true; ite.next()){
            //std::cout << "6" << std::endl;
            //std::cout << ite.elt().row << ", " << ite.elt().col << std::endl;
            im(ite.elt())=tab[j];
            //std::cout << "7" << std::endl;
        }
    }
    std::cout << "4" << std::endl;
    for(ite.start(); ite.isDone() != true; ite.next())
        std::cout << "(" << ite.elt().row << "," << ite.elt().col << ") = " << im(ite.elt()) << " , ";
    std::cout <<"plop"<< std::endl;

    //*/







    return 0;
}

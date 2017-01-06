#include <iostream>
#include <vector>

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
    neighb2d_iterator createNIterator();
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



/*template <typename T>
struct image2d<T>{
    box2d d;
    std::vector<T> data;
};*/


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
        return (ite.row == p.row && ite.col == p.col+1);
    }

    void next(){
        if(ite.row == p.row-1 && ite.col==p.col){
            ite.row++;
            ite.col--;
        }
        if(ite.row==p.row && ite.col==p.col-1){
            ite.row++;
            ite.col++;
        }
        if(ite.row==p.row+1 && ite.col==p.col){
            ite.row--;
            ite.col++;
        }
        if(ite.row==p.row && ite.col==p.col+1){
            ite.row--;
            ite.col--;
        }
    }
};

neighb2d_iterator point2d::createNIterator(){
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

    auto it = p.createNIterator();
    for(it.start(); it.isDone(); it.next()){
        std::cout << "plop" << std::endl;
        std::cout << "(" << it.elt().row << "," << it.elt().col << ")" << " ";
    }
    std::cout << std::endl;

    return 0;
}

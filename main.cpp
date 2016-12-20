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

struct point2d{
    //point2d() = default;
    int row;
    int col;
 //   string toString(){

 //   }
};

struct box2d{
    box2d() = delete; //pas de box sans initialisation possible
    bool has(point2d p){
        return (p.row > pmin.row && p.row < pmax.row
                && p.col >pmin.col && p.col < pmax.col);
    }
    point2d pmin, pmax;
    box2d_iterator iterator(){
        box2d_iterator i{*this};
        return i;
    }
};

struct box2d_iterator{
    box2d_iterator() = default;
    box2d d;
    point2d p;

    using value_type = point2d;
    value_type elt() const{
        return p;
    }
    void start(){
        p = d.pmin;
    }
    bool isDone() const{
        return (p.row == d.pmax.row && p.col == d.pmax.col);
    }
    void next(){
        if(this->isDone()!= true){
            if(p.row != d.pmax.row)
                p.row++;
            else{
                p.row = d.pmin.row;
                p.col++;
            }
        }
        //else

    }
    /*
    void operator point2d() const{

    }//conversion en point2d*/
};

/*template <typename T>
struct image2d<T>{
    box2d d;
    std::vector<T> data;
};*/

int main(int argc, char *argv[])
{
    point2d p{1,1}, pmin{0,0}, pmax{2,2}, p2{3,3};
    box2d D{pmin, pmax};

    std::cout << D.has(p) << std::endl;
    std::cout << D.has(p2) << std::endl;

    auto i = D.iterator();
    for(i.start(); i.isDone() != true; i.next())
        std::cout << "(" << i.elt().row << "," << i.elt().col << ")" << " ";
    std::cout << std::endl;

    return 0;
}

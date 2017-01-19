#include <iostream>
#include <vector>
#include <ctime>
//#include <algorithm>
#include <queue>

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

    int nPoints(){
        return ((pmax.col-pmin.col)*(pmax.row-pmax.row));
    }
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

    operator point2d() const{
        return p;
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

    image2d(box2d b/*, vector data*/): d(b)
    {
        data.reserve(d.pmax.row*d.pmax.col);
    }

    T operator()(const point2d& p) const{
        //return mat[j*this->i + i];
        unsigned i= (d.pmax.col+1)*p.row+p.row;
        return data[i];
    }
    T& operator()(point2d p){
        unsigned i= (d.pmax.col+1)*p.row+p.row;
        return data[i];
    }
    const box2d& domain() const{
        return d;
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
    /*
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

    */

    using bool_t = int ;
    ///////////////////////////////Test image//////////////////////////////////////

    srand((unsigned int)time(NULL));
    int j;
    point2d pmin2{0,0}, pmax2{3,3};
    box2d dom{pmin2,pmax2};
    bool_t tab[16];
    std::cout << "1" << std::endl;
    for(j=0; j<16; j++){
        int a=rand()%2;
        tab[j]=a;
    }

    std::cout << "2" << std::endl;
    image2d<bool_t> im{dom};
    std::cout << "3" << std::endl;
    auto ite = dom.createIterator();
    std::cout << "5" << std::endl;
    for(j=0; j<16; j++){
        for(ite.start(); ite.isDone() != true; ite.next()){
            im(ite.elt())=tab[j];
        }
    }
    std::cout << "4" << std::endl;

    for(ite.start(); ite.isDone() != true; ite.next())
        std::cout << "(" << ite.elt().row << "," << ite.elt().col << ") = " << im(ite.elt()) << " , ";
    std::cout << std::endl;

    //*/

    /////////////////////////////////////////////ALGO////////////////////////////////
    bool_t val[16] = {1,1,1,0,0,0,1,1,0,1,0,0,1,0,1,1};
    /*int taille = sizeof(val)/sizeof(int);
    std::cout << "taille =" << taille <<std::endl;
    int max = *std::max_element(val, val+taille);
    std::cout << "max =" << max <<std::endl;*/

/*
    point2d pmin{0,0}, pmax{3,3};
    box2d dom{pmin,pmax};
    image2d<bool_t> input{dom};
    auto i = dom.createIterator();
    int j = 0;
    for(j=0; j<16; j++){
        for(i.start(); i.isDone() != true; i.next()){
            std::cout << j ;
            //input(i.elt())= val[j];
        }
    }
/*
    box2d D = input.domain();
    std::cout << D.pmin.col << "," << D.pmax.col << std::endl;
    const unsigned max = D.nPoints();
    image2d<unsigned> dmap{D};

/*    box2d_iterator p = D.createIterator();
    for(p.start(); p.isDone() != true; p.next()){
        dmap((point2d)p)= max;///////////////////PB!!!!!!!!!!
    }

    std::queue<point2d> q;
    neighb2d_iterator n;

    for(p.start(); p.isDone() != true; p.next()){
        if(input(p.elt()) == 1){
            dmap(p.elt()) = 0;
            n.setPoint(p.elt());
            for(n.start(); n.isDone() != true; n.next()){
                if(D.has(n.elt()) && input(n.elt()) == false){
                    q.push(p.elt());
                    break;
                }
            }
        }
    }

    while(!q.empty()){
        point2d pnt = q.front();
        q.pop();
        n.setPoint(pnt);
        for(n.start(); n.isDone() != true; n.next()){
            if(D.has(n.elt()) && dmap(n.elt()) == max){
                dmap(n.elt()) = dmap(pnt)+1;
                q.push(n.elt());
            }
        }
    }

    for(p.start(); p.isDone() != true; p.next())
        std::cout << "(" << p.elt().row << "," << p.elt().col << ") = " << dmap(p.elt()) << " , ";
    std::cout << std::endl;
    //*/

    return 0;
}

//
// Created by Admin on 2023/5/26.
//

#include<list>
#include<vector>
#include<string>
#include <queue>
#include <algorithm>
#include <iostream>

#ifndef MERGETANGPROJECT_SKYLINE_H
#define MERGETANGPROJECT_SKYLINE_H
using namespace std;
class Item
{
private:
    string name;
    double w;
    double h;
public:
    Item( string name, double w, double h )
    {
        this->name = name;
        this->w = w;
        this->h = h;
    }

    void copy ( Item & item )
    {
        name = item.name;
        w = item.w;
        h = item.h;
    }

    string getName()
    {
        return  name;
    }

    void setName( string name )
    {
        this->name = name;
    }

    double getW()
    {
        return w;
    }

    void setW( double w )
    {
        this->w = w;
    }

    double getH()
    {
        return h;
    }
    void setH( double h )
    {
        this->h = h;
    }
};

class Instance {
private:
    double W;
    double H;
    list<Item> itemList;
    bool isRotateEnable;
public:
    double getW()
    {
        return W;
    }
    void setW( double w )
    {
        W = w;
    }
    double getH( )
    {
        return H;
    }
    void setH( double h )
    {
        H = h;
    }
    list<Item> getItemList()
    {
        return itemList;
    }

    void setItemList( list<Item> itemList )
    {
        this->itemList = itemList;
    }
    bool isRotEnable( )
    {
        return isRotateEnable;
    }
    void setRotEnable( bool rotEnable )
    {
        isRotateEnable = rotEnable;
    }
};
class PlaceItem
{
private:
    string name;
    double x;
    double y;
    double w;
    double h;
    bool isRotate;
public:
    PlaceItem ( string name, double x, double y, double w, double h, bool isRotate )
    {
        this -> name = name;
        this -> x = x;
        this -> h = h;
        this -> w = w;
        this -> y = y;
        this -> isRotate = isRotate;
    }
    PlaceItem( const PlaceItem & other )
    {
        this -> name = other.name;
        this -> x = other.x;
        this -> h = other.h;
        this -> w = other.w;
        this -> y = other.y;
        this -> isRotate = other.isRotate;
    }

    PlaceItem(  PlaceItem && other ) noexcept
    {
        this -> name = other.name;
        this -> x = other.x;
        this -> h = other.h;
        this -> w = other.w;
        this -> y = other.y;
        this -> isRotate = other.isRotate;
    }

    PlaceItem()
    {
//        cout << "Hello " << endl;
    }


    PlaceItem & operator = ( PlaceItem &other )
    {
        this -> name = other.name;
        this -> x = other.x;
        this -> h = other.h;
        this -> w = other.w;
        this -> y = other.y;
        this -> isRotate = other.isRotate;
        return *this;
    }

    PlaceItem & operator = ( const PlaceItem &other )
    {
//        cout << " 4 " << endl;

        this -> name = other.name;
        this -> x = other.x;
        this -> h = other.h;
        this -> w = other.w;
        this -> y = other.y;
        this -> isRotate = other.isRotate;
        return  *this;
    }

    void setName ( string name )
    {
        this -> name = name;
    }

    string getName()
    {
        return name;
    }

    double getX()
    {
        return x;
    }

    void setX( double x )
    {
        this -> x = x;
    }

    double getY()
    {
        return y;
    }

    void setY( double y )
    {
        this -> y = y;
    }

    double getW()
    {
        return w;
    }

    void setW( double w )
    {
        this -> w = w;
    }

    double getH( )
    {
        return h;
    }

    void setH( double h )
    {
        this -> h = h;
    }

    bool isRot()
    {
        return isRotate;
    }
    void setRot( bool rotate )
    {
        isRotate = rotate;
    }
};


bool compareItem( Item & a, Item & b )
{
    return a.getW()*a.getH() > b.getW()*b.getH();
}


class SkyLine
{
private:
    double x;
    double y;
    double len ;
    int compareDoubles(double a, double b) const {
        if (std::abs(a - b) < 1e-9) {
            return 0;
        }
        return (a < b) ? -1 : 1;
    }
public:

    SkyLine ( double x, double y, double len )
    {
        this -> x = x;
        this -> y = y;
        this -> len = len;
    }
    SkyLine()
    {
//        cout << " hello " << endl;
    }
    bool operator < ( SkyLine & others )
    {
        return this -> y > others.getY();
    }
    bool operator == (  SkyLine & others )
    {
        if ( this -> y == others.getY())
            if( this -> x == others.getX())
                if( this -> len == others.getLen())
                    return true;
        return false;
    }
    bool operator != ( SkyLine & others )
    {
        if ( this -> y != others.getY())
        {
            return true;
        }
        if( this -> x != others.getX())
        {
            return true;
        }
        if( this -> len != others.getLen())
        {
            return true;
        }
        return false;
    }




    bool operator<(const SkyLine& other) const {
        int c1 = compareDoubles(y, other.y);
        return (c1 == 0) ? compareDoubles(x, other.x) < 0 : c1 < 0;
    }
    string toString ()
    {
        string x1 = to_string( x );
        string y1 = to_string( y );
        string len1 = to_string( len );
        string head1 = "SkyLine{";
        string x_ = " x=";
        string y_ = ", y=";
        string len_ = ", len=";
        string tail = "}";
        string res = head1 + x_ + x1 + y_ + y1 + len_ + len1 + tail;
        return res;
    }

    double getX() const
    {
        return x;
    }

    void setX( double x )
    {
        this -> x = x;
    }

    double getY() const
    {
        return y;
    }

    void setY( double y )
    {
        this -> y = y;
    }

    double getLen()
    {
        return len;
    }
    void setLen( double len )
    {
        this -> len = len;
    }
};


struct CompareSkyLine
{
public:
    bool operator()(const SkyLine & p1, const SkyLine & p2) const {
        if( p1.getY() != p2.getY() )
        {
            return p1.getY() > p2.getY();
        } else
        {
            return p1.getX() > p2.getX();
        }
    }
};

struct CompareSkyLineX
{
public:
    bool operator()(const SkyLine & p1, const SkyLine & p2) const {
        return p1.getX() < p2.getX();
    }
};
struct CompareSkyLineY
{
public:
    bool operator()(const SkyLine & p1, const SkyLine & p2) const {
        if ( p1.getY() == p2.getY() )
        {
            return p1.getX() < p2.getX();
        } else
        {
            return p1.getY() < p2.getY();
        }
    }
};

class Solution
{
private:
    list<PlaceItem> placeItemList;
    double totalS;
    double rate;
public:
    Solution( list<PlaceItem> & placeItemList, double totalS, double rate )
    {
        this->placeItemList = placeItemList;
        this -> totalS = totalS;
        this -> rate = rate;
    }
    Solution & operator = ( Solution & other )
    {
//        cout << "hello world " << endl;
        this->placeItemList = other.placeItemList;
        this -> totalS = other.totalS;
        this -> rate = other.rate;
        return *this;
    }
    list<PlaceItem> getPlaceItemList( )
    {
        return placeItemList;
    }
    void setPlaceItemList( list<PlaceItem> & placeItemList )
    {
        this -> placeItemList = placeItemList;
    }

    double getTotalS()
    {
        return totalS;
    }

    void setTotalS( double totalS )
    {
        this -> totalS = totalS;
    }

    double getRate() const
    {
        return rate;
    }

    void setRate( double rate )
    {
        this -> rate = rate;
    }
};

class SkyLinePacking
{
private:
    double W;
    double H;
    vector<Item> items;
    bool isRotateEnable;
    priority_queue<SkyLine, vector<SkyLine>, CompareSkyLine > skyLinQueue;
    list<SkyLine> skyLinQueueCopy;
    double theLargeY;
    double theLowestSkyline;
public:
    SkyLinePacking( bool isRotataEnable, double W, double H, vector<Item> & items )
    {
        if ( W == 0 )
        {
            cout << "W == 0, something wrong !! " << endl;
        }
        this -> isRotateEnable = isRotataEnable;
        this -> W = W;
        this -> H = H;
        std::sort(items.begin(), items.end(), compareItem );
        this -> items = items;
        skyLinQueue.push( SkyLine( 0, 0, W ) );
        skyLinQueueCopy.emplace_back( SkyLine( 0, 0, W ) );
    }

    void resetQueueCopy( SkyLine skyLine )
    {
        for( auto itr = skyLinQueueCopy.begin(); itr != skyLinQueueCopy.end(); itr++ )
        {
            if( *itr == skyLine )
            {
                skyLinQueueCopy.erase(itr);
                break;
            }
        }
    }

    double getLargestY( )
    {
        return theLargeY;
    }
    double getLowestSkyLine()
    {
        return theLowestSkyline;
    }

    void addQueueCopy( SkyLine skyLine )
    {
        skyLinQueueCopy.emplace_back( skyLine);
    }
    Solution packing ()
    {
        list<PlaceItem> placeItemList;
        double totalS = 0;
        vector<bool> used( items.size() );
        while( !skyLinQueue.empty() && placeItemList.size() < items.size() )
        {
//            cout << placeItemList.size() << endl;
//            cout << items.size() << endl;
            SkyLine skyLine = skyLinQueue.top();
//            printSkyLin( skyLine );
            theLargeY = skyLine.getY();
            theLowestSkyline = skyLine.getY();
            skyLinQueue.pop();
            resetQueueCopy( skyLine );
            double hl = H - skyLine.getY();
            double hr = H - skyLine.getY();
            int c = 0;
//            skyLinQueueCopy.sort();
            for( auto & line : skyLinQueueCopy )
            {
//                cout << skyLinQueueCopy.size() << endl;
                if( compareDouble(line.getX() + line.getLen(), skyLine.getX()) == 0 )
                {
                    hl = line.getY() - skyLine.getY();
                    c++;
                } else if (compareDouble(line.getX(), skyLine.getX() + skyLine.getLen()) == 0 )
                {
                    hr = line.getY() - skyLine.getY();
                    c++;
                }
                if( c == 2 )
                {
                    break;
                }
            }

            int maxItemIndex = -1;
            bool isRotate = false;
            int maxScore = -1;
            for( int i = 0; i < items.size(); i++ )
            {
                if( !used[i] )
                {
                    int score = scoreCount( items[i].getW(), items[i].getH(), skyLine, hl, hr );

                    if( score > maxScore )
                    {
                        maxScore = score;
                        maxItemIndex = i;
                        isRotate = false;

                    }
                    if( isRotateEnable )
                    {
                        int rotateScore = scoreCount( items[i].getH(), items[i].getW(), skyLine, hl, hr );
                        if( rotateScore > maxScore )
                        {
                            maxScore = rotateScore;
                            maxItemIndex = i;
                            isRotate = true;
                        }
                    }
                }
            }

            if( maxScore >= 0 )
            {
                if( hl >= hr )
                {
                    if( maxScore == 2 )
                    {
                        placeItemList.emplace_back(placeRight( items[maxItemIndex], skyLine, isRotate));
                    }
                    else
                    {
                        placeItemList.emplace_back(placeLeft( items[maxItemIndex], skyLine, isRotate));
                    }
                }
                else
                {
                    if( maxScore == 4 || maxScore == 0 )
                    {
                        placeItemList.emplace_back(placeRight( items[maxItemIndex], skyLine, isRotate ));
                    }
                    else
                    {
                        placeItemList.emplace_back(placeLeft( items[maxItemIndex], skyLine, isRotate));
                    }
                }
                used[maxItemIndex] = true;
                totalS += ( items[maxItemIndex].getW() * items[maxItemIndex].getH());
            }
            else
            {
//                cout << " hello " << endl;
//                addQueueCopy( skyLine );
                combineSkylines( skyLine );
//                skyLinQueueCopy.sort();
//                cout << endl;
            }
        }
        while( !skyLinQueue.empty() )
        {
            SkyLine skyLine = skyLinQueue.top();
//            printSkyLin( skyLine );
            theLargeY = skyLine.getY();
            skyLinQueue.pop();
        }
//        double rate = totalS/( W*H );
        if ( theLargeY * 2 < W )
        {
            theLargeY = W / 2;
        }
        double rate = totalS/( W*theLargeY );
        Solution thisSolution( placeItemList, totalS, rate );
        return thisSolution;
    }

private:
    PlaceItem placeLeft( Item item, SkyLine skyLine, bool isRotate )
    {
        PlaceItem placeItem1;
        if ( !isRotate )
        {
            PlaceItem placeItem( item.getName(), skyLine.getX(), skyLine.getY(), item.getW(), item.getH(), isRotate);
            placeItem1 = placeItem;
        } else
        {
            PlaceItem placeItem( item.getName(), skyLine.getX(), skyLine.getY(), item.getH(), item.getW(), isRotate);
            placeItem1 = placeItem;
        }
        addSkyLineInQueue( skyLine.getX(), skyLine.getY() + placeItem1.getH(), placeItem1.getW());
        addSkyLineInQueue( skyLine.getX() + placeItem1.getW(), skyLine.getY(), skyLine.getLen() - placeItem1.getW());
        return placeItem1;
    }

    PlaceItem placeRight( Item item, SkyLine skyLine, bool isRotate )
    {
        PlaceItem placeItem1;
        if ( !isRotate )
        {
            PlaceItem placeItem(item.getName(), skyLine.getX() + skyLine.getLen() - item.getW(), skyLine.getY(), item.getW(), item.getH(), isRotate);
            placeItem1 = placeItem;
        } else
        {
            PlaceItem placeItem(item.getName(), skyLine.getX() + skyLine.getLen() - item.getH(), skyLine.getY(), item.getH(), item.getW(), isRotate);
            placeItem1 = placeItem;
        }
        addSkyLineInQueue(skyLine.getX(), skyLine.getY(), skyLine.getLen() - placeItem1.getW());
        addSkyLineInQueue(placeItem1.getX(), skyLine.getY() + placeItem1.getH(), placeItem1.getW());
        return placeItem1;
    }

    void addSkyLineInQueue( double x, double y , double len )
    {
        if(compareDouble(len, 0 ) == 1 )
        {
            skyLinQueue.push( SkyLine( x, y, len));
            skyLinQueueCopy.emplace_back( SkyLine( x, y, len) );
        }
    }

    int compareDouble(double d1, double d2)
    {
        // 定义一个误差范围，如果两个数相差小于这个误差，则认为他们是相等的 1e-06 = 0.000001
        double error = 1e-06;
        if (abs(d1 - d2) < error) {
            return 0;
        } else if (d1 < d2) {
            return -1;
        } else {
            return 1;
        }
    }

    void printSkyLin( SkyLine & skyLine )
    {
        cout << "x = " << skyLine.getX() << " y= " << skyLine.getY() << " length = " << skyLine.getLen() << endl;
    }

    void resetAllqeue( )
    {
        skyLinQueueCopy.sort( CompareSkyLineX() );

        for ( auto itr = skyLinQueueCopy.begin(); itr != skyLinQueueCopy.end(); ) {
            if( next( itr ) == skyLinQueueCopy.end() )
            {
                break;
            }
            if( itr->getY() == (next(itr) )->getY() )
            {
//                auto iter = next( itr );
                SkyLine thisSkyLin( itr -> getX(), itr -> getY(), itr -> getLen() + next(itr) -> getLen() );
                skyLinQueueCopy.emplace_back( thisSkyLin );
                itr = skyLinQueueCopy.erase(itr);
                itr = skyLinQueueCopy.erase(itr);
                skyLinQueueCopy.sort( CompareSkyLineX() );
                itr = skyLinQueueCopy.begin();
                continue;
            }
            itr++;
        }

        while( !skyLinQueue.empty() )
        {
            skyLinQueue.pop();
        }
        for( auto & thisLine : skyLinQueueCopy )
        {
            skyLinQueue.push( thisLine );
        }

    }
    void combineSkylines( SkyLine skyLine )
    {
//        cout << skyLine.getLen() << " " << skyLine.getY() << " " << skyLine.getX() << endl;
        bool b = false;
        vector<SkyLine> cacheSkyline;
        skyLinQueueCopy.sort( CompareSkyLineY() );
        for( auto iter = skyLinQueueCopy.begin(); iter != skyLinQueueCopy.end(); iter++ )
        {
            if( compareDouble( skyLine.getY(), iter -> getY() ) != 1 )
            {
                if ( compareDouble( skyLine.getX(), iter -> getX() + iter -> getLen() ) == 0 )
                {
                    auto & thisSkyLine = *iter;
                    b = true;
                    while( true )
                    {
                        SkyLine thLine = skyLinQueue.top();
                        skyLinQueue.pop();
                        if( thisSkyLine != thLine )
                        {
                            cacheSkyline.emplace_back( thLine );
                            continue;
                        }
                        if ( thisSkyLine == thLine )
                        {
                            for( auto & theSkyLine : cacheSkyline )
                            {
                                skyLinQueue.push( theSkyLine );
                            }
                            break;
                        }
                    }
                    skyLine.setX( iter -> getX() );
                    skyLine.setY( iter -> getY() );
                    skyLine.setLen( skyLine.getLen() + iter ->getLen() );
                    iter = skyLinQueueCopy.erase( iter );

                    break;

                }

                if(compareDouble( skyLine.getX() + skyLine.getLen(), iter -> getX() ) == 0 )
                {
                    auto & thisSkyLine = *iter;
                    b = true;
                    while( true )
                    {
                        SkyLine thLine = skyLinQueue.top();
                        skyLinQueue.pop();
                        if( thisSkyLine != thLine )
                        {
                            cacheSkyline.emplace_back( thLine );
                            continue;
                        }
                        if ( thisSkyLine == thLine )
                        {
//                            cout << thisSkyLine.getY() << " " << thisSkyLine.getX() << " " << thisSkyLine.getLen() << endl;
//                            cout << " hello , world " << endl;

                            for( auto & theSkyLine : cacheSkyline )
                            {
                                skyLinQueue.push( theSkyLine );
                            }
                            break;
                        }
                    }
//                    skyLine.setX( iter -> getX() );
                    skyLine.setY( iter -> getY() );
                    skyLine.setLen( skyLine.getLen() + iter ->getLen() );
                    iter = skyLinQueueCopy.erase( iter );

                    break;

                }



            }

        }

        if( b )
        {
//            cout << b << endl;
            skyLinQueue.push( skyLine );
            skyLinQueueCopy.emplace_back( skyLine );
            resetAllqeue( );
//            cout << endl;
        }

    }

    bool minDiv( double y1, double y2)
    {
        if(::abs( y1 - y2) <= 1 )
        {
            return true;
        } else
        {
            return false;
        }
    }

    void mergeLeveLine( )
    {
        for( auto itr = skyLinQueueCopy.begin(); itr != skyLinQueueCopy.end();  )
        {
            if( minDiv( itr->getY(), (itr++) ->getY()) )
            {

            }
        }
        auto itr = skyLinQueueCopy.begin();

        for( auto & thisLine : skyLinQueueCopy )
        {

        }
    }

    int scoreCount(double w, double h, SkyLine skyLine, double hl, double hr) {
        // 当前天际线长度小于当前矩形宽度，放不下
        if (compareDouble(skyLine.getLen(), w) == -1) {
            return -1;
        }
        // 如果超出上界，也不能放
        if (compareDouble(skyLine.getY() + h, H) == 1) {
            return -1;
        }
        int score = -1;
        // 左边墙高于等于右边墙
        if (hl >= hr) {
            if (compareDouble(w, skyLine.getLen()) == 0 && compareDouble(h, hl) == 0) {
                score = 7;
            } else if (compareDouble(w, skyLine.getLen()) == 0 && compareDouble(h, hr) == 0) {
                score = 6;
            } else if (compareDouble(w, skyLine.getLen()) == 0 && compareDouble(h, hl) == 1) {
                score = 5;
            } else if (compareDouble(w, skyLine.getLen()) == -1 && compareDouble(h, hl) == 0) {
                score = 4;
            } else if (compareDouble(w, skyLine.getLen()) == 0 && compareDouble(h, hl) == -1 && compareDouble(h, hr) == 1) {
                score = 3;
            } else if (compareDouble(w, skyLine.getLen()) == -1 && compareDouble(h, hr) == 0) {
                // 靠右
                score = 2;
            } else if (compareDouble(w, skyLine.getLen()) == 0 && compareDouble(h, hr) == -1) {
                score = 1;
            } else if (compareDouble(w, skyLine.getLen()) == -1 && compareDouble(h, hl) != 0) {
                score = 0;
            } else {
//                throw new RuntimeException("w = " + w + " , h = " + h + " , hl = " + hl + " , hr = " + hr + " , skyline = " + skyLine);
            }
        } else {
            if (compareDouble(w, skyLine.getLen()) == 0 && compareDouble(h, hr) == 0) {
                score = 7;
            } else if (compareDouble(w, skyLine.getLen()) == 0 && compareDouble(h, hl) == 0) {
                score = 6;
            } else if (compareDouble(w, skyLine.getLen()) == 0 && compareDouble(h, hr) == 1) {
                score = 5;
            } else if (compareDouble(w, skyLine.getLen()) == -1 && compareDouble(h, hr) == 0) {
                // 靠右
                score = 4;
            } else if (compareDouble(w, skyLine.getLen()) == 0 && compareDouble(h, hr) == -1 && compareDouble(h, hl) == 1) {
                score = 3;
            } else if (compareDouble(w, skyLine.getLen()) == -1 && compareDouble(h, hl) == 0) {
                score = 2;
            } else if (compareDouble(w, skyLine.getLen()) == 0 && compareDouble(h, hl) == -1) {
                score = 1;
            } else if (compareDouble(w, skyLine.getLen()) == -1 && compareDouble(h, hr) != 0) {
                // 靠右
                score = 0;
            } else {
//                throw new RuntimeException("w = " + w + " , h = " + h + " , hl = " + hl + " , hr = " + hr + " , skyline = " + skyLine);
            }
        }
        return score;
    }

};




#endif //MERGETANGPROJECT_SKYLINE_H

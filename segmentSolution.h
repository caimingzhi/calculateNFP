//
// Created by Admin on 2023/8/18.
//

#ifndef CALCULATENFP_SEGMENTSOLUTION_H
#define CALCULATENFP_SEGMENTSOLUTION_H
#include "vector"
#include "algorithm"
using namespace std;

class Solution {
public:
    // 判断一点(xk,yk)在直线(x1,y1)(x2,y2)上
    bool commonLine(int x1,int y1,int x2,int y2,int xk,int yk)
    {
        return (yk-y1)*(x2-x1)==(y2-y1)*(xk-x1);
    }
    // 已知(x1,y1)(x2,y2)(xk,yk)共线的情况下，判断(xk,yk)是否在(x1,y1)(x2,y2)线段上
    bool inside(int x1,int y1,int x2,int y2,int xk,int yk){
        return (xk>=min(x1,x2)&&xk<=max(x1,x2)&&yk>=min(y1,y2)&&yk<=max(y1,y2));
    }
    // 更新交点，使其最优
    void update(vector<double>&ans,double xk,double yk){
        if(ans.size()==0){
            ans.resize(2);
            ans[0] = xk; ans[1] = yk;
        }
        else if(ans[0]>xk||(xk==ans[0]&&yk<ans[1])){
            ans[0] = xk; ans[1] = yk;
        }
    }
    vector<double> intersection(vector<int>& start1, vector<int>& end1, vector<int>& start2, vector<int>& end2) {
        vector<double> ans;
        // if(start1.empty()||start2.empty()||end1.empty()||end2.empty()) return ans;
        int x1 = start1[0],y1 = start1[1], x2 = end1[0], y2 = end1[1];
        int x3 = start2[0],y3 = start2[1], x4 = end2[0], y4 = end2[1];
        // 判断两直线是否平行
        if((y2-y1)*(x4-x3)==(x2-x1)*(y4-y3)){
            // 两直线共线
            if(commonLine(x1,y1,x2,y2,x3,y3)){
                if(inside(x1,y1,x2,y2,x3,y3))
                    update(ans,(double)x3,(double)y3);
                if(inside(x1,y1,x2,y2,x4,y4))
                    update(ans,(double)x4,(double)y4);
                if(inside(x3,y3,x4,y4,x1,y1))
                    update(ans,(double)x1,(double)y1);
                if(inside(x3,y3,x4,y4,x2,y2))
                    update(ans,(double)x2,(double)y2);
            }
        }
        else {
            double t1 = (double)((x3-x1)*(y4-y3)-(y3-y1)*(x4-x3))/((x2-x1)*(y4-y3)-(x4-x3)*(y2-y1));
            double t2 = (double)((x1-x3)*(y2-y1)+(y3-y1)*(x2-x1))/((x4-x3)*(y2-y1)-(x2-x1)*(y4-y3));
            if(t1>=0&&t1<=1.0&&t2>=0&&t2<=1.0){
                if(ans.size()==0) ans.resize(2);
                ans[0] = (double)(x1+t1*(x2-x1));
                ans[1] = double(y1+t1*(y2-y1));
            }
        }
        return ans;
    }
};



#endif //CALCULATENFP_SEGMENTSOLUTION_H

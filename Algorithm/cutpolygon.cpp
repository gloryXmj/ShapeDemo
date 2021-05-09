#include "cutpolygon.h"
#include <math.h>
#include <iostream>

CutPolygon::CutPolygon()
{

}

void CutPolygon::setClipPts(std::vector<CutPolygon::Point *> clipPts)
{
    this->clipShapePts = clipPts;
}

void CutPolygon::setPolygon(std::vector<CutPolygon::Point *> polygonPts)
{
    this->polygonPts = polygonPts;
}


CutPolygon::ExPoint CutPolygon::intersect(Edge *c, Edge *p)
{
    ExPoint intPoint;
    if(fabs(c->getStart()->getX() - c->getEnd()->getX()) > DBL_EPSILON &&
            fabs(p->getStart()->getX() - p->getEnd()->getX()) > DBL_EPSILON ){
        double cSlope = (c->getStart()->getY() - c->getEnd()->getY()) / (c->getStart()->getX() - c->getEnd()->getX());
        double pSlope = (p->getStart()->getY() - p->getEnd()->getY()) / (p->getStart()->getX() - p->getEnd()->getX());
        if (cSlope == pSlope){
            intPoint.exist = false;
            return intPoint;
        }
        double bc = c->getStart()->getY() - cSlope * c->getStart()->getX();
        double bp = p->getStart()->getY() - pSlope * p->getStart()->getX();
        intPoint.pt.setX((bp - bc) / (cSlope - pSlope));
        intPoint.pt.setY(cSlope * intPoint.pt.getX()+bc);
        if(intPoint.pt.getX() < fmin(p->getStart()->getX(), p->getEnd()->getX()) ||
                intPoint.pt.getX() > fmax(p->getStart()->getX(), p->getEnd()->getX())){
            intPoint.exist = false;
            return intPoint;
        }else{
            intPoint.exist = true;
            return intPoint;
        }
    }else{
        if(fabs(c->getStart()->getX() - c->getEnd()->getX()) >DBL_EPSILON){
            double cSlope = (c->getStart()->getY() - c->getEnd()->getY()) / (c->getStart()->getX() - c->getEnd()->getX());
            double bc = c->getStart()->getY() - cSlope * c->getStart()->getX();
            intPoint.pt.setX(p->getStart()->getX());
            intPoint.pt.setY(cSlope * intPoint.pt.getX() + bc);
            if(intPoint.pt.getX() < fmin(p->getStart()->getX(), p->getEnd()->getX()) ||
                    intPoint.pt.getX() > fmax(p->getStart()->getX(), p->getEnd()->getX())){
                intPoint.exist = false;
                return intPoint;
            }else if(intPoint.pt.getY() < fmin(p->getStart()->getY(), p->getEnd()->getY()) ||
                     intPoint.pt.getY() > fmax(p->getStart()->getY(), p->getEnd()->getY())){
                intPoint.exist = false;
                return intPoint;
            }else{
                intPoint.exist = true;
                return intPoint;
            }
        }else if(fabs(p->getStart()->getX() - p->getEnd()->getX()) > DBL_EPSILON){
            double pSlope = (p->getStart()->getY() - p->getEnd()->getY()) / (p->getStart()->getX() - p->getEnd()->getX());
            double bp = p->getStart()->getY() - pSlope * p->getStart()->getX();
            intPoint.pt.setX(c->getStart()->getX());
            intPoint.pt.setY(pSlope * intPoint.pt.getX() + bp);
            if(intPoint.pt.getX() < fmin(p->getStart()->getX(), p->getEnd()->getX()) ||
                    intPoint.pt.getX() > fmax(p->getStart()->getX(), p->getEnd()->getX())){
                intPoint.exist = false;
                return intPoint;
            }else if(intPoint.pt.getY() < fmin(p->getStart()->getY(), p->getEnd()->getY()) ||
                     intPoint.pt.getY() > fmax(p->getStart()->getY(), p->getEnd()->getY())){
                intPoint.exist = false;
                return intPoint;
            }else{
                intPoint.exist = true;
                return intPoint;
            }
        }else{
            intPoint.exist = false;
            return intPoint;
        }
    }
}


bool CutPolygon::inside(Point *p,  Edge *c){
    double tmpy;
    double cSlope = (c->getStart()->getY() - c->getEnd()->getY()) / (c->getStart()->getX() - c->getEnd()->getX());
    double bc = c->getStart()->getY() - cSlope * c->getStart()->getX();
    if(c->getStart()->getX() != c->getEnd()->getX()){
        tmpy = cSlope * p->getX() + bc;
        if(c->getStart()->getX() < c->getEnd()->getX()){       //point right
            if(tmpy <= p->getY()) return true;
            else return false;
        }else{                  //point left
            if(tmpy < p->getY()) return false;
            else return true;
        }
    }else{
        if(c->getStart()->getY() < c->getEnd()->getY()){       //point up
            if(p->getX() <= c->getStart()->getX()) return true;
            else return false;
        }else{                  //point down
            if(p->getX() < c->getStart()->getX()) return false;
            else return true;
        }
    }
}



/*
裁剪函数
*/
void CutPolygon::clipFunc(std::vector<Point> &output){
    std::vector<Edge> cedges;
    cedges.resize(this->clipShapePts.size());
    std::vector<Point> input;
    input.resize(this->polygonPts.size());

    int cc = clipShapePts.size();
    int pc = polygonPts.size();
    //构造边
    for(int i = 0; i <(int)this->clipShapePts.size(); i++){
        cedges[i].getStart()->setX(this->clipShapePts.at(i%cc)->getX());
        cedges[i].getStart()->setY(this->clipShapePts.at(i%cc)->getY());
        cedges[i].getEnd()->setX(this->clipShapePts.at((i+1)%cc)->getX());
        cedges[i].getEnd()->setY(this->clipShapePts.at((i+1)%cc)->getY());
    }

    //copy the target polygon's info to a new array
    for(int i = 0; i < pc; i ++){
        input[i].setX(this->polygonPts.at(i)->getX());
        input[i].setY(this->polygonPts.at(i)->getY());
    }

    int cnt;
    int loop = pc;
    ExPoint intPoint;
    Edge  tmp;
    for(int i = 0; i < cc; i++){
        cnt = 0;
        //one point may become two, 2*loop just make sure the array won't overflow
        //        for(int  i =0 ; i <int(2*loop - output.size()); i++)
        //            output.push_back(new Point());
        output.resize(2*loop);
        for(int j = 0; j < loop; j ++){
            tmp.getStart()->setX(input[j%loop].getX()) ;
            tmp.getStart()->setY(input[j%loop].getY()) ;
            tmp.getEnd()->setX(input[(j+1)%loop].getX());
            tmp.getEnd()->setY(input[(j+1)%loop].getY());
            intPoint = intersect(&cedges[i], &tmp);
            if(intPoint.exist){
//                std::cout <<"cedges HeadPt  " << cedges[i].getStart()->getX()<<"    "<<cedges[i].getStart()->getY()<<std::endl;
//                std::cout <<"cedges TailPt  " << cedges[i].getEnd()->getX()<<"    "<<cedges[i].getEnd()->getY()<<std::endl;
//                std::cout <<"tmp HeadPt  " << tmp.getStart()->getX()<<"    "<<tmp.getStart()->getY()<<std::endl;
//                std::cout <<"tmp TailPt  " << tmp.getEnd()->getX()<<"    "<<tmp.getEnd()->getY()<<std::endl;
//                printf("x:%f  y:%f\n", intPoint.pt.getX(), intPoint.pt.getY());
//                printf("cnt: %d \n", cnt);

                /*
                check if the start point of current line is inside clip line or not
                */
                if(inside(&input[j%loop], &cedges[i])){
                    //check if the start point is the same as intersecton point or not
                    //if it is, the do the next step
                    if(input[j%loop].getX() == intPoint.pt.getX() &&
                            input[j%loop].getY() == intPoint.pt.getY()){
                        if(inside(&input[(j+1)%loop], &cedges[i])){
                            output[cnt].setX(input[(j+1)%loop].getX());
                            output[cnt].setY(input[(j+1)%loop].getY());
                            cnt ++;
                        }else continue;
                        //if it is not, just continue;
                    }else{
                        output[cnt].setX(intPoint.pt.getX()) ;
                        output[cnt].setY(intPoint.pt.getY());
                        cnt ++;
                    }
                    /*
                the start point is not inside clip line, then do the next steps
                */
                }else{
                    //check if the end point is the same as intersection point or not
                    //if it is, only add intPoint to output list;
                    if(input[(j+1)%loop].getX() == intPoint.pt.getX() &&
                            input[(j+1)%loop].getY() == intPoint.pt.getY()){
                        output[cnt].setX(intPoint.pt.getX());
                        output[cnt].setY(intPoint.pt.getY());
                        cnt ++;
                        //if it is not, add both end point and intPoint to output list
                    }else{
                        output[cnt].setX(intPoint.pt.getX());
                        output[cnt].setY(intPoint.pt.getY());
                        output[cnt+1].setX(input[(j+1)%loop].getX()) ;
                        output[cnt+1].setY(input[(j+1)%loop].getY());
                        cnt += 2;
                    }
                }
                //no insection with clip edge
            }else{
                // one point is inside or both is inside, only add the end point
                // to the outputlist
                if(inside(&input[j%loop], &cedges[i])){
                    output[cnt].setX(input[(j+1)%loop].getX());
                    output[cnt].setY(input[(j+1)%loop].getY());
                    cnt ++;
                    //both outside, then continue
                }else{
                    continue;
                }
            }
        }
        loop = cnt;
        input.clear();
        input = output;
    }
    //删除后面的非必要的点数据
    output.resize(cnt);
}




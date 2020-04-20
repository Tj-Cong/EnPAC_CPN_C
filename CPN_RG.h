//
// Created by hecong on 19-12-10.
//

#ifndef CPN_PNML_PARSE_CPN_RG_H
#define CPN_PNML_PARSE_CPN_RG_H

#include "CPN.h"
#include <cmath>
#include <ctime>
#include <iomanip>
using namespace std;

#define CPNRGTABLE_SIZE 1048576
#define random(x) rand()%(x)

extern NUM_t placecount;
extern NUM_t transitioncount;
extern NUM_t varcount;
extern CPN *cpnet;
extern bool timeflag;
extern bool colorflag;

class CPN_RG;
class CPN_Product;
class CPN_Product_Automata;

class CPN_RGNode
{
public:
    MarkingMeta *marking;
    CPN_RGNode *next;
public:
    int numid;
    CPN_RGNode(){
        numid = 0;
        marking=new MarkingMeta[placecount];
        for(int i=0;i<placecount;++i) {
            marking[i].initiate(cpnet->place[i].tid,cpnet->place[i].sid);
        }
        next=NULL;
    }
    ~CPN_RGNode();
    index_t Hash(SHORTNUM *weight);
    bool isFiringBinding(const COLORID *varvec,const CTransition &tran);
    void printMarking();
    void selfcheck();
    bool operator==(const CPN_RGNode &n1);
    void operator=(const CPN_RGNode &rgnode);
    friend class CPN_RG;
};

class CPN_RG
{
private:
    CPN_RGNode **markingtable;
    CPN_RGNode *initnode;
public:
    NUM_t nodecount;
    SHORTNUM *weight;
    NUM_t hash_conflict_times;
public:
    CPN_RG();
    ~CPN_RG();
    void addRGNode(CPN_RGNode *mark);
    CPN_RGNode *CPNRGinitialnode();
    bool NodeExist(CPN_RGNode *mark,CPN_RGNode *&existmark);
    friend class CPN_Product_Automata;
    friend class CPN_Product;
};
#endif //CPN_PNML_PARSE_CPN_RG_H

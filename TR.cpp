#include "TR.h"
#include <cmath>

int MINSEP = 7;

BTNode::BTNode(int info, BTNode *father) : m_info(info), left(nullptr), right(nullptr), x(-1), y(-1), offset(0), thread(false), parent(father), status(0) { }

void BTNode::changeInfo(int info) { m_info = info; }
int BTNode::getInfo() const { return m_info; }

void BTNode::setLeft(BTNode *l) { left = l; }
BTNode *BTNode::getLeft() const { return left; }

void BTNode::setRight(BTNode *r) { right = r; }
BTNode *BTNode::getRight() const { return right; }

void BTNode::setX(int x) { this->x = x; }
int BTNode::getX() const { return x; }

void BTNode::setY(int y) { this->y = y; }
int BTNode::getY() const { return y; }

bool BTNode::isThread() const { return thread; }
void BTNode::setThread(bool val) { thread = val; }

void BTNode::setOffset(int val) { offset = val; }
int BTNode::getOffset() const { return offset; }

void BTNode::setParent(BTNode *father) { this->parent = father; }
BTNode *BTNode::getParent() const {return this->parent; }

int BTNode::getStatus() const { return this->status; }
void BTNode::setStatus(int stat) {this->status = stat; }

int BTNode::getModifier() const {return this->offset; }
void BTNode::setModifier(int modf) {this->offset = modf;}



BTNode::~BTNode() {
    if(left != nullptr)
        left->~BTNode();
    if(right != nullptr)
        right->~BTNode();
}


/**
The TR tree drawing algorithm
*/
void TRSetup(BTNode *root, int level, struct Extreme *rMost, struct Extreme *lMost, int stepY) {
    BTNode *l, *r;
    struct Extreme ll, lr, rl, rr;

    int currSep, rootSep, lOffSum, rOffSum;
    if(root == nullptr) {
        rMost->lev = -1;
        lMost->lev = -1;
    }
    else {
        root->setY(level);
        l = root->getLeft();
        r = root->getRight();
        TRSetup(l, level+1, &lr, &ll, stepY);
        TRSetup(r, level+1, &rr, &rl, stepY);
        if(r == nullptr && l == nullptr) {
            rMost->addr = root;
            lMost->addr = root;
            rMost->lev = level;
            lMost->lev = level;
            rMost->off = 0;
            lMost->off = 0;
            root->setOffset(0);
        }
        else {
            currSep = MINSEP;
            rootSep = MINSEP;
            lOffSum = 0;
            rOffSum = 0;

            while(l != nullptr && r != nullptr) {
                if(currSep < MINSEP) {
                    rootSep += MINSEP - currSep;
                    currSep = MINSEP;
                }
                if(l->getRight() != nullptr) {
                    lOffSum += l->getOffset();
                    currSep -= l->getOffset();
                    l = l->getRight();
                }
                else {
                    lOffSum -= l->getOffset();
                    currSep += l->getOffset();
                    l = l->getLeft();
                }

                if(r->getLeft() != nullptr) {
                    rOffSum -= r->getOffset();
                    currSep -= r->getOffset();
                    r = r->getLeft();
                }
                else {
                    rOffSum += r->getOffset();
                    currSep += r->getOffset();
                    r = r->getRight();
                }
            } // while ends
            root->setOffset((rootSep + 1)/2);
            lOffSum -= root->getOffset();
            rOffSum += root->getOffset();

            if(rl.lev > ll.lev || root->getLeft() == nullptr) {
                lMost->addr = rl.addr;
                lMost->lev = rl.lev;
                lMost->off = rl.off;
                lMost->off += root->getOffset();
            }
            else {
                lMost->addr = ll.addr;
                lMost->lev = ll.lev;
                lMost->off = ll.off;
                lMost->off -= root->getOffset();
            }
            if(lr.lev > rr.lev || root->getRight() == nullptr) {
                rMost->addr = lr.addr;
                rMost->lev = lr.lev;
                rMost->off = lr.off;
                rMost->off -= root->getOffset();
            }
            else {
                rMost->addr = rr.addr;
                rMost->lev = rr.lev;
                rMost->off = rr.off;
                rMost->off += root->getOffset();
            }

            if (l != nullptr && l != root->getLeft()) {
                rr.addr->setThread(true);
                rr.addr->setOffset(abs((rr.off + root->getOffset()) - lOffSum));
                if((lOffSum - root->getOffset()) <= rr.off) {
                    rr.addr->setLeft(l);
                }
                else {
                    rr.addr->setRight(l);
                }
            }
            else if(r != nullptr && r != root->getRight()) {
                ll.addr->setThread(true);
                ll.addr->setOffset(abs((ll.off - root->getOffset()) - rOffSum));
                if((rOffSum + root->getOffset()) >= ll.off) {
                    ll.addr->setRight(r);
                }
                else {
                    ll.addr->setLeft(r);
                }
            }
        }
    }
}

/**
Assigns to the nodes their the absolute x coordinates
*/
void TRPetrify(BTNode *root, int xPos) {
    if(root != nullptr){
        root->setX(xPos);
        if(root->isThread()) {
            root->setThread(false);
            root->setLeft(nullptr);
            root->setRight(nullptr);
        }
        TRPetrify(root->getLeft(), xPos - root->getOffset());
        TRPetrify(root->getRight(), xPos + root->getOffset());
    }
}

void TRPlotTree(BTNode *root, int minsep) {
    MINSEP = minsep;
    struct Extreme rm, lm;
    TRSetup(root, 0, &rm, &lm, minsep);
    TRPetrify(root, 0);

}

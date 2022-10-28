#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<float.h>
#include<stdbool.h>

// points

struct point {
    float x;
    float y;
};

typedef struct point point;

point* newpoint(float x,float y){
    // creates a new point
    point* p = malloc(sizeof(point));
    p->x = x;
    p->y = y;
    return p;
}

// chech if two points are equal

int equal(point* p1,point* p2){
    // checks if two points are equal
    return (p1->x == p2->x && p1->y == p2->y);
}

// region 
// we are moving in clock wise direction always for region


struct region {
    point* p1; // top left
    point* p2; // top right
    point* p3; // bottom right
    point* p4;  // bottom left
};

typedef struct region region;

region* newregion(point* p1,point* p2,point* p3,point* p4){
    region* r = malloc(sizeof(region));
    r->p1 = p1;
    r->p2 = p2;
    r->p3 = p3;
    r->p4 = p4;
    return r;
}

//find if point in region or not

int ispointinregion(point* p,region* r){
    if(p->x >= r->p1->x && p->x <= r->p2->x && p->y >= r->p1->y && p->y <= r->p4->y){
        return 1;
    }
    return 0;
}

// find which region point is in

int findregion(point*p, region* r){
    // 1 for top left N/W
    // 2 for top right N/E
    // 3 for bottom right S/E
    // 4 for bottom left S/W

    float xmid = (r->p1->x + r->p2->x)/2;
    float ymid = (r->p1->y + r->p4->y)/2;
    if(p->x <= xmid && p->y <= ymid){
        return 1;
    }
    else if(p->x >= xmid && p->y <= ymid){
        return 2;
    }
    else if(p->x >= xmid && p->y >= ymid){
        return 3;
    }
    else if(p->x <= xmid && p->y >= ymid){
        return 4;
    }
    return 0;
}

bool box_intersect_check(region* b1,region* b2)
{
    if(b1->p2->x > b2->p1->x && b1->p2->x < b2->p2->x)
    {
        if(b1->p3->y < b2->p1->y && b1->p3->y > b2->p3->y)
            return true;
        else if(b1->p1->y < b2->p1->y && b1->p1->y > b2->p3->y)
            return true;
    }
    else if(b1->p1->x < b2->p2->x && b1->p1->x > b2->p1->x)
    {
        if(b1->p1->y < b2->p1->y && b1->p1->y > b2->p3->y)
            return true;
        else if(b1->p3->y < b2->p1->y && b1->p3->y > b2->p3->y)
            return true;
    }
    return false;
}

// quad tree

struct quadtree{
    region* r;
    point* p;
    struct quadtree* nw;
    struct quadtree* ne;
    struct quadtree* se;
    struct quadtree* sw;
};

typedef struct quadtree quadtree;

// new quad tree 

quadtree* newquadtree(point* p1,point* p2,point* p3,point* p4){
    // creates an empty quad tree whose region top left point is p1 and bottom right point is p3
    quadtree* qt = malloc(sizeof(quadtree));
    qt->p = NULL;
    qt->nw = NULL;
    qt->ne = NULL;
    qt->se = NULL;
    qt->sw = NULL;
    qt->r = newregion(p1,p2,p3,p4);
}

// insert in quad tree

void insertquadtree(quadtree* qt,point* p){
    if (qt == NULL){
        ;
    }
    else if (ispointinregion(p,qt->r)){
        if (qt->p == NULL){
            // base case for recursion
            // if there is no point then we insert the point in the tree
            //by creating new quad trees as its children.
            qt->p = p;
            point* tophalf = newpoint((qt->r->p1->x + qt->r->p2->x)/2,qt->r->p1->y);
            point* bottomhalf = newpoint((qt->r->p1->x + qt->r->p2->x)/2,qt->r->p4->y);
            point* lefthalf = newpoint(qt->r->p1->x,(qt->r->p1->y + qt->r->p4->y)/2);
            point* righthalf = newpoint(qt->r->p2->x,(qt->r->p1->y + qt->r->p4->y)/2);
            point* center = newpoint((qt->r->p1->x + qt->r->p2->x)/2,(qt->r->p1->y + qt->r->p4->y)/2);
            qt->nw= newquadtree(qt->r->p1,tophalf,center,lefthalf);
            qt->ne= newquadtree(tophalf,qt->r->p2,righthalf,center);
            qt->se= newquadtree(center,righthalf,qt->r->p3,bottomhalf);
            qt->sw= newquadtree(lefthalf,center,bottomhalf,qt->r->p4);
        }
        else {
            // if there is a point in the tree then we insert the point in the appropriate child
            if (ispointinregion(p,qt->nw->r)){
                insertquadtree(qt->nw,p);
            }
            else if (ispointinregion(p,qt->ne->r)){
                insertquadtree(qt->ne,p);
            }
            else if (ispointinregion(p,qt->se->r)){
                insertquadtree(qt->se,p);
            }
            else if (ispointinregion(p,qt->sw->r)){
                insertquadtree(qt->sw,p);
            }
        }
    }
    else {
        printf("point not in region");
    }
}

// searching in quad tree

int searchquadtree(quadtree* qt,point* p){
    if (qt->p == NULL){
        // base case for recursion
        return 0;
    }
    else{
        if (equal(qt->p,p)){
            // also base case for recursion
            return 1; // the point is found
        }
        else {
            int region = findregion(p,qt->r);
            if (region == 1){
                return searchquadtree(qt->nw,p);
            }
            else if (region == 2){
                return searchquadtree(qt->ne,p);
            }
            else if (region == 3){
                return searchquadtree(qt->se,p);
            }
            else if (region == 4){
                return searchquadtree(qt->sw,p);
            }
        }

    }
}

void range_query(quadtree* qt,region* r)
{
    if(!box_intersect_check(qt->r,r))
    {
        return;
    }
    if(ispointinregion(qt->p, r)==1)
        printf("%d ",qt->p);
    range_query(qt->nw,r);
    range_query(qt->ne,r);
    range_query(qt->se,r);
    range_query(qt->sw,r);
}

int main(){
    // code by Jignesh Test passed
    point* p1 = newpoint(0,0);
    point* p2 = newpoint(32,0);
    point* p3 = newpoint(32,32);
    point* p4 = newpoint(0,32);
    quadtree* qt = newquadtree(p1,p2,p3,p4);
    point* p = newpoint(5,5);
    printf("%f\n",p->x);
    point* a = newpoint(16,16);
    insertquadtree(qt,p);
    insertquadtree(qt,a);
    printf("%d",searchquadtree(qt,a));

    // code check by kritika 
    

    return 0;
}

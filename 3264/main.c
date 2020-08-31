#include <stdio.h>

#define MAX (50000+5L)

struct node{
    int from ,to;
    long height;
};

long cows[MAX];
struct node hi[MAX*4], lo[MAX*4];
int build_tree(struct node *tree, long *cows, long idx, int from, int to, int hol);
long find_selection(struct node *tree, long idx, int from, int to, int hol);

int main(void){
    long nc,nm;
    printf("INPUT:\n");
    scanf("%ld %ld",&nc,&nm);
    for(long i = 0; i < nc; i++) scanf("%ld",cows+i);
    build_tree(hi, cows, 0, 1, (int)nc, 0);
    build_tree(lo, cows, 0, 1, (int)nc, 1);
    for(long i = 0; i < nm; i++){
        int idxa, idxb;
        scanf("%d %d",&idxa,&idxb);
        long hh = find_selection(hi, 0, idxa, idxb, 0);
        long lh = find_selection(lo, 0, idxa, idxb, 1);
        printf("%ld\n",hh-lh);
    }
    
    return 0;
}

int build_tree(struct node *tree, long *cows, long idx, int from, int to, int hol){
    int h_idx = (from + to)/2;
    tree[idx].from = from;
    tree[idx].to = to;
    if(from < to){
        build_tree(tree, cows, idx*2+1, from, h_idx, hol);
        build_tree(tree, cows, idx*2+2, h_idx+1, to, hol);
        long l = tree[idx*2+1].height, r = tree[idx*2+2].height;
        if(hol == 0) tree[idx].height = r>l?r:l;
        else tree[idx].height = r>l?l:r;
    }
    else{
        tree[idx].height = cows[from-1];
    }
    
    return 0;
}

long find_selection(struct node *tree, long idx, int from, int to, int hol){
    int h_idx = (tree[idx].from + tree[idx].to)/2;
    if(from == tree[idx].from && to == tree[idx].to) return tree[idx].height;
    if(from <= h_idx && to > h_idx){
        long l = find_selection(tree, idx*2+1, from, h_idx, hol), r = find_selection(tree, idx*2+2, h_idx+1, to, hol);
        if(hol == 0) return r>l?r:l;
        else return r>l?l:r;
    }
    else if(from <= h_idx && to <= h_idx){
        return find_selection(tree, idx*2+1, from, to, hol);
    }
    else if (from > h_idx && to > h_idx){
        return find_selection(tree, idx*2+2, from, to, hol);
    }
    return 0;
}

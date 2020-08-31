#include <stdio.h>

#define MAX 200005

struct node {
    long from, to;
    int value;
};

long peo[MAX],num[MAX],line[MAX];
struct node tree[4*MAX];

int build_tree(struct node *tree, long idx, long from, long to);
long find_section(struct node *tree, long idx, long spn);
int upd_tree(struct node *tree, long idx, long tidx);

int main(void){
    int n;
    
    while(scanf("%d",&n) != EOF){
        build_tree(tree, 0, 1, n);
        for(int i = 0; i < n; i++){
            scanf("%ld %ld",peo+i, num+i);
        }
        for(int i = n-1; ~i; i--){
            long idx = find_section(tree, 0, peo[i]);
            line[idx-1] = num[i];
            upd_tree(tree, 0, idx);
        }
        for(int i = 0; i < n; i++){
            if(i) printf(" ");
            printf("%ld",line[i]);
        }
        printf("\n");
    }
    return 0;
}

int build_tree(struct node *tree, long idx, long from, long to){
    long h_idx = (from + to)/2;
    tree[idx].from = from;
    tree[idx].to = to;
    tree[idx].value = 0;
    if(from < to){
        build_tree(tree, idx*2+1, from, h_idx);
        build_tree(tree, idx*2+2, h_idx+1, to);
        tree[idx].value = tree[idx*2+1].value + tree[idx*2+2].value;
    }
    else{
        tree[idx].value = 1;
    }
    return 0;
}

long find_section(struct node *tree, long idx, long spn){
    if(tree[idx].from == tree[idx].to){
        return tree[idx].from;
    }
    if(tree[idx*2+1].value <= spn){
        return find_section(tree, idx*2+2, spn-tree[idx*2+1].value);
    }
    else{
        return find_section(tree, idx*2+1, spn);
    }
}

int upd_tree(struct node *tree, long idx, long tidx){
    long h_idx = (tree[idx].from + tree[idx].to)/2;
    tree[idx].value--;
    if(tree[idx].from < tree[idx].to){
        if(tidx <= h_idx) upd_tree(tree, idx*2+1, tidx);
        else upd_tree(tree, idx*2+2, tidx);
    }
    return 0;
}

#include <stdio.h>

#define MAX 8005

struct node {
    int from, to;
    int value;
};

int cows[MAX];
struct node tree[4*MAX];

int build_tree(struct node *tree, long idx, int from, int to);
int find_section(struct node *tree, long idx, int spn);
int upd_tree(struct node *tree, long idx, int tidx);

int main(void){
    int n;
    scanf("%d",&n);
    build_tree(tree, 0, 1, n);
    cows[0] = 0;
    for(int i = 1; i < n; i++){
        scanf("%d",cows+i);
    }
    for(int i = n-1; ~i; i--){
        int idx = find_section(tree, 0, cows[i]);
        cows[i] = idx;
        upd_tree(tree, 0, idx);
    }
    for(int i = 0; i < n; i++) printf("%d\n",cows[i]);
    return 0;
}

int build_tree(struct node *tree, long idx, int from, int to){
    int h_idx = (from + to)/2;
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

int find_section(struct node *tree, long idx, int spn){
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

int upd_tree(struct node *tree, long idx, int tidx){
    int h_idx = (tree[idx].from + tree[idx].to)/2;
    tree[idx].value--;
    if(tree[idx].from < tree[idx].to){
        if(tidx <= h_idx) upd_tree(tree, idx*2+1, tidx);
        else upd_tree(tree, idx*2+2, tidx);
    }
    return 0;
}

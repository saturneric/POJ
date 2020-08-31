#include<stdio.h>

#define MAX (15000+5L)

struct node{
    int from, to;
    int n;
};


int rank[MAX];
struct node tree[32000*4L];

int build_tree(struct node *tree, long idx, int from , int to);
int upd_tree(struct node *tree, long idx, int p_idx);
int find_section(struct node *tree, long idx, int from, int to);

int main(void){
    int number, i;
    build_tree(tree, 0, 0, 32000);
    scanf("%d",&number);
    for(i = 0; i < number; i++){
        int x,y;
        scanf("%d %d",&x,&y);
        rank[find_section(tree, 0, 0, x)]++;
        upd_tree(tree, 0, x);
    }
    for(i = 0; i < number; i++){
        printf("%d\n",rank[i]);
    }
    return 0;
}

int build_tree(struct node *tree, long idx, int from , int to){
    int h_idx = (from+to)/2;
    tree[idx].from = from;
    tree[idx].to = to;
    tree[idx].n = 0;
    if(from < to){
        build_tree(tree, idx*2+1, from, h_idx);
        build_tree(tree, idx*2+2, h_idx+1, to);
    }
    return 0;
}

int upd_tree(struct node *tree, long idx, int p_idx){
    int h_idx = (tree[idx].from + tree[idx].to)/2;
    tree[idx].n++;
    if(tree[idx].from < tree[idx].to){
        if(p_idx <= h_idx) upd_tree(tree, idx*2+1, p_idx);
        else upd_tree(tree, idx*2+2, p_idx);
    }
    return 0;
}

int find_section(struct node *tree, long idx, int from, int to){
    int h_idx = (tree[idx].from + tree[idx].to)/2, sum = 0;
    if(tree[idx].from == from && tree[idx].to == to) return tree[idx].n;
    if(from <= h_idx && to > h_idx)
        sum = find_section(tree, idx*2+1, from, h_idx) + find_section(tree, idx*2+2, h_idx+1, to);
    else if(from <= h_idx && to <= h_idx)
        sum = find_section(tree, idx*2+1, from , to);
    else if(from > h_idx && to > h_idx)
        sum = find_section(tree, idx*2+2, from , to);
    else printf("IMP!\n");
    return sum;
}
